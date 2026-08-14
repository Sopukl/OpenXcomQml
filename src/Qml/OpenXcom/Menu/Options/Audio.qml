import QtQuick
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC
import "." as This
This.Page {
    title: "Audio"
    Column
    {
        x: 2
        spacing: 2
        XC.GroupBox {
            title: "Music volume"
            width: 110
            XC.Slider {
                width: parent.width
                from: 0
                to: 128
                value: Options1.musicVolume
                onValueChanged: Options1.musicVolume = value
            }
        }
        XC.GroupBox {
            title: "SFX volume"
            width: 110
            XC.Slider {
                width: parent.width
                from: 0
                to: 128
                value: Options1.soundVolume
                onValueChanged: Options1.soundVolume = value
            }
        }
        XC.GroupBox {
            title: "UI volume"
            width: 110
            XC.Slider {
                width: parent.width
                from: 0
                to: 128
                value: Options1.uiVolume
                onValueChanged: Options1.uiVolume = value
            }
        }
        XC.GroupBox {
            title: "Sound options"
            width: 110
            XC.CheckBox {
                text: "Background mute"
                checked: Options1.backgroundMute
                onClicked: Options1.backgroundMute = checked
            }
        }
    }
    Column
    {
        anchors{
            right: parent.right
            rightMargin: 2
        }
        spacing: 2
        XC.GroupBox {
            title: "Video format"
            width: 110
            XC.ComboBox {
                width: parent.width
                model: [{text: "ANIMATION", value: Options1.VIDEO_FMV},
                        {text: "SLIDE",     value: Options1.VIDEO_SLIDE}]

                currentIndex: model.findIndex(
                        e=>e.value === Options1.preferredVideo)

                onActivated: Options1.preferredVideo = model[currentIndex].value
            }
        }
        XC.GroupBox {
            title: "Music format"
            width: 110
            XC.ComboBox {
                width: parent.width
                model: [{text: "AUTO",  value: Options1.MUSIC_AUTO},
                        {text: "FLAC",  value: Options1.MUSIC_FLAC},
                        {text: "OGG",   value: Options1.MUSIC_OGG},
                        {text: "MP3",   value: Options1.MUSIC_MP3},
                        {text: "MOD",   value: Options1.MUSIC_MOD},
                        {text: "WAV",   value: Options1.MUSIC_WAV},
                        {text: "Adlib", value: Options1.MUSIC_ADLIB},
                        {text: "GM",    value: Options1.MUSIC_GM},
                        {text: "MIDI",  value: Options1.MUSIC_MIDI}]

                currentIndex: model.findIndex(
                        e=>e.value === Options1.preferredMusic)

                onActivated: Options1.preferredMusic = model[currentIndex].value
            }
        }
        XC.GroupBox {
            title: "SFX format"
            width: 110
            XC.ComboBox {
                width: parent.width
                model: [{text: "AUTO", value: Options1.SOUND_AUTO},
                        {text: "1.0", value: Options1.SOUND_10},
                        {text: "1.4", value: Options1.SOUND_14}]

                currentIndex: model.findIndex(
                        e=>e.value === Options1.preferredSound)

                onActivated: Options1.preferredSound = model[currentIndex].value
            }
        }
    }
}
