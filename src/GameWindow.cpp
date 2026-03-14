#include "GameWindow.h"
#include "Engine/Screen.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#ifdef Q_OS_WIN
#include <windows.h>
#include <dinput.h> // Для DirectInput скан-кодов
#endif

#ifdef Q_OS_WIN
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
#endif
#ifdef Q_OS_LINUX
#include <X11/keysym.h>
#include <X11/X.h>

SDLKey convertLinuxKeyToSDLKey(quint32 nativeKey) {
	switch (nativeKey) {
	case XK_q: return SDLK_q;
	case XK_w: return SDLK_w;
	case XK_e: return SDLK_e;
	case XK_r: return SDLK_r;
	case XK_t: return SDLK_t;
	case XK_y: return SDLK_y;
	case XK_u: return SDLK_u;
	case XK_i: return SDLK_i;
	case XK_o: return SDLK_o;
	case XK_p: return SDLK_p;
	case XK_a: return SDLK_a;
	case XK_s: return SDLK_s;
	case XK_d: return SDLK_d;
	case XK_f: return SDLK_f;
	case XK_g: return SDLK_g;
	case XK_h: return SDLK_h;
	case XK_j: return SDLK_j;
	case XK_k: return SDLK_k;
	case XK_l: return SDLK_l;
	case XK_z: return SDLK_z;
	case XK_x: return SDLK_x;
	case XK_c: return SDLK_c;
	case XK_v: return SDLK_v;
	case XK_b: return SDLK_b;
	case XK_n: return SDLK_n;
	case XK_m: return SDLK_m;

	case XK_Cyrillic_a: return SDLK_f;
	case XK_Cyrillic_be: return SDLK_comma;

	case XK_0: return SDLK_0;
	case XK_1: return SDLK_1;
	case XK_2: return SDLK_2;
	case XK_3: return SDLK_3;
	case XK_4: return SDLK_4;
	case XK_5: return SDLK_5;
	case XK_6: return SDLK_6;
	case XK_7: return SDLK_7;
	case XK_8: return SDLK_8;
	case XK_9: return SDLK_9;

	case XK_Escape: return SDLK_ESCAPE;
	case XK_Return: return SDLK_RETURN;
	case XK_Tab: return SDLK_TAB;
	case XK_BackSpace: return SDLK_BACKSPACE;
	case XK_space: return SDLK_SPACE;
	case XK_Up: return SDLK_UP;
	case XK_Down: return SDLK_DOWN;
	case XK_Left: return SDLK_LEFT;
	case XK_Right: return SDLK_RIGHT;
	case XK_Home: return SDLK_HOME;
	case XK_End: return SDLK_END;
	case XK_Page_Up: return SDLK_PAGEUP;
	case XK_Page_Down: return SDLK_PAGEDOWN;
	case XK_Insert: return SDLK_INSERT;
	case XK_Delete: return SDLK_DELETE;

	case XK_F1: return SDLK_F1;
	case XK_F2: return SDLK_F2;
	case XK_F3: return SDLK_F3;
	case XK_F4: return SDLK_F4;
	case XK_F5: return SDLK_F5;
	case XK_F6: return SDLK_F6;
	case XK_F7: return SDLK_F7;
	case XK_F8: return SDLK_F8;
	case XK_F9: return SDLK_F9;
	case XK_F10: return SDLK_F10;
	case XK_F11: return SDLK_F11;
	case XK_F12: return SDLK_F12;

	case XK_Control_L: return SDLK_LCTRL;
	case XK_Control_R: return SDLK_RCTRL;
	case XK_Shift_L: return SDLK_LSHIFT;
	case XK_Shift_R: return SDLK_RSHIFT;
	case XK_Alt_L: return SDLK_LALT;
	case XK_Alt_R: return SDLK_RALT;
	case XK_Meta_L: return SDLK_LMETA;
	case XK_Meta_R: return SDLK_RMETA;
	case XK_Super_L: return SDLK_LSUPER;
	case XK_Super_R: return SDLK_RSUPER;

	default: return SDLK_UNKNOWN;
	}
}
#endif

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
			// Аналог KMOD_MODE в некоторых системах
			sdlMods = (SDLMod)(sdlMods | KMOD_MODE);
		}

		return sdlMods;
	}

	SDLKey getPhysicalKey(QKeyEvent* event) {
#ifdef Q_OS_WIN
		quint32 nativeScanCode = event->nativeScanCode();
		return convertScanCodeToSDLKey(nativeScanCode);
#elif defined(Q_OS_LINUX)
		quint32 nativeKey = event->nativeVirtualKey();
		return convertLinuxKeyToSDLKey(nativeKey);
#else
		// Fallback
		return convertQtKey(event->key());
#endif
	}

	GameWindow::GameWindow(QWidget* parent)
		: QWidget{parent},
		m_Game(this)
	{
		setMouseTracking(true);
		startTimer(10);
	}

	void GameWindow::pushSDLEvent(Uint32 type, int x, int y, Uint8 button)
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

	Uint8 GameWindow::convertMouseButton(Qt::MouseButton button)
	{
		switch (button) {
		case Qt::LeftButton: return SDL_BUTTON_LEFT;
		case Qt::RightButton: return SDL_BUTTON_RIGHT;
		case Qt::MiddleButton: return SDL_BUTTON_MIDDLE;
		default: return 0;
		}
	}

	Uint8 GameWindow::getMouseState()
	{
		Uint8 state = 0;
		if (_mousePressed[0]) state |= SDL_BUTTON_LMASK;
		if (_mousePressed[1]) state |= SDL_BUTTON_RMASK;
		if (_mousePressed[2]) state |= SDL_BUTTON_MMASK;
		return state;
	}
	void GameWindow::mousePressEvent(QMouseEvent *event)
	{
		QPoint pos = event->pos();
		Uint8 button = convertMouseButton(event->button());

		if (button > 0) {
			int idx = button - 1;
			if (idx < 3) _mousePressed[idx] = true;
			pushSDLEvent(SDL_MOUSEBUTTONDOWN, pos.x(), pos.y(), button);
		}
		QWidget::mousePressEvent(event);
	}

	void GameWindow::mouseMoveEvent(QMouseEvent *event)
	{
		QPoint pos = event->pos();
		pushSDLEvent(SDL_MOUSEMOTION, pos.x(), pos.y());
		QWidget::mouseMoveEvent(event);
	}

	void GameWindow::mouseReleaseEvent(QMouseEvent *event)
	{
		QPoint pos = event->pos();
		Uint8 button = convertMouseButton(event->button());

		if (button > 0) {
			int idx = button - 1;
			if (idx < 3) _mousePressed[idx] = false;
			pushSDLEvent(SDL_MOUSEBUTTONUP, pos.x(), pos.y(), button);
		}
		QWidget::mouseReleaseEvent(event);
	}

	void GameWindow::keyPressEvent(QKeyEvent *event)
	{
		QWidget::keyPressEvent(event);
		SDL_Event e;
		e.type = SDL_KEYDOWN;
		e.key.keysym.sym = getPhysicalKey(event);
		e.key.keysym.mod = convertQtModifiers(event->modifiers());
		SDL_PushEvent(&e);
	}

	void GameWindow::keyReleaseEvent(QKeyEvent *event)
	{
		QWidget::keyReleaseEvent(event);
		SDL_Event e;
		e.type = SDL_KEYDOWN;
		e.key.keysym.sym = getPhysicalKey(event);
		e.key.keysym.mod = convertQtModifiers(event->modifiers());
		SDL_PushEvent(&e);
	}

	void GameWindow::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);

		if (m_Game.getScreen())
		{
			SDL_Surface* screen = m_Game.getScreen()->getSurface();

			SDL_LockSurface(screen);

			QImage image(
				(const uchar*)screen->pixels,
				screen->w,
				screen->h,
				screen->pitch,
				screen->format->BitsPerPixel == 32 ?
					QImage::Format_ARGB32 : QImage::Format_Indexed8
				);

			// Если это 8-битный формат, нужно установить палитру
			if (screen->format->BitsPerPixel == 8) {
				QVector<QRgb> colorTable(256);
				SDL_Palette* pal = screen->format->palette;
				for (int i = 0; i < pal->ncolors; i++) {
					colorTable[i] = qRgb(pal->colors[i].r,
										 pal->colors[i].g,
										 pal->colors[i].b);
				}
				image.setColorTable(colorTable);
			}

			// Масштабируем под размер виджета
			QImage scaled = image.scaled(size(), Qt::KeepAspectRatio);

			// Рисуем с центрированием
			int x = (width() - scaled.width()) / 2;
			int y = (height() - scaled.height()) / 2;
			painter.drawImage(x, y, scaled);

			SDL_UnlockSurface(screen);
		}
	}

	void GameWindow::timerEvent(QTimerEvent *)
	{
		m_Game.run();
		update();
	}
}
