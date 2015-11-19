#ifndef DHUFFMAN_H
#define DHUFFMAN_H
#include "read.h"
#include "node.h"
#include "tree.h"
#include "list.h"
#include <QObject>
#define ASCII 256
class DHuffman : public QObject {
    Q_OBJECT
    int Trash;
    int SRepresentation;
    int SNameFile;
    QByteArray NameFile;
public:
    DHuffman();
    Q_INVOKABLE void DHuff( QString in, QString out);
};

#endif // DHUFFMAN_H
