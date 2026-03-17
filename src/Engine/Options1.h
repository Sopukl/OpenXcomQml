#pragma once
#include <QSettings>
#include <string>

//OPTION, get/set/notify/save to file
#define OPTION(type, name) \
Q_PROPERTY(type name READ name WRITE set##name NOTIFY name##Changed FINAL) \
	public: \
	type name() const { return m_##name; } \
	void set##name(type value) { \
		if (m_##name != value) { \
			m_##name = value; \
			Q_EMIT name##Changed(); \
	} \
} \
	Q_SIGNAL void name##Changed(); \
	private: \
	type m_##name;

//MEMBER, no get/set/notify/ no save to file
#define MEMBER(type, name) \
	Q_PROPERTY(type name MEMBER name FINAL) \
	public: \
	type name;


Q_DECLARE_METATYPE(std::string)
namespace OpenXcom
{
	class Options1 final: public QSettings
	{
		Q_OBJECT

		//general
		OPTION(qint32, pauseMode)
		OPTION(qint32, changeValueByMouseWheel)
		OPTION(qint32, dragScrollTimeTolerance)
		OPTION(qint32, dragScrollPixelTolerance)
		OPTION(qint32, mousewheelSpeed)
		OPTION(qint32, autosaveFrequency)

		OPTION(bool, fullscreen)
		OPTION(bool, asyncBlit)
		OPTION(bool, playIntro)
		OPTION(bool, useScaleFilter)
		OPTION(bool, useHQXFilter)
		OPTION(bool, useXBRZFilter)
		OPTION(bool, useOpenGL)
		OPTION(bool, checkOpenGLErrors)
		OPTION(bool, vSyncForOpenGL)
		OPTION(bool, useOpenGLSmoothing)

		OPTION(bool, autosave)
		OPTION(bool, allowResize)
		OPTION(bool, borderless)
		OPTION(bool, debug)
		OPTION(bool, debugUi)
		OPTION(bool, fpsCounter)
		OPTION(bool, newSeedOnLoad)
		OPTION(bool, keepAspectRatio)
		OPTION(bool, nonSquarePixelRatio)
		OPTION(bool, cursorInBlackBandsInFullscreen)
		OPTION(bool, cursorInBlackBandsInWindow)
		OPTION(bool, cursorInBlackBandsInBorderlessWindow)
		OPTION(bool, maximizeInfoScreens)
		OPTION(bool, musicAlwaysLoop)
		OPTION(bool, stereoSound)
		OPTION(bool, verboseLogging)
		OPTION(bool, soldierDiaries)
		OPTION(bool, touchEnabled)
		OPTION(bool, rootWindowedMode)
		OPTION(bool, lazyLoadResources)
		OPTION(bool, backgroundMute)

		OPTION(QString, language)
		OPTION(qint32, keyboardMode)
		OPTION(qint32, saveOrder)
		OPTION(qint32, preferredMusic)
		OPTION(qint32, preferredSound)
		OPTION(qint32, preferredVideo)
		OPTION(qint32, captureMouse)
		OPTION(qint32, wordwrap)
		OPTION(QString, useOpenGLShader)
		//video
		OPTION(qint32, displayWidth)
		OPTION(qint32, displayHeight)
		OPTION(qint32, windowedModePositionX)
		OPTION(qint32, windowedModePositionY)
		OPTION(qint32, maxFPS)
		OPTION(qint32, maxFPSInactive)
		//audio
		OPTION(qint32, soundVolume)
		OPTION(qint32, musicVolume)
		OPTION(qint32, uiVolume)
		OPTION(qint32, audioSampleRate)
		OPTION(qint32, audioBitDepth)
		OPTION(qint32, audioChunkSize)

		//other
		MEMBER(qint32, maxFrameSkip)
		MEMBER(qint32, baseXResolution)
		MEMBER(qint32, baseYResolution)
		MEMBER(qint32, baseXGeoscape)
		MEMBER(qint32, baseYGeoscape)
		MEMBER(qint32, baseXBattlescape)
		MEMBER(qint32, baseYBattlescape)
	  public:
		Options1();
		~Options1();

		void saveSettings();
	};

	inline Options1 options1;
}
