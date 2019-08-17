#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&serial,
               SIGNAL(readyRead()),
               this,
               SLOT(dadosRecebidos()));
    for(auto& item : QSerialPortInfo::availablePorts())
           ui->box_serial->addItem(item.portName());
    for(auto& item : QSerialPortInfo::standardBaudRates())
           ui->box_velocidade->addItem(QString::number(item) );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    serial.setPortName(ui->box_serial->currentText());
       serial.setBaudRate(ui->box_velocidade->currentText().toInt());
    
       if(serial.open(QIODevice::ReadWrite)){
           ui->status_conexao->setText("Status: Conectado");
       } 
    
}

void MainWindow::on_pushButton_2_clicked()
{
    serial.close();
       ui->status_conexao->setText("Status: Desconectado");
    
}
void MainWindow::dadosRecebidos()
{

   auto data = serial.readAll();
   auto dados = QJsonDocument::fromJson(data).object().toVariantMap();
        if(dados.contains("MOTOR"))
      {
          if(dados["MOTOR"].toBool() == 1){
              ui->label_6->setText("Ligada");
          }
          else
          {
              ui->label_6->setText("Desligada");
          }
       }
      if(dados.contains("CONTADOR")){
          ui->label_8->setText(dados["CONTADOR"].toString());
      }
}



void MainWindow::on_pushButton_3_clicked()
{
    serial.write("{\"MOTOR\": 1}");
}

void MainWindow::on_pushButton_4_clicked()
{
    serial.write("{\"MOTOR\": 0}");
}
