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
<<<<<<< HEAD
#include <QSqlRecord>
#include <QStandardItemModel>

=======
<<<<<<< HEAD
#include <QSqlRecord>
#include <QStandardItemModel>

=======
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97

ShopManagerForm::ShopManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShopManagerForm)
{
    //ui 설정 부분
    ui->setupUi(this);

<<<<<<< HEAD
    //위젯의 사이즈 설정. 540은 전체 화면의 왼쪽에 해당하는 비중, 650은 전체 화면의 오른쪽에 해당하는 비중
    QList<int> sizes;
    sizes << 540 << 650;

=======
    ui->treeWidget->hide();


    //위젯의 사이즈 설정. 540은 전체 화면의 왼쪽에 해당하는 비중, 650은 전체 화면의 오른쪽에 해당하는 비중
    QList<int> sizes;
    sizes << 540 << 650;
<<<<<<< HEAD
    //ui->splitter->setSizes(sizes);
=======
<<<<<<< HEAD
    //ui->splitter->setSizes(sizes);

//    //트리위젯의 컬럼별 너비 설정
//    ui->treeWidget->setColumnWidth(0,50);
//    ui->treeWidget->setColumnWidth(1,80);
//    ui->treeWidget->setColumnWidth(2,130);
//    ui->treeWidget->setColumnWidth(3,80);
//    ui->treeWidget->setColumnWidth(4,50);
//    ui->treeWidget->setColumnWidth(5,70);

=======
<<<<<<< HEAD
    //ui->splitter->setSizes(sizes);
=======
    ui->splitter->setSizes(sizes);
>>>>>>> d909dbfecd081b130e3216b38300aa7a71178669
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3

    //    //트리위젯의 컬럼별 너비 설정
    //    ui->treeWidget->setColumnWidth(0,50);
    //    ui->treeWidget->setColumnWidth(1,80);
    //    ui->treeWidget->setColumnWidth(2,130);
    //    ui->treeWidget->setColumnWidth(3,80);
    //    ui->treeWidget->setColumnWidth(4,50);
    //    ui->treeWidget->setColumnWidth(5,70);

>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    //remove 액션 추가. remove를 클릭했을 때 아이템이 삭제되도록 만듦
    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    //메뉴를 생성하고 remove 액션을 메뉴에 추가
    menu = new QMenu;
    menu->addAction(removeAction);

<<<<<<< HEAD
    ui->shopTableView->setContextMenuPolicy(Qt::CustomContextMenu);
=======
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->shopTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));
    connect(ui->shopTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

<<<<<<< HEAD
    /*테이블의 헤더를 설정해 줌*/
=======
<<<<<<< HEAD
    connect(ui->shopTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
=======
<<<<<<< HEAD
    connect(ui->shopTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
=======
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3

>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
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
<<<<<<< HEAD
}

// 저장된 텍스트를 가져오는 부분

void ShopManagerForm::loadData()
{
    /*DB를 추가하고 DB의 이름을 설정*/
=======

//    searchCustomerModel = new QStandardItemModel(0, 4);
//    searchCustomerModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
//    searchCustomerModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
//    searchCustomerModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
//    searchCustomerModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
//    ui->searchCustomerTableView->setModel(searchCustomerModel);

//    searchProductModel = new QStandardItemModel(0, 4);
//    searchProductModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
//    searchProductModel->setHeaderData(1, Qt::Horizontal, tr("Product Name"));
//    searchProductModel->setHeaderData(2, Qt::Horizontal, tr("Price"));
//    searchProductModel->setHeaderData(3, Qt::Horizontal, tr("Category"));
//    ui->searchProductTableView->setModel(searchProductModel);

}

// 저장된 텍스트를 가져오는 부분
<<<<<<< HEAD

=======
<<<<<<< HEAD

=======
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
void ShopManagerForm::loadData()
{
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "shopConnection");
    db.setDatabaseName("shoplist.db");
    if (db.open( )) {
        query= new QSqlQuery(db);
<<<<<<< HEAD
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
=======
        query->exec("CREATE TABLE IF NOT EXISTS shoplist(s_id INTEGER Primary Key, s_c_id INTEGER, s_p_id INTEGER, s_date VARCHAR(50) NOT NULL, s_count INTEGER, s_price INTEGER, s_totalprice INTEGER, s_address VARCHAR(50) NOT NULL, s_phonenum VARCHAR(50));");

        shopModel = new QSqlTableModel(this, db);
        shopModel->setTable("shoplist");
        shopModel->select();
        shopModel->setHeaderData(0, Qt::Horizontal, tr("SID"));
        shopModel->setHeaderData(1, Qt::Horizontal, tr("CID"));
        shopModel->setHeaderData(2, Qt::Horizontal, tr("PID"));
        shopModel->setHeaderData(3, Qt::Horizontal, tr("Date"));
        shopModel->setHeaderData(4, Qt::Horizontal, tr("Count"));
        shopModel->setHeaderData(5, Qt::Horizontal, tr("Price"));
        shopModel->setHeaderData(6, Qt::Horizontal, tr("Total Price"));
        shopModel->setHeaderData(7, Qt::Horizontal, tr("Address"));
        shopModel->setHeaderData(8, Qt::Horizontal, tr("Phone Number"));

<<<<<<< HEAD
        ui->shopTableView->setModel(shopModel);
=======
<<<<<<< HEAD
        ui->shopTableView->setModel(shopModel);
        ui->shopTableView->resizeColumnsToContents();
    }

    for(int i = 0; i < shopModel->rowCount(); i++) {
        int id = shopModel->data(shopModel->index(i, 0)).toInt();
        QString name = shopModel->data(shopModel->index(i, 1)).toString();
=======
    QTextStream in(&file);
    while (!in.atEnd()) {                       //파일이 끝까지 읽힐 때까지 반복함
        QString line = in.readLine();
        QList<QString> row = line.split(", ");  //", "을 기준으로 데이터를 구분해 데이터를 저장함
        if(row.size()) {                        //행이 0개가 아닐 때
            int sid = row[0].toInt();           //스트링값을 toInt() 함수를 통해 정수값으로 변환
            //int cid = row[1].toInt();
            //int pid = row[2].toInt();
            int count = row[4].toInt();         //스트링값을 toInt() 함수를 통해 정수값으로 변환
            int price = row[5].toInt();         //스트링값을 toInt() 함수를 통해 정수값으로 변환
            int totalprice = count*price;
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3

        /*테이블 컬럼 사이즈 조절*/

<<<<<<< HEAD

        //ui->shopTableView->resizeColumnsToContents();
    }

>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    for(int i = 0; i < shopModel->rowCount(); i++) {
        int id = shopModel->data(shopModel->index(i, 0)).toInt();
        QString name = shopModel->data(shopModel->index(i, 1)).toString();
    }
<<<<<<< HEAD

    /*테이블 컬럼 사이즈 조절*/
=======
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    ui->shopTableView->setColumnWidth(0,50);
    ui->shopTableView->setColumnWidth(1,100);
    ui->shopTableView->setColumnWidth(2,100);
    ui->shopTableView->setColumnWidth(3,90);
    ui->shopTableView->setColumnWidth(4,50);
    ui->shopTableView->setColumnWidth(5,50);
    ui->shopTableView->setColumnWidth(6,100);
    ui->shopTableView->setColumnWidth(7,150);
    ui->shopTableView->setColumnWidth(8,110);
<<<<<<< HEAD
}

/*DB가 오픈되어 있으면 모델에 정보를 submit해주고 해당 DB를 종료한다.*/
ShopManagerForm::~ShopManagerForm()
{
    delete ui;
=======
=======
        }
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
    }
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
}

//void ShopManagerForm::loadData()
//{

//    QFile file("shoplist.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QTextStream in(&file);
//    while (!in.atEnd()) {                       //파일이 끝까지 읽힐 때까지 반복함
//        QString line = in.readLine();
//        QList<QString> row = line.split(", ");  //", "을 기준으로 데이터를 구분해 데이터를 저장함
//        if(row.size()) {                        //행이 0개가 아닐 때
//            int sid = row[0].toInt();           //스트링값을 toInt() 함수를 통해 정수값으로 변환
//            //int cid = row[1].toInt();
//            //int pid = row[2].toInt();
//            int count = row[4].toInt();         //스트링값을 toInt() 함수를 통해 정수값으로 변환
//            int price = row[5].toInt();         //스트링값을 toInt() 함수를 통해 정수값으로 변환
//            int totalprice = count*price;

//            ShopItem* s = new ShopItem(sid, row[1], row[2], row[3], count, price, totalprice, row[7], row[8]);
//            ui->treeWidget->addTopLevelItem(s); //ShopItem을 저장함
//            shopList.insert(sid, s);            //정보 추가

//        }
//    }
//    file.close( );
//}

ShopManagerForm::~ShopManagerForm()
{
    delete ui;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    QSqlDatabase db = QSqlDatabase::database("shopConnection");
    if(db.isOpen()) {
        shopModel->submitAll();
        delete shopModel;
        db.close();
        QSqlDatabase::removeDatabase("shopConnection");
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
=======

    //파일을 저장함
    QFile file("shoplist.txt");          //shoplist.txt를 열음
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);              //파일이 있을 때
    for (const auto& v : shopList) {     //for문을 통해 productlist의 값을 하나씩 가져옴
        ShopItem* s = v;                 //s에 각각의 값들을 저장해 줌
        out << s->SID() << ", ";
        out << s->getCID() << ", ";
        out << s->getPID() << ", ";
        out << s->getDate() << ", ";
        out << s->getCount() << ", ";
        out << s->getPrice() << ", ";
        out << (s->getPrice() * s->getCount()) << ", ";
        out << s->getPhoneNum() << ", ";
        out <<s->getAddress() << "\n";

>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    }
}
//ShopManagerForm::~ShopManagerForm()
//{
//    delete ui;
<<<<<<< HEAD

<<<<<<< HEAD

/*쇼핑아이디 만들기*/
int ShopManagerForm::makeId( )
{
    if(shopModel->rowCount()== 0) {          //상품아이디가 없으면 70001번부터 고객아이디를 부여
        return 70001;
    } else {
        auto sid = shopModel->data(shopModel->index(shopModel->rowCount()-1, 0)).toInt();     //clientlist의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
        ;   //shopList의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
=======
//    //파일을 저장함
//    QFile file("shoplist.txt");          //shoplist.txt를 열음
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        return;

//    QTextStream out(&file);              //파일이 있을 때
//    for (const auto& v : shopList) {     //for문을 통해 productlist의 값을 하나씩 가져옴
//        ShopItem* s = v;                 //s에 각각의 값들을 저장해 줌
//        out << s->SID() << ", ";
//        out << s->getCID() << ", ";
//        out << s->getPID() << ", ";
//        out << s->getDate() << ", ";
//        out << s->getCount() << ", ";
//        out << s->getPrice() << ", ";
//        out << (s->getPrice() * s->getCount()) << ", ";
//        out << s->getPhoneNum() << ", ";
//        out <<s->getAddress() << "\n";

//    }
//    file.close( );
//}
=======
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3

<<<<<<< HEAD
//    //파일을 저장함
//    QFile file("shoplist.txt");          //shoplist.txt를 열음
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        return;

//    QTextStream out(&file);              //파일이 있을 때
//    for (const auto& v : shopList) {     //for문을 통해 productlist의 값을 하나씩 가져옴
//        ShopItem* s = v;                 //s에 각각의 값들을 저장해 줌
//        out << s->SID() << ", ";
//        out << s->getCID() << ", ";
//        out << s->getPID() << ", ";
//        out << s->getDate() << ", ";
//        out << s->getCount() << ", ";
//        out << s->getPrice() << ", ";
//        out << (s->getPrice() * s->getCount()) << ", ";
//        out << s->getPhoneNum() << ", ";
//        out <<s->getAddress() << "\n";

//    }
//    file.close( );
//}

/*쇼핑아이디 만들기*/
int ShopManagerForm::makeId( )
{
    if(shopModel->rowCount()== 0) {          //상품아이디가 없으면 20000번부터 고객아이디를 부여
        return 70001;
    } else {
        auto sid = shopModel->data(shopModel->index(shopModel->rowCount()-1, 0)).toInt();     //clientlist의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
;   //shopList의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
=======
/*쇼핑아이디 만들기*/
int ShopManagerForm::makeId( )
{
    if(shopModel->rowCount()== 0) {          //상품아이디가 없으면 20000번부터 고객아이디를 부여
        return 70001;
    } else {
<<<<<<< HEAD
        auto sid = shopModel->data(shopModel->index(shopModel->rowCount()-1, 0)).toInt();     //clientlist의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
        ;   //shopList의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
=======
        auto sid = shopList.lastKey();   //shopList의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
        return ++sid;
    }
}

/*아이템 삭제*/
void ShopManagerForm::removeItem()                  //treeWidget에 추가할 아이템을 만들어 줌
{
<<<<<<< HEAD
    /*지우려고 하는 아이템의 row를 delete로 제거하고, 제거한 해당 row값을 emit으로 보내줌*/
    QModelIndex idx = ui->shopTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();
    int row = idx.row();
=======
<<<<<<< HEAD
    //    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    //    if(item != nullptr) {                           //아이템이 있을 때
    //        //shopList.remove(item->text(0).toInt());     //쇼핑리스트에서 아이템의 첫번째 컬럼에 해당하는 아이템을 삭제해 줌
    //        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));    //해당하는 상품을 treeWidget에서도 삭제해줌
    //        ui->treeWidget->update();                   //treeWidget 업데이트
    //    }
=======
<<<<<<< HEAD
//    QTreeWidgetItem* item = ui->treeWidget->currentItem();
//    if(item != nullptr) {                           //아이템이 있을 때
//        //shopList.remove(item->text(0).toInt());     //쇼핑리스트에서 아이템의 첫번째 컬럼에 해당하는 아이템을 삭제해 줌
//        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));    //해당하는 상품을 treeWidget에서도 삭제해줌
//        ui->treeWidget->update();                   //treeWidget 업데이트
//    }
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3

    QModelIndex idx = ui->shopTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();

    int row = idx.row();

>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    query->prepare("DELETE FROM shoplist WHERE s_id = ?;");
    query->addBindValue(delid);
    query->exec();
    shopModel->select();
<<<<<<< HEAD
}

/*tableView 영역에서 마우스 오른쪽버튼 클릭했을 때 메뉴가 나오게 해주는 부분*/
void ShopManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->shopTableView->mapToGlobal(pos);    //위치를 구해줌
    menu->exec(globalPos);                                  //그 위치에 메뉴가 뜨게 만들어 줌
}

/*search 버튼 클릭 시 해당하는 정보가 searchTableView에 뜨게 만들어 줌*/
=======
<<<<<<< HEAD
=======
=======
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {                           //아이템이 있을 때
        shopList.remove(item->text(0).toInt());     //쇼핑리스트에서 아이템의 첫번째 컬럼에 해당하는 아이템을 삭제해 줌
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));    //해당하는 상품을 treeWidget에서도 삭제해줌
        ui->treeWidget->update();                   //treeWidget 업데이트
    }
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
}

/*treeWidget 영역에서 마우스 오른쪽버튼 클릭했을 때 메뉴가 나오게 해주는 부분*/
void ShopManagerForm::showContextMenu(const QPoint &pos)
{
<<<<<<< HEAD
    //    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);    //위치를 구해줌
    //    menu->exec(globalPos);                                  //그 위치에 메뉴가 뜨게 만들어 줌
    QPoint globalPos = ui->shopTableView->mapToGlobal(pos);    //위치를 구해줌
=======
<<<<<<< HEAD
//    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);    //위치를 구해줌
//    menu->exec(globalPos);                                  //그 위치에 메뉴가 뜨게 만들어 줌
    QPoint globalPos = ui->shopTableView->mapToGlobal(pos);    //위치를 구해줌
=======
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);    //위치를 구해줌
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
    menu->exec(globalPos);                                  //그 위치에 메뉴가 뜨게 만들어 줌
}

