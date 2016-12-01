#ifndef TINIFYCOMPRESSER_H
#define TINIFYCOMPRESSER_H

#include "compresser.h"
#include <QNetworkAccessManager>

class TinifyCompresser : public Compresser
{
    enum HttpStatusCodes {
        Created = 201
    };

    Q_OBJECT

signals:
    void gotResult();
private slots:
    void replyFinished();
    void downloadFile();
public:
    TinifyCompresser(QString apiKey);
    virtual ~TinifyCompresser();
protected:
    bool canCompressWith(ICompressibleImage &imageInfo) override;
    ICompressibleImage* compress(ICompressibleImage &target) override;
private:
    QString getDownloadStringFromRawResponse(QByteArray rawResponse, QString protocoltype, QString extension);

    QNetworkAccessManager* m_manager;
    QNetworkRequest* m_request;
    QNetworkReply* m_postReply;
    QNetworkReply* m_getReply;
    QString m_apiKey;
    ICompressibleImage* m_imageToShrink;
};

#endif // TINIFYCOMPRESSER_H
