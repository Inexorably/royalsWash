#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand (time(NULL));

    //Window title.
    this->setWindowTitle("Wash Analysis");

    //Add columns to the table on start up.
    for (int i = 0; i < 6; ++i){
        ui->tableWidgetBaseStats->setColumnCount(ui->tableWidgetBaseStats->horizontalHeader()->count() + 1);
    }

    //Fit the columns.
    ui->tableWidgetBaseStats->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Title columns.
    ui->tableWidgetBaseStats->setHorizontalHeaderItem(0, new QTableWidgetItem("Lvl"));
    ui->tableWidgetBaseStats->setHorizontalHeaderItem(1, new QTableWidgetItem("Hp (Pre-wash)"));
    ui->tableWidgetBaseStats->setHorizontalHeaderItem(2, new QTableWidgetItem("Mp (Pre-wash)"));
    ui->tableWidgetBaseStats->setHorizontalHeaderItem(3, new QTableWidgetItem("Hp (Post-wash)"));
    ui->tableWidgetBaseStats->setHorizontalHeaderItem(4, new QTableWidgetItem("Mp (Post-wash)"));
    ui->tableWidgetBaseStats->setHorizontalHeaderItem(5, new QTableWidgetItem("APRs used"));
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

    //Find the min mp.
    int minMp = 0;
    if (m.mapleClass == SPEARMAN){
        minMp = m.lvl*4+156;
    }
    else if (m.mapleClass == FIGHTER){
        minMp = m.lvl*4+56;
    }
    else if (m.mapleClass == ARCHER || m.mapleClass == THEIF){
        minMp = m.lvl*14+148;
    }
    else if (m.mapleClass == BUCC || m.mapleClass == SAIR){
        minMp = m.lvl*18+111;
    }
    else if (m.mapleClass == MAGE){
        minMp = m.lvl*22+488;
    }

    //If min mp button is checked and if the value is not below the minimum mp for that class:
    if (ui->checkBoxTargetMp->isChecked()){
        if (minMp > ui->spinBoxTargetMp->value()){
            ui->spinBoxTargetMp->setValue(minMp);
        }
    }

    //Include hp quest?
    if (m.hpQuest){
        if (m.mapleClass == SPEARMAN || m.mapleClass == FIGHTER){
            m.hp += 1000;
        }
        else if (m.mapleClass != MAGE){
            m.hp += 500;
        }
    }

    //Store our start values in the table.
    ui->tableWidgetBaseStats->setRowCount(0);
    ui->tableWidgetBaseStats->insertRow(0);
    //ui->tableWidgetBaseStats->setItem(0, 0, new QTableWidgetItem(QString::number(m.lvl)));
    //ui->tableWidgetBaseStats->setItem(0, 1, new QTableWidgetItem(QString::number(m.hp)));
   // ui->tableWidgetBaseStats->setItem(0, 2, new QTableWidgetItem(QString::number(m.mp)));

    //Level up to 200, printing the results to the table widget.
    for (; m.lvl <= 200;){

        ui->tableWidgetBaseStats->insertRow(ui->tableWidgetBaseStats->rowCount());
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 0, new QTableWidgetItem(QString::number(m.lvl)));
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 1, new QTableWidgetItem(QString::number(m.hp)));
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 2, new QTableWidgetItem(QString::number(m.mp)));

        //Wash mp > hp.
        //Get min mp for class and figure out how many washes we can get.
        int washedMp = 0;
        int washedHp = 0;
        int maxWashes = 0;
        if (m.mapleClass == SPEARMAN){
            washedMp = m.lvl*4+156;
            if (ui->checkBoxTargetMp->isChecked() && ui->spinBoxTargetMp->value() > washedMp){
                washedMp = ui->spinBoxTargetMp->value();
                if (ui->spinBoxTargetMp->value() > m.mp){
                    washedMp = m.mp;
                }
            }
            maxWashes = (m.mp - washedMp)/4;
            washedHp = m.hp + static_cast<int>(static_cast<double>(maxWashes)*52.0);
        }
        else if (m.mapleClass == FIGHTER){
            washedMp = m.lvl*4+56;
            if (ui->checkBoxTargetMp->isChecked() && ui->spinBoxTargetMp->value() > washedMp){
                washedMp = ui->spinBoxTargetMp->value();
                if (ui->spinBoxTargetMp->value() > m.mp){
                    washedMp = m.mp;
                }
            }
            maxWashes = (m.mp - washedMp)/4;
            washedHp = m.hp + static_cast<int>(static_cast<double>(maxWashes)*52.0);
        }
        else if (m.mapleClass == ARCHER || m.mapleClass == THEIF){
            washedMp = m.lvl*14+148;
            if (ui->checkBoxTargetMp->isChecked() && ui->spinBoxTargetMp->value() > washedMp){
                washedMp = ui->spinBoxTargetMp->value();
                if (ui->spinBoxTargetMp->value() > m.mp){
                    washedMp = m.mp;
                }
            }
            maxWashes = (m.mp - washedMp)/12;
            washedHp = m.hp + maxWashes*18;
        }
        else if (m.mapleClass == BUCC || m.mapleClass == SAIR){
            washedMp = m.lvl*18+111;
            if (ui->checkBoxTargetMp->isChecked() && ui->spinBoxTargetMp->value() > washedMp){
                washedMp = ui->spinBoxTargetMp->value();
                if (ui->spinBoxTargetMp->value() > m.mp){
                    washedMp = m.mp;
                }
            }
            if (m.mapleClass == BUCC){
                maxWashes = (m.mp - washedMp)/16;
                washedHp = m.hp + maxWashes*40;
            }
            else if (m.mapleClass == SAIR){
                maxWashes = (m.mp - washedMp)/16;
                washedHp = m.hp + maxWashes*20;
            }
        }
        else if (m.mapleClass == MAGE){ //Note: Assumes remove points in mp up.
            washedMp = m.lvl*22+488;
            if (ui->checkBoxTargetMp->isChecked() && ui->spinBoxTargetMp->value() > washedMp){
                washedMp = ui->spinBoxTargetMp->value();
                if (ui->spinBoxTargetMp->value() > m.mp){
                    washedMp = m.mp;
                }
            }
            maxWashes = (m.mp - washedMp)/20;
            washedHp = m.hp + maxWashes*13;
        }

        //Push to qtable.
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 3, new QTableWidgetItem(QString::number(washedHp)));
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 4, new QTableWidgetItem(QString::number(washedMp)));
        ui->tableWidgetBaseStats->setItem(ui->tableWidgetBaseStats->rowCount()-1, 5, new QTableWidgetItem(QString::number(m.aprUsed+maxWashes)));

        m.levelUp();
    }

    //Hacky but quick.
    ui->tableWidgetBaseStats->removeRow(0);

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

void MainWindow::on_checkBoxTargetMp_clicked(bool checked){
    ui->spinBoxTargetMp->setEnabled(checked);
}

//Temporary implementation.
void MainWindow::on_actionNew_triggered(){
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    qApp->quit();
}
