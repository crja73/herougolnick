#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "math.h"

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

void MainWindow::on_pushButton_clicked()
{
    int rows = ui->tableWidget->rowCount();
    double points_x[200];
    double points_y[200];
    bool error = false;
    for(int i=0; i<rows; i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(0, 0);
        if (item == nullptr)
        {
            item = new QTableWidgetItem;
            ui->tableWidget->setItem(0, 0, item);
        }
        QString text = item->text();
        bool flag;
        double value = text.toDouble(&flag);
        if(flag)
        {
            points_x[i] = value;
        }
        else
        {
            error = true;
        }
        item = ui->tableWidget->item(i, 1);
        if(item == nullptr)
        {
            item = new QTableWidgetItem;
            ui->tableWidget->setItem(i, 1, item);
        }
        text = item->text();
        value = text.toDouble(&flag);
        if (flag)
        {
            points_y[i] = value;
        }
        else
        {
            error = true;
        }
    }
    if(error)
    {
        QMessageBox::information(this, "ERROR", "Incorrect data!");
    }
    else
    {
        double P = 0.0;
        for(int i=0; i<rows;i++)
        {
            int next = i + 1;
            if(next == rows)
            {
                next = 0;
            }
            double x1 = points_x[i];
            double x2 = points_x[next];
            double y1 = points_y[i];
            double y2 = points_y[next];
            double dist = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
            P += dist;
        }
        ui->label_perim->setNum(P);
    }

}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
    ui->tableWidget->setColumnCount(2);
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    QString text = item->text();
    bool flag;
    double value = text.toDouble(&flag);
    if(flag)
    {
        item->setForeground(Qt::black);
        item->setBackground(Qt::white);
    }
    else
    {
        item->setBackground(Qt::red);
        item->setForeground(Qt::white);
    }
}
