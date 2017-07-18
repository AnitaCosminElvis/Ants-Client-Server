#ifndef DIALOGGAME_H
#define DIALOGGAME_H

#include <QDialog>

#include <QMessageBox>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "thread_class_define.h"


namespace Ui {
class DialogGame;
}

class DialogGame : public QDialog
{
    Q_OBJECT
private:
    Ui::DialogGame *ui;
    
public:
    InputThread *pointerForDeleteThread;
    bool first;
    int serverDescript;
    QString Cards[30];
    int availableCards[6];
    int bufferCard;
    int returnCard;

    explicit DialogGame(QWidget *parent = 0);

    ~DialogGame();

    void setServerDescript(int);
    void setCards();
    void setFirstTime();
    void enableCards();
    void disableCards();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void updateInputsFromThread(const QString &string);
};

#endif // DIALOGGAME_H
