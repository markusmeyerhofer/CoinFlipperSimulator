#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()),
            this, SLOT(startStop()));

    connect(this, SIGNAL(updateGUI()),
            this, SLOT(setGUIValues()));

    ui->headsBar->setValue(0);
    ui->tailsBar->setValue(0);
    isFlipping = false;

    side = 0;
    headsNum = 0;
    tailsNum = 0;
    curNum = 0;

    connect(&watcher, SIGNAL(finished()),
            this, SLOT(flippingHasFinished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startStop() {

    if (isFlipping) {
        isFlipping = false;
        ui->pushButton->setText("Start");
    }
 else {
        isFlipping = true;

        side = 0;
        headsNum = 0;
        tailsNum = 0;
        curNum = 0;

        initGUIElements();

        QFuture<void> future = QtConcurrent::run(this,&MainWindow::flipCoins);
        watcher.setFuture(future);

        ui->pushButton->setText("Stop");
    }
}

void MainWindow::flipCoins() {

    srand(time(NULL));

     while ((curNum < ui->spinBox->value()) && isFlipping) {

        side = rand() %2;

        if(side == 0)
           headsNum++;
        else
            tailsNum++;

        curNum++;

        if (curNum %10000 == 0)
            emit updateGUI();
    }
}

void MainWindow::initGUIElements() {

    ui->headsBar->setMaximum(ui->spinBox->value());
    ui->tailsBar->setMaximum(ui->spinBox->value());

    ui->headsBar->setValue(0);
    ui->tailsBar->setValue(0);
}

void MainWindow::flippingHasFinished() {
    isFlipping = false;
    ui->pushButton->setText("Start");
    setGUIValues();
}

void MainWindow::setGUIValues() {

    ui->headsBar->setValue(headsNum);
    ui->tailsBar->setValue(tailsNum);

    ui->headsNum->setText(str.setNum(headsNum));
    ui->tailsNum->setText(str.setNum(tailsNum));

    ui->numCurrent->setText(str.setNum(curNum));
}
