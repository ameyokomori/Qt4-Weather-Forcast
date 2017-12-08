#include "weather.h"
#include "ui_weather.h"
#include <QTextCodec>
#include <QDateTime>


weather::weather(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::weather)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    connect(&http,SIGNAL(done(bool)),this,SLOT(httpDone(bool)));
    connect(this,SIGNAL(done(bool)),this,SLOT(showData(bool)));
    QString url("http://m.weather.com.cn/data/101190101.html");
    readData(url);
    ui->setupUi(this);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(selectCity(int)));
    this->setFixedSize(this->width(),this->height());

}

weather::~weather()
{
    delete ui;
}

void weather::showData(bool error)
{

    if(error)
    {
        this->statusBar()->showMessage("连接网络失败，请检查网络！");
    }
        else
        this->statusBar()->showMessage("成功连接到中国气象局数据!");
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->showDate->setText(currentTime.toString("yyyy-mm-dd hh:mm ddd"));
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(weatherValue.property("weather1").toString()));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem(weatherValue.property("weather2").toString()));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem(weatherValue.property("weather3").toString()));
    ui->tableWidget->setItem(3,0,new QTableWidgetItem(weatherValue.property("weather4").toString()));
    ui->tableWidget->setItem(4,0,new QTableWidgetItem(weatherValue.property("weather5").toString()));
    ui->tableWidget->setItem(5,0,new QTableWidgetItem(weatherValue.property("weather6").toString()));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(weatherValue.property("temp1").toString()));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem(weatherValue.property("temp2").toString()));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem(weatherValue.property("temp3").toString()));
    ui->tableWidget->setItem(3,1,new QTableWidgetItem(weatherValue.property("temp4").toString()));
    ui->tableWidget->setItem(4,1,new QTableWidgetItem(weatherValue.property("temp5").toString()));
    ui->tableWidget->setItem(5,1,new QTableWidgetItem(weatherValue.property("temp6").toString()));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(weatherValue.property("wind1").toString()));
    ui->tableWidget->setItem(1,2,new QTableWidgetItem(weatherValue.property("wind2").toString()));
    ui->tableWidget->setItem(2,2,new QTableWidgetItem(weatherValue.property("wind3").toString()));
    ui->tableWidget->setItem(3,2,new QTableWidgetItem(weatherValue.property("wind4").toString()));
    ui->tableWidget->setItem(4,2,new QTableWidgetItem(weatherValue.property("wind5").toString()));
    ui->tableWidget->setItem(5,2,new QTableWidgetItem(weatherValue.property("wind6").toString()));
    ui->wearShow->setWordWrap(true);
    ui->wearShow->setText(weatherValue.property("index_d").toString());
    ui->carShow->setText(weatherValue.property("index_xc").toString());
    ui->exShow->setText(weatherValue.property("index_cl").toString());
    ui->comfortShow->setText(weatherValue.property("index_co").toString());
    ui->dryingShow->setText(weatherValue.property("index_ls").toString());
    ui->ultraShow->setText(weatherValue.property("index_uv").toString());

}

void weather::httpDone(bool error)
{
    QScriptEngine engine;
    QScriptValue json = engine.evaluate("("+buffer->data()+")");
    weatherValue = json.property("weatherinfo");
    delete buffer;
    emit done(error);

}


void weather::selectCity(int index)
{
    QString url("http://m.weather.com.cn/data/");
    QString html(".html");
    QString code[] = {"101190101","101020100","101010100"};
    readData(url+code[index]+html);
}


bool weather::readData(const QUrl &url)
{

    if (url.path().isEmpty())
    {
        return false;
    }
    buffer = new QBuffer;
    http.setHost(url.host(), url.port(80));
    buffer->open(QIODevice::ReadWrite);
    buffer->setBuffer(0);
    http.get(url.path(), buffer);
    buffer->close();
    http.close();
    return true;

}
