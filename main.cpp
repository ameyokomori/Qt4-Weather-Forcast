#include "weather.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    weather w;
    w.show();
    return app.exec();
}
