#pragma once
#ifndef AREYOUOKDIALOG_H
#define AREYOUOKDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class AreYouOkDialog;
}

class AreYouOkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AreYouOkDialog(QWidget *parent = nullptr, unsigned long=0, unsigned long=0);
    ~AreYouOkDialog();
    void run(void);
    void stop(void);

private slots:
    void startDialogTimer();
    void sendMessageTimer();
    void on_YESpushButton_clicked();
    void updateMessageTimer();

    void on_NOpushButton_clicked();

private:
    Ui::AreYouOkDialog *ui;
    unsigned long repeatTime;
    unsigned long messageTime;
    unsigned long currentMessageTime;
    QTimer *dialogTimer;
    QTimer *messageTimer;
    QTimer *messageLabelTimer;
};

#endif // AREYOUOKDIALOG_H
