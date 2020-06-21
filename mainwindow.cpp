#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow),
                                          _view(new QGraphicsView()),
                                          _scene(new GraphicsScene(_view))
{
    ui->setupUi(this);

    _view->setScene(_scene);
    _view->setCursor(Qt::CrossCursor);

    ui->gridLayout->addWidget(_view);

    ui->canvas->show();

    this->setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->canvas->setMouseTracking(true);

    addMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _scene;
}

void MainWindow::addMenu()
{
    QMenu *fileMenu = this->menuBar()->addMenu(tr("File"));

    QAction *save= new QAction(tr("Save as"), this);
    save->setShortcut(tr("Ctrl+S"));
    connect(save, SIGNAL(triggered()), this, SLOT(save()));
    fileMenu->addAction(save);

    QAction *open = new QAction(tr("Open"), this);
    open ->setShortcut(tr("Ctrl+O"));
    connect(open , SIGNAL(triggered()), this, SLOT(open()));
    fileMenu->addAction(open);

    fileMenu->addSeparator();

    QAction *exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    fileMenu->addAction(exitAction);
}

void MainWindow::save()
{
    QString outName = QFileDialog::getSaveFileName(
        this, "Save file", tr("C:/Users/User/Desktop"), "Image (*.png)");
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QPixmap pixmap = QPixmap::grabWidget(_view);
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pixmap.save(outName);
}

void MainWindow::open()
{
    QString caption = QFileDialog::getOpenFileName(
        this, "Open", tr("C:/Users/User/Desktop"), "Image (*.png;*.jpg)");
    QImage image(caption);
    int wDifference = image.width() / 1110 + 1;
    int hDifference = image.height() / 580 + 1;
    int mDifference = wDifference > hDifference ? wDifference : hDifference;
    image = image.scaled(image.width() / mDifference , image.height() / mDifference );
    _scene->addPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pencil_clicked()
{
    _scene->setTool(GraphicsScene::Tool::Pencil);
}

void MainWindow::on_eraser_clicked()
{
    _scene->setTool(GraphicsScene::Tool::Eraser);
}

void MainWindow::on_spray_clicked()
{
    _scene->setTool(GraphicsScene::Tool::Spray);
}

void MainWindow::on_line_clicked()
{
    _scene->setTool(GraphicsScene::Tool::Line);
}

void MainWindow::on_rectangle_clicked()
{
    _scene->setTool(GraphicsScene::Tool::Rectangle);
}

void MainWindow::on_elipse_clicked()
{
    _scene->setTool(GraphicsScene::Tool::Ellipse);
}
void MainWindow::on_triangle_clicked()
{
    _scene->setTool(GraphicsScene::Tool::Triangle);
}

void MainWindow::on_size_actionTriggered()
{
    _scene->setSize(ui->size->value());
}

void MainWindow::on_colorPicker_clicked()
{
    QColor color = QColorDialog::getColor();
    QString style = QString("background-color: %1").arg(color.name());
    ui->colorPicker->setStyleSheet(style);
    _scene->setColor(color);
}
