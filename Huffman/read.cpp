#include "read.h"

Read::Read( QString out )
{
    this->Name_out = out;
    Freq.insert( Freq.begin(), ASCII, 0 );
}
Read::Read( QString in, QString out )
{
    if( in.compare(out) )
        this->Dir = out;
    else
    {
        QDir dir(in);
        QString aux = dir.dirName();
        qDebug() << "Dir " << aux;
        qDebug() << "Todo " << in;
        in.remove( in.size()-aux.size(), aux.size() );
        qDebug() << "Apos " << in;
        this->Dir = in;
    }
}
bool Read::OpenFileCod(QString dir)
{
    QFile *File = new QFile(dir);
    if( !File->open(QIODevice::ReadOnly) )
    {
        qDebug() << "Arquivo Inexistente";
        return false;
    }
    QDir Dir(dir);
    this->Name = Dir.dirName();
    dir.remove( dir.size()-this->Name.size(), this->Name.size() );
    this->Dir = dir;
    if( !dir.compare(this->Name_out) )
    {
         Name_out = Dir.dirName();
         for (int i = Name_out.size()-1; i >= 0  ; --i)
         {
            if( !QString::compare(Name_out.at(i),"." ) )
            {
                Name_out.chop( Name_out.size() - i);
                Name_out += "huff";
            }
         }
    }
    while(!File->atEnd() )
    {
        QByteArray Part = File->read(1024);
        for (int i = 0;  i < Part.size() ; i++)
            ++Freq[ (uchar) Part.at(i) ];
    }
    File->close();
    free(File);
    return true;
}
QVector<long long> Read::GetFreq()  {    return Freq;   }
bool Read::CodeFile(QString dir, QHash<unsigned char, QVector<bool> > Code)
{
    this->FileBit.clear();
    this->FileByte.clear();
    this->Trash = 0;
    QFile *File = new QFile(dir);
    if( !File->open(QIODevice::ReadOnly) )
    {
        qDebug() << "Arquivo Inexistente";
        return false;
    }
    while(!File->atEnd() )
    {
        QByteArray Part = File->readLine(1024);
        for (int i = 0;  i < Part.size() ; i++)
            this->FileBit.operator +=( Code.value( (unsigned char) Part.at(i) ) );
        while( FileBit.size() >= 8 )
        {
            FileByte.push_back( 128*FileBit.at(0) + 64*FileBit.at(1) + 32*FileBit.at(2) + 16*FileBit.at(3) +
                                8*FileBit.at(4) + 4*FileBit.at(5) + 2*FileBit.at(6) + 1*FileBit.at(7)                   ) ;
            FileBit.erase(FileBit.begin(), FileBit.begin()+8);
        }
    }
    File->close();
    if( this->FileBit.size() )
    {
        this->Trash = 8 - this->FileBit.size();
        if( this->Trash )
        {
            qDebug() << "Tamanho do Lixo " << this->Trash ;
            for (int i = 0; i < this->Trash; ++i)
                this->FileBit.push_back(false);
            FileByte.push_back( 128*FileBit.at(0) + 64*FileBit.at(1) + 32*FileBit.at(2) + 16*FileBit.at(3) +
                                8*FileBit.at(4) + 4*FileBit.at(5) + 2*FileBit.at(6) + 1*FileBit.at(7)                   ) ;
            FileBit.erase(FileBit.begin(), FileBit.begin()+8);
        }
    }
    return true;
}
QVector<bool> Read::getFileCod() { return this->FileBit; }
void Read::Show_FileCod()
{
    qDebug() << "----------------------Arquivo codificado----------------------";
    for (int var = 0; var < FileBit.size() ; ++var)
        cout << FileBit.at(var) ? 1 : 0;
    cout << endl;
    qDebug() << "---------------------------FIM---------------------------";
}
void Read::Show_FileByte()
{
    qDebug() << "----------------------Arquivo em Byte----------------------";
    qDebug() << "Tamanho do Arquivo: " << FileByte.size();
    for (int var = 0; var < FileByte.size() ; ++var) {
        qDebug() << FileByte.at(var);
    }
    cout << endl;
    qDebug() << "---------------------------FIM---------------------------";
}
void Read::BuildFile(QByteArray Rep)
{
    this->FileOut.clear();
    FileOut.append( ((((this->Trash&0x07)<<5)&0xFF)|(Rep.size()>>8)&0xFF) );
    FileOut.append(Rep.size()&0xFF);
    FileOut.append(Name.size()&0xFF);
    qDebug() << "Lixo " << this->Trash;
    qDebug() << Name.size();
    FileOut.append(this->Name).append(Rep).append(FileByte);
    qDebug() << this->Name;
    qDebug() << this->Name_out;
    qDebug() << this->Dir;
    QFile NewFile( this->Name_out);
    if(!NewFile.open(QIODevice::WriteOnly)){
        qDebug() << "Ocorreu um erro ao abrir o arquivo da compressão.";
        exit(1);
    }
    NewFile.write(FileOut);
    NewFile.close();
}
void Read::BuildFile()
{
    QFile NewFile( this->Dir + this->Name );
    if(!NewFile.open(QIODevice::WriteOnly)){
        qDebug() << "Ocorreu um erro ao abrir o arquivo da descompressão.";
        exit(1);
    }
    NewFile.write(FileOut);
    NewFile.close();
}

