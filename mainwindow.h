#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QProcess>

#include <QDebug>

#include "maplestats.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonProcess_clicked();

    void on_checkBoxMpWash_clicked();

    void on_comboBoxClass_currentTextChanged(const QString &arg1);

    void on_checkBoxTargetMp_clicked(bool checked);

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
