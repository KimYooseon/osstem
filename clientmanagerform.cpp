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
    //ui 설정 부분
    ui->setupUi(this);

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

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    /*clientTableView가 ContextMenu를 어떻게 보여줄지 결정.*/
    ui->clientTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    /*customMenu가 요청될 때 ContextMenu를 보여준다*/
    connect(ui->clientTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    /*테이블 뷰의 헤더 설정*/
    searchModel = new QStandardItemModel(0, 4);
    searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    searchModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
    searchModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
    ui->searchTableView->setModel(searchModel);
}

void ClientManagerForm::loadData()
{
    /*DB를 추가하고 DB의 이름을 설정*/
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "clientConnection");
    db.setDatabaseName("clientlist.db");

    /*DB를 오픈해 새로운 테이블을 만듦*/
    if (db.open( )) {
        query= new QSqlQuery(db);
        query->exec("CREATE TABLE IF NOT EXISTS clientlist(c_id INTEGER Primary Key, c_name VARCHAR(30) NOT NULL, c_phonenum VARCHAR(20) NOT NULL, c_address VARCHAR(50));");

        /*Model을 만들고 테이블의 헤더 설정*/
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
    }

    /*Model의 줄 수를 세 id와 name을 저장하여 shopmanagerform에 이름과 id를 보내준다*/
    for(int i = 0; i < clientModel->rowCount(); i++) {
        int id = clientModel->data(clientModel->index(i, 0)).toInt();
        QString name = clientModel->data(clientModel->index(i, 1)).toString();

        emit clientAdded(name, id);
    }
}

/*DB가 오픈되어 있으면 모델에 정보를 submit해주고 해당 DB를 종료한다.*/
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

    /*지우려고 하는 아이템의 row를 delete로 제거하고, 제거한 해당 row값을 emit으로 보내줌*/
    QModelIndex idx = ui->clientTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();
    int row = idx.row();
    query->prepare("DELETE FROM clientlist WHERE c_id = ?;");
    query->addBindValue(delid);
    query->exec();
    clientModel->select();
    emit clientRemoved(row);
}

/*tableView 영역에서 마우스 오른쪽버튼 클릭했을 때 메뉴가 나오게 해주는 부분*/
void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->clientTableView->mapToGlobal(pos);
    menu->exec(globalPos);
}

/*search 버튼 클릭 시 해당하는 정보가 searchTableView에 뜨게 만들어 줌*/
void ClientManagerForm::on_searchPushButton_clicked()
{
    searchModel->clear();

    int i = ui->searchComboBox->currentIndex();     //i에 검색콤보박스의 현재인덱스 번호를 저장해준다
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains   //flag값을 지정해 줌. i가 0이 아닐 때는 입력한 값이 포함되면 검색이 되도록 만듦
                   : Qt::MatchCaseSensitive;                    //i가 0이 아닌 값일 때는 입력한 값이 정확할 때만 검색이 되도록 만듦
    QModelIndexList clients = clientModel->match(clientModel->index(0,i),Qt::EditRole, ui->searchLineEdit->text(),-1,Qt::MatchFlags(flag));


    /*id, name, number, address 값들을 clientStrings 리스트에 넣어줌*/
    foreach(auto ix,clients) {
        int id =ix.sibling(ix.row(),0).data().toInt();
        QString name = ix.sibling(ix.row(),1).data().toString();
        QString number =ix.sibling(ix.row(),2).data().toString();
        QString address = ix.sibling(ix.row(),3).data().toString();
        QStringList clientStrings;
        clientStrings << QString::number(id)<<name<<number<<address;

        /*item을 append 해줌*/
        QList<QStandardItem *> items;
        for (int i = 0; i < 4; ++i) {
            items.append(new QStandardItem(clientStrings.at(i)));
        }

        /*search 버튼을 누를 때마다 헤더가 바뀌지 않도록 만들어 줌*/
        searchModel->appendRow(items);
        searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        searchModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
        searchModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
    }

}

