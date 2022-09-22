#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "physbody.h"
#include <math.h>


bool IsRun = false; // флаг запуска анимации
double rad = 10; // радиус шарика
double dt = 10; // временной шаг
double v0; // начальная скорость
double angle; // начальное направление скорости
vector v; // вектор скорости
vector r; // радиус-вектор
physBody * ball = new physBody(); // физическое тело
QImage * img; // картинка для фона
QImage bgr, bgr_clear; // фон с траекторией и без неё
QPainterPath traj; // траектория
QPainter * p; // объект рисовальщик


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //создадим сцену
    scene = new QGraphicsScene(ui->graphicsView);
    // anti-aliasing
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // создаём картинку с фоном, будем использовать её как текстуру
    int imgSize = 800; // размер картинки
    img = new QImage(imgSize,imgSize,QImage::Format_RGB16);
    QPainter painter(img); // рисовальщик
    painter.setPen(Qt::NoPen); // будем рисовать без контура
    painter.setBrush(QColor(255,255,224)); // цвет фона
    painter.drawRect(0,0,imgSize,imgSize);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

}

void MainWindow::move()
{
    // изменение направления скорости при отскоке
    if (r.x+rad > scene->width()-1 || r.x-rad < 0) {
    v.x = -v.x; }
    if (r.y+rad > scene->height()-1 || r.y-rad < 0) {
    v.y = -v.y; }

    // определение новых координат тела
    r.x += v.x*dt;
    r.y += v.y*dt;


    ball->setPos(r.x-rad, scene->height()-(r.y+rad));
    // добавление участка траектории
    traj.lineTo(r.x, scene->height()-r.y);
    p->drawPath(traj);

    if (ui->chTrajectory->isChecked()) {
    scene->setBackgroundBrush(bgr); }
    else {
    scene->setBackgroundBrush(bgr_clear);}
}

void MainWindow::showEvent(QShowEvent *)
{
    // начальное положение тела
    r.x = ui->radX->text().toDouble();
    r.y = ui->radY->text().toDouble();
// задаём область графической сцены
    scene->setSceneRect(0,0,ui->graphicsView->height(),
    ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // устанавливаем в качестве фона изображение img
    bgr = img->scaledToHeight(ui->graphicsView->height()+40);
    bgr_clear = img->scaledToHeight(ui->graphicsView->height());
    scene->setBackgroundBrush(bgr);
    // создание и настройка рисовальщика траектории
    p = new QPainter(&bgr);
    QPen pen(Qt::black,2);
    p->setPen(pen);
    traj.moveTo(r.x, scene->height()-r.y);
    // добавление физического тела
    ball->radius = rad;
    ball->setPos(r.x-rad, scene->height()-(r.y+rad));
    scene->addItem(ball);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnGo_clicked()
{

    // модуль начальной скорости
    v0 = ui->edtV->text().toDouble();
    // угол наклона начальной скорости к горизонтальной оси
    angle = ui->edtA->text().toDouble()/180*M_PI;
    // определение проекций начальной скорости
    v.x = v0*cos(angle); v.y = v0*sin(angle);
    IsRun = !IsRun;
    if (IsRun) {
        timer->start(dt);
        ui->btnGo->setText("Стоп");
    }
    else {
        timer->stop();
        ui->btnGo->setText("Запуск");
    }

}


