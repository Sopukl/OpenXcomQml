#include "Options1.h"
#include "Options.h"
#include <QStandardPaths>
#include <SDL_mixer.h>
#define readValue(name, type, defaultValue) \
    m_##name = value(#name, defaultValue).value<type>();
#define writeValue(name, value) \
    setValue(#name, value);

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
            readValue(pauseMode,  qint32, 0)
            readValue(maxFPS, qint32, 60)
            readValue(maxFPSInactive, qint32, 30)
            readValue(pauseMode, qint32, 0)
            readValue(changeValueByMouseWheel, qint32, 0)
            readValue(dragScrollTimeTolerance, qint32, 300)
            readValue(dragScrollPixelTolerance, qint32, 10)
            readValue(mousewheelSpeed, qint32, 3)
            readValue(autosaveFrequency, qint32, 5)

			readValue(fullscreen, bool, false)
			readValue(asyncBlit, bool, false)
			readValue(playIntro, bool, false)
			readValue(useScaleFilter, bool, false)
			readValue(useHQXFilter, bool, false)
			readValue(useXBRZFilter, bool, false)
			readValue(useOpenGL, bool, false)
			readValue(checkOpenGLErrors, bool, false)
			readValue(vSyncForOpenGL, bool, true)
			readValue(useOpenGLSmoothing, bool, false)

			readValue(autosave, bool, true)
			readValue(allowResize, bool, false)
			readValue(borderless, bool, false)
			readValue(debug, bool, false)
			readValue(debugUi, bool, false)
			readValue(fpsCounter, bool, true)
			readValue(newSeedOnLoad, bool, false)
			readValue(keepAspectRatio, bool, true)
			readValue(nonSquarePixelRatio, bool, false)
			readValue(cursorInBlackBandsInFullscreen, bool, false)
			readValue(cursorInBlackBandsInWindow, bool, true)
			readValue(cursorInBlackBandsInBorderlessWindow, bool, true)
			readValue(maximizeInfoScreens, bool, true)
			readValue(musicAlwaysLoop, bool, false)
			readValue(stereoSound, bool, true)
			readValue(verboseLogging, bool, false)
			readValue(soldierDiaries, bool, true)
			readValue(touchEnabled, bool, false)
			readValue(rootWindowedMode, bool, false)
			readValue(lazyLoadResources, bool, true)
			readValue(backgroundMute, bool, true)

			readValue(language, QString, "")
			readValue(keyboardMode, KeyboardType, KEYBOARD_ON)
			readValue(saveOrder, SaveSort, SORT_DATE_DESC)
			readValue(preferredMusic, MusicFormat, MUSIC_AUTO)
			readValue(preferredSound, SoundFormat, SOUND_AUTO)
			readValue(preferredVideo, VideoFormat, VIDEO_FMV)
			readValue(captureMouse, SDL_GrabMode, 0)
			readValue(wordwrap, TextWrapping, WRAP_AUTO)
			readValue(keyOk, SDLKey, SDLK_RETURN)
			readValue(keyCancel, SDLKey, SDLK_ESCAPE)
			readValue(keyScreenshot, SDLKey, SDLK_F12)
			readValue(keyFps, SDLKey, SDLK_F7)
			readValue(keyQuickLoad, SDLKey, SDLK_F9)
			readValue(keyQuickSave, SDLKey, SDLK_F5)
			readValue(useOpenGLShader, QString, "Shaders/Raw.OpenGL.shader")
		endGroup();
		beginGroup("Geoscape");
			readValue(geoClockSpeed, qint32, 80)
			readValue(dogfightSpeed, qint32, 30)
			readValue(geoScrollSpeed, qint32, 20)
			readValue(geoDragScrollButton, qint32, SDL_BUTTON_LEFT)
			readValue(geoscapeScale, qint32, 0)
			readValue(includePrimeStateInSavedLayout, bool, false)
			readValue(anytimePsiTraining, bool, false)
			readValue(weaponSelfDestruction, bool, false)
			readValue(retainCorpses, bool, false)
			readValue(craftLaunchAlways, bool, false)
			readValue(globeSurfaceCache, bool, false)
			readValue(globeSeasons, bool, false)
			readValue(globeDetail, bool, true)
			readValue(globeRadarLines, bool, true)
			readValue(globeFlightPaths, bool, true)
			readValue(globeAllRadarsOnBaseBuild, bool, true)
			readValue(storageLimitsEnforced, bool, false)
			readValue(canSellLiveAliens, bool, false)
			readValue(canTransferCraftsWhileAirborne, bool, false)
			readValue(customInitialBase, bool, false)
			readValue(aggressiveRetaliation, bool, false)
			readValue(geoDragScrollInvert, bool, false)
			readValue(allowBuildingQueue, bool, false)
			readValue(showFundsOnGeoscape, bool, false)
			readValue(psiStrengthEval, bool, false)
			readValue(allowPsiStrengthImprovement, bool, false)
			readValue(fieldPromotions, bool, false)
			readValue(meetingPoint, bool, false)
		endGroup();
        beginGroup("Video");
            readValue(displayWidth,  qint32, 640)
            readValue(displayHeight, qint32, 480)
            readValue(windowedModePositionX, qint32, 0)
            readValue(windowedModePositionY, qint32, 0)
        endGroup();
        beginGroup("Audio");
            readValue(soundVolume,  qint32, 2*(MIX_MAX_VOLUME/3))
            readValue(musicVolume,  qint32, 2*(MIX_MAX_VOLUME/3))
            readValue(uiVolume,  qint32, (MIX_MAX_VOLUME/3))
            readValue(audioSampleRate,  qint32, 22050)
            readValue(audioBitDepth,  qint32, 16)
            readValue(audioChunkSize,  qint32, 1024)
        endGroup();
    }

	Options1::~Options1()
	{
		saveSettings();
	}

	void Options1::saveSettings()
	{
		beginGroup("General");
			writeValue(pauseMode, m_pauseMode);
			writeValue(maxFPS, m_maxFPS)
			writeValue(maxFPSInactive, m_maxFPSInactive)
			writeValue(pauseMode, m_pauseMode)
			writeValue(changeValueByMouseWheel, m_changeValueByMouseWheel)
			writeValue(dragScrollTimeTolerance, m_dragScrollTimeTolerance)
			writeValue(dragScrollPixelTolerance, m_dragScrollPixelTolerance)
			writeValue(mousewheelSpeed, m_mousewheelSpeed)
			writeValue(autosaveFrequency, m_autosaveFrequency)

			writeValue(fullscreen, m_fullscreen)
			writeValue(asyncBlit, m_asyncBlit)
			writeValue(playIntro, m_playIntro)
			writeValue(useScaleFilter, m_useScaleFilter)
			writeValue(useHQXFilter, m_useHQXFilter)
			writeValue(useXBRZFilter, m_useXBRZFilter)
			writeValue(useOpenGL, m_useOpenGL)
			writeValue(checkOpenGLErrors, m_checkOpenGLErrors)
			writeValue(vSyncForOpenGL, m_vSyncForOpenGL)
			writeValue(useOpenGLSmoothing, m_useOpenGLSmoothing)

			writeValue(autosave, m_autosave)
			writeValue(allowResize, m_allowResize)
			writeValue(borderless, m_borderless)
			writeValue(debug, m_debug)
			writeValue(debugUi, m_debugUi)
			writeValue(fpsCounter, m_fpsCounter)
			writeValue(newSeedOnLoad, m_newSeedOnLoad)
			writeValue(keepAspectRatio, m_keepAspectRatio)
			writeValue(nonSquarePixelRatio, m_nonSquarePixelRatio)
			writeValue(cursorInBlackBandsInFullscreen, m_cursorInBlackBandsInFullscreen)
			writeValue(cursorInBlackBandsInWindow, m_cursorInBlackBandsInWindow)
			writeValue(cursorInBlackBandsInBorderlessWindow, m_cursorInBlackBandsInBorderlessWindow)
			writeValue(maximizeInfoScreens, m_maximizeInfoScreens)
			writeValue(musicAlwaysLoop, m_musicAlwaysLoop)
			writeValue(StereoSound, m_stereoSound)
			writeValue(verboseLogging, m_verboseLogging)
			writeValue(soldierDiaries, m_soldierDiaries)
			writeValue(touchEnabled, m_touchEnabled)
			writeValue(rootWindowedMode, m_rootWindowedMode)
			writeValue(lazyLoadResources, m_lazyLoadResources)
			writeValue(backgroundMute, m_backgroundMute)
			writeValue(language, m_language)
			writeValue(keyboardMode, m_keyboardMode)
			writeValue(saveOrder, m_saveOrder)
			writeValue(preferredMusic, m_preferredMusic)
			writeValue(preferredSound, m_preferredSound)
			writeValue(preferredVideo, m_preferredVideo)
			writeValue(captureMouse, m_captureMouse)
			writeValue(wordwrap, m_wordwrap)
			writeValue(keyOk, m_keyOk)
			writeValue(keyCancel, m_keyCancel)
			writeValue(keyScreenshot, m_keyScreenshot)
			writeValue(keyFps, m_keyFps)
			writeValue(keyQuickLoad, m_keyQuickLoad)
			writeValue(keyQuickSave, m_keyQuickSave)
			writeValue(useOpenGLShader, m_useOpenGLShader)
		endGroup();
		beginGroup("Geoscape");
			writeValue(geoClockSpeed, m_geoClockSpeed)
			writeValue(dogfightSpeed, m_dogfightSpeed)
			writeValue(geoScrollSpeed, m_geoScrollSpeed)
			writeValue(geoDragScrollButton, m_geoDragScrollButton)
			writeValue(geoscapeScale, m_geoscapeScale)
			writeValue(includePrimeStateInSavedLayout, m_includePrimeStateInSavedLayout)
			writeValue(anytimePsiTraining, m_anytimePsiTraining)
			writeValue(weaponSelfDestruction, m_weaponSelfDestruction)
			writeValue(retainCorpses, m_retainCorpses)
			writeValue(craftLaunchAlways, m_craftLaunchAlways)
			writeValue(globeSurfaceCache, m_globeSurfaceCache)
			writeValue(globeSeasons, m_globeSeasons)
			writeValue(globeDetail, m_globeDetail)
			writeValue(globeRadarLines, m_globeRadarLines)
			writeValue(globeFlightPaths, m_globeFlightPaths)
			writeValue(globeAllRadarsOnBaseBuild, m_globeAllRadarsOnBaseBuild)
			writeValue(storageLimitsEnforced, m_storageLimitsEnforced)
			writeValue(canSellLiveAliens, m_canSellLiveAliens)
			writeValue(canTransferCraftsWhileAirborne, m_canTransferCraftsWhileAirborne)
			writeValue(customInitialBase, m_customInitialBase)
			writeValue(aggressiveRetaliation, m_aggressiveRetaliation)
			writeValue(geoDragScrollInvert, m_geoDragScrollInvert)
			writeValue(allowBuildingQueue, m_allowBuildingQueue)
			writeValue(showFundsOnGeoscape, m_showFundsOnGeoscape)
			writeValue(psiStrengthEval, m_psiStrengthEval)
			writeValue(allowPsiStrengthImprovement, m_allowPsiStrengthImprovement)
			writeValue(fieldPromotions, m_fieldPromotions)
			writeValue(meetingPoint, m_meetingPoint)
		endGroup();
		beginGroup("Video");
			writeValue(displayWidth, m_displayWidth)
			writeValue(displayHeight, m_displayHeight)
			writeValue(windowedModePositionX, m_windowedModePositionX)
			writeValue(windowedModePositionY, m_windowedModePositionY)
		endGroup();
		beginGroup("Audio");
			writeValue(soundVolume, m_soundVolume)
			writeValue(musicVolume, m_musicVolume)
			writeValue(uiVolume, m_uiVolume)
			writeValue(audioSampleRate, m_audioSampleRate)
			writeValue(audioBitDepth, m_audioBitDepth)
			writeValue(audioChunkSize, m_audioChunkSize)
		endGroup();

		sync();
	}
}
