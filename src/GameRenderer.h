#pragma once
#include <QQuickPaintedItem>
#include "Engine/Game.h"

namespace OpenXcom
{
	class GameRenderer : public QQuickPaintedItem
	{
		Q_OBJECT
		QML_ELEMENT
		Game m_Game;
		SDL_Event _sdlEvent;
		bool _mousePressed[3]; // LMB, RMB, MMB
		QPoint _lastMousePos;
	  protected:
		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void hoverMoveEvent(QHoverEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
		void keyPressEvent(QKeyEvent* event) override;
		void keyReleaseEvent(QKeyEvent* event) override;
		void timerEvent(QTimerEvent*) override;
		void focusInEvent(QFocusEvent*) override;
		void focusOutEvent(QFocusEvent*) override;
	  public:
		explicit GameRenderer(QQuickItem *parent = nullptr);

		void paint(QPainter *painter) override;

	  signals:
	  private:
		void pushSDLEvent(Uint32 type, int x, int y, Uint8 button = 0);
		Uint8 getMouseState();
		Uint8 convertMouseButton(Qt::MouseButton button);
		void initSDL();
	};
}
