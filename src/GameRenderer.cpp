#include "GameRenderer.h"
#include <QPainter>
#include <QDebug>
#include <QThread>
#include "Engine/Screen.h"
#include <QDebug>
#include <QMouseEvent>
#include "Engine/Options.h"

// #include <windows.h>
// #include <dinput.h>

SDLKey convertScanCodeToSDLKey(quint32 scanCode)
{
	scanCode &= 0x7F;

	switch (scanCode) {
	case 0x10: return SDLK_q;  // Q
	case 0x11: return SDLK_w;  // W
	case 0x12: return SDLK_e;  // E
	case 0x13: return SDLK_r;  // R
	case 0x14: return SDLK_t;  // T
	case 0x15: return SDLK_y;  // Y
	case 0x16: return SDLK_u;  // U
	case 0x17: return SDLK_i;  // I
	case 0x18: return SDLK_o;  // O
	case 0x19: return SDLK_p;  // P
	case 0x1A: return SDLK_LEFTBRACKET;  // [
	case 0x1B: return SDLK_RIGHTBRACKET; // ]
	case 0x1C: return SDLK_RETURN;       // Enter

	case 0x1E: return SDLK_a;  // A
	case 0x1F: return SDLK_s;  // S
	case 0x20: return SDLK_d;  // D
	case 0x21: return SDLK_f;  // F
	case 0x22: return SDLK_g;  // G
	case 0x23: return SDLK_h;  // H
	case 0x24: return SDLK_j;  // J
	case 0x25: return SDLK_k;  // K
	case 0x26: return SDLK_l;  // L
	case 0x27: return SDLK_SEMICOLON;  // ;
	case 0x28: return SDLK_QUOTE;       // '
	case 0x29: return SDLK_BACKQUOTE;   // `

	case 0x2B: return SDLK_BACKSLASH;
	case 0x2C: return SDLK_z;  // Z
	case 0x2D: return SDLK_x;  // X
	case 0x2E: return SDLK_c;  // C
	case 0x2F: return SDLK_v;  // V
	case 0x30: return SDLK_b;  // B
	case 0x31: return SDLK_n;  // N
	case 0x32: return SDLK_m;  // M
	case 0x33: return SDLK_COMMA;   // ,
	case 0x34: return SDLK_PERIOD;  // .
	case 0x35: return SDLK_SLASH;   // /

	case 0x02: return SDLK_1;
	case 0x03: return SDLK_2;
	case 0x04: return SDLK_3;
	case 0x05: return SDLK_4;
	case 0x06: return SDLK_5;
	case 0x07: return SDLK_6;
	case 0x08: return SDLK_7;
	case 0x09: return SDLK_8;
	case 0x0A: return SDLK_9;
	case 0x0B: return SDLK_0;

	case 0x01: return SDLK_ESCAPE;
	case 0x0C: return SDLK_MINUS;     // -
	case 0x0D: return SDLK_EQUALS;    // =
	case 0x0E: return SDLK_BACKSPACE;
	case 0x0F: return SDLK_TAB;
	case 0x1D: return SDLK_LCTRL;     // Left Ctrl
	case 0x2A: return SDLK_LSHIFT;    // Left Shift
	case 0x36: return SDLK_RSHIFT;    // Right Shift
	case 0x38: return SDLK_LALT;       // Left Alt
	case 0x39: return SDLK_SPACE;
	case 0x3A: return SDLK_CAPSLOCK;
	case 0x3B: return SDLK_F1;
	case 0x3C: return SDLK_F2;
	case 0x3D: return SDLK_F3;
	case 0x3E: return SDLK_F4;
	case 0x3F: return SDLK_F5;
	case 0x40: return SDLK_F6;
	case 0x41: return SDLK_F7;
	case 0x42: return SDLK_F8;
	case 0x43: return SDLK_F9;
	case 0x44: return SDLK_F10;
	case 0x45: return SDLK_NUMLOCK;
	case 0x46: return SDLK_SCROLLOCK;
	case 0x47: return SDLK_HOME;
	case 0x48: return SDLK_UP;
	case 0x49: return SDLK_PAGEUP;
	case 0x4A: return SDLK_KP_MINUS;
	case 0x4B: return SDLK_LEFT;
	case 0x4C: return SDLK_KP5;
	case 0x4D: return SDLK_RIGHT;
	case 0x4E: return SDLK_KP_PLUS;
	case 0x4F: return SDLK_END;
	case 0x50: return SDLK_DOWN;
	case 0x51: return SDLK_PAGEDOWN;
	case 0x52: return SDLK_INSERT;
	case 0x53: return SDLK_DELETE;
	case 0x54: return SDLK_SYSREQ;    // Print Screen
	case 0x57: return SDLK_F11;
	case 0x58: return SDLK_F12;

	default: return SDLK_UNKNOWN;
	}
}

