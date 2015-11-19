#include "huffman.h"
#include <QChar>

Huffman::Huffman()
{

}

void Huffman::Huff(QString in, QString out)
{
    qDebug() << "Iniciou o processo de compressão!";
    qDebug() << in;
    qDebug() << out;
    Read *Input = new Read(out);
    if( Input->OpenFileCod(in) )
    {
        qDebug() << "Abriu o arquivo";
        Freq = Input->GetFreq();
        qDebug() << "Criando a lista";
        for (int i = 0; i < ASCII ; ++i)
                if( Freq[i] )
                    NList.insert( new Node( Freq[i] ,  i) );
        //NList.ShowList();
        qDebug() << "Criando a Arvore";
        Tree *HTree = new Tree(NList);
        qDebug() << "Arvore Criada";
        qDebug() << "Representacao";
        QVector<bool> Rep;
        HTree->builtRep(HTree->getRoot(), Rep);
        qDebug() << "Fez a reprentação e Codifição";
        //HTree->Show_Code();
        //HTree->Show_Represent();
        qDebug() << "Arquivo Codificado";
        Input->CodeFile(in,HTree->GetCoding());
        //Input->Show_FileByte();
        Input->BuildFile(HTree->getRepresent());
    }
    else
        qDebug() << "Não abriu o arquivo";
}
