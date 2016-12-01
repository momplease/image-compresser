#ifndef LSTINIFYCOMPRESSERVIAPYTHON_H
#define LSTINIFYCOMPRESSERVIAPYTHON_H

#include "lstinifycompresser.h"

class LSTinifyCompresserViaPython : public LSTinifyCompresser
{
public:
    LSTinifyCompresserViaPython();
    virtual ~LSTinifyCompresserViaPython();
protected:
    int compress(LSImageInfo &imageInfo) override;
    bool checkTinifyConnection() override;
};

#endif // LSTINIFYCOMPRESSERVIAPYTHON_H