/*search 버튼 클릭 시 해당하는 정보가 searchTreeWidget에 뜨게 만들어 줌*/
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
void ShopManagerForm::on_searchPushButton_clicked()
{
    searchModel->clear();

<<<<<<< HEAD
    int i = ui->searchComboBox->currentIndex();                            //i에 검색콤보박스의 현재인덱스 번호를 저장해준다
    //MatchCaseSensitive: 대소문자 구별, MatchContains: 포함하는지 확인
    auto flag = (i==3)? Qt::MatchCaseSensitive|Qt::MatchContains    //flag값을 지정해 줌. i가 3일 때는 입력한 값이 포함되면 검색이 되도록 만듦
                            : Qt::MatchCaseSensitive;  //i가 3이 아닐 때는 정확한 값을 입력했을 때만 검색이 되도록 만듦
    QModelIndexList orders = shopModel->match(shopModel->index(0,i),Qt::EditRole, ui->searchLineEdit->text(),-1,Qt::MatchFlags(flag));

    /*id, cid, pid, date, count, price, totalprice, phonenumber, address 값들을 orderStrings 리스트에 넣어줌*/
=======
    ui->searchTreeWidget->clear();                                         //search 버튼 다시 누르기 전에 저장되어 있었던 정보를 지워줌
    int i = ui->searchComboBox->currentIndex();                            //i에 검색콤보박스의 현재인덱스 번호를 저장해준다
    //MatchCaseSensitive: 대소문자 구별, MatchContains: 포함하는지 확인
    auto flag = (i==0||i==4)? Qt::MatchCaseSensitive    //flag값을 지정해 줌. i가 0이나 4일 때는 정확한 값을 입력했을 때만 검색이 되도록 만듦
                            : Qt::MatchCaseSensitive|Qt::MatchContains;  //i가 0이나 4가 아닐 때는 입력한 값이 포함되면 검색이 되도록 만듦

    QModelIndexList orders = shopModel->match(shopModel->index(0,i),Qt::EditRole, ui->searchLineEdit->text(),-1,Qt::MatchFlags(flag));


>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
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

<<<<<<< HEAD
        /*item을 append 해줌*/
=======
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
        QList<QStandardItem *> items;
        for (int i = 0; i < 9; ++i) {
            items.append(new QStandardItem(orderStrings.at(i)));
        }

<<<<<<< HEAD
        /*search 버튼을 누를 때마다 헤더가 바뀌지 않도록 만들어 줌*/
        searchModel->appendRow(items);
=======
        searchModel->appendRow(items);

>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
        searchModel->setHeaderData(0, Qt::Horizontal, tr("SID"));
        searchModel->setHeaderData(1, Qt::Horizontal, tr("CID"));
        searchModel->setHeaderData(2, Qt::Horizontal, tr("PID"));
        searchModel->setHeaderData(3, Qt::Horizontal, tr("Date"));
        searchModel->setHeaderData(4, Qt::Horizontal, tr("Count"));
        searchModel->setHeaderData(5, Qt::Horizontal, tr("Price"));
        searchModel->setHeaderData(6, Qt::Horizontal, tr("Total Price"));
        searchModel->setHeaderData(7, Qt::Horizontal, tr("Phone Number"));
        searchModel->setHeaderData(8, Qt::Horizontal, tr("Address"));
<<<<<<< HEAD
=======


        //    {
        //        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);//flag와 i값에 해당하는 정보를 searchLineEdit에 입력한 텍스트를 찾고, items에 해당 값을 저장해준다

        //        foreach(auto i, items) {                                           //아이템들을 하나씩 꺼내옴
        //            ShopItem* s = static_cast<ShopItem*>(i);                       //i의 자료형을 ProductItem이라는 형식으로 변환하고 고정
        //            int sid = s->SID();
        //            QString cid = s->getCID();
        //            QString pid = s->getPID();
        //            QString date = s->getDate();
        //            int count = s->getCount();
        //            int price = s->getPrice();
        //            int totalprice = s->getCount()*s->getPrice();
        //            QString phonenumber = s->getPhoneNum();
        //            QString address = s->getAddress();

        //            //sid, cid, pid, date, count, price, totalprice, address, phonenumber를 item에 넣어줌
        //            ShopItem* item = new ShopItem(sid, cid, pid, date, count, price, totalprice, address, phonenumber);
        //            ui->searchTreeWidget->addTopLevelItem(item);                   //item을 searchTreeWidget의 맨 위에 추가해 줌
        //        }
        //    }
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    }
}

