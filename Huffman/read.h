#ifndef READ_H
#define READ_H
#include <QByteArray>
#include <QBitArray>
#include <QVector>
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <iostream>
#include <tree.h>
using namespace std;
#define ASCII 256
#define LSB(x) (x&(-x))
class Read
{
    //Frequencia dos caracteres
    QVector<long long> Freq;
    // Arquivo em byte
    QByteArray FileByte;
    // Arquivo em bit
    QVector<bool> FileBit;
    // Tamanho do Lixo
    int Trash;
    // Nomes do Arquivo
    QString Name;
    QString Name_out;
    // Tamanho da Representação
    int SRep;
    // Diretorio
    QString Dir;
    // Representação
    QByteArray TreeRep;
    // Arquivo de Saida
    QByteArray FileOut;
    // Tamanho do Nome
    int SName;
public:
    // Construtor
    Read(QString out);
    // Construtor
    Read(QString in, QString out);
    // Abertura do arquivo
    bool OpenFileCod(QString dir);
    // Codificação do arquivo
    bool CodeFile(QString dir, QHash<unsigned char, QVector<bool> > Code);
    // Frequencias
    QVector<long long> GetFreq();
    // Retorna o arquivo codificado
    QVector<bool> getFileCod();
    // Mostra o arquivo em bits
    void Show_FileCod();
    // Mostra o arquivo em byte
    void Show_FileByte();
    // Mostra o arquivo de saida
    void Show_FileOut();
    // Escreve o arquivo codificado
    void BuildFile(QByteArray Rep);
    // Escreve o arquivo decodificado
    void BuildFile();
    // Abertura do Arquivo codificado
    bool OpenFileEnc(QString dir);
    // Decode
    char Decode( Node* SubTree, int depth = 0 );
    // Byte para bits
    QVector<bool> Bytetobits(char Byte);
    // Escreve o arquivo decodificado
};

#endif // READ_H
