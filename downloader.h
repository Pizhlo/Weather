#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>

class downloader : public QObject
{

    Q_OBJECT

public:
    explicit downloader(QObject *parent = 0);
   // ~downloader();
    void makeRequest(QString endPointRequest);

signals:
    //void onReady();
    void dataReadyRead(QByteArray);

public slots:
    //void getData(); // инициализация запроса на получение данных
    void onResult(QNetworkReply *reply); // обработка ответа о полученных данных

private:
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this); // менеджер сетевого доступа


};

#endif // DOWNLOADER_H