/*수정버튼이 눌렸을 때*/
void ShopManagerForm::on_modifyPushButton_clicked()
{
<<<<<<< HEAD
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




=======
    QTreeWidgetItem* item = ui->treeWidget->currentItem();      //item에 treeWidget의 현재 아이템을 넣어줌

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
    //id productname price category
    QString date, cid, pid;
    int count, price, totalprice, sid;
    sid = ui->shopsidLineEdit->text().toInt();
    cid = ui->shopcidcomboBox->currentText().right(6).left(5);   //shopcidcomboBox에서 선택한 값을 변수 cid에 저장해준다
    pid = ui->shoppidcomboBox->currentText().right(6).left(5);   //shoppidcomboBox에서 선택한 값을 변수 pid에 저장해준다
    //cid = ui->shopcidLineEdit->text().toInt();
    //pid = ui->shoppidLineEdit->text().toInt();
    date = ui->dateLineEdit->text();                        //dateLineEdit에 입력한 값을 변수 date에 저장해준다
    count = ui->countLineEdit->text().toInt();              //countLineEdit에 입력한 값을 변수 count에 저장해준다

    QModelIndex idx = ui->shopTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();

    int row = idx.row();

    query->prepare("UPDATE shoplist SET s_c_id = ?, s_p_id = ?, s_date = ?, s_count = ? WHERE s_id = ?");
    query->bindValue(0, cid);
    query->bindValue(1, pid);
    query->bindValue(2, date);
    query->bindValue(3, count);
    query->bindValue(4, sid);

    query->exec();
    shopModel->select();


<<<<<<< HEAD
=======
=======
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
    if(item != nullptr) {                                       //item이 있을 때
        int key = item->text(0).toInt();                        //item의 0번째 인덱스 값인 쇼핑번호를 key에 저장함
        //        int cid = item->text(1).toInt();
        //        int pid = item->text(2).toInt();
        //        int count = item->text(4).toInt();

<<<<<<< HEAD
        //ShopItem* s = shopList[key];                            //shopList[key]에 해당하는 값을 s에 저장해준다




        //수정되도록 만들기
        //        price = ui->treeWidget->currentItem().c
        //        totalprice = ui->
=======
<<<<<<< HEAD
        //ShopItem* s = shopList[key];                            //shopList[key]에 해당하는 값을 s에 저장해준다
=======
        ShopItem* s = shopList[key];                            //shopList[key]에 해당하는 값을 s에 저장해준다

        //id productname price category
        QString date, cid, pid;
        int count, price, totalprice;
        cid = ui->shopcidcomboBox->currentText().right(6).left(5);   //shopcidcomboBox에서 선택한 값을 변수 cid에 저장해준다
        pid = ui->shoppidcomboBox->currentText().right(6).left(5);   //shoppidcomboBox에서 선택한 값을 변수 pid에 저장해준다
        //cid = ui->shopcidLineEdit->text().toInt();
        //pid = ui->shoppidLineEdit->text().toInt();
        date = ui->dateLineEdit->text();                        //dateLineEdit에 입력한 값을 변수 date에 저장해준다
        count = ui->countLineEdit->text().toInt();              //countLineEdit에 입력한 값을 변수 count에 저장해준다


//수정되도록 만들기
//        price = ui->treeWidget->currentItem().c
//        totalprice = ui->
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad




//수정되도록 만들기
//        price = ui->treeWidget->currentItem().c
//        totalprice = ui->
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3


        /*s->setCID(cid);
        s->setPID(pid);
        s->setDate(date);
        s->setCount(count);
<<<<<<< HEAD
        shopList[key] = s; */                                     //shopList[key]에 s를 넣어준다
=======
<<<<<<< HEAD
        shopList[key] = s; */                                     //shopList[key]에 s를 넣어준다
=======
        shopList[key] = s;                                      //shopList[key]에 s를 넣어준다
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
    }

}