char Read::Decode( Node* SubTree, int depth )
{
    if( SubTree->isLeaf() )
    {
        this->FileBit.erase( FileBit.begin() , FileBit.begin()+depth );
        return SubTree->getChar();
    }
    else
    {
        if( this->FileBit.at(depth) ) return Decode( SubTree->getNodeRight(), depth+1 );
        else return Decode( SubTree->getNodeLeft(), depth+1 );
    }
}

bool Read::OpenFileEnc(QString dir)
{
    this->FileBit.clear();
    this->FileOut.clear();
    QFile *File = new QFile(dir);
    if( !File->open(QIODevice::ReadOnly) )
    {
        qDebug() << "Nao abriu";
        return false;
    }
    //qDebug() << "inicio do arquivo";
    QByteArray Keys = File->read(3);
    this->Trash = uchar(Keys.at(0)&(0xE0))>>5;
    this->SRep = (uchar(Keys.at(0)&0x1F))<<8;
    this->SRep += uchar(Keys.at(1)&0xFF);
    this->SName = uchar(Keys.at(2)&0xFF);
    //qDebug() << "Pegou o cabeçalho";
    QByteArray RName = File->read(this->SName);
    //qDebug() << "Nome do arquivo";
    this->Name = RName;
    //qDebug() << this->Name;
    //qDebug() << "Representação";
    QByteArray RTree = File->read(this->SRep);
    //qDebug() << RTree;
    Tree *TreeEnc = new Tree(RTree);
    //qDebug() << "Construção da arvore";
    while(!File->atEnd() )
    {
        QByteArray Part = File->read(1024);
        for( int i = 0 ; i < Part.size() ; ++i )
            this->FileBit += Bytetobits( uchar(Part.at(i)) );
        while( this->FileBit.size() - this->Trash >= TreeEnc->GetMaxRep() )
            this->FileOut.append( (this->Decode(TreeEnc->getRoot())) );
    }
    qDebug() << "Leitura final do arquivo";
    qDebug() << this->Trash << "  " << FileBit.size();
    for (int i = 0; i < this->Trash; ++i)   FileBit.pop_back();
    qDebug() << "Tirando o lixo";
    while( FileBit.size() > 0)
        this->FileOut.append( this->Decode(TreeEnc->getRoot()) );
    qDebug() << "Decodificao final";
    return true;
}

QVector<bool> Read::Bytetobits(char Byte)
{
    QVector<bool> Bits(8);
    Bits[0] = Byte&(0x80);
    Bits[1] = Byte&(0x40);
    Bits[2] = Byte&(0x20);
    Bits[3] = Byte&(0x10);
    Bits[4] = Byte&(0x08);
    Bits[5] = Byte&(0x04);
    Bits[6] = Byte&(0x02);
    Bits[7] = Byte&(0x01);
    return Bits;
}
void Read::Show_FileOut()
{
    qDebug() << this->FileOut;
}
