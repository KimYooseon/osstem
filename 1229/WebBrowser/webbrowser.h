#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QMainWindow>
#include <QWebEngineView>
class QLineEdit;

class WebBrowser : public QMainWindow
{
    Q_OBJECT

public:
    WebBrowser(QWidget *parent = nullptr);
    ~WebBrowser();

private:
    QLineEdit *lineEditURL;
    QWebEngineView *webEngineView;

public slots:
    void goSlot();
    void goBackwardSlot();
    void goForwardSlot();
    void goHomeSlot();

};
#endif // WEBBROWSER_H
