#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QDebug>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dateOnScreen();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);

    manager->get(QNetworkRequest(QUrl("http://api.weatherunlocked.com/api/current/55.45,37.36?app_id=18fdb593&app_key=592b64ad8b4240186225b9dff72b9e8c")));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{

    QByteArray myData = reply->readAll();

    ui->textBrowser->setText(myData);

    QJsonDocument itemDoc = QJsonDocument::fromJson(myData);
    QJsonObject rootObject = itemDoc.object();

    QJsonValue temp_c = rootObject.value("temp_c");
    int tempc_c_int = temp_c.toInt();
    QString temp_c_string = QString::number(tempc_c_int);

    ui->textBrowser->setText(myData);

    ui->temp_label->setText(temp_c_string);


}

void MainWindow::dateOnScreen() {

    QList<QLabel*> thisWeekDatesLabelArray;

    thisWeekDatesLabelArray << new QLabel(ui->first_day_label);
    thisWeekDatesLabelArray << new QLabel(ui->second_day_label);
    thisWeekDatesLabelArray << new QLabel(ui->third_day_label);
    thisWeekDatesLabelArray << new QLabel(ui->fourth_day_label);
    thisWeekDatesLabelArray << new QLabel(ui->fifth_day_label);
    thisWeekDatesLabelArray << new QLabel(ui->sixth_day_label);
    thisWeekDatesLabelArray << new QLabel(ui->seventh_day_label);


    QDate today_date;
    today_date = today_date.currentDate();

    QString thisWeekDatesArr[7];

    for (int i = 0; i < 7; i++) {

        thisWeekDatesArr[i] = today_date.currentDate().addDays(i).toString("d");

        qDebug() << thisWeekDatesArr[i];

        thisWeekDatesLabelArray[i]->setText(thisWeekDatesArr[i]);


    }



}

