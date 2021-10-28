#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QList<QString> thisWeekDatesArr;
    int countDays = 0;

    void replyFinished(QNetworkReply *reply);
    void showDateOnScreen();
    void calcDate();
    void tempOnScreen(QJsonArray temp);
    void makeNewRequest();

    ~MainWindow();

private slots:
    void on_left_button_clicked();

    void on_right_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
