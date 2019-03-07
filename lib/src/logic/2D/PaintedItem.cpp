#include "PaintedItem.hpp"
#include "Scene2D.hpp"

#include <iostream>

namespace ART {
namespace Logic {

void PaintedItem::paint(QPainter *painter) {
  if (_scene2D != nullptr) {
    _scene2D->paint(painter);
  }
}

void PaintedItem::setScene2D(Scene2D *scene2D) {
  _scene2D = scene2D;
}

void PaintedItem::mousePressEvent(QMouseEvent *event) { 
  _scene2D->mousePressEvent(event);
}
void PaintedItem::mouseMoveEvent(QMouseEvent *event) { 
  _scene2D->mouseMoveEvent(event);
}
void PaintedItem::mouseReleaseEvent(QMouseEvent *event) { 
  _scene2D->mouseReleaseEvent(event);
}

} // namespace Logic
} // namespace ART