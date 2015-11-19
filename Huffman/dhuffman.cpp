#include "dhuffman.h"

DHuffman::DHuffman(){}

void DHuffman::DHuff( QString in, QString out){
    qDebug() << "Funfou!";
    Read *Input = new Read(in, out);
    if( Input->OpenFileEnc(in) ){
        qDebug() << "Abriu o arquivo";
        Input->BuildFile();
    }
    else
        qDebug() << "Não Abriu o arquivo";

}
