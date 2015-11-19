#ifndef TREE_H
#define TREE_H
#include <QList>
#include "list.h"
#include <QtAlgorithms>
#include "node.h"
#include <QDebug>
#include <QBitArray>
#include <QHash>
#include <QPair>
#include <QVector>
#include <QChar>
#include <QQueue>
#include <QSet>
#include <bits/stdc++.h>
using namespace std;
typedef QPair< uchar , bool > Pub;
#define ASCII 256
class Tree
{
    // Nó da árvore
    Node *Root;
    // Dicionario de Transformação de byte para code
    QHash< unsigned char , QVector<bool> > Code;
    // Representação da arvore codificada
    QByteArray Represent;
    // Representação da decodificada
    QQueue < Pub > Rpt;
    // Maior representação
    int Mcode;
public:
    Tree(List NList);
    Tree(QByteArray Rep);
    void builtRep(Node * SubTree, QVector<bool> Rep);
    Node *getRoot();
    void Show_Code();
    QByteArray getRepresent();
    void Show_Represent();
    QHash< unsigned char, QVector<bool> > GetCoding();
    Node *buildTree(QVector<bool> Enc);
    int GetMaxRep();
};

#endif // TREE_H
