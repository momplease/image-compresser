#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <QFileInfo>
#include "icompressible.h"

class ImageInfo : public QFileInfo, public ICompressibleImage
{

public:
    ImageInfo(const QString &file, bool compressed = false);
    virtual ~ImageInfo();
    void setCompressed(bool compressed) override;
    bool isCompressed() override;
    bool isAllowedImage() override;
    qint64 getSizeInBytes() const override;
    QString getAbsoluteImagePath() const override;
    QString getImageExtension() const override;
    QString getImageName() const override;
};

#endif // IMAGEINFO_H
