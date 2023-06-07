#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPushButton"
#include "poland.h"
#include <QPainter>
#include <QPixmap>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    QPushButton * button = new QPushButton(this);
    button->setGeometry(width() / 15 * 13, 10, 100, 30);
    button->setText("кнопка");
    connect(button, SIGNAL(clicked()), this, SLOT(button_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    QPen pen;
    pen.setColor(0xff0000);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.end();
}

void MainWindow::button_clicked() {
    QPixmap pm(width() * 0.7, height() * 0.8);
    QPainter painter;
    painter.begin(&pm);
    pm.fill(Qt::yellow);
    ui->label->setGeometry(10, 10, width() * 0.7, height() * 0.8);

    QString s = ui->lineEdit->text();
    double rez = 0;

    double xmin = -2*M_PI, xmax = 2*M_PI;
    double ymin = -1.335, ymax = 1;

    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();

    double x = xmin;
    double y = 0;

    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (xgmin - xgmax) / (ymax - ymin);

    double x0 = xgmin - kx * xmin;
    double y0 = ygmin - ky * ymax;

    int xg = x0 + kx * x;
    int yg = y0 + ky * y;

    double stepx = (xmax - xmin) / (xgmax - xgmin);

    QPen pen;

    QPainterPath path;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine((xmin + xmax) / 2, 0, (xmin + xmax) / 2, pm.height());
    painter.drawLine(0, pm.height() / 2, pm.width(), pm.height() / 2);

    QString xs;
    QString ss;
    xs = QString::number(x);
    ss = s;
    ss.replace(QRegularExpression("x"), '(' + xs + ')');
    int pr = calc(ss.toStdString(), rez);
    y = rez;
    xg = x0 + kx * x;
    yg = y0 + ky * y;
    path.moveTo(xg, yg);
    x += stepx;

    while(x <= xmax) {
        xs = QString::number(x);
        ss = s;
        ss.replace(QRegularExpression("x"), '(' + xs + ')');
        int pr = calc(ss.toStdString(), rez);
        if(pr != -1) {
            double lasty = y;
            y = rez;
            xg = x0 + kx * x;
            yg = y0 + ky * y;

            if (abs(y - lasty) > 5) {
                path.moveTo(xg, yg);
            } else {
                pen.setColor(Qt::red);
                painter.setPen(pen);
                path.lineTo(xg, yg);
                painter.drawPath(path);
            }
        }
        x += stepx;
    }

    pen.setColor(Qt::black);
    painter.setPen(pen);
    ui->label->setPixmap(pm);

    painter.end();

}













