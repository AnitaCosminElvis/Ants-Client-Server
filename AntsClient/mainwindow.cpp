#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoggame.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Connect(){
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);

    /*if((ui->user->text().isEmpty()) || (ui->password->text().isEmpty()) || (ui->serverIP->text().isEmpty())){
        msgBox.setText("One of the fields are empty");
        msgBox.setInformativeText("Try again");
        msgBox.exec();
        return;
    }*/

    ip = "192.168.1.101";

    int port;
    int sd;			// descriptorul de socket
    port = 7777;

    char *user = new char[1000];
    char *password = new char[1000];

    strcpy(user,"admin");
    strcpy(password,"1234");

    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1){
        msgBox.setText("Socket error.");
        msgBox.exec();
        ::close (sd);
        return;
    }


    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip.toAscii());
    server.sin_port = htons (port);

    if (::connect(sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1){
        msgBox.setText("Server unavailable try again later.");
        msgBox.exec();
        ::close (sd);
        return;
    }

    char sentData[1000];
    strcpy(sentData,user);
    strcat(sentData,password);

    int errorType;

    do{
        errorType = write (sd, sentData, sizeof(sentData));
        if(errorType == 0){
            msgBox.setText("Server unavailable try again later.");
            msgBox.exec();
            ::close (sd);
            return;
        }else break;
    }while(errorType == -1);


    delete user;
    delete password;


    char ok[100];

    do{
        errorType = read (sd, ok, sizeof(ok));
        if(errorType == 0){
            msgBox.setText("Server unavailable try again later.");
            msgBox.exec();
            ::close (sd);
            return;
        }else break;
    }while(errorType == -1);


    if(*ok == 'K'){
        DialogGame GAME;
        GAME.setModal(true);
        GAME.setStyleSheet("background-image: url(./BackgroundAnts.jpg)");
        GAME.setServerDescript(sd);
        GAME.setCards();
        GAME.setFirstTime();
        GAME.exec();
    }else{
        msgBox.setText("Your user/password are incorrect.");
        msgBox.exec();
        ::close (sd);
    }
    ::close(sd);
}
