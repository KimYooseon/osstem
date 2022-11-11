#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
#include "clientitem.h"

#include <QFile>
#include <QMenu>
#include <QApplication>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QStandardItemModel>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{

    //    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //    db.setDatabaseName("data.db");
    //    if(!db.open()) return;

    //    QSqlQuery query;
    //    query.exec("CREATE TABLE IF NOT EXISTS person(c_id INTEGER Primary Key,"
    //               "c_name VARCHAR(100) NOT NULL, c_phonenum VARCHAR(200) NOT NULL, c_addr VARCHAR(100) NOT NULL);");

    //ui 설정 부분
    ui->setupUi(this);

    ui->treeWidget->hide();

    //위젯의 사이즈 설정. 540은 전체 화면의 왼쪽에 해당하는 비중, 400은 전체 화면의 오른쪽에 해당하는 비중
    QList<int> sizes;
    sizes << 540 << 400;
    ui->splitter->setSizes(sizes);

    //remove 액션 추가. remove를 클릭했을 때 아이템이 삭제되도록 만듦
    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    //메뉴를 생성하고 remove 액션을 메뉴에 추가
    menu = new QMenu;
    menu->addAction(removeAction);

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->clientTableView->setContextMenuPolicy(Qt::CustomContextMenu);

    //트리위젯의 컬럼별 너비 설정
    ui->treeWidget->setColumnWidth(0,50);
    ui->treeWidget->setColumnWidth(1,70);
    ui->treeWidget->setColumnWidth(2,110);

    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    connect(ui->clientTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));


    searchModel = new QStandardItemModel(0, 4);
    searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    searchModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
    searchModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
    ui->searchTableView->setModel(searchModel);
}

void ClientManagerForm::loadData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "clientConnection");
    db.setDatabaseName("clientlist.db");
    if (db.open( )) {
        query= new QSqlQuery(db);
        query->exec("CREATE TABLE IF NOT EXISTS clientlist(c_id INTEGER Primary Key, c_name VARCHAR(30) NOT NULL, c_phonenum VARCHAR(20) NOT NULL, c_address VARCHAR(50));");

        clientModel = new QSqlTableModel(this, db);
        clientModel->setTable("clientlist");
        clientModel->select();
        clientModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        clientModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        clientModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
        clientModel->setHeaderData(3, Qt::Horizontal, tr("Address"));

        ui->clientTableView->setModel(clientModel);

        /*테이블 컬럼 사이즈 조절*/
        ui->clientTableView->setColumnWidth(0,100);
        ui->clientTableView->setColumnWidth(1,150);
        ui->clientTableView->setColumnWidth(2,200);
        ui->clientTableView->setColumnWidth(3,480);
        //ui->clientTableView->resizeColumnsToContents();


    }

    for(int i = 0; i < clientModel->rowCount(); i++) {
        int id = clientModel->data(clientModel->index(i, 0)).toInt();
        QString name = clientModel->data(clientModel->index(i, 1)).toString();
        qDebug() << "id: " <<id;
        qDebug() << "name: " <<name;

        //clientList.insert(id, clientModel->index(i, 0));
        emit clientAdded(name, id);
    }
}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("clientConnection");
    if(db.isOpen()) {
        clientModel->submitAll();
        delete clientModel;
        db.close();
        QSqlDatabase::removeDatabase("clientConnection");
    }
}

/*
ClientManagerForm::~ClientManagerForm()
{
    delete ui;

    QSqlDatabase db = QSqlDatabase::database("clientConnection");
    if(db.isOpen()) {
        clientModel->submitAll();
        db.close();
        QSqlDatabase::removeDatabase("clientConnection");
    }

    //파일을 저장함
    QFile file("clientlist.txt");           //clientlist.txt를 열음
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);                 //파일이 있을 때
    for (const auto& v : clientList) {      //for문을 통해 clientList의 값을 하나씩 가져옴
        ClientItem* c = v;                  //c에 각각의 값들을 저장해 줌
        out << c->id() << ", " << c->getName() << ", ";
        out << c->getPhoneNumber() << ", ";
        out << c->getAddress() << "\n";
    }
    file.close( );
}
*/

