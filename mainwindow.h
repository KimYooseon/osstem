#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ClientManagerForm;
class ProductManagerForm;
class ShopManagerForm;
class ChatServerForm;
class Widget;
class ClientLogThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionClient_triggered();

    void on_actionProduct_triggered();

    void on_actionOrder_triggered();

    void on_actionChat_triggered();

    void on_actionServer_triggered();

private:
    Ui::MainWindow *ui;
    ClientManagerForm *clientForm;
    ProductManagerForm *productForm;
    ShopManagerForm* orderForm;
    ChatServerForm* serverForm;
    Widget* wd;
    ClientLogThread* clientLogTh;


};
#endif // MAINWINDOW_H
