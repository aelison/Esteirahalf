#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSerialPort serial;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dadosRecebidos();
    void on_acender_vermelho_clicked();
    void on_apagar_vermelho_clicked();
    void on_acender_amarelo_clicked();
    void on_apagar_amarelo_clicked();


private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();
    
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
