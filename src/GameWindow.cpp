#include "GameWindow.h"
#include <QDebug>

namespace OpenXcom
{
void GameWindow::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);
	qDebug() << event;
}

GameWindow::GameWindow(QWidget* parent)
		: QWidget{parent},
		m_Game(this)
	{
	}

	void GameWindow::start()
	{
		m_Game.run();
	}
}
