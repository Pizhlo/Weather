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

    QList<QString> weekDatesForScreen; // need to show dates on screen
    QList<QString> weekDatesForRequest;  // need to make new request with new dates
    QList<QString> weekDatesForKeys; // need to take value in QList temperature (void tempOnScreen)
    QString temp_now;
    QUrl url;
    int countDays = 0;

    void replyFinished(QNetworkReply *reply);
    void showDateOnScreen();
    void calcDate();
    void infoOnScreen(int parametr = 0);
    void makeRequest();
    void makeWeekKeysForShowing();
    void makeWeekKeysForRequest();

    ~MainWindow();

private slots:
    void on_left_button_clicked();

    void on_right_button_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
