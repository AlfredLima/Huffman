#include "list.h"

List::List()
{
    
}
void List::insert(Node *node)   {    this->NodeList.append(node);    }
Node * List::getFirst() { return this->NodeList.first(); }
void List::RemoveFirst() { this->NodeList.removeFirst(); }
int List::size() { return this->NodeList.size(); }
bool compare(Node * &nd1, Node * &nd2)
{
        if( nd1->getFreq() == nd2->getFreq() )
            return nd1->getChar() < nd2->getChar();
        return nd1->getFreq() < nd2->getFreq();
}
void List::Sort(){ qSort( this->NodeList.begin(), this->NodeList.end(), compare  ); }
void List::ShowList()
{
    qDebug() << "Tamanho da lista: "<< NodeList.size();
    for( int i = 0 ; i < NodeList.size() ; i++ )
    {
        qDebug() << "Caracter " << NodeList.at(i)->getChar() << "Frequencia " << NodeList.at(i)->getFreq();
    }
}
