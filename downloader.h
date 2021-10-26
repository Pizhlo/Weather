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
    //void getData(); // ������������� ������� �� ��������� ������
    void onResult(QNetworkReply *reply); // ��������� ������ � ���������� ������

private:
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this); // �������� �������� �������


};

#endif // DOWNLOADER_H
