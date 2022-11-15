#include "shopmanagerform.h"
#include "ui_shopmanagerform.h"
#include "shopitem.h"
#include "productitem.h"

#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QStandardItemModel>


ShopManagerForm::ShopManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShopManagerForm)
{
    //ui 설정 부분
    ui->setupUi(this);

    //위젯의 사이즈 설정. 540은 전체 화면의 왼쪽에 해당하는 비중, 650은 전체 화면의 오른쪽에 해당하는 비중
    QList<int> sizes;
    sizes << 540 << 650;

    //remove 액션 추가. remove를 클릭했을 때 아이템이 삭제되도록 만듦
    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    //메뉴를 생성하고 remove 액션을 메뉴에 추가
    menu = new QMenu;
    menu->addAction(removeAction);

    ui->shopTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));
    connect(ui->shopTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    /*테이블의 헤더를 설정해 줌*/
    searchModel = new QStandardItemModel(0, 9);
    searchModel->setHeaderData(0, Qt::Horizontal, tr("SID"));
    searchModel->setHeaderData(1, Qt::Horizontal, tr("CID"));
    searchModel->setHeaderData(2, Qt::Horizontal, tr("PID"));
    searchModel->setHeaderData(3, Qt::Horizontal, tr("Date"));
    searchModel->setHeaderData(4, Qt::Horizontal, tr("Count"));
    searchModel->setHeaderData(5, Qt::Horizontal, tr("Price"));
    searchModel->setHeaderData(6, Qt::Horizontal, tr("Total Price"));
    searchModel->setHeaderData(7, Qt::Horizontal, tr("Phone Number"));
    searchModel->setHeaderData(8, Qt::Horizontal, tr("Address"));
    ui->searchTableView->setModel(searchModel);
}

// 저장된 텍스트를 가져오는 부분

void ShopManagerForm::loadData()
{
    /*DB를 추가하고 DB의 이름을 설정*/
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "shopConnection");
    db.setDatabaseName("shoplist.db");
    if (db.open( )) {
        query= new QSqlQuery(db);
        query->exec("CREATE TABLE IF NOT EXISTS shoplist(s_id INTEGER Primary Key, s_c_id INTEGER, s_p_id INTEGER, "
                    "s_date VARCHAR(50) NOT NULL, s_count INTEGER, s_price INTEGER, s_totalprice INTEGER, "
                    "s_address VARCHAR(50) NOT NULL, s_phonenum VARCHAR(50));");

        /*DB를 오픈해 새로운 테이블을 만듦*/
        shopModel = new QSqlTableModel(this, db);
        shopModel->setTable("shoplist");
        shopModel->select();

        /*Model을 만들고 테이블의 헤더 설정*/
        shopModel->setHeaderData(0, Qt::Horizontal, tr("SID"));
        shopModel->setHeaderData(1, Qt::Horizontal, tr("CID"));
        shopModel->setHeaderData(2, Qt::Horizontal, tr("PID"));
        shopModel->setHeaderData(3, Qt::Horizontal, tr("Date"));
        shopModel->setHeaderData(4, Qt::Horizontal, tr("Count"));
        shopModel->setHeaderData(5, Qt::Horizontal, tr("Price"));
        shopModel->setHeaderData(6, Qt::Horizontal, tr("Total Price"));
        shopModel->setHeaderData(7, Qt::Horizontal, tr("Address"));
        shopModel->setHeaderData(8, Qt::Horizontal, tr("Phone Number"));

        ui->shopTableView->setModel(shopModel);
    }

    /*Model의 줄 수를 세 id, name를 저장*/
    for(int i = 0; i < shopModel->rowCount(); i++) {
        int id = shopModel->data(shopModel->index(i, 0)).toInt();
        QString name = shopModel->data(shopModel->index(i, 1)).toString();
    }

    /*테이블 컬럼 사이즈 조절*/
    ui->shopTableView->setColumnWidth(0,50);
    ui->shopTableView->setColumnWidth(1,100);
    ui->shopTableView->setColumnWidth(2,100);
    ui->shopTableView->setColumnWidth(3,90);
    ui->shopTableView->setColumnWidth(4,50);
    ui->shopTableView->setColumnWidth(5,50);
    ui->shopTableView->setColumnWidth(6,100);
    ui->shopTableView->setColumnWidth(7,150);
    ui->shopTableView->setColumnWidth(8,110);
}

