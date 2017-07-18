#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    int cardClient1;
    int cardClient2;

    int statsClient1[18];
    int statsClient2[18];

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void start();
    void stop();
    void initClients(MainWindow*,int,int);
    void getStatsForClients();
    void setStatsForClients();
    int DoBot(int,int);
    int loose();
    void doBoundaries();
    friend void* threadFunction(void *);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
