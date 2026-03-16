#include "Options1.h"
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