/*고객아이디 만들기*/
int ClientManagerForm::makeId( )
{
    if(clientModel->rowCount() == 0) {           //고객아이디가 없으면 1번부터 고객아이디를 부여
        return 1;
    } else {
        auto id = clientModel->data(clientModel->index(clientModel->rowCount()-1, 0)).toInt();     //clientlist의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
        return ++id;
    }
}

/*아이템 삭제*/
void ClientManagerForm::removeItem()
{
    int i;
    QTreeWidgetItem* item = ui->treeWidget->currentItem();      //treeWidget에 추가할 아이템을 만들어 줌

    if(item != nullptr) {                                       //아이템이 있을 때
        i = ui->treeWidget->currentIndex().row();           //i는 현재 인덱스 줄 번호
        qDebug()<<i;
        //clientList.remove(item->text(0).toInt());               //고객리스트에서 아이템의 첫번째 컬럼에 해당하는 아이템을 삭제해 줌
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));    //해당하는 고객을 treeWidget에서도 삭제해줌

        ui->treeWidget->update();                               //treeWidget 업데이트
        //emit clientRemoved(i);                                  //삭제한 인덱스 정보를 쇼핑매니저로 보내줌
    }

    QModelIndex idx = ui->clientTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();

    int row = idx.row();

    query->prepare("DELETE FROM clientlist WHERE c_id = ?;");
    query->addBindValue(delid);
    query->exec();
    clientModel->select();
    emit clientRemoved(row);
}

/*treeWidget 영역에서 마우스 오른쪽버튼 클릭했을 때 메뉴가 나오게 해주는 부분*/
void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    /*QPoint globalPos = ui->treeWidget->mapToGlobal(pos);    //위치를 구해줌
    menu->exec(globalPos);   */                               //그 위치에 메뉴가 뜨게 만들어 줌

    QPoint globalPos = ui->clientTableView->mapToGlobal(pos);
    menu->exec(globalPos);
}

/*search 버튼 클릭 시 해당하는 정보가 searchTreeWidget에 뜨게 만들어 줌*/
void ClientManagerForm::on_searchPushButton_clicked()
{
    searchModel->clear();

    ui->searchTreeWidget->clear();                  //search 버튼 다시 누르기 전에 저장되어 있었던 정보를 지워줌
    int i = ui->searchComboBox->currentIndex();     //i에 검색콤보박스의 현재인덱스 번호를 저장해준다
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains   //flag값을 지정해 줌. i가 0이 아닐 때는 입력한 값이 포함되면 검색이 되도록 만듦
                   : Qt::MatchCaseSensitive;                    //i가 0이 아닌 값일 때는 입력한 값이 정확할 때만 검색이 되도록 만듦
    QModelIndexList clients = clientModel->match(clientModel->index(0,i),Qt::EditRole, ui->searchLineEdit->text(),-1,Qt::MatchFlags(flag));


    foreach(auto ix,clients) {
        int id =ix.sibling(ix.row(),0).data().toInt();
        QString name = ix.sibling(ix.row(),1).data().toString();
        QString number =ix.sibling(ix.row(),2).data().toString();
        QString address = ix.sibling(ix.row(),3).data().toString();
        QStringList clientStrings;
        clientStrings << QString::number(id)<<name<<number<<address;

        QList<QStandardItem *> items;
        for (int i = 0; i < 4; ++i) {
            items.append(new QStandardItem(clientStrings.at(i)));
        }

        searchModel->appendRow(items);

        searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        searchModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
        searchModel->setHeaderData(3, Qt::Horizontal, tr("Address"));

        //ui->searchTableView->resizeColumnsToContents();

//        new QTreeWidgetItem(ui->searchTreeWidget,clientStrings);
//        for(int i = 0; i<ui->searchTreeWidget->columnCount(); i++)
//            ui->searchTreeWidget->resizeColumnToContents(i);
    }

}

