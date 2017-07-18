#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>



using namespace std;

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
   void Connect();
    
private:
    QString ip;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
