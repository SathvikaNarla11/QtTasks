#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <baseclass.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<baseclass>("t",1,0,"SomeClass"); //Registering a type

    // baseclass objbaseclass; //QQMLContext

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qmlBasicOne", "Main");


    /*
    QQMLContext
    QQmlContext *rootContext = engine.rootContext();
    rootContext->setContextProperty("classA", &objbaseclass);
    */



    return app.exec();
}
