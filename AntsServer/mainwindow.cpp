#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 7777


#define MAX_THREAD 1000

char user[100] = "admin";
char passwd[100] = "1234";

using namespace std;

typedef struct _THREAD_STRUCT{
    int fd1;
    int fd2;
    MainWindow *MainW;
}THREAD_STRUCT,*PTHREAD_STRUCT;

int Login(int client){
    char userMsg[100];
    char passwordMsg[100];
    char k[100];
    k[0]= 'F';
     read (client, userMsg, sizeof (userMsg));
     read(client,passwordMsg,sizeof(passwordMsg));
     if((0 == strcmp(user,userMsg)) &&  (0 == strcmp(passwd,passwordMsg))) k[0] = 'K';


     write(client, k, sizeof(k));
     if(k[0] != 'K') return 0;
     else return 1;
}



void* threadFunction(void *pointerToStructureOfThread){
    _THREAD_STRUCT *pointerCopy = NULL;
    pointerCopy = (THREAD_STRUCT*)pointerToStructureOfThread;

    pointerCopy->MainW->initClients(MainWindow *pointerCopy->MainW,pointerCopy->fd1,pointerCopy->fd2);


    while(1){
        read(pointerCopy->fd1,pointerCopy->MainW->cardClient1,sizeof(int));
        read(pointerCopy->fd1,pointerCopy->MainW->cardClient1,sizeof(int));
        //random(msg);
        int statsToBeSent[18];
        for(int i = 0 ; i < 18; ++i)
            statsToBeSent[i] = qrand() % 29;
        write(pointerCopy->fd1,&statsToBeSent,sizeof(statsToBeSent));
    }
}

void MainWindow::stop(){

}

void MainWindow::start(){
    struct sockaddr_in serverStruct;
    int descrptS;		/* descriptori de socket */
    int optval=1; 			/* optiune folosita pentru setsockopt()*/


    /* creare socket */
    if ((descrptS = socket (AF_INET, SOCK_STREAM, 0)) == -1){
        QMessageBox msg;
        msg.setText("Error creating socket");
        msg.exec();
        return;
    }

    /*setam pentru socket optiunea SO_REUSEADDR */
    setsockopt(descrptS, SOL_SOCKET, SO_REUSEADDR,&optval,sizeof(optval));

    bzero (&serverStruct, sizeof (serverStruct));

    /* umplem structura folosita de server */
    serverStruct.sin_family = AF_INET;
    serverStruct.sin_addr.s_addr = htonl (INADDR_ANY);
    serverStruct.sin_port = htons (PORT);

    /* atasam socketul */
    if (bind (descrptS, (struct sockaddr *) &serverStruct, sizeof (struct sockaddr)) == -1)
      {
        QMessageBox msg;
        msg.setText("Error binding");
        msg.exec();
        return;
      }

    /* punem serverul sa asculte daca vin clienti sa se conecteze */
      if (listen (descrptS, 10) == -1)
        {
          QMessageBox msg;
          msg.setText("Fail to set up listening");
          msg.exec();
          return;
      }

      QMessageBox msg;
      msg.setText("Waiting for clients");
      msg.exec();

      /* servim in mod concurent clientii... */
      pthread_t thread[MAX_THREAD];
      THREAD_STRUCT threadMemory[MAX_THREAD];
      int numberOfActiveThreads = 0;
      while (1)
        { 
          int client1;
          int client2;
          struct sockaddr_in clientStruct1;
          struct sockaddr_in clientStruct2;
          /* pregatirea structurii client */
          socklen_t len1 = sizeof (clientStruct1);
          socklen_t len2 = sizeof (clientStruct1);
          bzero (&clientStruct1, sizeof (clientStruct1));

          /* a venit un client, acceptam conexiunea */
          client1 = accept (descrptS, (struct sockaddr *) &clientStruct1, &len1);

          while(!Login(client1)){
            client1 = accept (descrptS, (struct sockaddr *) &clientStruct1, &len1);
          }

          //client2 = accept (descrptS, (struct sockaddr *) &clientStruct2, &len2);

          //while(!Login(client2)){
            //client2 = accept (descrptS, (struct sockaddr *) &clientStruct2, &len2);
          //}
          threadMemory[numberOfActiveThreads].fd1 = client1;
          threadMemory[numberOfActiveThreads].fd2 = client2;
          threadMemory[numberOfActiveThreads].MainW = this;
          pthread_create(&thread[numberOfActiveThreads],NULL,threadFunction,&threadMemory[numberOfActiveThreads]);

         }



}




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

void MainWindow::initClients(MainWindow* M,int client1,int client2){
    char messageInitClient1[5];
    char messageInitClient2[5];
    for(int i = 0; i < 5; ++i){
        messageInitClient1[i] = rand() % 29;
        messageInitClient2[i] = rand() % 29;
    }
    write(client1,&messageInitClient1,sizeof(messageInitClient1));
    write(client2,&messageInitClient2,sizeof(messageInitClient1));

    for(int i = 2; i < 18; ++i){
        M->statsClient1[i] = 5;
        M->statsClient2[i] = 5;

    }
}
