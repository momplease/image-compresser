#include "mainwindowcontroller.h"
#include "ui_mainwindow.h"
#include "tinifycompresser.h"
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QPointer>
#include "imageinfomodel.h"

MainWindowController::MainWindowController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _imageInfoData(new ImageInfoModel())
{
    this->initUI();
    this->initAPI();
    connect(ui->selectButton, SIGNAL(clicked()), this, SLOT(onSelectButtonClick()));
    connect(ui->compressButton, SIGNAL(clicked()), this, SLOT(onCompressButtonClick()));
    connect(ui->apiKeyOK, SIGNAL(clicked()), this, SLOT(onOKButtonClick()));
    qDebug("init app");
}

MainWindowController::~MainWindowController()
{
    delete ui;
}
////////////////////////////////////////////////////////////////////////////////////////////////

ImageInfoModel * MainWindowController::getModel() const {
    return this->_imageInfoData;
}



void MainWindowController::initAPI() {
    m_apiKey = getSavedApiKey();

    if (m_apiKey == QString::null){
        QPointer<QPropertyAnimation> animation = new QPropertyAnimation(ui->frame, "geometry");
        animation->setDuration(250);
        animation->setStartValue(QRect(ui->frame->geometry().left(),
                                   ui->frame->geometry().top() - ui->frame->geometry().height() - 10,
                                   ui->frame->geometry().width(),
                                   ui->frame->geometry().height()));

        animation->setEndValue(ui->frame->geometry());
        animation->start();


        ui->compressButton->setEnabled(false);
    } else {
        ui->frame->hide();
    }


}

void MainWindowController::initUI(){
    ui->setupUi(this);
    this->ui->imageInfoView->setModel(this->getModel());

    this->ui->compressProgressBar->reset();
}

void MainWindowController::onSelectButtonClick(){
    const QStringList selectedFiles = selectFiles();
    this->getModel()->addFiles(selectedFiles);
    this->ui->imageInfoView->viewport()->repaint();
    //this->updateImageInfoHolderViewWithNewFiles(selectedFiles);
}

const QStringList MainWindowController::selectFiles(){
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    const QStringList filenames = QFileDialog::getOpenFileNames(
                this,
                "Select file",
                desktopPath,
                "Images (*.png *.jpg)"
                );
    return filenames;
}

void MainWindowController::addFiles(const QStringList &filenames){

}

bool MainWindowController::imageInfoHolderViewContainsElement(const QString &elementText){
    /*int rowCount = ui->imageInfoHolder->rowCount();
    int columnIndex = 0;
    bool result = false;
    for(int i = 0; i < rowCount; ++i){
       if(ui->imageInfoHolder->item(i, columnIndex)->text() == (elementText)){
            result = true;
            break;
        }
    }
    return result;*/
    return true;
}

void MainWindowController::updateImageInfoHolderViewWithNewFiles(const QStringList &filenames){
        /*QTableWidgetItem *item;
        int iCounter = ui->imageInfoHolder->rowCount();
        int colomnCounter = 0;
        for(int i = 0; i < filenames.count(); ++i){
            colomnCounter = 0;
            if(!imageInfoHolderViewContainsElement(filenames[i])){
                ui->imageInfoHolder->insertRow(iCounter);

                item = new QTableWidgetItem(m_files[iCounter].absoluteFilePath(), QTableWidgetItem::ItemType::Type);
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->imageInfoHolder->setItem(iCounter, colomnCounter++, item);

                item = new QTableWidgetItem(m_files[iCounter].completeBaseName(), QTableWidgetItem::ItemType::Type);
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->imageInfoHolder->setItem(iCounter, colomnCounter++, item);

                item = new QTableWidgetItem(QString::number(m_files[iCounter].size()), QTableWidgetItem::ItemType::Type);
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->imageInfoHolder->setItem(iCounter, colomnCounter++, item);

                item = new QTableWidgetItem(m_files[iCounter].isCompressed() ? "YES" : "NO", QTableWidgetItem::ItemType::Type);
                m_files[iCounter].isCompressed() ? item->setTextColor(QColor(0, 255, 0)) : item->setTextColor(QColor(255, 0, 0));
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->imageInfoHolder->setItem(iCounter++, colomnCounter++, item);

            }

       }*/
}


void MainWindowController::onCompressButtonClick() { //update
    /*qDebug("compress button");
    ui->compressButton->setEnabled(false);
    ui->compressButton->setText("Compressing...");

    QScopedPointer<Compresser> compressManager(new TinifyCompresser(this->m_apiKey));

    ICompressibleImage* result;
    for(ulong i = 0; i < m_files.size(); ++i){
        if (!m_files[i].isCompressed()){
            result = compressManager->performCompression(m_files[i]);
            m_files[i] = ImageInfo(result->getAbsoluteImagePath(), result->isCompressed());
            updateImageInfoHolderViewCompressionInfo();
        }
    }

    ui->compressButton->setEnabled(true);
    ui->compressButton->setText("Compress");
    qDebug() << "ended";*/
}


void MainWindowController::updateImageInfoHolderViewCompressionInfo() {
    /*int sizeColumn = 2;
    int compressionColumn = 3;
    QTableWidgetItem * item;
    for(ulong i = 0; i < m_files.size(); ++i){
        item = this->ui->imageInfoHolder->item(i, sizeColumn);
        item->setText(QString::number(m_files[i].size()));

        item = this->ui->imageInfoHolder->item(i, compressionColumn);
        item->setText(m_files[i].isCompressed() ? "YES":"NO");
        m_files[i].isCompressed() ? item->setTextColor(QColor(0, 255, 0)) : item->setTextColor(QColor(255, 0, 0));
    }*/
}


void MainWindowController::onOKButtonClick() {
    QString holderText = ui->apiKeyHolder->text();
    if (holderText == "") {
        QScopedPointer<QMessageBox> warning(new QMessageBox(QMessageBox::Icon::Warning,
                                                              "API key checking",
                                                              "You do not enter anything"));
        warning->exec();
    } else {
        this->m_apiKey = holderText;

        QPointer<QPropertyAnimation> animation = new QPropertyAnimation(ui->frame, "geometry");
        animation->setDuration(250);
        animation->setEndValue(QRect(ui->frame->geometry().left(),
                                   ui->frame->geometry().top() - ui->frame->geometry().height() - 10,
                                   ui->frame->geometry().width(),
                                   ui->frame->geometry().height()));

        animation->setStartValue(ui->frame->geometry());
        animation->start();

        ui->compressButton->setEnabled(true);
    }
}



QString MainWindowController::getSavedApiKey() {
    QString result = QString::null;


    return result;
}

int MainWindowController::saveApiKeyToFile() {
    int result = SaveFailed;


    return result;
}
