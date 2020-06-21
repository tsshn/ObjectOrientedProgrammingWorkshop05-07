#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPen>
#include <QQueue>

#include <ctime>

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QGraphicsView *view = nullptr);

    enum class Tool
    {
        Pencil,
        Eraser,
        Spray,
        Line,
        Rectangle,
        Ellipse,
        Triangle
    };

    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;

    void setTool(Tool);
    void setSize(int);
    void setColor(QColor);

private:
    QGraphicsView *_parentView;

    qreal _mouseX;
    qreal _mouseY;

    Tool _currentTool;
    QPen _currentPencil;

    QGraphicsItem *_item1;
    QGraphicsItem *_item2;
    QGraphicsItem *_item3;
};

#endif
