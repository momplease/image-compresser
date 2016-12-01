#ifndef PNGQUANTCOMPRESSER_H
#define PNGQUANTCOMPRESSER_H

#include "compresser.h"

class PngquantCompresser : public Compresser
{
public:
    PngquantCompresser();
    virtual ~PngquantCompresser();
protected:
    bool canCompressWith(ICompressible &target) override;
    int compress(ICompressible &target) override;
};

#endif // PNGQUANTCOMPRESSER_H
