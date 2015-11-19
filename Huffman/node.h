#ifndef NODE_H
#define NODE_H
#include <QDebug>
class Node
{
    // Filho da esquerda
    Node *Left;
    // Filho da direita
    Node *Right;
    // Folha
    bool Leaf;
    // Caracter
    unsigned char Carac;
    // Frequencia
    long long Freq;

public:
    // Construtor padrao
    Node();
    // Construtor de Folhas
    Node( long long Freq = 0, unsigned char Carac = 0);
    // Construtor de Folhas Decodificando
    Node( unsigned char Carac );
    // Construtor de Ramos
    Node( long long Freq , Node *Left, Node * Right );
    // Construtor de Ramos Decodificado
    Node( Node *Left, Node * Right );
    // Destrutor
    ~Node();
    // Se eh folha
    bool isLeaf();
    // Retorna a frequencia
    long long getFreq();
    // Retorna o caracter
    unsigned char getChar();
    // Retorna o Filho a esquerda
    Node *getNodeLeft();
    // Retorna o Filho a direita
    Node *getNodeRight();
    // Seta Filho da esquerda
    void setNodeLeft(Node *Left);
    // Seta Filho da diretia
    void setNodeRight(Node *Right);
    void ShowNode();
};

#endif // NODE_H
