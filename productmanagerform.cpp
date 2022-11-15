#include "productmanagerform.h"
#include "ui_productmanagerform.h"
#include "productitem.h"

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

ProductManagerForm::ProductManagerForm(QWidget *parent) :
    QWidget(parent), ui(new Ui::ProductManagerForm)
{
    //ui 설정 부분
    ui->setupUi(this);

    //위젯의 사이즈 설정. 540은 전체 화면의 왼쪽에 해당하는 비중, 400은 전체 화면의 오른쪽에 해당하는 비중
    QList<int> sizes;
    sizes << 540 << 400;
    //ui->splitter->setSizes(sizes);

    //트리위젯의 컬럼별 너비 설정
    ui->toolBox->setCurrentIndex(0);

    //remove 액션 추가. remove를 클릭했을 때 아이템이 삭제되도록 만듦
    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    //메뉴를 생성하고 remove 액션을 메뉴에 추가
    menu = new QMenu;
    menu->addAction(removeAction);
    ui->productTableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));
    connect(ui->productTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    /*테이블 뷰의 헤더 설정*/
    searchModel = new QStandardItemModel(0, 4);
    searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    searchModel->setHeaderData(1, Qt::Horizontal, tr("Product Name"));
    searchModel->setHeaderData(2, Qt::Horizontal, tr("Price"));
    searchModel->setHeaderData(3, Qt::Horizontal, tr("Category"));
    ui->searchTableView->setModel(searchModel);
}

// 저장된 텍스트를 가져오는 부분
void ProductManagerForm::loadData()
{
    /*DB를 추가하고 DB의 이름을 설정*/
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "productConnection");
    db.setDatabaseName("product.db");

    /*DB를 오픈해 새로운 테이블을 만듦*/
    if (db.open( )) {
        query= new QSqlQuery(db);
        query->exec("CREATE TABLE IF NOT EXISTS product(p_id INTEGER Primary Key, p_pname VARCHAR(30) NOT NULL, p_price INTEGER NOT NULL, p_category VARCHAR(50));");

        /*Model을 만들고 테이블의 헤더 설정*/
        productModel = new QSqlTableModel(this, db);
        productModel->setTable("product");
        productModel->select();
        productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        productModel->setHeaderData(1, Qt::Horizontal, tr("Product Name"));
        productModel->setHeaderData(2, Qt::Horizontal, tr("Price"));
        productModel->setHeaderData(3, Qt::Horizontal, tr("Category"));

        ui->productTableView->setModel(productModel);

        /*테이블 컬럼 사이즈 조절*/
        ui->productTableView->setColumnWidth(0,100);
        ui->productTableView->setColumnWidth(1,300);
        ui->productTableView->setColumnWidth(2,150);
        ui->productTableView->setColumnWidth(3,260);
    }

    /*Model의 줄 수를 세 id, productname, price, category를 저장하여 shopmanagerform에 이름과 id를 보내준다*/
    for(int i = 0; i < productModel->rowCount(); i++) {
        int id = productModel->data(productModel->index(i, 0)).toInt();
        QString productname = productModel->data(productModel->index(i, 1)).toString();
        int price = productModel->data(productModel->index(i, 2)).toInt();
        QString category= productModel->data(productModel->index(i, 3)).toString();

        emit productAdded(productname, price, category, id);
    }
}

/*DB가 오픈되어 있으면 모델에 정보를 submit해주고 해당 DB를 종료한다.*/
ProductManagerForm::~ProductManagerForm()
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("productConnection");
    if(db.isOpen()) {
        productModel->submitAll();
        delete productModel;
        db.close();
        QSqlDatabase::removeDatabase("productConnection");
    }
}


/*상품아이디 만들기*/
int ProductManagerForm::makeId( )
{
    if(productModel->rowCount() == 0) {          //상품아이디가 없으면 40001번부터 고객아이디를 부여
        return 40001;
    } else {
        auto id = productModel->data(productModel->index(productModel->rowCount()-1, 0)).toInt();    //productList의 마지막 키 값 + 1로 다음 키 값을 설정해 줌
        return ++id;
    }
}

