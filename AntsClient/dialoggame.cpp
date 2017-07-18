#include "dialoggame.h"
#include "ui_dialoggame.h"

#define MAX_CARDS 30

DialogGame::DialogGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGame)
{
    ui->setupUi(this);
}

DialogGame::~DialogGame()
{
    delete ui;
}

void DialogGame::setServerDescript(int sd){
    serverDescript = sd;
}

void DialogGame::setCards(){
    Cards[0]  = "Curse\n(-25 crystals)\n+1 allstats\n-1 enemy allstats";
    Cards[1]  = "School\n(-8 bricks)\n+1 builder";
    Cards[2]  = "Soldier\n(-8 weapons)\n+1 soldier";
    Cards[3]  = "Sorcerer\n(-8 crystals)\n+1 magi";
    Cards[4]  = "Conjure\n(-4 crystals)\n+8 bricks";
    Cards[5]  = "Conjure\n(-4 crystals)\n+8 weapons";
    Cards[6]  = "Conjure\n(-4 crystals)\n+8 crystals";
    Cards[7]  = "Fence\n(-1 brick)\n+3 fence";
    Cards[8]  = "Fence\n(-3 brick)\n+6 fence";
    Cards[9]  = "Fence\n(-12 brick)\n+22 fence";
    Cards[10] = "Base\n(-1 brick)\n+2 castle";
    Cards[11] = "Tower\n(-5 bricks)\n+5 castle";
    Cards[12] = "Reserve\n(-3 bricks)\n+8 castle -4 fence";
    Cards[13] = "Wain\n(-10 bricks)\n+8 castle -4 enemy castle";
    Cards[14] = "Fort\n(-18 bricks)\n+20 castle";
    Cards[15] = "Pixies\n(-22 crystals)\n+22 castle";
    Cards[16] = "Babylon\n(-39 bricks)\n+32 castle";
    Cards[17] = "Archer\n(-1 weapons)\n-2 enemy castle/fence";
    Cards[18] = "Knight\n(-2 weapons)\n-3 enemy castle/fence";
    Cards[19] = "Rider\n(-2 weapons)\n-4 enemy castle/fence";
    Cards[20] = "Platoon\n(-4 weapons)\n-6 enemy castle/fence";
    Cards[21] = "Catapult\n(-10 weapons)\n-12 enemy castle/fence";
    Cards[22] = "SWAT\n(-18 weapons)\n-10 enemy castle";
    Cards[23] = "Dragon\n(-21 crystals)\n-25 enemy castle";
    Cards[24] = "Banshee\n(-28 weapons)\n-32 enemy castle/fence";
    Cards[25] = "Crush\n(-4 crystals)\n-8 enemy weapons";
    Cards[26] = "Crush\n(-4 crystals)\n-8 enemy bricks";
    Cards[27] = "Crush\n(-4 crystals)\n-8 enemy crystals";
    Cards[28] = "Saboteur\n(-12 weapons)\n-4 enemy stocks ";
    Cards[29] = "Thief\n(-15 weapons)\ntransfer enemy stocks (5)";
}


void DialogGame::on_pushButton_clicked()
{
    ui->pushButton_6->setText(ui->pushButton->text());

    bufferCard = availableCards[1];
    returnCard = 1;

    on_pushButton_6_clicked();
}

void DialogGame::on_pushButton_2_clicked()
{
    ui->pushButton_6->setText(ui->pushButton_2->text());

    bufferCard = availableCards[2];
    returnCard = 2;

    on_pushButton_6_clicked();
}

void DialogGame::on_pushButton_3_clicked()
{

    ui->pushButton_6->setText(ui->pushButton_3->text());

    bufferCard = availableCards[3];
    returnCard = 3;

    on_pushButton_6_clicked();
}

void DialogGame::on_pushButton_4_clicked()
{

    ui->pushButton_6->setText(ui->pushButton_4->text());

    bufferCard = availableCards[4];
    returnCard = 4;

    on_pushButton_6_clicked();
}

void DialogGame::on_pushButton_5_clicked()
{

    ui->pushButton_6->setText(ui->pushButton_5->text());


    bufferCard = availableCards[5];
    returnCard = 5;

    on_pushButton_6_clicked();
}

void DialogGame::on_pushButton_6_clicked()
{
    if(first)enableCards();
    else    disableCards();

    ui->pushButton_6->setEnabled(false);
   // delete pointerForDeleteThread;

    InputThread *inputThread =  new InputThread;

    pointerForDeleteThread = inputThread;

    inputThread->firstT = first;

    static bool FirstTime = true;
    if(!FirstTime && first){
        inputThread->cardT = availableCards[returnCard];
        for(int i = 1; i <= 5; ++i){
            inputThread->availableCardsT[i] = availableCards[i];
        }
    }else
        FirstTime = false;
    inputThread->serverDescriptT = serverDescript;

    QObject::connect(inputThread,SIGNAL(signalGUI(const QString&)),this,SLOT(updateInputsFromThread(const QString&)),Qt::QueuedConnection);

    inputThread->start();
}


