#pragma once
#include <QSettings>
#include "Language.h"
#include <SDL/SDL_keysym.h>
#include <SDL/SDL_video.h>
#include <string>
#include "Logger.h"
#include <qqmlintegration.h>

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
	enum ScrollType { SCROLL_NONE, SCROLL_TRIGGER, SCROLL_AUTO };
	enum PathPreview {
		PATH_NONE         = 0x00,
		PATH_ARROWS       = 0x01,
		PATH_TU_COST      = 0x02,
		PATH_ARROW_TU     = 0x03,
		PATH_ENERGY_COST  = 0x04,
		PATH_ARROW_ENERGY = 0x05,
		PATH_TU_ENERGY    = 0x06,
		PATH_FULL         = 0x07
	};
	enum ScaleType
	{
		SCALE_ORIGINAL,
		SCALE_15X,
		SCALE_2X,
		SCALE_SCREEN_DIV_3,
		SCALE_SCREEN_DIV_2,
		SCALE_SCREEN,
		SCALE_SCREEN_DIV_4,
		SCALE_SCREEN_DIV_5,
		SCALE_SCREEN_DIV_6,
		SCALE_SCREEN_DIV_8,
		SCALE_SCREEN_DIV_10
	};

	class Options1: public QSettings
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
		OPTION(SDLKey, keyGeoLeft)
		OPTION(SDLKey, keyGeoRight)
		OPTION(SDLKey, keyGeoUp)
		OPTION(SDLKey, keyGeoDown)
		OPTION(SDLKey, keyGeoZoomIn)
		OPTION(SDLKey, keyGeoZoomOut)
		OPTION(SDLKey, keyGeoSpeed1)
		OPTION(SDLKey, keyGeoSpeed2)
		OPTION(SDLKey, keyGeoSpeed3)
		OPTION(SDLKey, keyGeoSpeed4)
		OPTION(SDLKey, keyGeoSpeed5)
		OPTION(SDLKey, keyGeoSpeed6)
		OPTION(SDLKey, keyGeoIntercept)
		OPTION(SDLKey, keyGeoBases)
		OPTION(SDLKey, keyGeoGraphs)
		OPTION(SDLKey, keyGeoUfopedia)
		OPTION(SDLKey, keyGeoOptions)
		OPTION(SDLKey, keyGeoFunding)
		OPTION(SDLKey, keyGeoToggleDetail)
		OPTION(SDLKey, keyGeoToggleRadar)
		OPTION(SDLKey, keyBaseSelect1)
		OPTION(SDLKey, keyBaseSelect2)
		OPTION(SDLKey, keyBaseSelect3)
		OPTION(SDLKey, keyBaseSelect4)
		OPTION(SDLKey, keyBaseSelect5)
		OPTION(SDLKey, keyBaseSelect6)
		OPTION(SDLKey, keyBaseSelect7)
		OPTION(SDLKey, keyBaseSelect8)

		//battlescape
		OPTION(ScrollType, battleEdgeScroll)
		OPTION(PathPreview, battleNewPreviewPath)
		OPTION(qint32, battleScrollSpeed)
		OPTION(qint32, battleDragScrollButton)
		OPTION(qint32, battleFireSpeed)
		OPTION(qint32, battleXcomSpeed)
		OPTION(qint32, battleAlienSpeed)
		OPTION(qint32, battleExplosionHeight)
		OPTION(qint32, battlescapeScale)

		OPTION(bool, traceAI)
		OPTION(bool, sneakyAI)
		OPTION(bool, battleInstantGrenade)
		OPTION(bool, battleNotifyDeath)
		OPTION(bool, battleTooltips)
		OPTION(bool, battleHairBleach)
		OPTION(bool, battleAutoEnd)
		OPTION(bool, strafe)
		OPTION(bool, forceFire)
		OPTION(bool, showMoreStatsInInventoryView)
		OPTION(bool, allowPsionicCapture)
		OPTION(bool, skipNextTurnScreen)
		OPTION(bool, disableAutoEquip)
		OPTION(bool, battleDragScrollInvert)
		OPTION(bool, battleUFOExtenderAccuracy)
		OPTION(bool, battleConfirmFireMode)
		OPTION(bool, battleSmoothCamera)
		OPTION(bool, noAlienPanicMessages)
		OPTION(bool, alienBleeding)

		OPTION(SDLKey, keyBattleLeft)
		OPTION(SDLKey, keyBattleRight)
		OPTION(SDLKey, keyBattleUp)
		OPTION(SDLKey, keyBattleDown)
		OPTION(SDLKey, keyBattleLevelUp)
		OPTION(SDLKey, keyBattleLevelDown)
		OPTION(SDLKey, keyBattleCenterUnit)
		OPTION(SDLKey, keyBattlePrevUnit)
		OPTION(SDLKey, keyBattleNextUnit)
		OPTION(SDLKey, keyBattleDeselectUnit)
		OPTION(SDLKey, keyBattleUseLeftHand)
		OPTION(SDLKey, keyBattleUseRightHand)
		OPTION(SDLKey, keyBattleInventory)
		OPTION(SDLKey, keyBattleMap)
		OPTION(SDLKey, keyBattleOptions)
		OPTION(SDLKey, keyBattleEndTurn)
		OPTION(SDLKey, keyBattleAbort)
		OPTION(SDLKey, keyBattleStats)
		OPTION(SDLKey, keyBattleKneel)
		OPTION(SDLKey, keyBattleReserveKneel)
		OPTION(SDLKey, keyBattleReload)
		OPTION(SDLKey, keyBattlePersonalLighting)
		OPTION(SDLKey, keyBattleReserveNone)
		OPTION(SDLKey, keyBattleReserveSnap)
		OPTION(SDLKey, keyBattleReserveAimed)
		OPTION(SDLKey, keyBattleReserveAuto)
		OPTION(SDLKey, keyBattleCenterEnemy1)
		OPTION(SDLKey, keyBattleCenterEnemy2)
		OPTION(SDLKey, keyBattleCenterEnemy3)
		OPTION(SDLKey, keyBattleCenterEnemy4)
		OPTION(SDLKey, keyBattleCenterEnemy5)
		OPTION(SDLKey, keyBattleCenterEnemy6)
		OPTION(SDLKey, keyBattleCenterEnemy7)
		OPTION(SDLKey, keyBattleCenterEnemy8)
		OPTION(SDLKey, keyBattleCenterEnemy9)
		OPTION(SDLKey, keyBattleCenterEnemy10)
		OPTION(SDLKey, keyBattleVoxelView)
		OPTION(SDLKey, keyBattleZeroTUs)
		OPTION(SDLKey, keyInvCreateTemplate)
		OPTION(SDLKey, keyInvApplyTemplate)
		OPTION(SDLKey, keyInvClear)
		OPTION(SDLKey, keyInvAutoEquip)

		//oxce
		OPTION(SDLKey, keyGeoDailyPilotExperience)
		OPTION(SDLKey, keyGeoUfoTracker)
		OPTION(SDLKey, keyGeoTechTreeViewer)
		OPTION(SDLKey, keyGeoGlobalResearch)
		OPTION(SDLKey, keyGeoGlobalProduction)
		OPTION(SDLKey, keyGeoGlobalAlienContainment)
		OPTION(SDLKey, keyGraphsZoomIn)
		OPTION(SDLKey, keyGraphsZoomOut)
		OPTION(SDLKey, keyToggleQuickSearch)
		OPTION(SDLKey, keyInstaSave)
		OPTION(SDLKey, keyCraftLoadoutSave)
		OPTION(SDLKey, keyCraftLoadoutLoad)
		OPTION(SDLKey, keyMarkAllAsSeen)
		OPTION(SDLKey, keySellAll)
		OPTION(SDLKey, keySellAllButOne)
		OPTION(SDLKey, keyTransferAll)
		OPTION(SDLKey, keyRemoveSoldiersFromCraft)
		OPTION(SDLKey, keyRemoveSoldiersFromAllCrafts)
		OPTION(SDLKey, keyRemoveEquipmentFromCraft)
		OPTION(SDLKey, keyRemoveArmorFromCraft)
		OPTION(SDLKey, keyRemoveArmorFromAllCrafts)
		OPTION(SDLKey, keyRemoveSoldiersFromTraining)
		OPTION(SDLKey, keyAddSoldiersToTraining)
		OPTION(SDLKey, keyInventoryArmor)
		OPTION(SDLKey, keyInventoryAvatar)
		OPTION(SDLKey, keyInventoryDiaryLight)
		OPTION(SDLKey, keyInventorySave)
		OPTION(SDLKey, keyInventoryLoad)
		OPTION(SDLKey, keyInvSavePersonalEquipment)
		OPTION(SDLKey, keyInvLoadPersonalEquipment)
		OPTION(SDLKey, keyInvShowPersonalEquipment)
		OPTION(SDLKey, keyBattleUnitUp)
		OPTION(SDLKey, keyBattleUnitDown)
		OPTION(SDLKey, keyBattleShowLayers)
		OPTION(SDLKey, keyBattleUseSpecial)
		OPTION(SDLKey, keyBattleActionItem1)
		OPTION(SDLKey, keyBattleActionItem2)
		OPTION(SDLKey, keyBattleActionItem3)
		OPTION(SDLKey, keyBattleActionItem4)
		OPTION(SDLKey, keyBattleActionItem5)
		OPTION(SDLKey, keyNightVisionToggle)
		OPTION(SDLKey, keyNightVisionHold)
		OPTION(SDLKey, keySelectMusicTrack)
		OPTION(SDLKey, keyBasescapeBuildNewBase)
		OPTION(SDLKey, keyBasescapeBaseInfo)
		OPTION(SDLKey, keyBasescapeSoldiers)
		OPTION(SDLKey, keyBasescapeCrafts)
		OPTION(SDLKey, keyBasescapeFacilities)
		OPTION(SDLKey, keyBasescapeResearch)
		OPTION(SDLKey, keyBasescapeManufacture)
		OPTION(SDLKey, keyBasescapeTransfer)
		OPTION(SDLKey, keyBasescapePurchase)
		OPTION(SDLKey, keyBasescapeSell)
		OPTION(bool, oxceUpdateCheck)
		OPTION(qint32, autosaveSlots)
		OPTION(qint32, oxceGeoAutosaveFrequency)
		OPTION(qint32, oxceGeoAutosaveSlots)
		OPTION(bool, oxceLinks)
		OPTION(bool, oxceLinksDisableTextEdit)
		OPTION(bool, oxceFatFingerLinks)
		OPTION(bool, oxceBattleTouchButtonsEnabled)
		OPTION(bool, oxceQuickSearchButton)
		OPTION(bool, oxceHighlightNewTopics)
		OPTION(bool, oxcePediaShowClipSize)
		OPTION(qint32, oxcePediaSortResistances)

		OPTION(qint32, oxceInterceptTableSize)
		OPTION(bool, oxceEnableSlackingIndicator)
		OPTION(qint32, oxceInterceptGuiMaintenanceTime)
		OPTION(qint32, oxceShowETAMode)
		OPTION(bool, oxceUfoLandingAlert)
		OPTION(bool, oxceRememberDisabledCraftWeapons)
		OPTION(bool, oxceGeoscapeEventsInstantDelivery)
		OPTION(bool, oxceShowBaseNameInPopups)

		OPTION(bool, oxceAlternateCraftEquipmentManagement)
		OPTION(bool, oxceBaseInfoScaleEnabled)
		OPTION(qint32, oxceResearchScrollSpeed)
		OPTION(qint32, oxceResearchScrollSpeedWithCtrl)
		OPTION(bool, oxceManufactureFilterSuppliesOK)
		OPTION(qint32, oxceManufactureScrollSpeed)
		OPTION(qint32, oxceManufactureScrollSpeedWithCtrl)
		OPTION(bool, oxcePersonalLayoutIncludingArmor)
		OPTION(bool, oxceManualPromotions)

		OPTION(qint32, oxceWoundedDefendBaseIf)
		OPTION(bool, oxcePlayBriefingMusicDuringEquipment)
		OPTION(qint32, oxceNightVisionColor)
		OPTION(qint32, oxceAutoNightVisionThreshold)
		OPTION(qint32, oxceShowAccuracyOnCrosshair)
		OPTION(qint32, oxceReactionFireThreshold)
		OPTION(bool, oxceAutoSell)
		OPTION(bool, oxceAutomaticPromotions)
		OPTION(bool, oxceEnableOffCentreShooting)
		OPTION(bool, oxceUniformShootingSpread)
		OPTION(qint32, oxceCrashedOrLanded)
		OPTION(qint32, oxceModValidationLevel)
		OPTION(bool, oxceRawScreenShots)
		OPTION(bool, oxceFirstPersonViewFisheyeProjection)
		OPTION(bool, oxceThumbButtons)
		OPTION(qint32, oxceThrottleMouseMoveEvent)
		OPTION(bool, oxceDisableThinkingProgressBar)

		OPTION(bool, oxceEmbeddedOnly)
		OPTION(bool, oxceListVFSContents)
		OPTION(bool, oxceEnablePaletteFlickerFix)
		OPTION(bool, oxceRecommendedOptionsWereSet)
		OPTION(QString, password)

		OPTION(qint32, oxceStartUpTextMode)

		OPTION(qint32, oxceGeoscapeDebugLogMaxEntries)
		OPTION(qint32, oxceGeoSlowdownFactor)
		OPTION(bool, oxceGeoShowScoreInsteadOfFunds)
		OPTION(bool, oxceGeoEnableTrainingIndicator)
		OPTION(bool, oxceGeoSuppressRedundantHKAlert)
		OPTION(bool, oxceGeoSuppressLandingWithoutEquipment)
		OPTION(bool, oxceGeoGoToNearestBase)
		OPTION(bool, oxceGeoSortCraftByDistanceToTarget)

		OPTION(qint32, oxceBaseInfoDefenseScaleMultiplier)
		OPTION(bool, oxceBaseSoldierTransformationShowOnlyEligible)
		OPTION(bool, oxceBaseFilterResearchable)
		OPTION(bool, oxceBaseResearchReorder)
		OPTION(bool, oxceBaseManufactureFallbackButton)
		OPTION(bool, oxceBaseManufactureInfinityButton)
		OPTION(bool, oxceBaseTouchButtons)

		OPTION(bool, oxceDisableAlienInventory)
		OPTION(bool, oxceDisableHitLog)
		OPTION(bool, oxceDisableInventoryTuCost)
		OPTION(bool, oxceDisableProductionDependencyTree)
		OPTION(bool, oxceDisableStatsForNerds)
		OPTION(bool, oxceDisableTechTreeViewer)

		OPTION(qint32, oxceTogglePersonalLightType)
		OPTION(qint32, oxceToggleNightVisionType)
		OPTION(qint32, oxceToggleBrightnessType)

		OPTION(bool, oxceShowBurningAsWounded)
		OPTION(bool, oxceDisableInfoOnThrowCursor)
		OPTION(bool, oxceSwapDontReselectActions)
		OPTION(bool, oxceEnableUnitResponseSounds)
		OPTION(qint32, oxceHiddenMovementBackgroundChangeFrequency)
		OPTION(bool, oxceInventoryShowUnitSlot)
		OPTION(bool, oxceReplaceNotesLink)

		OPTION(bool, oxceInventorySplitScrollButton)
		OPTION(bool, oxceInventoryDropItemOverPaperdoll)
		OPTION(bool, oxceInventoryUnloadFixedWeapons)

		OPTION(qint32, oxceMaxEquipmentLayoutTemplates)
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
		MEMBER(bool, mute)
		MEMBER(bool, reload)
		MEMBER(bool, newOpenGL)
		MEMBER(bool, newScaleFilter)
		MEMBER(bool, newHQXFilter)
		MEMBER(bool, newXBRZFilter)
		MEMBER(bool, newRootWindowedMode)
		MEMBER(bool, newFullscreen)
		MEMBER(bool, newAllowResize)
		MEMBER(bool, newBorderless)
		MEMBER(qint32, newDisplayWidth)
		MEMBER(qint32, newDisplayHeight)
		MEMBER(qint32, newBattlescapeScale)
		MEMBER(qint32, newGeoscapeScale)
		MEMBER(qint32, newWindowedModePositionX)
		MEMBER(qint32, newWindowedModePositionY)
		MEMBER(QString, newOpenGLShader)
		MEMBER(SoundFormat, currentSound)
		MEMBER(qint32, battleXcomSpeedOrig)
		MEMBER(qint32, battleAlienSpeedOrig)
		MEMBER(qint32, maxFrameSkip)
		MEMBER(qint32, baseXResolution)
		MEMBER(qint32, baseYResolution)
		MEMBER(qint32, baseXGeoscape)
		MEMBER(qint32, baseYGeoscape)
		MEMBER(qint32, baseXBattlescape)
		MEMBER(qint32, baseYBattlescape)
	  public:
		std::vector< std::pair<std::string, bool> > mods; // ordered list of available mods (lowest priority to highest) and whether they are active
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
Q_DECLARE_METATYPE(OpenXcom::ScrollType)
Q_DECLARE_METATYPE(OpenXcom::PathPreview)
Q_DECLARE_METATYPE	(OpenXcom::ScaleType)
Q_DECLARE_METATYPE(OpenXcom::TextDirection)
Q_DECLARE_METATYPE(OpenXcom::TextWrapping)

