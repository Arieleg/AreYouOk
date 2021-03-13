#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "areyouokdialog.h"

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
    void on_RunButton_clicked();

    void on_StopButton_clicked();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *mSystemTrayIcon;
    void changeEvent(QEvent* e) override;
    void maximize_try_icon(QSystemTrayIcon::ActivationReason reason);
    AreYouOkDialog *areYouOk;
};
#endif // MAINWINDOW_H
