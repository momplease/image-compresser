#ifndef ICOMPRESSIBLE_H
#define ICOMPRESSIBLE_H

#include <QtGlobal>

class ICompressibleImage
{
public:
    ICompressibleImage() : m_compressed(false) {}
    virtual ~ICompressibleImage(){}
    virtual void setCompressed(bool compressed) = 0;
    virtual bool isCompressed() = 0;
    virtual bool isAllowedImage() = 0;
    virtual qint64 getSizeInBytes() const = 0;
    virtual QString getAbsoluteImagePath() const = 0;
    virtual QString getImageExtension() const = 0;
    virtual QString getImageName() const = 0; //might be needed soon
protected:
    bool m_compressed;
};



#endif // ICOMPRESSIBLE_H
