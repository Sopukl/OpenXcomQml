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
		auto sl = id.split('#');
		auto mod = game.mod();

		auto imgName = sl.at(0);
		auto paletteName = (sl.size() == 2)?sl.at(1)
										   :QString("PAL_GEOSCAPE");

		auto& bgImageName = mod->getInterface(imgName.toStdString())
							   ->getBackgroundImage(mod, game.savedGame());
		auto* bgImage = mod->getSurface(bgImageName);

		auto colors = mod->getPalette(paletteName.toStdString())->getColors();

		QImage image(
			bgImage->getBuffer(),
			bgImage->getWidth(),
			bgImage->getHeight(),
			bgImage->getPitch(),
			bgImage->getSurface()->format->BitsPerPixel == 32 ?
				QImage::Format_ARGB32:
				QImage::Format_Indexed8
			);

		if (bgImage->getSurface()->format->BitsPerPixel == 8) {
			QVector<QRgb> colorTable(256);
			for (int i = 0; i < 256; i++) {
				colorTable[i] = qRgb(colors[i].r,
									 colors[i].g,
									 colors[i].b);
			}
			image.setColorTable(colorTable);
		}

		if(size)
			*size = QSize(320, 240);
		return image.copy();
	}
}
