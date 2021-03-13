#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->StopButton->hide();
    mSystemTrayIcon = new QSystemTrayIcon(this);
    mSystemTrayIcon->setIcon(QIcon(":/icons/icon.png"));
    connect(mSystemTrayIcon, &QSystemTrayIcon::activated, this, &MainWindow::maximize_try_icon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent* e)
{
    switch (e->type())
    {
        case QEvent::LanguageChange:
            this->ui->retranslateUi(this);
            break;
        case QEvent::WindowStateChange:
            {
                if (this->windowState() & Qt::WindowMinimized)
                {
                    QTimer::singleShot(250, this, SLOT(hide()));
                    mSystemTrayIcon->show();
                    mSystemTrayIcon->showMessage("","AreYouOK? was minimized to the system tray.");
                }

               break;
            }

        default:
            break;
    }

    QMainWindow::changeEvent(e);
}

void MainWindow::maximize_try_icon( QSystemTrayIcon::ActivationReason reason )
{
    if( reason )
    {
        if( reason != QSystemTrayIcon::DoubleClick )
        return;
    }

    if( isVisible() )
    {
        this->hide();
    }
    else
    {
        this->show();
        this->setWindowState(Qt::WindowState::WindowActive);
        this->setFocus();
    }
}

void MainWindow::on_RunButton_clicked()
{
    unsigned long timeRepeat=0;
    unsigned long timeMessage=0;
    this->ui->RunButton->hide();
    this->ui->StopButton->show();
    this->ui->MessageTimeH->setDisabled(true);
    this->ui->MessageTimeMin->setDisabled(true);
    this->ui->repeatTimeH->setDisabled(true);
    this->ui->repeatTimeMin->setDisabled(true);
    timeRepeat+=this->ui->repeatTimeH->value()*3600000;
    timeRepeat+=this->ui->repeatTimeMin->value()*60000;
    timeMessage+=this->ui->MessageTimeH->value()*3600000;
    timeMessage+=this->ui->MessageTimeMin->value()*60000;
    this->areYouOk=new AreYouOkDialog(nullptr, timeRepeat,timeMessage);
    this->areYouOk->run();
}

void MainWindow::on_StopButton_clicked()
{
    this->areYouOk->stop();
    this->ui->StopButton->hide();
    this->ui->MessageTimeH->setDisabled(false);
    this->ui->MessageTimeMin->setDisabled(false);
    this->ui->repeatTimeH->setDisabled(false);
    this->ui->repeatTimeMin->setDisabled(false);
    this->ui->RunButton->show();
}
