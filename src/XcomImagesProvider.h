#pragma once
#include <QQuickImageProvider>

namespace OpenXcom
{
    class XcomImagesProvider: public QQuickImageProvider
    {
      public:
        XcomImagesProvider();

        QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    };
}
