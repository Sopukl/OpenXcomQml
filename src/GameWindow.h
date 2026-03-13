#pragma once

#include <QWidget>
#include "Engine/Game.h"
namespace OpenXcom
{
	class GameWindow : public QWidget
	{
		Q_OBJECT

		Game m_Game;
	  protected:
		void mousePressEvent(QMouseEvent *event) override;
	  public:
		explicit GameWindow(QWidget* parent = nullptr);

		void start();
	  signals:
	};
}