/*수정버튼이 눌렸을 때*/
void ClientManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();      //item에 treeWidget의 현재 아이템을 넣어줌


    QString name, number, address;
    int cid = ui->idLineEdit->text().toInt();
    name = ui->nameLineEdit->text();                        //nameLineEdit에 입력한 값을 변수 name에 저장해준다
    number = ui->phoneNumberLineEdit->text();               //phoneNumberLineEdit에 입력한 값을 변수 name에 저장해준다
    address = ui->addressLineEdit->text();                  //addressLineEdit에 입력한 값을 변수 name에 저장해준다

    QModelIndex idx = ui->clientTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();

    int row = idx.row();

    //QSqlQuery query;
    query->prepare("UPDATE clientlist SET c_name=?, c_phonenum=?, c_address=? WHERE c_id=?");
    query->bindValue(0, name);
    query->bindValue(1, number);
    query->bindValue(2, address);
    query->bindValue(3, cid);
    query->exec();
    clientModel->select();

    emit clientModified(name, cid, row);


    if(item != nullptr) {                                       //item이 있을 때
        int key = item->text(0).toInt();                        //item의 0번째 인덱스 값인 고객번호를 key에 저장함
        //ClientItem* c = clientList[key];                        //clientList[key]에 해당하는 값을 ClientItem에 저장해준다
        int i = ui->treeWidget->currentIndex().row();           //treeWidget의 현재 인덱스 줄 번호를 i에 저장

        //c->setName(name);
        //c->setPhoneNumber(number);
        //c->setAddress(address);
        //clientList[key] = c;                                    //clientList[key]에 c를 넣어준다

        //emit clientModified(name, key, i);                      //name, key, i를 시그널을 통해 shopmanagerform으로 보내준다

    }

}


/*add 버튼을 클릭했을 때*/
/*void ClientManagerForm::on_addPushButton_clicked()
{
    QString name, number, address;
    int id = makeId( );
    ui->idLineEdit->setText(QString::number(id));
    name = ui->nameLineEdit->text();
    number = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    QSqlDatabase db = QSqlDatabase::database("clientConnection");
    if(db.isOpen() && name.length()) {
        QSqlQuery query(clientModel->database());
        query.prepare("INSERT INTO client VALUES (?, ?, ?, ?)");
        query.bindValue(0, id);
        query.bindValue(1, name);
        query.bindValue(2, number);
        query.bindValue(3, address);
        query.exec();
        clientModel->select();
        ui->clientTableView->resizeColumnsToContents();
        emit clientAdded(name, id);
    }
}*/

void ClientManagerForm::on_addPushButton_clicked()
{
    QString name, number, address;

    int id = makeId( );                             //makeId()를 통해 새로운 고객 id 값을 추가해 줌

    //lineEdit에 정보를 적지 않은 채로 add버튼을 눌렀을 때
    if(ui->nameLineEdit->text() == "" || ui->phoneNumberLineEdit->text() == "" || ui->addressLineEdit->text() == "")
    {
        return;                                 //그냥 리턴해줘서 아무 일도 일어나지 않게끔 해 줌
    }
    name = ui->nameLineEdit->text();            //nameLineEdit에 입력한 값을 변수 name에 저장해준다
    number = ui->phoneNumberLineEdit->text();   //phoneNumberLineEdit에 입력한 값을 변수 name에 저장해준다
    address = ui->addressLineEdit->text();      //addressLineEdit에 입력한 값을 변수 name에 저장해준다
    if(name.length()) {                         //이름 길이가 1이상일 때만 if문 실행
        ClientItem* c = new ClientItem(id, name, number, address);
        //clientList.insert(id, c);               //clientList에 정보들을 넣어줌
        ui->treeWidget->addTopLevelItem(c);     //treeWidget에 c값을 추가해 줌
        //ui->clientTableView->resizeColumnsToContents();
        emit clientAdded(name, id);             //clientAdded 시그널에 name과 id를 담아 shopmanagerform으로 정보를 보내준다
    }

    //QSqlQuery query;
    query->exec(QString("INSERT INTO clientlist VALUES (%1, '%2', '%3', '%4')").arg(id).arg(name).arg(number).arg(address));
    clientModel->select();


}


