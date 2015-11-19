#include <QDebug>
#include <QTime>
#include <dhuffman.h>
#include <huffman.h>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QIcon>

int main(int argc, char *argv[]){
    QTime t;
    t.start();
    //START APP
    QApplication app(argc,argv);
    app.setWindowIcon(QIcon(":/data/img/11412394_407750046078820_6932822019341529347_n.jpg"));
    QApplication::setApplicationName("Huffman");
    QApplication::setApplicationVersion("ÚNICO");
    QQmlApplicationEngine engine;
    QQmlContext *interpreter = engine.rootContext();
    Huffman huff;
    DHuffman deHuff;
    QCommandLineParser parser;
    //Parser
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription("Huffman Parsers");
    parser.addPositionalArgument("in-file.x", QCoreApplication::translate("main", "File being compressed."));
    parser.addPositionalArgument("out-name.huff", QCoreApplication::translate("main", "Name to save archive."));
    //parser.addPositionalArgument("dir", QCoreApplication::translate("main", "Dir being compressed"));
    parser.addPositionalArgument("local", QCoreApplication::translate("main", "Local to save archive."));
    QCommandLineOption compress("c",QApplication::translate("main","Compress <in-file.x>."),
                                QApplication::translate("main","in-file.x"));
    parser.addOption(compress);
    QCommandLineOption outName("o",QApplication::translate("main","Save as <out-name.huff>."),
                               QApplication::translate("main","out-file.huff"));
    parser.addOption(outName);
    QCommandLineOption local("d",QApplication::translate("main","Decompress in <local>."),
                             QApplication::translate("main","local"));
    parser.addOption(local);
    QCommandLineOption startGui({"g", "gui"},QApplication::translate("main","Start gui."));
    parser.addOption(startGui);
    parser.process(app);

    //ARGUMENTS
    if(parser.isSet(startGui)){
        interpreter->setContextProperty("_huff",&huff);
        interpreter->setContextProperty("_dehuff",&deHuff);
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    }
    else if(parser.isSet(compress) && parser.isSet(outName))
    {
        cout << "case 1" << endl;
        huff.Huff(parser.value(compress),parser.value(outName));
    }
    else if(parser.isSet(compress))
    {
        cout << "case 2" << endl;
        huff.Huff(parser.value(compress),parser.value(compress));
    }
    else{
        if(app.arguments().size() == 1)
            qDebug() << qPrintable(parser.helpText());
        else if(parser.isSet(local))
            deHuff.DHuff(app.arguments().at(1),parser.value(local));
        else
            deHuff.DHuff(app.arguments().at(1),app.arguments().at(1));
    }
    //END APP
    qDebug("%s <> Tempo de execução: %d ms",Q_FUNC_INFO,t.elapsed());
    return app.exec();
}