>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
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

<<<<<<< HEAD
    /*정보들을 변수에 저장*/
    cid = ui->shopcidcomboBox->currentText().right(6).left(5);   //shopcidcomboBox에서 선택한 값을 변수 cid에 저장해준다
    pid = ui->shoppidcomboBox->currentText().right(6).left(5);   //shoppidcomboBox에서 선택한 값을 변수 pid에 저장해준다
    date = ui->dateLineEdit->text();            //dateLineEdit에 입력한 값을 변수 date에 저장해준다
    count = ui->countLineEdit->text().toInt();  //countLineEdit에 입력한 값을 변수 count에 저장해준다
=======
    cid = ui->shopcidcomboBox->currentText().right(6).left(5);   //shopcidcomboBox에서 선택한 값을 변수 cid에 저장해준다
    pid = ui->shoppidcomboBox->currentText().right(6).left(5);   //shoppidcomboBox에서 선택한 값을 변수 pid에 저장해준다

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
    qDebug() <<"cid: " <<cid;
    qDebug() <<"pid: " <<pid;

>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
    date = ui->dateLineEdit->text();            //dateLineEdit에 입력한 값을 변수 date에 저장해준다
    count = ui->countLineEdit->text().toInt();  //countLineEdit에 입력한 값을 변수 count에 저장해준다

