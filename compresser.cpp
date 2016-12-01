#include "compresser.h"

Compresser::Compresser()
{
}

ICompressibleImage* Compresser::performCompression(ICompressibleImage &target){
    ICompressibleImage* compressionResult = nullptr;
    if(this->canCompressWith(target))
    {
        compressionResult = this->compress(target);
    }
    return compressionResult;
}

Compresser::~Compresser(){

}
