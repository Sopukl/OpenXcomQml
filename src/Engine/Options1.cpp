#include "Options1.h"
#include <QStandardPaths>

namespace OpenXcom
{
    QString openXComFolder()
    {
        QString pathToDocuments = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        return pathToDocuments + "/OpenXCom";
    }
    Options1::Options1():
        QSettings(openXComFolder()+"/Options1.cfg", IniFormat)
    {
        beginGroup("Video");
            m_DisplayWidth = value("displayWidth", 640).value<qint32>();
            m_DisplayHeight = value("displayHeight", 480).value<qint32>();
        endGroup();

        saveDisplaySettings();
    }

	Options1::~Options1()
	{
	}

	qint32 Options1::displayWidth() const
	{
		return m_DisplayWidth;
	}

	void Options1::setDisplayWidth(qint32 newDisplayWidth)
	{
		if (m_DisplayWidth != newDisplayWidth)
		{
			m_DisplayWidth = newDisplayWidth;
			Q_EMIT displayWidthChanged();
		}
	}

	qint32 Options1::displayHeight() const
	{
		return m_DisplayHeight;
	}

	void Options1::setDisplayHeight(qint32 newDisplayHeight)
	{
		if (m_DisplayHeight != newDisplayHeight)
		{
			m_DisplayHeight = newDisplayHeight;
			Q_EMIT displayHeightChanged();
		}
	}

	void Options1::saveDisplaySettings()
	{
		beginGroup("Video");
			setValue("displayWidth", m_DisplayWidth);
			setValue("displayHeight", m_DisplayHeight);
		endGroup();

		sync();
	}


}
