#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QByteArray>
#include <QLocale>
#include <QTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    calcDate();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);

    manager->get(QNetworkRequest(QUrl("http://api.weatherunlocked.com/api/forecast/55.45,37.36?app_id=18fdb593&app_key=592b64ad8b4240186225b9dff72b9e8c")));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeNewRequest() { // makes new request when any button presed

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QString url = "http://api.weatherunlocked.com/api/trigger/55.45,37.36/pastday.";

    if (countDays < 0) {

        QDate date = QDate::currentDate().addDays(countDays);
        QString date_1 = date.toString("yyyy.MM.dd");

        //qDebug() << date_1;

        url += date_1;

       // qDebug() << url;

        QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
       // qDebug() << reply->readAll();


    }

    //api/trigger/52.48,13.41/past morning.2014.01.25

    delete manager;
}



void MainWindow::replyFinished(QNetworkReply *reply)
{

    //QList<QTime> time = {QTime(4, 0), QTime(7, 0), QTime(10, 0), QTime(13, 0), QTime(16, 0), QTime(19, 0), QTime(22, 0)};
    //QTime now_time = QTime::currentTime();
    //QList<QDateTime> difference;
   // QTime min_difference;
   // int msec = 0;

    // for current temperature

   // for (int i =0; i <= time.length(); i++){

        //difference.append(QTime(QDateTime::currentDateTime()).secsTo(time[i]));

   // }



    QByteArray myData = reply->readAll();
    QJsonDocument itemDoc = QJsonDocument::fromJson(myData);
    QJsonObject rootObject = itemDoc.object();
    QJsonValue value_days = rootObject.take("Days");
    QJsonArray value_days_arr = value_days.toArray();

    QList<QJsonValue> a;
    QList <QJsonValue> temp_arr;
    QList <QJsonValue> data_arr;
    QJsonArray temperature_arr;
    QJsonObject temp;
    QJsonValue temp_2;
    QJsonObject temp_3;
    QJsonValue temp_now;

    for (int i = 0; i < 7; i++) {

        a.append(value_days_arr[i]);
        temp = a[i].toObject();
        temp_2 = temp.take("Timeframes");
        temp_arr.append(temp_2);
        data_arr.append(temp_arr[i][3]);
        temp_3 = data_arr[i].toObject();
        temperature_arr.append(temp_3.take("temp_c"));

    }

   tempOnScreen(temperature_arr);

}


void MainWindow::tempOnScreen(QJsonArray temp) { // shows temp on the screen

    QList<QLabel*> tempLabelsArray;

    tempLabelsArray.append(ui->first_day_temp_label);
    tempLabelsArray.append(ui->second_day_temp_label);
    tempLabelsArray.append(ui->third_day_temp_label);
    tempLabelsArray.append(ui->fourth_day_temp_label);
    tempLabelsArray.append(ui->fifth_day_temp_label);
    tempLabelsArray.append(ui->sixth_day_temp_label);
    tempLabelsArray.append(ui->sevent_day_temp_label);

    for (int i = 0; i < 7; i++) {

        tempLabelsArray.at(i)->setText(QString::number(temp.at(i).toDouble()));

    }

}

void MainWindow::calcDate() { // changes dates on the screen

    thisWeekDatesArr.clear();

    QDate today_date;
    QString week_of_day;

    today_date = today_date.currentDate();

    for (int i = 0; i < 7; i++) {

        week_of_day = QLocale{QLocale::Russian}.toString(today_date.currentDate().addDays(i+countDays), "ddd");

        thisWeekDatesArr << today_date.currentDate().addDays(i+countDays).toString("d") + " " + week_of_day;

    }

    showDateOnScreen();

}

void MainWindow::showDateOnScreen() { // shows dates on the screen

    QList<QLabel*> weekDatesLabelArray;

    weekDatesLabelArray.append(ui->first_day_label);
    weekDatesLabelArray.append(ui->second_day_label);
    weekDatesLabelArray.append(ui->third_day_label);
    weekDatesLabelArray.append(ui->fourth_day_label);
    weekDatesLabelArray.append(ui->fifth_day_label);
    weekDatesLabelArray.append(ui->sixth_day_label);
    weekDatesLabelArray.append(ui->seventh_day_label);

    for (int i = 0; i < 7; i++) {

        weekDatesLabelArray[i]->setText(thisWeekDatesArr[i]);

    }

}



void MainWindow::on_left_button_clicked()
{
    --countDays;

    makeNewRequest();

    calcDate();

}


void MainWindow::on_right_button_clicked()
{
    ++countDays;

    makeNewRequest();

    calcDate();
}

