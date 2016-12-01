#include "tinifycompresser.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>
#include <QImage>
#include <imageinfo.h>

TinifyCompresser::TinifyCompresser(QString apiKey):Compresser(), m_imageToShrink(nullptr)
{
    this->m_manager = new QNetworkAccessManager(this);
    this->m_manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    this->m_apiKey = apiKey;
}

bool TinifyCompresser::canCompressWith(ICompressibleImage &target) {
    bool result = false;
    if(!target.isCompressed() && m_manager->networkAccessible() == QNetworkAccessManager::Accessible) {
        result = true;
    }
    return result;
}


ICompressibleImage* TinifyCompresser::compress(ICompressibleImage &target) {

    this->m_imageToShrink = &target;

    QFile *file = new QFile(target.getAbsoluteImagePath());
    file->open(QIODevice::ReadOnly);

    QUrl url("https://api.tinify.com/shrink");
    QNetworkRequest request(url);
    request.setRawHeader("Host", "api.tinify.com");
    request.setRawHeader("Authorization", "Basic " + m_apiKey.toUtf8().toBase64());

    QEventLoop requestLoop;
    connect(this, &TinifyCompresser::gotResult, &requestLoop, &QEventLoop::quit);

    m_postReply = m_manager->post(request, file);
    connect(m_postReply, &QNetworkReply::finished, this, &TinifyCompresser::replyFinished);
    //connect(m_reply, SIGNAL(finished()), &requestLoop, SLOT(quit()));
    requestLoop.exec();
    m_imageToShrink->setCompressed(true);
    return m_imageToShrink;
}

void TinifyCompresser::replyFinished() {
    if (m_postReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == HttpStatusCodes::Created)
    {
        QByteArray rawResponse = m_postReply->readAll();
        QString downloadString = this->getDownloadStringFromRawResponse(rawResponse, "https", m_imageToShrink->getImageExtension());
        qDebug() << downloadString;

        QUrl url(downloadString);
        QNetworkRequest request(url);

        QEventLoop downloadLoop;

        m_getReply = m_manager->get(request);

        connect(m_getReply, &QNetworkReply::finished, this, &TinifyCompresser::downloadFile);
        connect(this, &TinifyCompresser::gotResult, &downloadLoop, &QEventLoop::quit);
        downloadLoop.exec();

    }

}


void TinifyCompresser::downloadFile() {

    //QImage image = QImage::fromData(m_getReply->readAll(), m_imageToShrink->getImageExtension().toUtf8().data());
    //image.save(m_imageToShrink->getAbsoluteImagePath(), m_imageToShrink->getImageExtension().toUtf8().data());

    QScopedPointer<QFile> file(new QFile(m_imageToShrink->getAbsoluteImagePath()));
    if (file->open(QIODevice::WriteOnly)) {
        file->write(m_getReply->readAll());
        file->close();
    }


    emit gotResult();
}

QString TinifyCompresser::getDownloadStringFromRawResponse(QByteArray rawResponse, QString protocoltype, QString extension) {
    QString responseString(rawResponse);
    std::string imageExtension = "." + extension.toStdString();
    std::string protocolType = protocoltype.toStdString();
    std::string stdResponeString = responseString.toStdString();
    std::string result = "";

    auto indexDownloadStringStart = stdResponeString.find(protocolType);
    if(indexDownloadStringStart != std::string::npos) {
        auto indexDownloadStringEnd = stdResponeString.find(imageExtension);
        qDebug() << indexDownloadStringStart;
        qDebug() << indexDownloadStringEnd;

        if (indexDownloadStringEnd != std::string::npos) {
            result = std::string(stdResponeString.begin() + indexDownloadStringStart, stdResponeString.begin() + indexDownloadStringEnd + imageExtension.length());
        }
    }
    return QString::fromStdString(result);

}

TinifyCompresser::~TinifyCompresser(){

}
