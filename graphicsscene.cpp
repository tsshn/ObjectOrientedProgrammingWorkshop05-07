#include "graphicsscene.h"
#include "math.h"

GraphicsScene::GraphicsScene(QGraphicsView *view)
    : QGraphicsScene(1, 1, 1119, 589),
      _parentView(view),
      _mouseX(0), _mouseY(0),
      _currentTool(Tool::Pencil),
      _currentPencil(Qt::black, 2),
      _item1(nullptr), _item2(nullptr), _item3(nullptr)
{
    setBackgroundBrush(Qt::white);
}

void GraphicsScene::setTool(Tool stage)
{
    _currentTool = stage;
}

void GraphicsScene::setSize(int size)
{
    _currentPencil.setWidth(size);
}

void GraphicsScene::setColor(QColor color)
{
    _currentPencil.setColor(color);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _mouseX = event->scenePos().x();
    _mouseY = event->scenePos().y();
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    _item1 = nullptr;
    _item2 = nullptr;
    _item3 = nullptr;
}
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    qreal currentX = event->scenePos().x(),
          currentY = event->scenePos().y();

    if (_item1 != nullptr)
    {
        removeItem(_item1);
        delete _item1;
    }

    switch (_currentTool)
    {

    case Tool::Pencil:
    {
        addLine(_mouseX, _mouseY, currentX, currentY, _currentPencil);
        _mouseX = currentX;
        _mouseY = currentY;
        break;
    }

    case Tool::Spray:
    {
        qreal width = _currentPencil.width();
        srand(time(NULL));
        for (int i = 0; i < width; i++)
        {
            qreal pointX = currentX - width + static_cast<qreal>(rand() % static_cast<int>(width));
            qreal pointY = currentY - width + static_cast<qreal>(rand() % static_cast<int>(width));
            addEllipse(pointX, pointY, 1, 1, QPen(_currentPencil.color(), 0));
        }
        break;
    }

    case Tool::Eraser:
    {
        QPen eraser(Qt::white, _currentPencil.width());
        int width = _currentPencil.width() / 2;
        addLine(currentX - width , currentY, currentX + width , currentY, eraser);
        break;
    }

    case Tool::Line:
    {
        _item1 = addLine(_mouseX, _mouseY, currentX, currentY, _currentPencil);
        break;
    }

    case Tool::Rectangle:
    {
        qreal rectX = currentX > _mouseX ? _mouseX : currentX;
        qreal rectY = currentY > _mouseY ? _mouseY : currentY;
        _item1 = addRect(rectX, rectY, abs(currentX - _mouseX), abs(currentY - _mouseY), _currentPencil);
        break;
    }

    case Tool::Ellipse:
    {
        qreal ellipseX = currentX > _mouseX ? _mouseX : currentX;
        qreal ellipseY = currentY > _mouseY ? _mouseY : currentY;
        _item1 = addEllipse(ellipseX, ellipseY, abs(currentX - _mouseX), abs(currentY - _mouseY), _currentPencil);
        break;
    }

    case Tool::Triangle:
    {
        if (_item2 != nullptr)
        {
            removeItem(_item2);
            delete _item2;
        }
        if (_item3 != nullptr)
        {
            removeItem(_item3);
            delete _item3;
        }
        _item1 = addLine(_mouseX, _mouseY, (_mouseX + currentX) / 2, currentY, _currentPencil);
        _item2 = addLine((_mouseX + currentX) / 2, currentY, currentX, _mouseY, _currentPencil);
        _item3 = addLine(currentX, _mouseY, _mouseX, _mouseY, _currentPencil);
        break;
    }

    }
}
