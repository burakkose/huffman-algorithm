#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "encode.h"
#include "decode.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encode_btton_clicked()
{
    encode enscreen;
    enscreen.setModal(true);
    enscreen.exec();
}

void MainWindow::on_decode_button_clicked()
{
    decode descreen;
    descreen.setModal(true);
    descreen.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, trUtf8("About"), trUtf8("Created by:\n\n\tBurak KÖSE"
                                                     "\n\tKübra GÜÇLÜ\n\tOnur SENTÜRK"
                                                     "\n\nHuffman Algorithm"));
}
