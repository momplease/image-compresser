#include "imageinfo.h"

ImageInfo::ImageInfo(const QString &file, bool compressed): QFileInfo(file)
{
   this->m_compressed = compressed;
}

ImageInfo::~ImageInfo(){

}

void ImageInfo::setCompressed(bool compressed){
     m_compressed = compressed;
}

bool ImageInfo::isCompressed(){
    return m_compressed;
}

bool ImageInfo::isAllowedImage(){
    bool result = false;
    if(this->suffix() == QString("png") || this->suffix() == QString("jpg") || this->suffix() == QString("jpeg"))
            result = true;
    return result;
}
qint64 ImageInfo::getSizeInBytes() const{
    return this->size();
}
QString ImageInfo::getAbsoluteImagePath() const{
    return this->absoluteFilePath();
}

QString ImageInfo::getImageExtension() const {
    return this->suffix();
}

QString ImageInfo::getImageName() const {
    return this->baseName();
}
