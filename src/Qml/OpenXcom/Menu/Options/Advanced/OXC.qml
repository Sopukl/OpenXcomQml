import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.Menu.Controls 1.0 as XC
import "../Controls"

Flickable {
    id: ctrl
    flickableDirection: Flickable.VerticalFlick
    contentHeight: col.height
    clip: true

    Column {
        id: col
        width: ctrl.width
        spacing: 2
        XC.GroupBox {
            title: "General"
            width: col.width
            Column {
                width: col.width
                spacing: 1
                BoolOption {
                    text: "Play intro"
                    key: "playIntro"
                }
                BoolOption {
                    text: "Autosave"
                    key: "autosave"
                }
                IntOption {
                    width: col.width
                    text: "Autosave Frequency"
                    key: "autosaveFrequency"
                    min: 1
                    max: 5
                }
                BoolOption {
                    text: "Save scumming"
                    key: "newSeedOnLoad"
                }
                BoolOption {
                    text: "Lazy loading"
                    key: "lazyLoadResources"
                }
                IntOption {
                    width: col.width
                    text: "Mouse wheel scroll speed"
                    key: "mousewheelSpeed"
                    min: 1
                    max: 7
                }
                IntOption {
                    width: col.width
                    text: "Change values with mouse wheel"
                    key: "changeValueByMouseWheel"
                    min: 0
                    max: 100
                    step: 10
                }
                IntOption {
                    width: col.width
                    text: "Fps limit"
                    key: "maxFPS"
                    min: 0
                    max: 120
                    step: 10
                }
                IntOption {
                    width: col.width
                    text: "Fps limit background"
                    key: "maxFPSInactive"
                    min: 0
                    max: 120
                    step: 10
                }
            }
        }
        XC.GroupBox {
            title: "Geoscape"
            width: col.width
            Column {
                spacing: 1
                width: col.width
                BoolOption {
                    text: "Invert drag scrolling"
                    key: "geoDragScrollInvert"
                }
                BoolOption {
                    text: "Agressive retalation"
                    key: "aggressiveRetaliation"
                }
                BoolOption {
                    text: "Custom initial base"
                    key: "customInitialBase"
                }
                BoolOption {
                    text: "Allow building queue"
                    key: "allowBuildingQueue"
                }
                BoolOption {
                    text: "Force craft launch"
                    key: "craftLaunchAlways"
                }
                BoolOption {
                    text: "Storage limits for recovered items"
                    key: "storageLimitsEnforced"
                }
                BoolOption {
                    text: "Live alien sale"
                    key: "canSellLiveAliens"
                }
                BoolOption {
                    text: "Psionic training at any time"
                    key: "anytimePsiTraining"
                }
                BoolOption {
                    text: "Realistic globe lighting"
                    key: "globeSeasons"
                }
                BoolOption {
                    text: "Psi-Strength evaluation"
                    key: "psiStrengthEval"
                }
                BoolOption {
                    text: "Airborne transfers"
                    key: "canTransferCraftsWhileAirborne"
                }
                BoolOption {
                    text: "Retain interrogated aliens"
                    key: "retainCorpses"
                }
                BoolOption {
                    text: "Field promotions"
                    key: "fieldPromotions"
                }
            }
        }
        XC.GroupBox {
            title: "Battlescape"
            Column {
                spacing: 1
                width: col.width
                BoolOption {
                    text: "Invert drag scrolling"
                    key: "battleDragScrollInvert"
                }
                BoolOption {
                    text: "Sneaky AI"
                    key: "sneakyAI"
                }
                BoolOption {
                    text: "Ufo extender accuracy"
                    key: "battleUFOExtenderAccuracy"
                }
                BoolOption {
                    text: "Inventory stats"
                    key: "showMoreStatsInInventoryView"
                }
                BoolOption {
                    text: "Enchanced soldier sprites"
                    key: "battleHairBleach"
                }
                BoolOption {
                    text: "Instant grenades"
                    key: "battleInstantGrenade"
                }
                BoolOption {
                    text: "Save pre-primed grenades"
                    key: "includePrimeStateInSavedLayout"
                }
                IntOption {
                    width: col.width
                    text: "Exposion height"
                    key: "battleExplosionHeight"
                    min: 0
                    max: 3
                    step: 1
                }
                BoolOption {
                    text: "Auto-end battle"
                    key: "battleAutoEnd"
                }
                BoolOption {
                    text: "Smooth bullet camera"
                    key: "battleSmoothCamera"
                }
                BoolOption {
                    text: "Disable auto-equip"
                    key: "disableAutoEquip"
                }
                BoolOption {
                    text: "Confirm fire mode"
                    key: "battleConfirmFireMode"
                }
                BoolOption {
                    text: "Alien weapon self-destruction"
                    key: "weaponSelfDestruction"
                }
                BoolOption {
                    text: "Alow psi-capture"
                    key: "allowPsionicCapture"
                }
                BoolOption {
                    text: "Alow psi-strength improvement"
                    key: "allowPsiStrengthImprovement"
                }
                BoolOption {
                    text: "Alternate movement methods"
                    key: "strafe"
                }
                BoolOption {
                    text: "Override line of fire"
                    key: "forceFire"
                }
                BoolOption {
                    text: "Skip\"Next Turn\" screen"
                    key: "skipNextTurnScreen"
                }
                BoolOption {
                    text: "Suppress panic messages for aliens"
                    key: "noAlienPanicMessages"
                }
                BoolOption {
                    text: "Alien bleeding"
                    key: "alienBleeding"
                }
            }
        }
    }
}