>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    price = ui->ProducttreeWidget->topLevelItem(0)->text(1).toInt();      //ProducttreeWidget의 첫번째 줄에 있는 값의 인덱스 1번 값을 변수 price에 저장해준다
    phonenumber =ui->CustomertreeWidget->topLevelItem(0)->text(1);        //CustomertreeWidget의 첫번째 줄에 있는 값의 인덱스 1번 값을 변수 phonenumber에 저장해준다
    address = ui->CustomertreeWidget->topLevelItem(0)->text(2);           //CustomertreeWidget의 첫번째 줄에 있는 값의 인덱스 2번 값을 변수 address에 저장해준다
    totalprice = price * count;

    if(date.length()) {                                                   //날짜 길이가 1이상일 때만 if문 실행
        ShopItem* s = new ShopItem(sid, cid, pid, date, count, price, totalprice, address, phonenumber);
<<<<<<< HEAD
=======
<<<<<<< HEAD
        //shopList.insert(sid, s);                                          //shopList에 정보들을 넣어줌
=======
<<<<<<< HEAD
        //shopList.insert(sid, s);                                          //shopList에 정보들을 넣어줌
=======
        shopList.insert(sid, s);                                          //shopList에 정보들을 넣어줌
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
        ui->treeWidget->addTopLevelItem(s);                               //treeWidget에 s값을 추가해 줌
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    }
    query->exec(QString("INSERT INTO shoplist VALUES (%1, %2, %3, '%4', %5, %6, %7, '%8', '%9')").arg(sid).arg(cid).arg(pid).arg(date).arg(count).arg(price).arg(totalprice).arg(address).arg(phonenumber));
    shopModel->select();
}

