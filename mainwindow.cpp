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
    m.mwLvl = ui->comboBoxMwLvl->currentText().toInt();
    m.mpWashStartLvl = ui->spinBoxMpWashStart->value();
    m.mpWashStopLvl = ui->spinBoxMpWashStop->value();
    m.mpWashing = ui->checkBoxMpWash->isChecked();
    m.intGear = ui->spinBoxIntGear->value();
    m.intGearStartLvl = ui->spinBoxIntGearStartLvl->value();
    m.hpQuest = ui->checkBoxIncludeHpQuest->isChecked();

    m.washBaseIntLvl = ui->spinBoxWashBaseIntLvl->value();
    m.addBaseIntUntilLvl = ui->spinBoxAddIntLvl->value();

    //Store our start values in the table.
    ui->tableWidgetBaseStats->setRowCount(0);
    ui->tableWidgetBaseStats->insertRow(0);
    ui->tableWidgetBaseStats->setItem(0, 0, new QTableWidgetItem(QString::number(m.lvl)));
    ui->tableWidgetBaseStats->setItem(0, 1, new QTableWidgetItem(QString::number(m.hp)));
    ui->tableWidgetBaseStats->setItem(0, 2, new QTableWidgetItem(QString::number(m.mp)));

    //Include hp quest?
    if (m.hpQuest){
        if (m.mapleClass == SPEARMAN || m.mapleClass == FIGHTER){
            m.hp += 1000;
        }
        else if (m.mapleClass != MAGE){
            m.hp += 500;
        }
    }

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

void MainWindow::on_checkBoxMpWash_clicked(){
    ui->spinBoxMpWashStart->setEnabled(!ui->spinBoxMpWashStart->isEnabled());
    ui->spinBoxMpWashStop->setEnabled(!ui->spinBoxMpWashStop->isEnabled());
    ui->labelMpWashStart->setEnabled(!ui->labelMpWashStart->isEnabled());
    ui->labelMpWashStop->setEnabled(!ui->labelMpWashStop->isEnabled());
}

void MainWindow::on_comboBoxClass_currentTextChanged(const QString &arg1){
    if (arg1 == MAGE){
        ui->spinBoxWashBaseIntLvl->setEnabled(0);
        ui->spinBoxAddIntLvl->setEnabled(0);
        ui->checkBoxIncludeHpQuest->setEnabled(0);
    }
    else{
        ui->spinBoxWashBaseIntLvl->setEnabled(1);
        ui->spinBoxAddIntLvl->setEnabled(1);
        ui->checkBoxIncludeHpQuest->setEnabled(1);
    }
}
