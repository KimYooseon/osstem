#ifndef CLIENTLOGTHREAD_H
#define CLIENTLOGTHREAD_H

#include <QThread>
#include <QList>

class QTreeWidgetItem;

class ClientLogThread : public QThread
{
    Q_OBJECT
public:
    explicit ClientLogThread(QObject *parent = nullptr);
private:
    void run();

    QList<QTreeWidgetItem*> itemList;
    QString filename;
    QString clientname;
    QString format;
signals:
    void send(int data);

public slots:
    void appendData(QTreeWidgetItem*);  //데이터들을 itemList에 추가해줌
    void saveData();                    //채팅로그를 저장
};


#endif // CLIENTLOGTHREAD_H
