#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include "imageinfo.h"
class ImageInfoModel;

enum saveResult {
    SaveSucces,
    SaveFailed
};

namespace Ui {
class MainWindow;
}

class MainWindowController : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowController(QWidget *parent = 0);
    ~MainWindowController();

    ImageInfoModel * getModel() const;
private slots:
    void onSelectButtonClick();
    void onCompressButtonClick();
    void onOKButtonClick();
private:
    void initUI();
    void initAPI();

    const QStringList selectFiles(); 
    void addFiles(const QStringList &filenames);

    void updateImageInfoHolderViewWithNewFiles(const QStringList &filenames);
    void updateImageInfoHolderViewCompressionInfo();

    bool imageInfoHolderViewContainsElement(const QString &element);

    QString getSavedApiKey();
    int saveApiKeyToFile();

    Ui::MainWindow *ui;
    ImageInfoModel * _imageInfoData;

    QString m_apiKey;
};

#endif // MAINWINDOW_H