/*DB가 오픈되어 있으면 모델에 정보를 submit해주고 해당 DB를 종료한다.*/
ShopManagerForm::~ShopManagerForm()
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("shopConnection");
    if(db.isOpen()) {
        shopModel->submitAll();
        delete shopModel;
        db.close();
        QSqlDatabase::removeDatabase("shopConnection");
    }
}


/*쇼핑아이디 만들기*/
int ShopManagerForm::makeId( )
{
    if(shopModel->rowCount()== 0) {          //상품아이디가 없으면 70001번부터 고객아이디를 부여
        return 70001;
    } else {
        auto sid = shopModel->data(shopModel->index(shopModel->rowCount()-1, 0)).toInt();     //clientlist의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
        ;   //shopList의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
        return ++sid;
    }
}

/*아이템 삭제*/
void ShopManagerForm::removeItem()                  //treeWidget에 추가할 아이템을 만들어 줌
{
    /*지우려고 하는 아이템의 row를 delete로 제거하고, 제거한 해당 row값을 emit으로 보내줌*/
    QModelIndex idx = ui->shopTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();
    int row = idx.row();
    query->prepare("DELETE FROM shoplist WHERE s_id = ?;");
    query->addBindValue(delid);
    query->exec();
    shopModel->select();
}

/*tableView 영역에서 마우스 오른쪽버튼 클릭했을 때 메뉴가 나오게 해주는 부분*/
void ShopManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->shopTableView->mapToGlobal(pos);    //위치를 구해줌
    menu->exec(globalPos);                                  //그 위치에 메뉴가 뜨게 만들어 줌
}

/*search 버튼 클릭 시 해당하는 정보가 searchTableView에 뜨게 만들어 줌*/
void ShopManagerForm::on_searchPushButton_clicked()
{
    searchModel->clear();

    int i = ui->searchComboBox->currentIndex();                            //i에 검색콤보박스의 현재인덱스 번호를 저장해준다
    //MatchCaseSensitive: 대소문자 구별, MatchContains: 포함하는지 확인
    auto flag = (i==3)? Qt::MatchCaseSensitive|Qt::MatchContains    //flag값을 지정해 줌. i가 3일 때는 입력한 값이 포함되면 검색이 되도록 만듦
                            : Qt::MatchCaseSensitive;  //i가 3이 아닐 때는 정확한 값을 입력했을 때만 검색이 되도록 만듦
    QModelIndexList orders = shopModel->match(shopModel->index(0,i),Qt::EditRole, ui->searchLineEdit->text(),-1,Qt::MatchFlags(flag));

    /*id, cid, pid, date, count, price, totalprice, phonenumber, address 값들을 orderStrings 리스트에 넣어줌*/
    foreach(auto ix,orders) {
        int id =ix.sibling(ix.row(),0).data().toInt();
        int cid =ix.sibling(ix.row(),1).data().toInt();
        int pid =ix.sibling(ix.row(),2).data().toInt();
        QString date = ix.sibling(ix.row(),3).data().toString();
        int count =ix.sibling(ix.row(),4).data().toInt();
        int price =ix.sibling(ix.row(),5).data().toInt();
        int totalprice =ix.sibling(ix.row(),6).data().toInt();
        QString phonenumber = ix.sibling(ix.row(),7).data().toString();
        QString address = ix.sibling(ix.row(),8).data().toString();
        QStringList orderStrings;
        orderStrings << QString::number(id)<<QString::number(cid)<<QString::number(pid)<<date<<QString::number(count)<<QString::number(price)<<QString::number(totalprice)<<phonenumber<<address;

        /*item을 append 해줌*/
        QList<QStandardItem *> items;
        for (int i = 0; i < 9; ++i) {
            items.append(new QStandardItem(orderStrings.at(i)));
        }

        /*search 버튼을 누를 때마다 헤더가 바뀌지 않도록 만들어 줌*/
        searchModel->appendRow(items);
        searchModel->setHeaderData(0, Qt::Horizontal, tr("SID"));
        searchModel->setHeaderData(1, Qt::Horizontal, tr("CID"));
        searchModel->setHeaderData(2, Qt::Horizontal, tr("PID"));
        searchModel->setHeaderData(3, Qt::Horizontal, tr("Date"));
        searchModel->setHeaderData(4, Qt::Horizontal, tr("Count"));
        searchModel->setHeaderData(5, Qt::Horizontal, tr("Price"));
        searchModel->setHeaderData(6, Qt::Horizontal, tr("Total Price"));
        searchModel->setHeaderData(7, Qt::Horizontal, tr("Phone Number"));
        searchModel->setHeaderData(8, Qt::Horizontal, tr("Address"));
    }
}

