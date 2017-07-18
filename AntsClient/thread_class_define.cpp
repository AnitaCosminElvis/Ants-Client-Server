#include "thread_class_define.h"

void InputThread::run()
{
    int valuesToBeupdated[19];
    static bool firstTime = true;

    //special case
    if(firstTime){
        firstTime = false;
        if(firstT){
            return;
        }
        if(!firstT){
            read(serverDescriptT,&valuesToBeupdated,sizeof(valuesToBeupdated));
        }
    }else{
        if(firstT){
            availableCardsT[0] = cardT;
            write(serverDescriptT,&availableCardsT,sizeof(availableCardsT));

            read(serverDescriptT,&valuesToBeupdated,sizeof(valuesToBeupdated));

        }else{
            read(serverDescriptT,&valuesToBeupdated,sizeof(valuesToBeupdated));

        }
    }
    QString string;

    for(int i = 0; i < 19; ++i){
        string.append(QString("%1").arg(valuesToBeupdated[i]));
        string += "|";
    }

    emit signalGUI(string);
}
