#pragma once
#include <QQuickImageProvider>

namespace OpenXcom
{
	class Surface;
	class Palette;

    class XcomImagesProvider: public QQuickImageProvider
    {
      public:
        XcomImagesProvider();

        QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
	  private:
		std::pair<QString, QString> parseUrl(const QString &id);
		std::pair<Surface*,QVector<QRgb>> getInterfaceData(QString id);
		std::pair<Surface*,QVector<QRgb>> getImageData(QString id);
		QVector<QRgb> colorsFromPalette(QString paletteName);
	};
}