<<<<<<< HEAD

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

=======
/*treeWidget에 있는 item을 클릭했을 때*/
void ShopManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);                                       //매개변수인 column을 사용하지 않았을 때 오류가 생기지 않게 해 줌
    ui->shopsidLineEdit->setText(item->text(0));            //item의 인덱스 0번 값에 쇼핑id를 저장해 줌
    ui->shopcidcomboBox->setCurrentIndex(ui->shopcidcomboBox->findText(item->text(1), Qt::MatchContains));     //item의 인덱스 1번 값에 고객id를 저장해 줌
    ui->shoppidcomboBox->setCurrentText(item->text(2));     //item의 인덱스 2번 값에 상품id를 저장해 줌

    ui->dateLineEdit->setText(item->text(3));               //item의 인덱스 3번 값에 날짜를 저장해 줌
    ui->countLineEdit->setText(item->text(4));              //item의 인덱스 4번 값에 구매수량을 저장해 줌

    //emit SendPID(item->text(2).right(6).left(5).toInt());   //pid만을 뽑아내어 productmanager로 보내줌
    //emit SendCID(item->text(1).right(4).left(3).toInt());   //cid만을 뽑아내어 clientmanager로 보내줌
    emit SendCID(item->text(1).toInt());
    ui->toolBox->setCurrentIndex(0);                        //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정
}