namespace OpenXcom
{
	SDLMod convertQtModifiers(Qt::KeyboardModifiers qtMods)
	{
		SDLMod sdlMods = KMOD_NONE;

		if (qtMods & Qt::ShiftModifier) {
			sdlMods = (SDLMod)(sdlMods | KMOD_SHIFT);
		}
		if (qtMods & Qt::ControlModifier) {
			sdlMods = (SDLMod)(sdlMods | KMOD_CTRL);
		}
		if (qtMods & Qt::AltModifier) {
			sdlMods = (SDLMod)(sdlMods | KMOD_ALT);
		}
		if (qtMods & Qt::MetaModifier) {
			sdlMods = (SDLMod)(sdlMods | KMOD_META);
		}
		if (qtMods & Qt::KeypadModifier) {
			sdlMods = (SDLMod)(sdlMods | KMOD_NUM);
		}
		if (qtMods & Qt::GroupSwitchModifier) {
			sdlMods = (SDLMod)(sdlMods | KMOD_MODE);
		}

		return sdlMods;
	}

	SDLKey getPhysicalKey(QKeyEvent* event) {
		return convertScanCodeToSDLKey(event->nativeScanCode());
	}


	GameRenderer::GameRenderer(QQuickItem *parent):
		QQuickPaintedItem(parent)
	{
		setAcceptHoverEvents(true);
		setAcceptedMouseButtons(Qt::AllButtons);
		setFocus(true);
		setFlag(QQuickItem::ItemAcceptsInputMethod, true);

		initSDL();
		startTimer(10);
	}

	void GameRenderer::mousePressEvent(QMouseEvent *event)
	{
		QPoint pos = event->pos();
		Uint8 button = convertMouseButton(event->button());

		if (button > 0) {
			int idx = button - 1;
			if (idx < 3) _mousePressed[idx] = true;
			pushSDLEvent(SDL_MOUSEBUTTONDOWN, pos.x(), pos.y(), button);
		}
		event->accept();
	}

	void GameRenderer::mouseMoveEvent(QMouseEvent *event)
	{
		QPoint pos = event->pos();
		pushSDLEvent(SDL_MOUSEMOTION, pos.x(), pos.y());
		event->accept();
	}

	void GameRenderer::hoverMoveEvent(QHoverEvent *event)
	{
		QPoint pos = event->position().toPoint();
		pushSDLEvent(SDL_MOUSEMOTION, pos.x(), pos.y());
		QQuickPaintedItem::hoverMoveEvent(event);
	}

	void GameRenderer::mouseReleaseEvent(QMouseEvent *event)
	{
		QPoint pos = event->pos();
		Uint8 button = convertMouseButton(event->button());

		if (button > 0) {
			int idx = button - 1;
			if (idx < 3) _mousePressed[idx] = false;
			pushSDLEvent(SDL_MOUSEBUTTONUP, pos.x(), pos.y(), button);
		}
		event->accept();
	}

	void GameRenderer::keyPressEvent(QKeyEvent *event)
	{
		SDL_Event e;
		e.type = SDL_KEYDOWN;
		e.key.keysym.sym = getPhysicalKey(event);
		e.key.keysym.mod = convertQtModifiers(event->modifiers());
		SDL_PushEvent(&e);
		event->accept();
	}

	void GameRenderer::keyReleaseEvent(QKeyEvent *event)
	{
		SDL_Event e;
		e.type = SDL_KEYUP;
		e.key.keysym.sym = getPhysicalKey(event);
		e.key.keysym.mod = convertQtModifiers(event->modifiers());
		SDL_PushEvent(&e);
		event->accept();
	}