/*수정버튼이 눌렸을 때*/
void ShopManagerForm::on_modifyPushButton_clicked()
{
    QModelIndex idx = ui->shopTableView->currentIndex();
    if(idx.isValid()) {
        QString date, cid, pid, address, phonenum;
        int sid, count, totalprice, price;

        /*sid, cid, pid, date, count, price, totalprice, address 값을 저장해 줌*/
        sid = ui->shopsidLineEdit->text().toInt();
        cid = ui->shopcidcomboBox->currentText().right(6).left(5);   //shopcidcomboBox에서 선택한 값을 변수 cid에 저장해준다
        pid = ui->shoppidcomboBox->currentText().right(6).left(5);   //shoppidcomboBox에서 선택한 값을 변수 pid에 저장해준다
        date = ui->dateLineEdit->text();                        //dateLineEdit에 입력한 값을 변수 date에 저장해준다
        count = ui->countLineEdit->text().toInt();              //countLineEdit에 입력한 값을 변수 count에 저장해준다
        price = ui->ProducttreeWidget->topLevelItem(0)->text(1).toInt();
        address = ui->CustomertreeWidget->topLevelItem(0)->text(2);
        phonenum = ui->CustomertreeWidget->topLevelItem(0)->text(1);
        totalprice = price * count;

        /*update문을 통해 tableview의 값들을 변경해 줌*/
        query->prepare("UPDATE shoplist SET s_c_id = ?, s_p_id = ?, s_date = ?, s_count = ?, s_price = ?,"
                       " s_totalprice = ?, s_address = ?, s_phonenum = ? WHERE s_id = ?;");
        query->bindValue(0, cid);
        query->bindValue(1, pid);
        query->bindValue(2, date);
        query->bindValue(3, count);
        query->bindValue(4, price);
        query->bindValue(5, totalprice);
        query->bindValue(6, address);
        query->bindValue(7, phonenum);
        query->bindValue(8, sid);

        query->exec();
        shopModel->select();
    }
    ui->shopsidLineEdit->clear();
    ui->countLineEdit->clear();
    ui->dateLineEdit->clear();
}




/*add 버튼을 클릭했을 때*/
void ShopManagerForm::on_addPushButton_clicked()
{
    QString date, cid, pid, address, phonenumber;
    int count, price, totalprice;
    int sid = makeId( );                        //makeId()를 통해 새로운 상품 id 값을 추가해 줌

    //정보를 입력하지 않은 채로 add버튼을 눌렀을 때
    if(ui->CustomertreeWidget->topLevelItemCount() == 0 || ui->ProducttreeWidget->topLevelItemCount() == 0 || ui->dateLineEdit->text() == ""
            ||ui->countLineEdit->text() == "")
    {
        return;                                 //그냥 리턴해줘서 아무 일도 일어나지 않게끔 해 줌                                                   //그냥 리턴해줘서 아무 일도 일어나지 않게끔 해 줌
    }

    /*정보들을 변수에 저장*/
    cid = ui->shopcidcomboBox->currentText().right(6).left(5);   //shopcidcomboBox에서 선택한 값을 변수 cid에 저장해준다
    pid = ui->shoppidcomboBox->currentText().right(6).left(5);   //shoppidcomboBox에서 선택한 값을 변수 pid에 저장해준다
    date = ui->dateLineEdit->text();            //dateLineEdit에 입력한 값을 변수 date에 저장해준다
    count = ui->countLineEdit->text().toInt();  //countLineEdit에 입력한 값을 변수 count에 저장해준다
    price = ui->ProducttreeWidget->topLevelItem(0)->text(1).toInt();      //ProducttreeWidget의 첫번째 줄에 있는 값의 인덱스 1번 값을 변수 price에 저장해준다
    phonenumber =ui->CustomertreeWidget->topLevelItem(0)->text(1);        //CustomertreeWidget의 첫번째 줄에 있는 값의 인덱스 1번 값을 변수 phonenumber에 저장해준다
    address = ui->CustomertreeWidget->topLevelItem(0)->text(2);           //CustomertreeWidget의 첫번째 줄에 있는 값의 인덱스 2번 값을 변수 address에 저장해준다
    totalprice = price * count;

    if(date.length()) {                                                   //날짜 길이가 1이상일 때만 if문 실행
        ShopItem* s = new ShopItem(sid, cid, pid, date, count, price, totalprice, address, phonenumber);
    }
    query->exec(QString("INSERT INTO shoplist VALUES (%1, %2, %3, '%4', %5, %6, %7, '%8', '%9')").arg(sid).arg(cid).arg(pid).arg(date).arg(count).arg(price).arg(totalprice).arg(address).arg(phonenumber));
    shopModel->select();
}


