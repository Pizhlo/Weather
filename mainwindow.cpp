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
#include <QMap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    calcDate();

    makeWeekKeysForRequest();

    makeRequest();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeRequest() { // makes new request when any button pressed

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QString thisUrl;

    thisUrl = "https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/Moscow%2C%20MOW%2C%20RU/";

    thisUrl += weekDatesForRequest[0] + '/' + weekDatesForRequest.last() + "?unitGroup=metric&key=P99F9W84P9WW97FYZSQ9KYJMH";

    url = thisUrl;

    manager->get(QNetworkRequest(QUrl(url)));

    connect(manager, &QNetworkAccessManager::finished,
                this, &MainWindow::replyFinished);

    makeWeekKeysForShowing();

}


void MainWindow::replyFinished(QNetworkReply *reply)
{   
    QByteArray myData = reply->readAll();

    qDebug() << myData;

    QJsonDocument itemDoc = QJsonDocument::fromJson(myData);
    QJsonObject rootObject = itemDoc.object();

    QJsonValue value_days = rootObject.take("days");
    QJsonArray days_arr = value_days.toArray();

    QJsonValue temp;
    QString temp_2;
    QJsonValue temp_1;
    QJsonObject temperatureAllWeek;
    QJsonObject humidityAllWeek;
    QJsonObject windSpeedAllWeek;

    for (int i = 0; i < days_arr.count(); i++) { // filling in array of temperature

        temp = days_arr[i].toObject().value("datetime");
        temp_2 = temp.toString();
        temp_1 = days_arr[i].toObject().value("temp");
        temperatureAllWeek.insert(temp_2, temp_1);

        temp_1 = days_arr[i].toObject().value("humidity");
        humidityAllWeek.insert(temp_2, temp_1);

        temp_1 = days_arr[i].toObject().value("windspeed");
        windSpeedAllWeek.insert(temp_2, temp_1);

        qDebug() << windSpeedAllWeek;


    }

    tempOnScreen(temperatureAllWeek);
}


void MainWindow::tempOnScreen(QJsonObject temp) { // shows temp on the screen

    QList<QLabel*> tempLabelsArray;

    if (countDays == 0) {

        temp_now = QString::number(temp.value(QDate::currentDate().toString("yyyy-MM-dd")).toDouble());
        ui->temp_label->setText(temp_now);
    }

    tempLabelsArray.append(ui->first_day_temp_label);
    tempLabelsArray.append(ui->second_day_temp_label);
    tempLabelsArray.append(ui->third_day_temp_label);
    tempLabelsArray.append(ui->fourth_day_temp_label);
    tempLabelsArray.append(ui->fifth_day_temp_label);
    tempLabelsArray.append(ui->sixth_day_temp_label);
    tempLabelsArray.append(ui->sevent_day_temp_label);

    for (int i = 0; i < 7; i++) {

        tempLabelsArray[i]->setText(QString::number(temp.value(weekDatesForKeys[i]).toDouble()));

    }
}

void MainWindow::makeWeekKeysForShowing() { // making keys for QJsonObject temp

    QDate today_date;

    today_date = today_date.currentDate();

    weekDatesForKeys.clear();

    for (int i = 0; i < 7; i++) { // filling in array with dates for showing matching temperature

        weekDatesForKeys << (today_date.currentDate().addDays(i+countDays).toString("yyyy-MM-dd"));
    }

}

void MainWindow::makeWeekKeysForRequest() {

    QDate today_date;

    weekDatesForRequest.clear();

    weekDatesForRequest << (today_date.currentDate().addDays(countDays)).toString("yyyy-MM-d");
    weekDatesForRequest << (today_date.currentDate().addDays(6 + countDays)).toString("yyyy-MM-d");

    if (countDays != 0) {

        makeRequest();
    }


}

void MainWindow::calcDate() { // changes dates on the screen

    weekDatesForScreen.clear();

    QDate today_date;
    QString week_of_day;

    for (int i = 0; i < 7; i++) {

        week_of_day = QLocale{QLocale::Russian}.toString(today_date.currentDate().addDays(i+countDays), "ddd");

        weekDatesForScreen << today_date.currentDate().addDays(i+countDays).toString("d") + " " + week_of_day;
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

        weekDatesLabelArray[i]->setText(weekDatesForScreen[i]);

    }

}



void MainWindow::on_left_button_clicked()
{
    --countDays;
    calcDate();
    makeWeekKeysForRequest();

}


void MainWindow::on_right_button_clicked()
{
    ++countDays;
    calcDate();
    makeWeekKeysForRequest();

}

