#include "downloader.h"


downloader::downloader(QObject *parent) : QObject (parent)
{

    //manager = new QNetworkAccessManager(); // инициализация менеджера
   // connect(manager, &QNetworkAccessManager::finished, this, &downloader::onResult); // подключение сигнала о завершении получения данных  к обработчику полученного ответа

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

    // request.setUrl(url); // установить url в запрос
    // manager->get(request); // выполнить запрос

//}

//void downloader::onResult(QNetworkReply *reply) {

    // если в процессе получения данных произошла ошибка

   // if(reply->error()) {
      //  qDebug() << "ERROR";
      //  qDebug() << reply->errorString();
   // } else {
        // вывод на форму информации
   // }


//}

//downloader::~downloader() {


//}
