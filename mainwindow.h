#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>


struct vector{
    double x;
    double y;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
void showEvent(QShowEvent * event);

private slots:
    void on_btnGo_clicked();
    void move();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
};
#endif // MAINWINDOW_H