	void GameRenderer::timerEvent(QTimerEvent *)
	{
		game.run();
		{
			static QVector<QRgb> colorTable(256);
			SDL_Surface* screen = game._screen->getSurface();
			SDL_LockSurface(screen);
			QImage image(
				(const uchar*)screen->pixels,
				screen->w,
				screen->h,
				screen->pitch,
				screen->format->BitsPerPixel == 32 ?
					QImage::Format_ARGB32 : QImage::Format_Indexed8
				);

			if (screen->format->BitsPerPixel == 8) {

				SDL_Palette* pal = screen->format->palette;
				for (int i = 0; i < pal->ncolors; i++) {
					colorTable[i] = qRgb(pal->colors[i].r,
										 pal->colors[i].g,
										 pal->colors[i].b);
				}
				image.setColorTable(colorTable);
			}

			game.mutex.lock();
			game.gameImage = image.convertToFormat(QImage::Format_RGBA8888);
			game.mutex.unlock();
			SDL_UnlockSurface(screen);
		}
		update();
	}

	void GameRenderer::paint(QPainter *painter)
	{
		game.mutex.lock();
		QImage scaled = game.gameImage.scaled(size().toSize(), Qt::KeepAspectRatio);
		game.mutex.unlock();

		int x = (width() - scaled.width()) / 2;
		int y = (height() - scaled.height()) / 2;
		painter->drawImage(x, y, scaled);
	}

	void GameRenderer::pushSDLEvent(Uint32 type, int x, int y, Uint8 button)
	{
		memset(&_sdlEvent, 0, sizeof(_sdlEvent));
		_sdlEvent.type = type;

		switch (type) {
		case SDL_MOUSEMOTION:
			_sdlEvent.motion.x = x;
			_sdlEvent.motion.y = y;
			_sdlEvent.motion.xrel = x - _lastMousePos.x();
			_sdlEvent.motion.yrel = y - _lastMousePos.y();
			_sdlEvent.motion.state = getMouseState();
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			_sdlEvent.button.x = x;
			_sdlEvent.button.y = y;
			_sdlEvent.button.button = button;
			_sdlEvent.button.state = (type == SDL_MOUSEBUTTONDOWN) ?
										 SDL_PRESSED : SDL_RELEASED;
			break;
		}

		SDL_PushEvent(&_sdlEvent);
		_lastMousePos = QPoint(x, y);
	}

	Uint8 GameRenderer::getMouseState()
	{
		Uint8 state = 0;
		if (_mousePressed[0]) state |= SDL_BUTTON_LMASK;
		if (_mousePressed[1]) state |= SDL_BUTTON_RMASK;
		if (_mousePressed[2]) state |= SDL_BUTTON_MMASK;
		return state;
	}

	Uint8 GameRenderer::convertMouseButton(Qt::MouseButton button)
	{
		switch (button) {
		case Qt::LeftButton: return SDL_BUTTON_LEFT;
		case Qt::RightButton: return SDL_BUTTON_RIGHT;
		case Qt::MiddleButton: return SDL_BUTTON_MIDDLE;
		default: return 0;
		}
	}

	void GameRenderer::initSDL()
	{
		SDL_EnableUNICODE(1);

		if (options1.captureMouse())
		{
			SDL_WM_GrabInput(SDL_GRAB_ON);
		}
	}

	void GameRenderer::focusInEvent(QFocusEvent *event)
	{
		QQuickPaintedItem::focusInEvent(event);
		SDL_Event e;
		e.type = SDL_ACTIVEEVENT;
		e.active.gain = 1;
		e.active.state = SDL_APPINPUTFOCUS;
		SDL_PushEvent(&e);
	}

	void GameRenderer::focusOutEvent(QFocusEvent *event)
	{
		QQuickPaintedItem::focusOutEvent(event);
		SDL_Event e;
		e.type = SDL_ACTIVEEVENT;
		e.active.gain = 0;
		e.active.state = SDL_APPINPUTFOCUS;
		SDL_PushEvent(&e);
	}
}
