#pragma once
#include <QSettings>
#include "Language.h"
#include <SDL_keysym.h>
#include <SDL_video.h>
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


namespace OpenXcom
{
	/// Keyboard input modes.
	enum KeyboardType { KEYBOARD_OFF, KEYBOARD_ON, KEYBOARD_VIRTUAL };
	/// Savegame sorting modes.
	enum SaveSort { SORT_NAME_ASC, SORT_NAME_DESC, SORT_DATE_ASC, SORT_DATE_DESC };
	/// Music format preferences.
	enum MusicFormat { MUSIC_AUTO, MUSIC_FLAC, MUSIC_OGG, MUSIC_MP3, MUSIC_MOD, MUSIC_WAV, MUSIC_ADLIB, MUSIC_GM, MUSIC_MIDI };
	/// Sound format preferences.
	enum SoundFormat { SOUND_AUTO, SOUND_14, SOUND_10 };
	/// Video format preferences.
	enum VideoFormat { VIDEO_FMV, VIDEO_SLIDE };
	/// Path preview modes (can be OR'd together).
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
		OPTION(KeyboardType, keyboardMode)
		OPTION(SaveSort, saveOrder)
		OPTION(MusicFormat, preferredMusic)
		OPTION(SoundFormat, preferredSound)
		OPTION(VideoFormat, preferredVideo)
		OPTION(SDL_GrabMode, captureMouse)
		OPTION(TextWrapping, wordwrap)
		OPTION(SDLKey, keyOk)
		OPTION(SDLKey, keyCancel)
		OPTION(SDLKey, keyScreenshot)
		OPTION(SDLKey, keyFps)
		OPTION(SDLKey, keyQuickLoad)
		OPTION(SDLKey, keyQuickSave)
		OPTION(QString, useOpenGLShader)

		//geoscape
		OPTION(qint32, geoClockSpeed)
		OPTION(qint32, dogfightSpeed)
		OPTION(qint32, geoScrollSpeed)
		OPTION(qint32, geoDragScrollButton)
		OPTION(qint32, geoscapeScale)
		OPTION(bool, includePrimeStateInSavedLayout)
		OPTION(bool, anytimePsiTraining)
		OPTION(bool, weaponSelfDestruction)
		OPTION(bool, retainCorpses)
		OPTION(bool, craftLaunchAlways)
		OPTION(bool, globeSurfaceCache)
		OPTION(bool, globeSeasons)
		OPTION(bool, globeDetail)
		OPTION(bool, globeRadarLines)
		OPTION(bool, globeFlightPaths)
		OPTION(bool, globeAllRadarsOnBaseBuild)
		OPTION(bool, storageLimitsEnforced)
		OPTION(bool, canSellLiveAliens)
		OPTION(bool, canTransferCraftsWhileAirborne)
		OPTION(bool, customInitialBase)
		OPTION(bool, aggressiveRetaliation)
		OPTION(bool, geoDragScrollInvert)
		OPTION(bool, allowBuildingQueue)
		OPTION(bool, showFundsOnGeoscape)
		OPTION(bool, psiStrengthEval)
		OPTION(bool, allowPsiStrengthImprovement)
		OPTION(bool, fieldPromotions)
		OPTION(bool, meetingPoint)
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
	Q_DECLARE_METATYPE(std::string)
	Q_DECLARE_METATYPE(SDLKey)
	Q_DECLARE_METATYPE(SDL_GrabMode)
	Q_DECLARE_METATYPE(OpenXcom::KeyboardType)
	Q_DECLARE_METATYPE(OpenXcom::SaveSort)
	Q_DECLARE_METATYPE(OpenXcom::MusicFormat)
	Q_DECLARE_METATYPE(OpenXcom::SoundFormat)
	Q_DECLARE_METATYPE(OpenXcom::VideoFormat)
	Q_DECLARE_METATYPE(OpenXcom::TextDirection)
	Q_DECLARE_METATYPE(OpenXcom::TextWrapping)

