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
		auto mod = game.getMod();
		auto& bgImageName = mod->getInterface(id.toStdString())->getBackgroundImage(mod, game.getSavedGame());
		auto* bgImage = mod->getSurface(bgImageName);

		auto colors = mod->getPalette("PAL_GEOSCAPE")->getColors();

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
