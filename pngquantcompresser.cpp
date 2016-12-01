#include "pngquantcompresser.h"
#include "libimagequant.h"
#include "libpng16/png.h"
#include <QImage>
#include <QProcess>

PngquantCompresser::PngquantCompresser() : Compresser() {
}

PngquantCompresser::~PngquantCompresser() {

}

bool PngquantCompresser::canCompressWith(ICompressible &target) {
    bool result = false;
    if(!target.isCompressed() && target.isAllowedImage())
    {
        result = true;
    }
    return result;
}
int PngquantCompresser::compress(ICompressible &target) {
    int compressionResult = NotCompressed;
    //TODO: main compression logic

    /*QImage targetAsImage(target.getAbsoluteFilePath()); //TODO: understand what is bitmap in liq_image_create_rgba

    liq_attr * attr = liq_attr_create();
    liq_image *image = liq_image_create_rgba(attr, targetAsImage.bits(), targetAsImage.width(), targetAsImage.height(), 0);
    liq_result *result = liq_quantize_image(attr, image);
    const liq_palette *pal = liq_get_palette(result);

    if ( result ) {
        int size = targetAsImage.width() * targetAsImage.height();
        liq_write_remapped_image(result, image, targetAsImage.bits(), size);
    }

    liq_attr_destroy(attr);
    liq_image_destroy(image);
    liq_result_destroy(result);

    QProcess compressionCommandLineUtility;
    QStringList arguments;
    arguments << target.getAbsoluteFilePath();
    compressionCommandLineUtility.start(":/new/pngquant", arguments);
    if(compressionCommandLineUtility.waitForStarted()){
        bool processResult = compressionCommandLineUtility.waitForFinished();
        processResult ? compressionResult = COMPRESSED : compressionResult = NOT_COMPRESSED;
    }*/
    return compressionResult;
}
