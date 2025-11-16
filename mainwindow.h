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
    void on_adminButton_clicked();

    void on_patronButton_clicked();

    void on_staffButton_clicked();

    void on_libLoginButton_clicked();

    void on_browseButton_clicked();

    void on_patronAccountButton_clicked();

    void on_patronLoanTable_cellDoubleClicked(int row, int column);

    void on_patronHoldTable_cellDoubleClicked(int row, int column);

    void on_adminLoginButton_clicked();

    void on_libLoginBackButton_clicked();

    void on_adminLoginBackButton_clicked();

    void on_patronBackButton_clicked();

    void on_patronLoginButton_clicked();

    void on_patronLogoutFromHomeButton_clicked();

    void on_patronBackFromCatalogueButton_clicked();

    void on_patronLogoutFromCatalogueButton_clicked();

    void on_patronBackFromAccountButton_clicked();

    void on_patronLogoutFromAccountButton_clicked();

    void on_staffFromHomeLogoutButton_clicked();

    void on_adminFromHomeLogoutButton_clicked();

    void on_CatalogueTable_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    Control* controller;
};

#endif // MAINWINDOW_H
