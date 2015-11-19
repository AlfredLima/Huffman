#include "node.h"
// Costrutor padrao
Node::Node()
{
}
// Construtor de Folhas
Node::Node( long long Freq, unsigned char Carac)
{
    this->Leaf = true;
    this->Freq= Freq;
    this->Carac = Carac;
}
// Construtor de Folhas Dec
Node::Node(unsigned char Carac)
{
    this->Leaf = true;
    this->Carac = Carac;
}

// Construtor de Ramos
Node::Node(long long Freq, Node *Left, Node *Right)
{
    this->Leaf = false;
    this->Carac = 0;
    this->Freq = Freq;
    this->Left = Left;
    this->Right = Right;
}
// Construtor de Ramos Decodificado
Node::Node( Node *Left, Node * Right )
{
    this->Leaf = false;
    this->Left = Left;
    this->Right = Right;
}

// Retorna o caracter
unsigned char Node::getChar()   { return this->Carac; }
// Retorna a frequencia
long long Node::getFreq() { return this->Freq; }
// Retorna se é folha
bool Node::isLeaf() { return this->Leaf; }
// Retorna o filho da esquerda
Node *Node::getNodeLeft() { return Left; }
// Retorna o filho da direita
Node *Node::getNodeRight() { return Right; }
// Seta o filho da esquerda
void Node::setNodeLeft(Node *Left) { this->Left = Left; }
// Seta o filho da direita
void Node::setNodeRight(Node *Right) { this->Right = Right; }
// Mostra o Node
void Node::ShowNode()
{
    qDebug() << "-----------------Node-----------------";
    if( this->Leaf ) qDebug() << "É folha";
    else qDebug() << "Não é Folha";
    qDebug() << this->getChar();
    qDebug() << this->getFreq();
    qDebug() << "-----------------Node-----------------";

}
