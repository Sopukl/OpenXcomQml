#pragma once
#include <QWidget>
#include "Engine/Game.h"
#include <QPoint>

namespace OpenXcom
{
	class GameWindow : public QWidget
	{
		Q_OBJECT

		Game m_Game;
		SDL_Event _sdlEvent;
		bool _mousePressed[3]; // LMB, RMB, MMB
		QPoint _lastMousePos;
	protected:
		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
		void keyPressEvent(QKeyEvent* event) override;
		void keyReleaseEvent(QKeyEvent* event) override;
		void paintEvent(QPaintEvent*) override;
		void timerEvent(QTimerEvent*) override;
	public:
		explicit GameWindow(QWidget* parent = nullptr);

	  signals:
	  private slots:
		void resize_Window();
	  private:
		void pushSDLEvent(Uint32 type, int x, int y, Uint8 button = 0);
		Uint8 getMouseState();
		Uint8 convertMouseButton(Qt::MouseButton button);
	};
}
