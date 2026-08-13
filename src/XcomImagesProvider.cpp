#include "XcomImagesProvider.h"
#include "Engine/Game.h"
#include "Engine/Surface.h"
#include "Engine/Palette.h"
#include "Mod/Mod.h"
#include "Mod/RuleInterface.h"
namespace OpenXcom
{
    XcomImagesProvider::XcomImagesProvider(): QQuickImageProvider(Image)
    {
    }

	QImage XcomImagesProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
	{
		QString url = id;
		auto [surface, colorTable] = (url.startsWith(u"Interface/"))
			?getInterfaceData(url.remove(0, 10))
			:getImageData(url);


		if(surface)
		{
			QImage image(
				surface->getBuffer(),
				surface->getWidth(),
				surface->getHeight(),
				surface->getPitch(),
				surface->getSurface()->format->BitsPerPixel == 32 ?
					QImage::Format_ARGB32:
					QImage::Format_Indexed8
				);

			if (surface->getSurface()->format->BitsPerPixel == 8)
			{
				image.setColorTable(colorTable);
			}

			if(size)
				*size = QSize(320, 240);
			return image.copy();
		}
		else
		{
			return {};
		}
	}

	std::pair<QString, QString> OpenXcom::XcomImagesProvider::parseUrl(const QString &id)
	{
		QString surfaceName, paletteName;
		auto sl = id.split('#');
		surfaceName = sl.at(0);
		paletteName = (sl.size() == 2)
						?sl.at(1)
						:QString(u"PAL_GEOSCAPE");

		return {surfaceName, paletteName};
	}

	std::pair<Surface *, QVector<QRgb>> XcomImagesProvider::getImageData(QString id)
	{
		auto mod = game.mod();
		auto [surfaceName, paletteName] = parseUrl(id);

		return {mod->getSurface(surfaceName.toStdString(), false ),
				colorsFromPalette(paletteName)};
	}

	QVector<QRgb> OpenXcom::XcomImagesProvider::colorsFromPalette(QString paletteName)
	{
		QVector<QRgb> colors;

		auto mod = game.mod();
		auto sl = paletteName.split(':');

		if(auto palette = mod->getPalette(sl.at(0).toStdString(), false))
		{
			//fill default colors from palette
			colors.resize(256);
			auto sdlColors = palette->getColors();
			for (int i = 0; i < 256; i++)
			{
				colors[i] = qRgb(sdlColors[i].r,
								 sdlColors[i].g,
								 sdlColors[i].b);
			}
			if(sl.size() == 2)
			{
				//override colors from palette BACKPALS.DAT + offset
				bool isDigit = false;
				if(int pIdx = sl.at(1).toInt(&isDigit); isDigit == true)
				{
					if(auto backPals = mod->getPalette("BACKPALS.DAT"))
					{
						auto bpColors = backPals->getColors(Palette::blockOffset(pIdx));
						for(auto i= 0; i<16; i++)
						{
							colors[Palette::backPos + i] = qRgb(bpColors[i].r,
																bpColors[i].g,
																bpColors[i].b);
						}
					}
				}
			}
		}

		return colors;
	}

	std::pair<Surface*, QVector<QRgb>> OpenXcom::XcomImagesProvider::getInterfaceData(QString id)
	{
		std::pair<Surface*, QVector<QRgb>> result;

		auto mod = game.mod();
		auto [surfaceName, paletteName] = parseUrl(id);

		if(auto* ruleInterface = mod->getInterface(surfaceName.toStdString(), false))
		{
			if(auto bgImageName = ruleInterface->getBackgroundImage(mod, game.savedGame());
				   !bgImageName.empty())
				result.first = mod->getSurface(bgImageName);
		}

		result.second = colorsFromPalette(paletteName);


		return result;
	}
}