<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
void ShopManagerForm::on_shopTableView_clicked(const QModelIndex &index)
{

    //QModelIndex idx = ui->clientTableView->currentIndex();
    int sid = index.sibling(index.row(), 0).data().toInt();
    int cid = index.sibling(index.row(), 1).data().toInt();
    int pid = index.sibling(index.row(), 2).data().toInt();
    QString date = index.sibling(index.row(), 3).data().toString();
    int count = index.sibling(index.row(), 4).data().toInt();

    qDebug()<<"pid: "<<pid;
    ui->shopsidLineEdit->setText(QString::number(sid));             //item의 인덱스 0번 값에 고객id를 저장해 줌
    ui->shopcidcomboBox->setCurrentIndex(ui->shopcidcomboBox->findText(QString::number(cid), Qt::MatchContains));
    ui->shoppidcomboBox->setCurrentIndex(ui->shoppidcomboBox->findText(QString::number(pid), Qt::MatchContains));
    ui->dateLineEdit->setText(date);           //item의 인덱스 1번 값에 고객이름를 저장해 줌
    ui->countLineEdit->setText(QString::number(count));    //item의 인덱스 2번 값에 고객전화번호를 저장해 줌
    ui->toolBox->setCurrentIndex(0);                    //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정
}



<<<<<<< HEAD
=======
=======
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
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
<<<<<<< HEAD
    int ID = arg1.right(6).left(5).toInt();
=======
<<<<<<< HEAD
    int ID = arg1.right(6).left(5).toInt();
=======
<<<<<<< HEAD
    int ID = arg1.right(6).left(5).toInt();
=======
    int ID = arg1.right(4).left(3).toInt();
>>>>>>> 5c7d7596cc6e7c0746ae023420c18bb27f3356ad
>>>>>>> d4bb97a7110e1e254903e178b9e5539cff2110d3
>>>>>>> 06db11e7a6a4eec6acd82a0723527bc089e7bb97
    emit SendCID(ID);
    qDebug()<<ID;
}

/*name, phonenumber, address 값을 customermanagerform에서 받아와 CustomertreeWidget에 띄워주는 부분*/
void ShopManagerForm::CInfoSended(QString name, QString phonenumber, QString address){
    ui->CustomertreeWidget->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, name);
    item->setText(1, phonenumber);
    item->setText(2, address);
    ui->CustomertreeWidget->addTopLevelItem(item);



    // ui->customerTableView->hideRow(i);


}




