#include "downloader.h"


downloader::downloader(QObject *parent) : QObject (parent)
{

    //manager = new QNetworkAccessManager(); // ������������� ���������
   // connect(manager, &QNetworkAccessManager::finished, this, &downloader::onResult); // ����������� ������� � ���������� ��������� ������  � ����������� ����������� ������

    connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

}

void downloader::makeRequest(QString endPointRequest) {

    qnam->get(QNetworkRequest(QUrl(endPointRequest)));

}

void downloader::onResult(QNetworkReply *reply) {

    QByteArray myData;

    myData =  reply->readAll();

    emit(dataReadyRead(myData));
}




















//void downloader::getData() {

    // QUrl url("https://www.gismeteo.ru");
    // QNetworkRequest request;

    // request.setUrl(url); // ���������� url � ������
    // manager->get(request); // ��������� ������

//}

//void downloader::onResult(QNetworkReply *reply) {

    // ���� � �������� ��������� ������ ��������� ������

   // if(reply->error()) {
      //  qDebug() << "ERROR";
      //  qDebug() << reply->errorString();
   // } else {
        // ����� �� ����� ����������
   // }


//}

//downloader::~downloader() {


//}
