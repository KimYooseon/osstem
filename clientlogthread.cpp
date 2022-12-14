#include "clientlogthread.h"

#include <QTreeWidgetItem>
#include <QFile>
#include <QDateTime>

ClientLogThread::ClientLogThread(QObject *parent)
    : QThread{parent}
{



    format = "yyyyMMdd_hhmm"; //로그파일의 이름 형식 지정. ex. 20221026_0916
    filename = QString("client_logthread_%1_%2.txt").arg(clientname).arg(QDateTime::currentDateTime().toString(format));    //현재 시간을 만들어 둔 형식에 맞게 txt파일로 만들어 줌
}

void ClientLogThread::run()
{
    Q_FOREVER {
        saveData();
        sleep(60);      // 1분마다 저장
    }
}

/*데이터들을 itemList에 추가해줌*/
void ClientLogThread::appendData(QTreeWidgetItem* item)
{
    itemList.append(item);
}

/*채팅로그를 저장*/
void ClientLogThread::saveData()
{
    QString name;
    //QString format = "yyyyMMdd"; //로그파일의 이름 형식 지정. ex. 20221026_091623
    if(itemList.count() > 0) {

        QFile file(filename);       //현재 시간을 담은 파일이름.txt 파일을 만듦
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        foreach(auto item, itemList) {
            clientname = item->text(2);
            out << item->text(0) << ", ";   //아이템의 0번째 인덱스 값을 ", "과 함께 저장
            out << item->text(1) << ", ";   //아이템의 1번째 인덱스 값을 ", "과 함께 저장
            out << item->text(2) << ", ";   //아이템의 2번째 인덱스 값을 ", "과 함께 저장
            out << item->text(3) << ", ";   //아이템의 3번째 인덱스 값을 ", "과 함께 저장
            out << item->text(4) << ", ";   //아이템의 4번째 인덱스 값을 ", "과 함께 저장
            out << item->text(5) << "\n";   //아이템의 5번째 인덱스 값을 "\n "과 함께 저장
        }

        file.close();
        file.rename(QString("client_logthread_%1_%2.txt").arg(clientname).arg(QDateTime::currentDateTime().toString(format)));
    }
}