void DialogGame::setFirstTime(){

    disableCards();
    int buffer[6];

    while(1 > read(serverDescript,&buffer,sizeof(buffer)));
    for(int i = 0; i < 6; ++i){
        availableCards[i] = buffer[i];
    }
    first = availableCards[0];
    pointerForDeleteThread = NULL;

    ui->pushButton->setText(Cards[availableCards[1]]);
    ui->pushButton_2->setText(Cards[availableCards[2]]);
    ui->pushButton_3->setText(Cards[availableCards[3]]);
    ui->pushButton_4->setText(Cards[availableCards[4]]);
    ui->pushButton_5->setText(Cards[availableCards[5]]);
    ui->pushButton_6->setText("Press\nHere\nTo START");



}


void DialogGame::enableCards(){
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
    ui->pushButton_5->setDisabled(false);
}


void DialogGame::disableCards(){
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);

}

void DialogGame::updateInputsFromThread(const QString &string){


    QByteArray numbers[19];
    QByteArray chars = string.toLocal8Bit();
    char *myString = chars.data();
    char *p = strtok(myString, "|");
    int i = 0;
    while (p) {
        numbers[i].append(p);
        p = strtok(NULL, "|");
        i++;
    }

    int valuesToBeupdated[19];
    bool ok;
    for(int i = 0; i < 19; ++i){
        QString myValue(numbers[i]);
        valuesToBeupdated[i] = myValue.toInt(&ok,10);
    }

    ui->pushButton_6->setText(Cards[valuesToBeupdated[0]]);
    if(!first){
        enableCards();
        first = true;
    }else {
        availableCards[returnCard] = valuesToBeupdated[1];
        first = false;
        disableCards();
    }


    switch(returnCard){
        case 1:
            if(valuesToBeupdated[1] != -1)
                ui->pushButton->setText(Cards[valuesToBeupdated[1]]);
            break;
        case 2:
            if(valuesToBeupdated[1] != -1)
                ui->pushButton_2->setText(Cards[valuesToBeupdated[1]]);
            break;
        case 3:
            if(valuesToBeupdated[1] != -1)
                ui->pushButton_3->setText(Cards[valuesToBeupdated[1]]);
            break;
        case 4:
            if(valuesToBeupdated[1] != -1)
                ui->pushButton_4->setText(Cards[valuesToBeupdated[1]]);
            break;
        case 5:
            if(valuesToBeupdated[1] != -1)
                ui->pushButton_5->setText(Cards[valuesToBeupdated[1]]);
            break;
    }

    //player view stats

    QString status;
    status = "+";
    status.append(QString("%1").arg(valuesToBeupdated[2]));
    ui->builders->setText(status);

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[3]));
    ui->bricks->setText(status);

    status.clear();
    status = "+";
    status.append(QString("%1").arg(valuesToBeupdated[4]));
    ui->soldiers->setText(status);

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[5]));
    ui->weapons->setText(status);

    status.clear();
    status = "+";
    status.append(QString("%1").arg(valuesToBeupdated[6]));
    ui->magi->setText(status);

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[7]));
    ui->crystals->setText(status);

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[8]));
    ui->castle->setText(status);

    ui->progressBar->setValue(valuesToBeupdated[8]);//the castle

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[9]));
    ui->fence->setText(status);

    ui->progressBar_2->setValue(valuesToBeupdated[9]);//the fence

    //enemy view stats

    status.clear();
    status = "+";
    status.append(QString("%1").arg(valuesToBeupdated[10]));
    ui->builders_2->setText(status);

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[11]));
    ui->bricks_2->setText(status);

    status.clear();
    status = "+";
    status.append(QString("%1").arg(valuesToBeupdated[12]));
    ui->soldiers_2->setText(status);

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[13]));
    ui->weapons_2->setText(status);

    status.clear();
    status = "+";
    status.append(QString("%1").arg(valuesToBeupdated[14]));
    ui->magi_2->setText(status);

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[15]));
    ui->crystals_2->setText(status);

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[16]));
    ui->castle_2->setText(status);

    ui->progressBar_3->setValue(valuesToBeupdated[16]);//the enemy castle

    status.clear();
    status.append(QString("%1").arg(valuesToBeupdated[17]));
    ui->fence_2->setText(status);

    ui->progressBar_4->setValue(valuesToBeupdated[17]);//the enemy fence

    if(valuesToBeupdated[18] == 0){
        QMessageBox msg;

        msg.setText("Game Over! You Lost!");
        disableCards();
        msg.exec();
        ::close(serverDescript);
        return;
    }

    if(valuesToBeupdated[18] == 1){
        QMessageBox msg;
        msg.setText("Game Over! You Won!");
        disableCards();
        ::close(serverDescript);
        msg.exec();
        return;
    }

    if(!first) on_pushButton_6_clicked();
}
