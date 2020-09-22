#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFutureWatcher>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    int side;
    int headsNum;
    int tailsNum;
    int curNum;

    bool isFlipping;
    QString str;
    void flipCoins();
    QFutureWatcher<void> watcher;

private slots:
    void startStop();
    void initGUIElements();
    void flippingHasFinished();
    void setGUIValues();

signals:

    void stopFlipping();
    void updateGUI();
};

#endif // MAINWINDOW_H
