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
    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    Control* controller;
};

#endif // MAINWINDOW_H
