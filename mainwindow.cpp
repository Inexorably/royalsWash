#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand (time(NULL));

    //Add columns to the table on start up.
    for (int i = 0; i < 3; ++i){
        ui->tableWidgetBaseStats->setColumnCount(ui->tableWidgetBaseStats->horizontalHeader()->count() + 1);
    }

    //Title columns.
    //ui->tableWidgetBaseStats->horizontalHeaderItem(0)->setText(QString("Base hp"));
    //ui->tableWidgetBaseStats->horizontalHeaderItem(1)->setText("Base mp");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonProcess_clicked(){
    //Get the input char stat parameters.
    mapleChar m;
    m.mapleClass = ui->comboBoxClass->currentText();
    m.hp = ui->spinBoxBaseHp->value();
    m.mp = ui->spinBoxBaseMp->value();
    m.intBase = ui->spinBoxBaseInt->value();
    m.lvl = ui->spinBoxBaseLvl->value();

    //Store our start values in the table.
    ui->tableWidgetBaseStats->setRowCount(0);
    ui->tableWidgetBaseStats->insertRow(0);
    ui->tableWidgetBaseStats->setItem(0, 0, new QTableWidgetItem(QString::number(m.lvl)));
    ui->tableWidgetBaseStats->setItem(0, 1, new QTableWidgetItem(QString::number(m.hp)));
    ui->tableWidgetBaseStats->setItem(0, 2, new QTableWidgetItem(QString::number(m.mp)));

    //Level up to 200, printing the results to the table widget.
    for (; m.lvl < 200;){
        m.levelUp();
        ui->tableWidgetBaseStats->insertRow(ui->tableWidgetBaseStats->rowCount());
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 0, new QTableWidgetItem(QString::number(m.lvl)));
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 1, new QTableWidgetItem(QString::number(m.hp)));
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 2, new QTableWidgetItem(QString::number(m.mp)));

        qDebug() << m.lvl;
    }

}
