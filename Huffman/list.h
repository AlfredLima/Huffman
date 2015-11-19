#ifndef LIST_H
#define LIST_H
#include <QList>
#include <QtAlgorithms>
#include <QDebug>
#include "node.h"
using namespace std;
class List
{
    QList< Node* > NodeList;
public:
    // Construtor
    List();
    // Inserte
    void insert(Node *node);
    // Retorna o primeiro elemento da lista
    Node* getFirst();
    // Remove o primeiro elemento da lista
    void RemoveFirst();
    // Retorna o tamanho da lista
    int size();
    // Ordena a lista
    void Sort();
    // Compare
    //bool compare(Node * &nd1, Node * &nd2);
    // Mostra a Lista
    void ShowList();
};

#endif // LIST_H
