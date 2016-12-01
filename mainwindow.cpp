#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinifycompresser.h"
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QPointer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->initUI();
    this->initAPI();
    connect(ui->selectButton, SIGNAL(clicked()), this, SLOT(onSelectButtonClick()));
    connect(ui->compressButton, SIGNAL(clicked()), this, SLOT(onCompressButtonClick()));
    connect(ui->apiKeyOK, SIGNAL(clicked()), this, SLOT(onOKButtonClick()));
    qDebug("init app");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAPI() {
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

void MainWindow::initUI(){
    ui->setupUi(this);
    this->initImageInfoHolderView();
    this->ui->compressProgressBar->reset();
}

void MainWindow::initImageInfoHolderView(){
    ui->imageInfoHolder->setColumnCount(4);
    ui->imageInfoHolder->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
    ui->imageInfoHolder->horizontalHeader()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    int fullpathSectionWidth = ui->imageInfoHolder->width() * 0.4;
    int filenameSectionWidth = ui->imageInfoHolder->width() * 0.3;
    int sizeSectionWidth = ui->imageInfoHolder->width() * 0.15;
    int compressedSectionWidth = ui->imageInfoHolder->width() * 0.15;

    ui->imageInfoHolder->setColumnWidth(0, fullpathSectionWidth);
    ui->imageInfoHolder->setColumnWidth(1, filenameSectionWidth);
    ui->imageInfoHolder->setColumnWidth(2, sizeSectionWidth);
    ui->imageInfoHolder->setColumnWidth(3, compressedSectionWidth);

    QStringList headerLables;
    headerLables << "Full path to file" << "File name" << "Size" << "Compressed";
    ui->imageInfoHolder->setHorizontalHeaderLabels(headerLables);
}

void MainWindow::onSelectButtonClick(){
    const QStringList selectedFiles = selectFiles();
    this->addFiles(selectedFiles);
    this->updateImageInfoHolderViewWithNewFiles(selectedFiles);
}

const QStringList MainWindow::selectFiles(){
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    const QStringList filenames = QFileDialog::getOpenFileNames(
                this,
                "Select file",
                desktopPath,
                "Images (*.png *.jpg)"
                );
    return filenames;
}

void MainWindow::addFiles(const QStringList &filenames){
    for(int i = 0; i < filenames.count(); ++i){
        if(std::find(m_files.begin(), m_files.end(), ImageInfo(filenames.at(i))) == m_files.end()){
            m_files.push_back(ImageInfo(filenames.at(i)));
        }
    }
}

bool MainWindow::imageInfoHolderViewContainsElement(const QString &elementText){
    int rowCount = ui->imageInfoHolder->rowCount();
    int columnIndex = 0;
    bool result = false;
    for(int i = 0; i < rowCount; ++i){
       if(ui->imageInfoHolder->item(i, columnIndex)->text() == (elementText)){
            result = true;
            break;
        }
    }
    return result;
}

void MainWindow::updateImageInfoHolderViewWithNewFiles(const QStringList &filenames){
        QTableWidgetItem *item;
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

       }
}


void MainWindow::onCompressButtonClick() { //update
    qDebug("compress button");
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
    qDebug() << "ended";
}


void MainWindow::updateImageInfoHolderViewCompressionInfo() {
    int sizeColumn = 2;
    int compressionColumn = 3;
    QTableWidgetItem * item;
    for(ulong i = 0; i < m_files.size(); ++i){
        item = this->ui->imageInfoHolder->item(i, sizeColumn);
        item->setText(QString::number(m_files[i].size()));

        item = this->ui->imageInfoHolder->item(i, compressionColumn);
        item->setText(m_files[i].isCompressed() ? "YES":"NO");
        m_files[i].isCompressed() ? item->setTextColor(QColor(0, 255, 0)) : item->setTextColor(QColor(255, 0, 0));
    }
}


void MainWindow::onOKButtonClick() {
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



QString MainWindow::getSavedApiKey() {
    QString result = QString::null;


    return result;
}

int MainWindow::saveApiKeyToFile() {
    int result = SaveFailed;


    return result;
}
