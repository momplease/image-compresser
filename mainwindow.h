#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include "imageinfo.h"

enum saveResult {
    SaveSucces,
    SaveFailed
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void onSelectButtonClick();
    void onCompressButtonClick();
    void onOKButtonClick();
private:
    void initUI();
    void initImageInfoHolderView();
    void initAPI();

    const QStringList selectFiles(); 
    void addFiles(const QStringList &filenames);

    void updateImageInfoHolderViewWithNewFiles(const QStringList &filenames);
    void updateImageInfoHolderViewCompressionInfo();

    bool imageInfoHolderViewContainsElement(const QString &element);

    QString getSavedApiKey();
    int saveApiKeyToFile();

    Ui::MainWindow *ui;

    std::vector<ImageInfo> m_files;
    QString m_apiKey;
};

#endif // MAINWINDOW_H
