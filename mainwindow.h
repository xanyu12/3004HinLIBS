#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "control.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow* getUI();
    void setControl(Control* c);

private slots:
    void on_catalogueTable_cellClicked(int row, int column);

    void on_adminButton_clicked();

    void on_patronButton_clicked();

    void on_staffButton_clicked();

    void on_libLoginButton_clicked();

    void on_browseButton_clicked();

    void on_patronAccountButton_clicked();

    void on_patronLoanTable_cellClicked(int row, int column);

    void on_patronHoldTable_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    Control* controller;
};

#endif // MAINWINDOW_H
