#include "areyouokdialog.h"
#include "ui_areyouokdialog.h"
#include <QProcess>

#define TOKEN "to complete"
#define CHAT_ID "to complete"
#define MESSAGE "Hola%2C necesito ayuda!"

AreYouOkDialog::AreYouOkDialog(QWidget *parent, unsigned long rtime, unsigned long mtime) :
    QDialog(parent),
    ui(new Ui::AreYouOkDialog)
{
    ui->setupUi(this);
    this->repeatTime=rtime;
    this->messageTime=mtime;

    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);


    this->dialogTimer = new QTimer(this);
    this->dialogTimer->setSingleShot(true);
    connect(this->dialogTimer, SIGNAL(timeout()),this, SLOT(startDialogTimer()));

    this->messageTimer = new QTimer(this);
    connect(this->messageTimer, SIGNAL(timeout()),this, SLOT(sendMessageTimer()));


    this->messageLabelTimer = new QTimer(this);
    connect(this->messageLabelTimer, SIGNAL(timeout()),this, SLOT(updateMessageTimer()));


}

AreYouOkDialog::~AreYouOkDialog()
{
    delete ui;
}

void AreYouOkDialog::run(){
    this->dialogTimer->start(this->repeatTime);
}

void AreYouOkDialog::stop(){
    this->dialogTimer->stop();
    this->close();
}

void AreYouOkDialog::updateMessageTimer(){
    if(this->currentMessageTime>0)
        this->currentMessageTime-=1000;
    this->ui->AreYouOkTimerLabel->setText("Time remaining for the next message:  "+QString::number(this->currentMessageTime/1000)+" s");
}



void AreYouOkDialog::startDialogTimer()
{
    this->show();
    this->setWindowState(Qt::WindowState::WindowActive);
    this->setFocus();
    this->currentMessageTime=this->messageTime;
    this->ui->AreYouOkTimerLabel->setText("Time remaining for the next message:  "+QString::number(this->currentMessageTime/1000)+" s");
    this->messageLabelTimer->start(1000);
    this->messageTimer->start(this->messageTime);
}

void AreYouOkDialog::sendMessageTimer()
{
    this->messageLabelTimer->stop();
    this->currentMessageTime=this->messageTime;
    this->messageLabelTimer->start(1000);
    QProcess *myProcess = new QProcess();
    QStringList arguments;
    QString token =TOKEN;
    QString chat_id=CHAT_ID;
    arguments<<"https://api.telegram.org/bot" + token+ "/sendMessage?chat_id=" + chat_id + "&text="+ MESSAGE;
    myProcess->start("curl", arguments);

}

void AreYouOkDialog::on_YESpushButton_clicked()
{
    this->hide();
    this->messageLabelTimer->stop();
    this->messageTimer->stop();
    this->dialogTimer->start(this->repeatTime);

}

void AreYouOkDialog::on_NOpushButton_clicked()
{
    sendMessageTimer();
}
