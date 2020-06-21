#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphicsscene.h"

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void save();
    void open();

    void on_pencil_clicked();
    void on_spray_clicked();
    void on_eraser_clicked();

    void on_line_clicked();
    void on_rectangle_clicked();
    void on_elipse_clicked();
    void on_triangle_clicked();

    void on_size_actionTriggered();
    void on_colorPicker_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsView *_view;
    GraphicsScene *_scene;

    void addMenu();
};

#endif
