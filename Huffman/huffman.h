#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "read.h"
#include "list.h"
#include "tree.h"
#include <QObject>
class Huffman : public QObject {
    Q_OBJECT
    QString IN;
    QString OUT;
    List NList;
    QVector<long long> Freq;
public:
    Huffman();
    Q_INVOKABLE void Huff(QString in,QString out);
};

#endif // HUFFMAN_H