/*아이템 삭제*/
void ProductManagerForm::removeItem()
{
    int i;

    /*지우려고 하는 아이템의 row를 delete로 제거하고, 제거한 해당 row값을 emit으로 보내줌*/
    QModelIndex idx = ui->productTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();
    int row = idx.row();
    query->prepare("DELETE FROM product WHERE p_id = ?;");
    query->addBindValue(delid);
    query->exec();
    productModel->select();
    emit productRemoved(row);
}

/*treeWidget 영역에서 마우스 오른쪽버튼 클릭했을 때 메뉴가 나오게 해주는 부분*/
void ProductManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->productTableView->mapToGlobal(pos);    //위치를 구해줌
    menu->exec(globalPos);                                  //그 위치에 메뉴가 뜨게 만들어 줌
}

/*search 버튼 클릭 시 해당하는 정보가 searchTableView에 뜨게 만들어 줌*/
void ProductManagerForm::on_searchPushButton_clicked()
{
    searchModel->clear();

    int i = ui->searchComboBox->currentIndex();     //i에 검색콤보박스의 현재인덱스 번호를 저장해준다
    //MatchCaseSensitive: 대소문자 구별, MatchContains: 포함하는지 확인
    auto flag = (i==1 || i==3)? Qt::MatchCaseSensitive|Qt::MatchContains   //flag값을 지정해 줌. i가 0이 아닐 때는 입력한 값이 포함되면 검색이 되도록 만듦
                   : Qt::MatchCaseSensitive;                    //i가 0이 아닌 값일 때는 입력한 값이 정확할 때만 검색이 되도록 만듦
    QModelIndexList clients = productModel->match(productModel->index(0,i),Qt::EditRole, ui->searchLineEdit->text(),-1,Qt::MatchFlags(flag));

    /*id, productname, price, category 값들을 productStrings 리스트에 넣어줌*/
    foreach(auto ix,clients) {
            int id =ix.sibling(ix.row(),0).data().toInt();
            QString productname = ix.sibling(ix.row(),1).data().toString();
            int price =ix.sibling(ix.row(),2).data().toInt();
            QString category = ix.sibling(ix.row(),3).data().toString();
            QStringList productStrings;
            productStrings << QString::number(id)<<productname<<QString::number(price)<<category;

            /*item을 append 해줌*/
            QList<QStandardItem *> items;
            for (int i = 0; i < 4; ++i) {
                items.append(new QStandardItem(productStrings.at(i)));
            }

            /*search 버튼을 누를 때마다 헤더가 바뀌지 않도록 만들어 줌*/
            searchModel->appendRow(items);
            searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
            searchModel->setHeaderData(1, Qt::Horizontal, tr("Product Name"));
            searchModel->setHeaderData(2, Qt::Horizontal, tr("Price"));
            searchModel->setHeaderData(3, Qt::Horizontal, tr("Category"));
        }
}


/*수정버튼이 눌렸을 때*/
void ProductManagerForm::on_modifyPushButton_clicked()
{

    /*pid, productname, price, category 값을 저장해 줌*/
    int pid = ui->idLineEdit->text().toInt();
    QString productname, category;
    productname = ui->productnameLineEdit->text();          //nameLineEdit에 입력한 값을 변수 name에 저장해준다
    int price = ui->priceLineEdit->text().toInt();              //priceLineEdit에 입력한 값을 변수 price에 int형으로 바꾸어 저장해준다
    category = ui->categoryLineEdit->text();

    /*수정할 부분의 row값을 구해줌*/
    QModelIndex idx = ui->productTableView->currentIndex();
    int delid = idx.sibling(idx.row(), 0).data().toInt();
    int row = idx.row();

    /*update문을 통해 tableview의 값들을 변경해 줌*/
    query->prepare("UPDATE product SET p_pname = ?, p_price = ?, p_category = ? WHERE p_id = ?");
    query->bindValue(0, productname);
    query->bindValue(1, price);
    query->bindValue(2, category);
    query->bindValue(3, pid);
    query->exec();
    productModel->select();

    emit productModified(productname, pid, row);    //바뀐 product 정보를 shopmanagerform으로 보내줌
}

