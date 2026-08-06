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
                IntOption {
                    text: "Autosave slots"
                    key: "autosaveSlots"
                    min: 1
                    max: 10
                }
                IntOption {
                    text: "Autosave frequency (Geoscape)"
                    key: "oxceGeoAutosaveFrequency"
                    min: 1
                    max: 10
                }
                IntOption {
                    text: "Autosave flots (Geoscape)"
                    key: "oxceGeoAutosaveSlots"
                    min: 1
                    max: 10
                }
                BoolOption {
                    text: "Extended links"
                    key: "oxceLinks"
                }
                BoolOption {
                    text: "Highlight new topics"
                    key: "oxceHighlightNewTopics"
                }
                BoolOption {
                    text: "Show clip size in Ufopedia"
                    key: "oxcePediaShowClipSize"
                }
            }
        }
        XC.GroupBox {
            title: "Geoscape"
            width: col.width
            Column {
                spacing: 1
                width: col.width
                IntOption {
                    text: "Intercept table size"
                    key: "oxceInterceptTableSize"
                    min: 8
                    max: 80
                    step: 8
                }
                BoolOption {
                    text: "Show slacking indicator"
                    key: "oxceEnableSlackingIndicator"
                }
                IntOption {
                    text: "Show craft maintenance time"
                    key: "oxceInterceptGuiMaintenanceTime"
                    min: 0
                    max: 2
                }
                IntOption {
                    text: "Show estimated flilght duration"
                    key: "oxceShowETAMode"
                    min: 0
                    max: 2
                }
                BoolOption {
                    text: "UFO landing alert"
                    key: "oxceUfoLandingAlert"
                }
                BoolOption {
                    text: "Remember disabled craft weapons"
                    key: "oxceRememberDisabledCraftWeapons"
                }
                BoolOption {
                    text: "Instant item delivery in events"
                    key: "oxceGeoscapeEventsInstantDelivery"
                }
                BoolOption {
                    text: "Show base name in popups"
                    key: "oxceShowBaseNameInPopups"
                }
            }
        }
        XC.GroupBox {
            title: "Basescape"
            Column {
                spacing: 1
                width: col.width
                BoolOption {
                    text: "Alternate craft equipnemt management"
                    key: "oxceAlternateCraftEquipmentManagement"
                }
                BoolOption {
                    text: "Scale large bars in base info"
                    key: "oxceBaseInfoScaleEnabled"
                }
                IntOption {
                    text: "Research scroll speed"
                    key: "oxceResearchScrollSpeed"
                    min: 1
                    max: 10
                }
                IntOption {
                    text: "Research scroll speed (with Ctrl)"
                    key: "oxceResearchScrollSpeedWithCtrl"
                    min: 5
                    max: 50
                    step: 5
                }
                BoolOption {
                    text: "Alternate filter in Manufactufing"
                    key: "oxceManufactureFilterSuppliesOK"
                }
                IntOption {
                    text: "Manufacture scroll speed"
                    key: "oxceManufactureScrollSpeed"
                    min: 1
                    max: 10
                }
                IntOption {
                    text: "Manufacture scroll speed (with Ctrl)"
                    key: "oxceManufactureScrollSpeedWithCtrl"
                    min: 5
                    max: 50
                    step: 5
                }
                BoolOption {
                    text: "Include armor in personal equipment"
                    key: "oxcePersonalLayoutIncludingArmor"
                }
                BoolOption {
                    text: "Manual promotions"
                    key: "oxceManualPromotions"
                }
            }
        }
        XC.GroupBox {
            title: "Battlescape"
            Column {
                spacing: 1
                width: col.width
                IntOption {
                    text: "Wounded defend (if HP above x%)"
                    key: "oxceWoundedDefendBaseIf"
                    min: 0
                    max: 100
                    step: 10
                }
                BoolOption {
                    text: "Play breefing music longer"
                    key: "oxcePlayBriefingMusicDuringEquipment"
                }
                IntOption {
                    text: "Select Night Visin color"
                    key: "oxceNightVisionColor"
                    min: 1
                    max: 15
                }
                IntOption {
                    text: "Auto Night Visin threshold"
                    key: "oxceAutoNightVisionThreshold"
                    min: 1
                    max: 15
                }
                IntOption {
                    text: "Show accuracy on crosshair"
                    key: "oxceShowAccuracyOnCrosshair"
                    min: 0
                    max: 2
                }
                IntOption {
                    text: "Reaction fire threshold"
                    key: "oxceReactionFireThreshold"
                    min: 0
                    max: 100
                    step: 5
                }
                BoolOption {
                    text: "Auto-Sell manager"
                    key: "oxceAutoSell"
                }
                BoolOption {
                    text: "Automatic promotions"
                    key: "oxceAutomaticPromotions"
                }
                BoolOption {
                    text: "Off-center shooting"
                    key: "oxceEnableOffCentreShooting"
                }
                BoolOption {
                    text: "Uniform shooting spread"
                    key: "oxceUniformShootingSpread"
                }
                IntOption {
                    text: "Crashed/landed button"
                    key: "oxceCrashedOrLanded"
                    min: 0
                    max: 2
                }
            }
        }
    }
}
