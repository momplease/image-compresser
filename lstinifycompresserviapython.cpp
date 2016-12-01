#include "lstinifycompresserviapython.h"
#include "QApplication"

LSTinifyCompresserViaPython::LSTinifyCompresserViaPython():LSTinifyCompresser()
{

}

int LSTinifyCompresserViaPython::compress(LSImageInfo &imageInfo){
    int compressionResult = NOT_COMPRESSED;
    Py_Initialize();

    QString filePath = qApp->applicationDirPath() + "/init.py";
    PyObject* pyFileObject = PyFile_FromString(filePath.toLatin1().data(), "r");
    PyRun_SimpleFileEx(PyFile_AsFile(pyFileObject), filePath.toLatin1().data(), 1);

    const char modulename[] = "tinifyPythonCompressScript";

    PyObject * module = PyUnicode_FromString(modulename);
    PyObject *pModule = PyImport_Import(module); //YASS BISH WORKING
    pModule?"Yes":"no";
    if (pModule){
        qDebug("111blayt");
        PyObject * pFunc = PyObject_GetAttrString(pModule, "compress");
        if(pFunc && PyCallable_Check(pFunc))
        {
            qDebug("woahhgg");
            qDebug(QString::number(imageInfo.size()).toUtf8() + " before");
            char * c = imageInfo.absoluteFilePath().toLatin1().data();
            PyObject * result = PyObject_CallFunction(pFunc, "s", c);
            if(result){
                compressionResult = COMPRESSED;
                imageInfo = LSImageInfo(imageInfo.absoluteFilePath());
                imageInfo.setCompressed(SUCCESS) ;

            }else{
                compressionResult = NOT_COMPRESSED;
            }
            qDebug(QString::number(imageInfo.size()).toUtf8() + " after");
        }
    }

    Py_XDECREF(pModule);
    Py_Finalize();
    return compressionResult;
}

bool LSTinifyCompresserViaPython::checkTinifyConnection(){
    return true; //MAYBE UPGRADETED IN SOONER VERSIONS
}

LSTinifyCompresserViaPython::~LSTinifyCompresserViaPython()
{

}
