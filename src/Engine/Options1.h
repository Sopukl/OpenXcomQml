#pragma once
#include <QSettings>

namespace OpenXcom
{
	class Options1 final: public QSettings
	{
		Q_OBJECT

		Q_PROPERTY(qint32 displayWidth  READ displayWidth  WRITE setDisplayWidth  NOTIFY displayWidthChanged  FINAL)
		Q_PROPERTY(qint32 displayHeight READ displayHeight WRITE setDisplayHeight NOTIFY displayHeightChanged FINAL)
	  public:
		Options1();
		~Options1();

		qint32 displayWidth() const;
		void setDisplayWidth(qint32 newDisplayWidth);
		qint32 displayHeight() const;
		void setDisplayHeight(qint32 newDisplayHeight);

		void saveDisplaySettings();
	  signals:
		void displayWidthChanged();
		void displayHeightChanged();

	  private:
		qint32 m_DisplayWidth;
		qint32 m_DisplayHeight;
	};

	inline Options1 options1;
}
