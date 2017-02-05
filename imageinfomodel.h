#ifndef IMAGEINFOMODEL_H
#define IMAGEINFOMODEL_H

#include <QAbstractTableModel>
#include <QItemDelegate>

class QModelIndex;
class QVariant;
class ImageInfo;

typedef std::vector<ImageInfo*> ImageInfoContainer;

class ImageInfoModel : public QAbstractTableModel, public QItemDelegate
{
public:
    ImageInfoModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    ImageInfoContainer const& getFiles() const;
    void addFiles(const QStringList &filenames);
private:
    ImageInfoContainer _files;
};

#endif // IMAGEINFOMODEL_H
