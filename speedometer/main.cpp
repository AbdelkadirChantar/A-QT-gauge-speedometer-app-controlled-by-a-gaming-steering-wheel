#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "speedometer.h"
#include <QTimer>
#include <iostream>
#include <fstream>
#include <QTime>
#include <string>
#include <unistd.h>
qreal val = 0;

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

/*
class IPC: public QObject
{
    Q_OBJECT

signals:
    void new_data(){};

};

IPC* myIPC;

int DoWork()
{
    using namespace std;
    char data[8];
    char init_data[145] = {0};

    int i = 0;
    ifstream joystick("/dev/input/js0", ios::binary);

    joystick.read(init_data, 144);
    for (int j = 0; j < 145; j++)
    {
        printf("%02x, ", *((uint8_t*)&init_data[j]));
    }
    cout << endl;
    while(true)
    {
        joystick.read(data, 8);
        //printf("[%d] ", i);
        //printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(*((uint8_t*)&data[0])));

        for (int j = 1; j < 8; j++)
        {
            //printf("%02x, ", *((uint8_t*)&data[j]));
        }
        cout << endl;
        i++;
        uint8_t ID=*((uint8_t*)&data[7]);
        printf("%d",ID);
       // emit myIPC->new_data();
    }

}
*/
int main(int argc, char *argv[])
{/*
    myIPC = new IPC();

    //std::thread worker(DoWork);

    //worker.join();

    std::cin.get();
    */

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Speedometer>("com.ulasdikme.speedometer",1,0,"Speedometer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *object = engine.rootObjects()[0];
    QObject *speedometer = object->findChild<QObject*>("speedoMeter");

    Speedometer *ptrSpeedometer = qobject_cast<Speedometer*>(speedometer);
    //Speedometer *ptrSpeedometer = dynamic_cast<Speedometer*>(speedometer);
    qreal val = 0;

        bool direction = true;
    QTimer timer;

    using namespace std;
    char data[8];
    char init_data[145] = {0};

    int i = 0;
    int ID=0;
    int accel=25;
/*
    QObject::connect(myIPC, &IPC::new_data, [&]()
        {
            printf("new msg \n");
        });

    emit myIPC->new_data();

    //auto worker = QThread::create(DoWork);

*/


            QObject::connect(&timer, &QTimer::timeout, [&]()
             {printf("timer is here");
                if(val < 4000){
                        ptrSpeedometer->setOuterColor(QColor(54, 50, 168));
                        ptrSpeedometer->setTextColor(QColor(255, 255, 255));
                        }
                else if(val > 4000 && val < 8000){
                        ptrSpeedometer->setOuterColor(QColor(168, 50, 125));
                        ptrSpeedometer->setTextColor(QColor(255, 255, 255));
                        }
                else if(val > 8000){
                        ptrSpeedometer->setOuterColor(QColor(168, 50, 50));
                        ptrSpeedometer->setTextColor(QColor(168, 50, 50));
                        }

             /*   if(val >= 4000)
                            direction = false;
                        else if(val <= 0.1)
                            direction = true;

                        if(direction)
                           val = val + 10;
                        else
                            val = val - 10;
*/



            });

            QTimer timer2;

            QObject::connect(&timer2,&QTimer::timeout, [&]()
               {
                ifstream joystick("/dev/input/js0", ios::binary);

                joystick.read(init_data, 144);
                for (int j = 0; j < 145; j++)
                {
                    printf("%02x, ", *((uint8_t*)&init_data[j]));
                }
                cout << endl;

                {
                    joystick.read(data, 8);
                    //printf("[%d] ", i);
                    //printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(*((uint8_t*)&data[0])));

                    for (int j = 1; j < 8; j++)
                    {
                        //printf("%02x, ", *((uint8_t*)&data[j]));
                    }
                    cout << endl;
                    i++;
                    ID=*((uint8_t*)&data[7]);
                    accel=*((uint8_t*)&data[4]);

                    printf("%d",ID);
                    printf("%d",accel);

                  }





            });

        QTimer timer3;

            QObject::connect(&timer3, &QTimer::timeout, [&]()
             {
                if(ID!=3){
                    val= val +30;
                   ;
                    if(val > 10400)
                        val=10400;
                }

                if(ID==3)

                {
                    val = val - 50;
                    if(val<0)
                        val=0;
            }
              /*  else{

                    val= val -5;
                     if(val<0)
                        val=0;}*/
                ptrSpeedometer->setSpeed(val);

            });












            timer2.start(180);
            //TODO: pretend first timer to update the data before start the seond timer
            timer.start(10);
            timer3.start(10);


           // timer2.start(180);

    return app.exec();

}



