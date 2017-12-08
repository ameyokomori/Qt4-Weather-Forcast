#ifndef WEATHER_H
#define WEATHER_H

#include <QMainWindow>
#include <QHttp>
#include <QUrl>
#include <QStatusBar>
#include <QString>
#include <QBuffer>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>




namespace Ui {
class weather;
}

class weather : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit weather(QWidget *parent = 0);
    ~weather();

signals:
    void done(bool);

private slots:
    void showData(bool error);
    void httpDone(bool error);
    void selectCity(int index);


private:
    bool readData(const QUrl &url);
    QHttp http;
    QBuffer *buffer;
    QScriptValue weatherValue;
    Ui::weather *ui;
};

#endif // WEATHER_H
