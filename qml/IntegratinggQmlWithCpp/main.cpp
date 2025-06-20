#include <QGuiApplication>
#include <QQmlApplicationEngine>
// #include <QQmlContext>

#include "base.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    // Base *obj = new Base();

    // Registering a type
    qmlRegisterType<Base>("t", 1, 0, "SomeClass");


    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection); 
    engine.loadFromModule("IntegratinggQmlWithCpp", "Main");

    //By setting context property - QQmlContext
    // QQmlContext *rootContext = engine.rootContext();
    // rootContext->setContextProperty("classBase", obj);


    return app.exec();
}