/*수정버튼이 눌렸을 때*/
void ClientManagerForm::on_modifyPushButton_clicked()
{
    /*cid, name, number, address 값을 저장해 줌*/
    QString name, number, address;
    int cid = ui->idLineEdit->text().toInt();
    name = ui->nameLineEdit->text();                        //nameLineEdit에 입력한 값을 변수 name에 저장해준다
    number = ui->phoneNumberLineEdit->text();               //phoneNumberLineEdit에 입력한 값을 변수 name에 저장해준다
    address = ui->addressLineEdit->text();                  //addressLineEdit에 입력한 값을 변수 name에 저장해준다

    /*수정할 부분의 row값을 구해줌*/
    QModelIndex idx = ui->clientTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();
    int row = idx.row();

    /*update문을 통해 tableview의 값들을 변경해 줌*/
    query->prepare("UPDATE clientlist SET c_name=?, c_phonenum=?, c_address=? WHERE c_id=?");
    query->bindValue(0, name);
    query->bindValue(1, number);
    query->bindValue(2, address);
    query->bindValue(3, cid);
    query->exec();
    clientModel->select();

    emit clientModified(name, cid, row);    //바뀐 client 정보를 shopmanagerform으로 보내줌
}

void ClientManagerForm::on_addPushButton_clicked()
{
    QString name, number, address;
    int id = makeId( );                             //makeId()를 통해 새로운 고객 id 값을 추가해 줌

    //lineEdit에 정보를 적지 않은 채로 add버튼을 눌렀을 때
    if(ui->nameLineEdit->text() == "" || ui->phoneNumberLineEdit->text() == "" || ui->addressLineEdit->text() == "")
    {
        return;                                 //그냥 리턴해줘서 아무 일도 일어나지 않게끔 해 줌
    }

    /*정보들을 변수에 저장*/
    name = ui->nameLineEdit->text();            //nameLineEdit에 입력한 값을 변수 name에 저장해준다
    number = ui->phoneNumberLineEdit->text();   //phoneNumberLineEdit에 입력한 값을 변수 name에 저장해준다
    address = ui->addressLineEdit->text();      //addressLineEdit에 입력한 값을 변수 name에 저장해준다

    if(name.length()) {                         //이름 길이가 1이상일 때만 if문 실행
        ClientItem* c = new ClientItem(id, name, number, address);

        emit clientAdded(name, id);             //clientAdded 시그널에 name과 id를 담아 shopmanagerform으로 정보를 보내준다
    }

    /*clientlist에 정보를 insert해줌*/
    query->exec(QString("INSERT INTO clientlist VALUES (%1, '%2', '%3', '%4')").arg(id).arg(name).arg(number).arg(address));
    clientModel->select();


}





void ClientManagerForm::on_clientTableView_clicked(const QModelIndex &index)
{
    /*변수에 정보를 저장*/
    int id = index.sibling(index.row(), 0).data().toInt();
    QString name = index.sibling(index.row(), 1).data().toString();
    QString phonenum = index.sibling(index.row(), 2).data().toString();
    QString address = index.sibling(index.row(), 3).data().toString();

    /*LineEdit에 정보를 띄워줌*/
    ui->idLineEdit->setText(QString::number(id)); //item의 인덱스 0번 값에 고객id를 저장해 줌
    ui->nameLineEdit->setText(name);              //item의 인덱스 1번 값에 고객이름를 저장해 줌
    ui->phoneNumberLineEdit->setText(phonenum);   //item의 인덱스 2번 값에 고객전화번호를 저장해 줌
    ui->addressLineEdit->setText(address);        //item의 인덱스 3번 값에 고객주소를 저장해 줌
    ui->toolBox->setCurrentIndex(0);              //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정
}

/*shopmanagerform에서 cid를 받는 부분*/
void ClientManagerForm::CIDsended(int id){

    auto flag = Qt::MatchCaseSensitive|Qt::MatchContains;   //flag값을 지정해 줌. i가 0이 아닐 때는 입력한 값이 포함되면 검색이 되도록 만듦
    QModelIndexList clients = clientModel->match(clientModel->index(0,0),Qt::EditRole, id,-1,Qt::MatchFlags(flag));

    /*변수에 정보를 저장*/
    foreach(auto ix,clients) {
        QString name = ix.sibling(ix.row(),1).data().toString();
        QString number =ix.sibling(ix.row(),2).data().toString();
        QString address = ix.sibling(ix.row(),3).data().toString();
        QStringList clientStrings;
        clientStrings << QString::number(id)<<name<<number<<address;

        /*name, number, address를 shopmanagerform으로 보내줌*/
        emit sendCInfo(name, number, address);
    }
}
