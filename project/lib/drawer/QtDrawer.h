#pragma once

#include <QGraphicsScene>

#include <BaseDrawer.h>

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = delete;
    explicit QtDrawer(QGraphicsScene *scene);
    QtDrawer(const QtDrawer &drawer);

    void drawLine(const Vertex &vertex1, const Vertex &vertex2) override;
//    void drawTriangle(const Vertex &vertex1, const Vertex &vertex2, const Vertex &vertex3) override;
    void clearScene() override;

    QGraphicsScene *getScene(); // TODO shared_ptr

private:
    QGraphicsScene *_scene; // ???
};
