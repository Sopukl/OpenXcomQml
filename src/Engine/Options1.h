#pragma once
#include <QSettings>

namespace OpenXcom
{
	class Options1 final: public QSettings
	{
		Q_OBJECT

		//general
		//
		Q_PROPERTY(qint32 pauseMode READ pauseMode WRITE setPauseMode NOTIFY pauseModeChanged FINAL)
		//video
		Q_PROPERTY(qint32 displayWidth  READ displayWidth  WRITE setDisplayWidth  NOTIFY displayWidthChanged  FINAL)
		Q_PROPERTY(qint32 displayHeight READ displayHeight WRITE setDisplayHeight NOTIFY displayHeightChanged FINAL)
		Q_PROPERTY(qint32 windowedModePositionX READ windowedModePositionX WRITE setWindowedModePositionX NOTIFY windowedModePositionXChanged FINAL)
		Q_PROPERTY(qint32 windowedModePositionY READ windowedModePositionY WRITE setWindowedModePositionY NOTIFY windowedModePositionYChanged FINAL)
		//audio
		Q_PROPERTY(qint32 soundVolume READ soundVolume WRITE setSoundVolume NOTIFY soundVolumeChanged FINAL)
		Q_PROPERTY(qint32 musicVolume READ musicVolume WRITE setMusicVolume NOTIFY musicVolumeChanged FINAL)
		Q_PROPERTY(qint32 uiVolume    READ uiVolume    WRITE setUiVolume    NOTIFY uiVolumeChanged    FINAL)
		Q_PROPERTY(qint32 audioSampleRate READ audioSampleRate WRITE setAudioSampleRate NOTIFY audioSampleRateChanged FINAL)
		Q_PROPERTY(qint32 audioBitDepth   READ audioBitDepth   WRITE setAudioBitDepth   NOTIFY audioBitDepthChanged   FINAL)
		Q_PROPERTY(qint32 audioChunkSize  READ audioChunkSize  WRITE setAudioChunkSize  NOTIFY audioChunkSizeChanged  FINAL)

		//other
		Q_PROPERTY(qint32 maxFrameSkip MEMBER maxFrameSkip FINAL)
		Q_PROPERTY(qint32 baseXResolution MEMBER baseXResolution FINAL)
		Q_PROPERTY(qint32 baseYResolution MEMBER baseYResolution FINAL)
		Q_PROPERTY(qint32 baseXGeoscape MEMBER baseXGeoscape FINAL)
		Q_PROPERTY(qint32 baseYGeoscape MEMBER baseYGeoscape FINAL)
		Q_PROPERTY(qint32 baseXBattlescape MEMBER baseXBattlescape FINAL)
		Q_PROPERTY(qint32 baseYBattlescape MEMBER baseYBattlescape FINAL)
	  public:
		Options1();
		~Options1();

		qint32 displayWidth() const;
		void setDisplayWidth(qint32 newDisplayWidth);

		qint32 displayHeight() const;
		void setDisplayHeight(qint32 newDisplayHeight);

		qint32 soundVolume() const;
		void setSoundVolume(qint32 newSoundVolume);

		qint32 musicVolume() const;
		void setMusicVolume(qint32 newMusicVolume);

		qint32 uiVolume() const;
		void setUiVolume(qint32 newUiVolume);

		qint32 audioSampleRate() const;
		void setAudioSampleRate(qint32 newAudioSampleRate);

		qint32 audioBitDepth() const;
		void setAudioBitDepth(qint32 newAudioBitDepth);

		qint32 audioChunkSize() const;
		void setAudioChunkSize(qint32 newAudioChunkSize);

		void saveSettings();
	  signals:
		void displayWidthChanged();
		void displayHeightChanged();
		void soundVolumeChanged();
		void musicVolumeChanged();
		void uiVolumeChanged();
		void audioSampleRateChanged();
		void audioBitDepthChanged();
		void audioChunkSizeChanged();
		void pauseModeChanged();

		void windowedModePositionXChanged();

		void windowedModePositionYChanged();

	  private:
		qint32 m_DisplayWidth;
		qint32 m_DisplayHeight;
		qint32 m_SoundVolume;
		qint32 m_MusicVolume;
		qint32 m_UiVolume;
		qint32 m_AudioSampleRate;
		qint32 m_AudioBitDepth;
		qint32 m_AudioChunkSize;
		qint32 m_PauseMode;

		qint32 m_WindowedModePositionX;

		qint32 m_WindowedModePositionY;

	  public:
		qint32 maxFrameSkip;
		qint32 baseXResolution;
		qint32 baseYResolution;
		qint32 baseXGeoscape;
		qint32 baseYGeoscape;
		qint32 baseXBattlescape;
		qint32 baseYBattlescape;
		qint32 pauseMode() const;
		void setPauseMode(qint32 newPauseMode);
		qint32 windowedModePositionX() const;
		void setWindowedModePositionX(qint32 newWindowedModePositionX);
		qint32 windowedModePositionY() const;
		void setWindowedModePositionY(qint32 newWindowedModePositionY);
	};

	inline Options1 options1;
}