void ShopManagerForm::on_shopTableView_clicked(const QModelIndex &index)
{
    /*변수에 정보를 저장*/
    int sid = index.sibling(index.row(), 0).data().toInt();
    int cid = index.sibling(index.row(), 1).data().toInt();
    int pid = index.sibling(index.row(), 2).data().toInt();
    QString date = index.sibling(index.row(), 3).data().toString();
    int count = index.sibling(index.row(), 4).data().toInt();

    /*LineEdit와 combobox에 정보를 띄워줌*/
    ui->shopsidLineEdit->setText(QString::number(sid));             //item의 인덱스 0번 값에 고객id를 저장해 줌
    ui->shopcidcomboBox->setCurrentIndex(ui->shopcidcomboBox->findText(QString::number(cid), Qt::MatchContains));
    ui->shoppidcomboBox->setCurrentIndex(ui->shoppidcomboBox->findText(QString::number(pid), Qt::MatchContains));
    ui->dateLineEdit->setText(date);           //item의 인덱스 1번 값에 고객이름를 저장해 줌
    ui->countLineEdit->setText(QString::number(count));    //item의 인덱스 2번 값에 고객전화번호를 저장해 줌
    ui->toolBox->setCurrentIndex(0);                    //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정

    emit SendCID(cid);
    emit SendPID(pid);

    ui->toolBox->setCurrentIndex(0);                        //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정
}

/*shopcidcomboBox에 고객이름과 cid를 추가함 (ex. 김유선(100) )*/
void ShopManagerForm::addClient(QString name, int cid)
{
    ui->shopcidcomboBox->addItem(name+"(" + QString::number(cid).rightJustified(5,'0')+")");
}

/*shoppidcomboBox에 상품이름과 pid를 추가함 (ex. SA-100(10000) )*/
void ShopManagerForm::addProduct(QString productname, int price, QString category, int pid)
{
    ui->shoppidcomboBox->addItem(productname+"(" + QString::number(pid)+")");
}

/*shopcidcomboBox에서 고객이름과 cid를 변경함 (ex. 이정연(101) )*/
void ShopManagerForm::modifyClient(QString name, int cid, int i)
{
    ui->shopcidcomboBox->setItemText(i, name+"(" + QString::number(cid)+")");
}

/*shopcidcomboBox에서 인덱스 i에 해당하는 정보를 삭제함*/
void ShopManagerForm::removeClient(int i)
{
    ui->shopcidcomboBox->removeItem(i);
}

/*shoppidcomboBox에서 상품이름과 pid를 변경함 (ex. SA-110(10001) )*/
void ShopManagerForm::modifyProduct(QString productname, int pid, int i)
{
    ui->shoppidcomboBox->setItemText(i, productname+"(" + QString::number(pid)+")");
}

/*shoppidcomboBox에서 인덱스 i에 해당하는 정보를 삭제함*/
void ShopManagerForm::removeProduct(int i)
{
    ui->shoppidcomboBox->removeItem(i);
}

/*shoppidcomboBox를 클릭했을 때, 해당 정보에서 pid만 빼서 productmanager로 보내주는 부분*/
void ShopManagerForm::on_shoppidcomboBox_textActivated(const QString &arg1)
{
    int ID = arg1.right(6).left(5).toInt();
    emit SendPID(ID);
}

/*pname, price, category 값을 productmanagerform에서 받아와 ProducttreeWidget에 띄워주는 부분*/
void ShopManagerForm::PInfoSended(QString pname, int price, QString category)
{
    ui->ProducttreeWidget->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, pname);
    item->setText(1, QString::number(price));
    item->setText(2, category);

    ui->ProducttreeWidget->addTopLevelItem(item);
}

/*shopcidcomboBox를 클릭했을 때, 해당 정보에서 cid만 빼서 clientmanager로 보내주는 부분*/
void ShopManagerForm::on_shopcidcomboBox_textActivated(const QString &arg1)
{
    int ID = arg1.right(6).left(5).toInt();
    emit SendCID(ID);
}

/*name, phonenumber, address 값을 customermanagerform에서 받아와 CustomertreeWidget에 띄워주는 부분*/
void ShopManagerForm::CInfoSended(QString name, QString phonenumber, QString address){
    ui->CustomertreeWidget->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, name);
    item->setText(1, phonenumber);
    item->setText(2, address);
    ui->CustomertreeWidget->addTopLevelItem(item);
}




