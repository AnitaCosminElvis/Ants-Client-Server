#ifndef THREAD_CLASS_DEFINE_H
#define THREAD_CLASS_DEFINE_H

#include <QThread>
#include <QMutex>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>


class InputThread : public QThread
{
   Q_OBJECT
public:
    bool firstT;
    int serverDescriptT;
    int cardT;
    int availableCardsT[6];
public:
   virtual void run();

signals:
    void signalGUI(QString);
};


#endif // THREAD_CLASS_DEFINE_H
