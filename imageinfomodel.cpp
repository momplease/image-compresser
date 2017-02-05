#include "imageinfomodel.h"
#include <QModelIndex>
#include <QVariant>
#include <vector>
#include "imageinfo.h"

ImageInfoModel::ImageInfoModel() {

}

ImageInfoContainer const& ImageInfoModel::getFiles() const {
    return _files;
}


void ImageInfoModel::addFiles(const QStringList &filenames) {
    beginResetModel();
    ImageInfo *objectToFind;
    for(int i = 0; i < filenames.count(); ++i) {
        objectToFind = new ImageInfo(filenames.at(i));
        if(std::find(_files.begin(), _files.end(), objectToFind) == _files.end()) {
            _files.push_back(objectToFind);

        } else {
            delete objectToFind;
        }
    }
    endResetModel();
}



//QAbstractTableModel methods
#pragma mark - QAbstractTableModel methods
int ImageInfoModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return static_cast<int>(this->getFiles().size());
}

int ImageInfoModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 1;
}

QVariant ImageInfoModel::data(const QModelIndex &index, int role) const {
    return QVariant(getFiles()[index.row()]->getImageName());
}