/*add 버튼을 클릭했을 때*/
void ProductManagerForm::on_addPushButton_clicked()
{
    QString productname, category;
    int price;
    int id = makeId( );                             //makeId()를 통해 새로운 상품 id 값을 추가해 줌

    //lineEdit에 정보를 적지 않은 채로 add버튼을 눌렀을 때
    if(ui->productnameLineEdit->text() == "" || ui->priceLineEdit->text() == "" || ui->categoryLineEdit->text() == "")
    {
        return;                                         //그냥 리턴해줘서 아무 일도 일어나지 않게끔 해 줌
    }

    /*정보들을 변수에 저장*/
    productname = ui->productnameLineEdit->text();      //nameLineEdit에 입력한 값을 변수 name에 저장해준다
    price = ui->priceLineEdit->text().toInt();          //priceLineEdit에 입력한 값을 변수 price에 int형으로 바꾸어 저장해준다
    category = ui->categoryLineEdit->text();            //categoryLineEdit에 입력한 값을 변수 category에 저장해준다

    if(productname.length()) {                          //상품이름 길이가 1이상일 때만 if문 실행
        ProductItem* p = new ProductItem(id, productname, price, category);

        emit productAdded(productname, price, category, id); //productAdded 시그널에 productname, price, category, id를 담아 shopmanagerform으로 정보를 보내준다
    }

    /*clientlist에 정보를 insert해줌*/
    query->exec(QString("INSERT INTO product VALUES (%1, '%2', %3, '%4')").arg(id).arg(productname).arg(price).arg(category));
    productModel->select();
}

void ProductManagerForm::on_productTableView_clicked(const QModelIndex &index)
{
    /*변수에 정보를 저장*/
    int id = index.sibling(index.row(), 0).data().toInt();
    QString pname = index.sibling(index.row(), 1).data().toString();
    int price = index.sibling(index.row(), 2).data().toInt();
    QString category = index.sibling(index.row(), 3).data().toString();

    /*LineEdit에 정보를 띄워줌*/
    ui->idLineEdit->setText(QString::number(id));           //item의 인덱스 0번 값에 고객id를 저장해 줌
    ui->productnameLineEdit->setText(pname);                //item의 인덱스 1번 값에 고객이름를 저장해 줌
    ui->priceLineEdit->setText(QString::number(price));     //item의 인덱스 2번 값에 고객전화번호를 저장해 줌
    ui->categoryLineEdit->setText(category);                //item의 인덱스 3번 값에 고객주소를 저장해 줌
    ui->toolBox->setCurrentIndex(0);                        //treeWidget에 있는 아이템을 선택했을 때 toolBox의 0번째 인덱스 값인 Input을 현재 화면으로 설정
}

/*shopmanagerform에서 pid를 받는 부분*/
void ProductManagerForm::PIDsended(int id){ //받은 pid에 대한 정보들을 c에 저장하고, pname, price, category를 각각 변수에 저장해준다

    auto flag = Qt::MatchCaseSensitive|Qt::MatchContains;   //flag값을 지정해 줌. i가 0이 아닐 때는 입력한 값이 포함되면 검색이 되도록 만듦
    QModelIndexList products = productModel->match(productModel->index(0,0),Qt::EditRole, id,-1,Qt::MatchFlags(flag));

    /*변수에 정보를 저장*/
    foreach(auto ix,products) {
        //int id =ix.sibling(ix.row(),0).data().toInt();
        QString productname = ix.sibling(ix.row(),1).data().toString();
        int price =ix.sibling(ix.row(),2).data().toInt();
        QString category = ix.sibling(ix.row(),3).data().toString();
        QStringList productStrings;
        productStrings << QString::number(id)<<productname<<QString::number(price)<<category;

        /*productname, price, category shopmanagerform으로 보내줌*/
        emit sendPInfo(productname, price, category);
    }
}
