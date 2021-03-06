#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polys.h"
#include "powell.h"
#include <string>

using namespace std;

QString PowellOut(vector<array<double,8> > input){
    QString result;
    result += "<table><thead><tr><th>i</th><th>j</th><th>u x</th><th>u y</th><th>alpha</th><th>x</th><th>y</th><th>f(x,y)</th></tr></thead><tbody>";
    for(int i=0;i<input.size();i++){
        result += "<tr>";
        for(int j=0;j<8;j++){
            result += "<td>";
            result += QString::number(input[i][j]);
            result += "</td>";
        }
        result += "</tr>";
    }
    result += "</tbody></table>";
    return result;
}
QString GoldenOut(vector<array<double,5> > input){
    QString result;
    result += "<table><thead><tr><th>a</th><th>b</th><th>c</th><th>f(b)</th><th>c-a</th></tr></thead><tbody>";
    for(int i=0;i<input.size();i++){
        result += "<tr>";
        for(int j=0;j<5;j++){
            result += "<td>";
            result += QString::number(input[i][j]);
            result += "</td>";
        }
        result += "</tr>";
    }
    result += "</tbody></table>";
    return result;
}

QString QuasiOut(vector<array<double,6> > input){
    QString result;
    result += "<table><thead><tr><th>i</th><th>x</th><th>y</th><th>x of gradient f</th><th>y of gradient f</th><th>f(x,y)</th></tr></thead><tbody>";
    for(int i=0;i<input.size();i++){
        result += "<tr>";
        for(int j=0;j<6;j++){
            result += "<td>";
            result += QString::number(input[i][j]);
            result += "</td>";
        }
        result += "</tr>";
    }
    result += "</tbody></table>";
    return result;
}

QString ConOut(vector<array<double,7> > input){
    QString result;
    result += "<table><thead><tr><th>i</th><th>x</th><th>y</th><th>x of gradient f</th><th>y of gradient f</th><th>beta</th><th>f(x,y)</th></tr></thead><tbody>";
    for(int i=0;i<input.size();i++){
        result += "<tr>";
        for(int j=0;j<7;j++){
            result += "<td>";
            result += QString::number(input[i][j]);
            result += "</td>";
        }
        result += "</tr>";
    }
    result += "</tbody></table>";
    return result;
}

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
    QString input = ui->lineEdit->text();
    QString x = ui->lineEdit_2->text();
    QString y = ui->lineEdit_3->text();
    QString initial = ui->lineEdit_4->text();
    std::string::size_type sz;
    double x_min = std::stod (x.toStdString().substr(1),&sz);
    double x_max = std::stod (x.toStdString().substr(sz+2));
    double y_min = std::stod (y.toStdString().substr(1),&sz);
    double y_max = std::stod (y.toStdString().substr(sz+2));
    double ix = std::stod (initial.toStdString().substr(1),&sz);
    double iy = std::stod (initial.toStdString().substr(sz+2));
    string str = input.toStdString();
    Polys a(str);
    QString o = PowellOut(powell(a,ix,iy,x_max,x_min,y_max,y_min,0.000001));
    ui->textBrowser->append(o);
}

void MainWindow::on_pushButton_2_clicked()
{
    vector<array<double,5> > record;
    QString input = ui->lineEdit->text();
    QString x = ui->lineEdit_2->text();
    QString initial = ui->lineEdit_4->text();
    std::string::size_type sz;
    double x_min = std::stod (x.toStdString().substr(1),&sz);
    double x_max = std::stod (x.toStdString().substr(sz+2));
    double ix = std::stod (initial.toStdString().substr(1),&sz);
    string str = input.toStdString();
    Polys a(str);
    golden(record,a,x_min,ix,x_max,0.000001);
    QString o = GoldenOut(record);
    ui->textBrowser->append(o);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString input = ui->lineEdit->text();
    QString x = ui->lineEdit_2->text();
    QString y = ui->lineEdit_3->text();
    QString initial = ui->lineEdit_4->text();
    std::string::size_type sz;
    double x_min = std::stod (x.toStdString().substr(1),&sz);
    double x_max = std::stod (x.toStdString().substr(sz+2));
    double y_min = std::stod (y.toStdString().substr(1),&sz);
    double y_max = std::stod (y.toStdString().substr(sz+2));
    double ix = std::stod (initial.toStdString().substr(1),&sz);
    double iy = std::stod (initial.toStdString().substr(sz+2));
    string str = input.toStdString();
    Polys a(str);
    QString o = QuasiOut(quasi(a,ix,iy,x_max,x_min,y_max,y_min,0.000001));
    ui->textBrowser->append(o);
}

void MainWindow::on_pushButton_6_clicked()
{
    QString input = ui->lineEdit->text();
    QString x = ui->lineEdit_2->text();
    QString y = ui->lineEdit_3->text();
    QString initial = ui->lineEdit_4->text();
    std::string::size_type sz;
    double x_min = std::stod (x.toStdString().substr(1),&sz);
    double x_max = std::stod (x.toStdString().substr(sz+2));
    double y_min = std::stod (y.toStdString().substr(1),&sz);
    double y_max = std::stod (y.toStdString().substr(sz+2));
    double ix = std::stod (initial.toStdString().substr(1),&sz);
    double iy = std::stod (initial.toStdString().substr(sz+2));
    string str = input.toStdString();
    Polys a(str);
    QString o = ConOut(conjugate(a,ix,iy,x_max,x_min,y_max,y_min,0.000001));
    ui->textBrowser->append(o);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString input = ui->lineEdit->text();
    QString x = ui->lineEdit_2->text();
    QString y = ui->lineEdit_3->text();
    QString initial = ui->lineEdit_4->text();
    std::string::size_type sz;
    double x_min = std::stod (x.toStdString().substr(1),&sz);
    double x_max = std::stod (x.toStdString().substr(sz+2));
    double y_min = std::stod (y.toStdString().substr(1),&sz);
    double y_max = std::stod (y.toStdString().substr(sz+2));
    double ix = std::stod (initial.toStdString().substr(1),&sz);
    double iy = std::stod (initial.toStdString().substr(sz+2));
    string str = input.toStdString();
    Polys a(str);
    QString o = QuasiOut(steep(a,ix,iy,x_max,x_min,y_max,y_min,0.000001));
    ui->textBrowser->append(o);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString input = ui->lineEdit->text();
    QString x = ui->lineEdit_2->text();
    QString y = ui->lineEdit_3->text();
    QString initial = ui->lineEdit_4->text();
    std::string::size_type sz;
    double x_min = std::stod (x.toStdString().substr(1),&sz);
    double x_max = std::stod (x.toStdString().substr(sz+2));
    double y_min = std::stod (y.toStdString().substr(1),&sz);
    double y_max = std::stod (y.toStdString().substr(sz+2));
    double ix = std::stod (initial.toStdString().substr(1),&sz);
    double iy = std::stod (initial.toStdString().substr(sz+2));
    string str = input.toStdString();
    Polys a(str);
    QString o = QuasiOut(newton(a,ix,iy,x_max,x_min,y_max,y_min,0.000001));
    ui->textBrowser->append(o);
}