/*treeWidget에 있는 item을 클릭했을 때*/
void ClientManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);   //매개변수인 column을 사용하지 않았을 때 오류가 생기지 않게 해 줌
    ui->idLineEdit->setText(item->text(0));             //item의 인덱스 0번 값에 고객id를 저장해 줌
    ui->nameLineEdit->setText(item->text(1));           //item의 인덱스 1번 값에 고객이름를 저장해 줌
    ui->phoneNumberLineEdit->setText(item->text(2));    //item의 인덱스 2번 값에 고객전화번호를 저장해 줌
    ui->addressLineEdit->setText(item->text(3));        //item의 인덱스 3번 값에 고객주소를 저장해 줌
    ui->toolBox->setCurrentIndex(0);                    //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정
}


void ClientManagerForm::on_clientTableView_clicked(const QModelIndex &index)
{
    //QModelIndex idx = ui->clientTableView->currentIndex();
    int id = index.sibling(index.row(), 0).data().toInt();
    QString name = index.sibling(index.row(), 1).data().toString();
    QString phonenum = index.sibling(index.row(), 2).data().toString();
    QString address = index.sibling(index.row(), 3).data().toString();

    ui->idLineEdit->setText(QString::number(id));             //item의 인덱스 0번 값에 고객id를 저장해 줌
    ui->nameLineEdit->setText(name);           //item의 인덱스 1번 값에 고객이름를 저장해 줌
    ui->phoneNumberLineEdit->setText(phonenum);    //item의 인덱스 2번 값에 고객전화번호를 저장해 줌
    ui->addressLineEdit->setText(address);        //item의 인덱스 3번 값에 고객주소를 저장해 줌
    ui->toolBox->setCurrentIndex(0);                    //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정
}




void ClientManagerForm::on_clientTableView_itemClicked(QTableView *item, int column){
    Q_UNUSED(column);   //매개변수인 column을 사용하지 않았을 때 오류가 생기지 않게 해 줌
    //ui->idLineEdit->setText(item->selectColumn(0));             //item의 인덱스 0번 값에 고객id를 저장해 줌
    //ui->nameLineEdit->setText(item->text(1));           //item의 인덱스 1번 값에 고객이름를 저장해 줌
    //ui->phoneNumberLineEdit->setText(item->text(2));    //item의 인덱스 2번 값에 고객전화번호를 저장해 줌
    //ui->addressLineEdit->setText(item->text(3));        //item의 인덱스 3번 값에 고객주소를 저장해 줌
    //ui->toolBox->setCurrentIndex(0);                    //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정


}


/*shopmanagerform에서 cid를 받는 부분*/
void ClientManagerForm::CIDsended(int id){

    //ClientItem *c = clientList[id]; //받은 cid에 대한 정보들을 c에 저장하고, name, phonenumber, address를 각각 변수에 저장해준다
    //QString name = c->getName();
    //QString phonenumber = c->getPhoneNumber();
    //QString address = c->getAddress();

    //int i = ui->searchComboBox->currentIndex();
    auto flag = Qt::MatchCaseSensitive|Qt::MatchContains;   //flag값을 지정해 줌. i가 0이 아닐 때는 입력한 값이 포함되면 검색이 되도록 만듦

    QModelIndexList clients = clientModel->match(clientModel->index(0,0),Qt::EditRole, id,-1,Qt::MatchFlags(flag));


    foreach(auto ix,clients) {
        //int id =ix.sibling(ix.row(),0).data().toInt();
        QString name = ix.sibling(ix.row(),1).data().toString();
        QString number =ix.sibling(ix.row(),2).data().toString();
        QString address = ix.sibling(ix.row(),3).data().toString();
        QStringList clientStrings;
        clientStrings << QString::number(id)<<name<<number<<address;
        new QTreeWidgetItem(ui->searchTreeWidget,clientStrings);
        for(int i = 0; i<ui->searchTreeWidget->columnCount(); i++)
            ui->searchTreeWidget->resizeColumnToContents(i);

        emit sendCInfo(name, number, address);

    }

    //emit sendCInfo(name, number, address);

    //emit sendCInfo(name, phonenumber, address); //name, phonenumber, address의 값들을 shopmanagerform으로 보내준다



}

/*
bool ClientManagerForm::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "clientConnection");
    db.setDatabaseName("client.db");
    if(!db.open()) return false;

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS client(c_id INTEGER Primary Key,"
               "c_name VARCHAR(100) NOT NULL, c_phonenum VARCHAR(200) NOT NULL, c_addr VARCHAR(100) NOT NULL);");

    return true;
}
*/

