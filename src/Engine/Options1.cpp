#include "Options1.h"
#include <QStandardPaths>
#include <SDL_mixer.h>

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
        beginGroup("General");
            m_PauseMode = value("pauseMode", 0).value<qint32>();
        endGroup();
        beginGroup("Video");
            m_DisplayWidth = value("displayWidth", 640).value<qint32>();
            m_DisplayHeight = value("displayHeight", 480).value<qint32>();
            m_WindowedModePositionX = value("windowedModePositionX").value<qint32>();
            m_WindowedModePositionY = value("windowedModePositionY").value<qint32>();
        endGroup();
        beginGroup("Audio");
        m_SoundVolume = value("soundVolume", 2*(MIX_MAX_VOLUME/3)).value<qint32>();
        m_MusicVolume = value("musicVolume", 2*(MIX_MAX_VOLUME/3)).value<qint32>();
        m_UiVolume = value("uiVolume", (MIX_MAX_VOLUME/3)).value<qint32>();
        m_AudioSampleRate = value("audioSampleRate", 22050).value<qint32>();
        m_AudioBitDepth = value("audioBitDepth", 16).value<qint32>();
        m_AudioChunkSize = value("audioChunkSize", 1024).value<qint32>();
        endGroup();

        saveSettings();
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

	void Options1::saveSettings()
	{
		beginGroup("General");
			setValue("pauseMode", m_PauseMode);
		endGroup();
		beginGroup("Video");
			setValue("displayWidth", m_DisplayWidth);
			setValue("displayHeight", m_DisplayHeight);
			setValue("windowedModePositionX", m_WindowedModePositionX);
			setValue("windowedModePositionY", m_WindowedModePositionY);
		endGroup();
		beginGroup("Audio");
			setValue("soundVolume", m_SoundVolume);
			setValue("musicVolume", m_MusicVolume);
			setValue("uiVolume", m_UiVolume);
			setValue("audioSampleRate", m_AudioSampleRate);
			setValue("audioBitDepth", m_AudioBitDepth);
			setValue("audioChunkSize", m_AudioChunkSize);
		endGroup();

		sync();
	}

	int Options1::soundVolume() const
	{
		return m_SoundVolume;
	}

	void Options1::setSoundVolume(int newSoundVolume)
	{
		if (m_SoundVolume != newSoundVolume)
		{
			m_SoundVolume = newSoundVolume;
			Q_EMIT soundVolumeChanged();
		}
	}

	int Options1::musicVolume() const
	{
		return m_MusicVolume;
	}

	void Options1::setMusicVolume(int newMusicVolume)
	{
		if (m_MusicVolume != newMusicVolume)
		{
			m_MusicVolume = newMusicVolume;
			Q_EMIT musicVolumeChanged();
		}
	}

	qint32 Options1::uiVolume() const
	{
		return m_UiVolume;
	}

	void Options1::setUiVolume(qint32 newUiVolume)
	{
		if (m_UiVolume != newUiVolume)
		{
			m_UiVolume = newUiVolume;
			Q_EMIT uiVolumeChanged();
		}
	}

	qint32 Options1::audioSampleRate() const
	{
		return m_AudioSampleRate;
	}

	void Options1::setAudioSampleRate(qint32 newAudioSampleRate)
	{
		if (m_AudioSampleRate != newAudioSampleRate)
		{
			m_AudioSampleRate = newAudioSampleRate;
			Q_EMIT audioSampleRateChanged();
		}
	}

	qint32 Options1::audioBitDepth() const
	{
		return m_AudioBitDepth;
	}

	void Options1::setAudioBitDepth(qint32 newAudioBitDepth)
	{
		if (m_AudioBitDepth != newAudioBitDepth)
		{
			m_AudioBitDepth = newAudioBitDepth;
			Q_EMIT audioBitDepthChanged();
		}
	}

	qint32 Options1::audioChunkSize() const
	{
		return m_AudioChunkSize;
	}

	void Options1::setAudioChunkSize(qint32 newAudioChunkSize)
	{
		if (m_AudioChunkSize != newAudioChunkSize)
		{
			m_AudioChunkSize = newAudioChunkSize;
			Q_EMIT audioChunkSizeChanged();
		}
	}

	qint32 Options1::pauseMode() const
	{
		return m_PauseMode;
	}

	void Options1::setPauseMode(qint32 newPauseMode)
	{
		if (m_PauseMode != newPauseMode)
		{
			m_PauseMode = newPauseMode;
			Q_EMIT pauseModeChanged();
		}
	}

	qint32 Options1::windowedModePositionX() const
	{
		return m_WindowedModePositionX;
	}

	void Options1::setWindowedModePositionX(qint32 newWindowedModePositionX)
	{
		if (m_WindowedModePositionX != newWindowedModePositionX)
		{
			m_WindowedModePositionX = newWindowedModePositionX;
			Q_EMIT windowedModePositionXChanged();
		}
	}

	qint32 Options1::windowedModePositionY() const
	{
		return m_WindowedModePositionY;
	}

	void Options1::setWindowedModePositionY(qint32 newWindowedModePositionY)
	{
		if (m_WindowedModePositionY != newWindowedModePositionY)
		{
			m_WindowedModePositionY = newWindowedModePositionY;
			Q_EMIT windowedModePositionYChanged();
		}
	}

}
