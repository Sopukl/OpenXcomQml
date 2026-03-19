// Don't worry about Intellisense errors here, as this file is only used in conjunction with Options.h/Options.cpp
// To add a new option, add a new variable entry and a corresponding OptionInfo in Options.cpp

// OXCE hidden, accessible only via options.cfg
/**
 * Verification level of mod data.
 * Same levels supported as `SeverityLevel`.
 */
OPT int oxceModValidationLevel;
OPT bool oxceRawScreenShots;
OPT bool oxceFirstPersonViewFisheyeProjection;
OPT bool oxceThumbButtons;
OPT int oxceThrottleMouseMoveEvent;
OPT bool oxceDisableThinkingProgressBar;

OPT bool oxceEmbeddedOnly;
OPT bool oxceListVFSContents;
OPT bool oxceEnablePaletteFlickerFix;
OPT bool oxceRecommendedOptionsWereSet;
OPT std::string password;

// OXCE hidden, but moddable via fixedUserOptions and/or recommendedUserOptions
OPT int oxceStartUpTextMode;

OPT int oxceGeoscapeDebugLogMaxEntries;
OPT int oxceGeoSlowdownFactor;
OPT bool oxceGeoShowScoreInsteadOfFunds;
OPT bool oxceGeoEnableTrainingIndicator;
OPT bool oxceGeoSuppressRedundantHKAlert;
OPT bool oxceGeoSuppressLandingWithoutEquipment;
OPT bool oxceGeoGoToNearestBase;
OPT bool oxceGeoSortCraftByDistanceToTarget;

OPT int oxceBaseInfoDefenseScaleMultiplier;
OPT bool oxceBaseSoldierTransformationShowOnlyEligible;
OPT bool oxceBaseFilterResearchable;
OPT bool oxceBaseResearchReorder;
OPT bool oxceBaseManufactureFallbackButton;
OPT bool oxceBaseManufactureInfinityButton;
OPT bool oxceBaseTouchButtons;

OPT bool oxceDisableAlienInventory;
OPT bool oxceDisableHitLog;
OPT bool oxceDisableInventoryTuCost;
OPT bool oxceDisableProductionDependencyTree;
OPT bool oxceDisableStatsForNerds;
OPT bool oxceDisableTechTreeViewer;

// 0 = not persisted; 1 = persisted per battle; 2 = persisted per campaign
OPT int oxceTogglePersonalLightType;
OPT int oxceToggleNightVisionType;
OPT int oxceToggleBrightnessType;

OPT bool oxceShowBurningAsWounded;
OPT bool oxceDisableInfoOnThrowCursor;
OPT bool oxceSwapDontReselectActions;
OPT bool oxceEnableUnitResponseSounds;
OPT int oxceHiddenMovementBackgroundChangeFrequency;
OPT bool oxceInventoryShowUnitSlot;
OPT bool oxceReplaceNotesLink;

OPT bool oxceInventorySplitScrollButton;
OPT bool oxceInventoryDropItemOverPaperdoll;
OPT bool oxceInventoryUnloadFixedWeapons;

OPT int oxceMaxEquipmentLayoutTemplates;

// Flags and other stuff that don't need OptionInfo's.
OPT bool mute, reload, newOpenGL, newScaleFilter, newHQXFilter, newXBRZFilter, newRootWindowedMode, newFullscreen, newAllowResize, newBorderless;
OPT int newDisplayWidth, newDisplayHeight, newBattlescapeScale, newGeoscapeScale, newWindowedModePositionX, newWindowedModePositionY;
OPT std::string newOpenGLShader;
OPT std::vector< std::pair<std::string, bool> > mods; // ordered list of available mods (lowest priority to highest) and whether they are active
OPT SoundFormat currentSound;

OPT int battleXcomSpeedOrig;
OPT int battleAlienSpeedOrig;
