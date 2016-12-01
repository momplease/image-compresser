#ifndef COMPRESSER_H
#define COMPRESSER_H

#include <QString>
#include <QObject>
#include "icompressible.h"


class Compresser : public QObject
{
    Q_OBJECT
public:
    enum CompressionResult {
        Compressed = 1,
        NotCompressed = -1
    };

    Compresser();
    virtual ~Compresser();
    virtual ICompressibleImage* performCompression(ICompressibleImage &target);
protected:
    virtual bool canCompressWith(ICompressibleImage &target) = 0;
    virtual ICompressibleImage* compress(ICompressibleImage &target) = 0;
};

#endif // COMPRESSER_H
