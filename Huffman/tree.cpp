#include "tree.h"

Tree::Tree(List NList)
{

    qDebug() << "Iniciou a Arvore com a lista de tamanho: " <<NList.size();
    while( NList.size() > 1 )
    {
        //qDebug() << "Tamanho: " << NList.size();
        NList.Sort();
        Node *t1 = NList.getFirst();        NList.RemoveFirst();
        Node *t2 = NList.getFirst();        NList.RemoveFirst();
        NList.insert( new Node(t1->getFreq()+t2->getFreq() , t1 , t2 ) );
    }
    Root = NList.getFirst(); NList.RemoveFirst();
    if( !NList.size() ) qDebug() << "Lista vazio, Arvore completa";
}
Tree::Tree(QByteArray Rep)
{
        this->Code.clear();
        this->Mcode = 0;
        this->Rpt.clear();
        for (int i = 0; i < Rep.size() ; ++i)
        {
                if( Rep.at(i) == (uchar)('!')  )
                {
                    this->Rpt.push_back(Pub( Rep.at(i+1), true ));
                    ++i;
                }
                else
                {
                    if( Rep.at(i) == (uchar)('*')  ) this->Rpt.push_back( Pub( Rep.at(i), false ) );
                    else this->Rpt.push_back( Pub( Rep.at(i), true ) );
                }
        }
        QVector<bool> Enc; Enc.clear();
        this->Root = buildTree(Enc);
}
Node *Tree::buildTree( QVector<bool> Enc )
{
    Pub No = this->Rpt.at(0);   this->Rpt.pop_front();
    if( No.second )
    {
        this->Mcode = max( Mcode, Enc.size() );
        return new Node( (uchar)(No.first) );
    }
    else
    {
        Enc.push_back(false);
        Node *Left = buildTree( Enc ); Enc.pop_back();
        Enc.push_back(true);
        Node *Right = buildTree( Enc ); Enc.pop_back();
        return new Node( Left, Right );
    }
}

void Tree::builtRep(Node * SubTree , QVector<bool> Rep )
{
        //SubTree->ShowNode();
        if( SubTree->isLeaf() )
        {
            Code.insert( SubTree->getChar(), Rep );
            if(SubTree->getChar() == '*' )
                this->Represent += "!*";
            else if( SubTree->getChar() == '!' )
                this->Represent += "!!";
            else
                this->Represent += SubTree->getChar();
        }
        else
        {
            this->Represent += "*";
            Rep.push_back(0);
            builtRep(SubTree->getNodeLeft(),  Rep); Rep.pop_back();
            Rep.push_back(1);
            builtRep(SubTree->getNodeRight(),Rep );
        }
}
Node *Tree::getRoot() { return this->Root; }
void Tree::Show_Code()
{
    qDebug() << "----------------Codificação----------------";
    QHash<unsigned char, QVector<bool> >::const_iterator i = Code.constBegin();
    while (i != Code.constEnd()) {
        qDebug() << i.key() << " : " << i.value();
        ++i;
    }
    qDebug() << "-------------Fim da Codificação-------------";
}
QByteArray Tree::getRepresent()    {    return this->Represent;    }
void Tree::Show_Represent()
{
    qDebug() << "----------------Representação----------------";
    for (int var = 0; var < this->Represent.size() ; ++var)
        cout << (int) Represent[var] << " ";
    cout << endl;
    qDebug() << "-------------Fim da Representação-------------";
}
QHash<unsigned char, QVector<bool> > Tree::GetCoding()  { return this->Code;   }
int Tree::GetMaxRep() { return this->Mcode; }
