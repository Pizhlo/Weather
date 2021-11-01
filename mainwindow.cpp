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

QJsonObject temperatureAllWeek; // �����������
QJsonObject humidityAllWeek; // ���������
QJsonObject precipitationAllWeek; // ������
QJsonObject windSpeedAllWeek; // �������� �����
QJsonObject sunriseAllWeek; // ������ ������
QJsonObject sunsetAllWeek; // ����� ������
QJsonObject pressureAllWeek; // ��������


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
    QJsonDocument itemDoc = QJsonDocument::fromJson(myData);
    QJsonObject rootObject = itemDoc.object();

    QJsonValue value_days = rootObject.take("days");
    QJsonArray days_arr = value_days.toArray();

    QJsonValue temp;
    QString temp_2;
    QJsonValue temp_1;

    for (int i = 0; i < days_arr.count(); i++) {

        temp = days_arr[i].toObject().value("datetime");
        temp_2 = temp.toString();

        temp_1 = days_arr[i].toObject().value("temp");
        temperatureAllWeek.insert(temp_2, temp_1);

        temp_1 = days_arr[i].toObject().value("humidity");
        humidityAllWeek.insert(temp_2, temp_1);

        temp_1 = days_arr[i].toObject().value("windspeed");
        windSpeedAllWeek.insert(temp_2, temp_1);

        temp_1 = days_arr[i].toObject().value("sunrise");
        sunriseAllWeek.insert(temp_2, temp_1);

        //qDebug() << sunriseAllWeek;

        temp_1 = days_arr[i].toObject().value("sunset");
        sunsetAllWeek.insert(temp_2, temp_1);

        //qDebug() << sunsetAllWeek;

        temp_1 = days_arr[i].toObject().value("pressure");
        pressureAllWeek.insert(temp_2, temp_1);

        temp_1 = days_arr[i].toObject().value("precip");
        precipitationAllWeek.insert(temp_2, temp_1);

    }

    infoOnScreen(ui->comboBox->currentIndex());
}


void MainWindow::infoOnScreen(int parametr) { // shows temp on the screen

    QList<QLabel*> tempLabelsArray;

    tempLabelsArray.append(ui->first_day_temp_label);
    tempLabelsArray.append(ui->second_day_temp_label);
    tempLabelsArray.append(ui->third_day_temp_label);
    tempLabelsArray.append(ui->fourth_day_temp_label);
    tempLabelsArray.append(ui->fifth_day_temp_label);
    tempLabelsArray.append(ui->sixth_day_temp_label);
    tempLabelsArray.append(ui->sevent_day_temp_label);

    if (countDays == 0) {

        temp_now = QString::number(temperatureAllWeek.value(QDate::currentDate().toString("yyyy-MM-dd")).toDouble());
        ui->temp_label->setText(temp_now);
    }

    if (parametr == 0) {

        for (int i = 0; i < 7; i++) {

            tempLabelsArray[i]->setText(QString::number(temperatureAllWeek.value(weekDatesForKeys[i]).toDouble()));

            }
        }

    if (parametr == 1) {

        for (int i = 0; i < 7; i++) {

            tempLabelsArray[i]->setText(QString::number(humidityAllWeek.value(weekDatesForKeys[i]).toDouble()));

            }
    }

    if (parametr == 2) {

        for (int i = 0; i < 7; i++) {

            tempLabelsArray[i]->setText(QString::number(precipitationAllWeek.value(weekDatesForKeys[i]).toDouble()));

            }
    }

    if (parametr == 3) {

        for (int i = 0; i < 7; i++) {

            tempLabelsArray[i]->setText(QString::number(pressureAllWeek.value(weekDatesForKeys[i]).toDouble()));

            }
    }

    if (parametr == 4) {

        for (int i = 0; i < 7; i++) {

            tempLabelsArray[i]->setText(QString::number(windSpeedAllWeek.value(weekDatesForKeys[i]).toDouble()));

            }
    }

    if (parametr == 5) {

        QTime time;
        QString time_2;

        for (int i = 0; i < 7; i++) {

            time_2 = sunriseAllWeek.value(weekDatesForKeys[i]).toString();

            qDebug() << "string = " << time_2;

            time = QTime::fromString(time_2, "hh:mm:ss"); // ??

            qDebug() << "time = " << time;

            tempLabelsArray[i]->setText(time.toString());

            }
    }

    if (parametr == 6) {

        for (int i = 0; i < 7; i++) {

            tempLabelsArray[i]->setText((sunsetAllWeek.value(weekDatesForKeys[i]).toString()));

            }
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


void MainWindow::on_comboBox_activated(int index)
{
    infoOnScreen(index);

}

