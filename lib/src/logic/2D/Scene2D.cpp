#include "Scene2D.hpp"
#include "Shape2D.hpp"
#include "Line.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Image.hpp"

#include <QPainter>

namespace ART {
namespace Logic {

Scene2D::Scene2D() {
  setFillColor("black");
  setAcceptedMouseButtons(Qt::AllButtons);
  setAcceptHoverEvents(true);
}

void Scene2D::paint(QPainter *painter) {
  for (auto & [ key, value ] : _entities) {
    value->draw(painter);
  }
}

void Scene2D::createLine() noexcept {
	userIsDrawing = true;
	drawingLine = true;
	std::string objId = "Line [" + std::to_string(id) + "]";
	std::unique_ptr<Line> line = std::make_unique<Line>(objId);
	_entities.emplace(objId, std::move(line));
	selectedShape = _entities.find(objId)->second.get();
	id++;
}

void Scene2D::createRectangle() noexcept {
	userIsDrawing = true;
	drawingRectangle = true;
	std::string objId = "Rectangle [" + std::to_string(id) + "]";
	std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(objId);
	_entities.emplace(objId, std::move(rect));
	selectedShape = _entities.find(objId)->second.get();
	id++;
}

void Scene2D::createCircle() noexcept {
	userIsDrawing = true;
	drawingCircle = true;
	std::string objId = "Circle [" + std::to_string(id) + "]";
	std::unique_ptr<Circle> circle = std::make_unique<Circle>(objId);
	_entities.emplace(objId, std::move(circle));
	selectedShape = _entities.find(objId)->second.get();
	id++;
}

void Scene2D::createTriangle() noexcept {
	userIsDrawing = true;
	drawingTriangle = true;
	std::string objId = "Triangle [" + std::to_string(id) + "]";
	std::unique_ptr<Triangle> triangle = std::make_unique<Triangle>(objId);
	_entities.emplace(objId, std::move(triangle));
	selectedShape = _entities.find(objId)->second.get();
	id++;
}

void Scene2D::importImg(const QUrl &url) noexcept {
	std::string objId = "Image [" + std::to_string(id) + "]";
	std::unique_ptr<Logic::Image> img = std::make_unique<Logic::Image>(url, objId);
	_entities.emplace(objId, std::move(img));
	id++;
	QQuickPaintedItem::update();
}

bool Scene2D::isCloseEnough(const QLineF& line, const QPointF& point) {
	QLineF perpendicLine(point, QPointF(point.x(), 0.0));
	perpendicLine.setAngle(90.0 + line.angle());
	QPointF result;
	line.intersect(perpendicLine, &result);

	if (abs(point.x() - result.x()) <= 5 && abs(point.y() - result.y()) <= 5) {
		return true;
	}

	return false;
}

void Scene2D::saveScene(const QUrl &url) noexcept {
	QString path = url.path() + ".png";

	if (QSysInfo::kernelType().compare("winnt") == 0) {
		path = path.mid(1);
	}

	auto imgResult = this->grabToImage();
	connect(imgResult.data(), &QQuickItemGrabResult::ready, [=]() {
		imgResult->saveToFile(path);
		//imgResult->image() for a QImage instance of the output
	});
}

void Scene2D::mousePressEvent(QMouseEvent *event) {
	if (userIsDrawing) {
		if (drawingRectangle || drawingLine || drawingCircle || drawingTriangle) {
			selectedShape->x1 = event->x();
			selectedShape->y1 = event->y();
		}
	} else {
		// Backward iteration into the map
		for (auto it = _entities.rbegin(); it != _entities.rend(); ++it) {
			selectedShape = it->second.get();

			// Did the user click on a shape?
			if (selectedShape->imgRect.contains(event->x(), event->y()) || selectedShape->shapeRect.contains(QPointF(event->x(), event->y())) || isCloseEnough(selectedShape->line, QPointF(event->x(), event->y()))) {
				decalx = event->x() - selectedShape->x1;
				decaly = event->y() - selectedShape->y1;
				shapePressed = true;
				break;
			}
		}
	}
}

void Scene2D::mouseMoveEvent(QMouseEvent *event) {
	if (userIsDrawing) {
		this->setCursor(QCursor(Qt::CrossCursor));
		if (drawingRectangle || drawingCircle || drawingTriangle) {
			selectedShape->x2 = event->x() - selectedShape->x1;
			selectedShape->y2 = event->y() - selectedShape->y1;
		} else if (drawingLine) {
			selectedShape->x2 = event->x();
			selectedShape->y2 = event->y();
		}
	} else if (shapePressed) {
		// Move item
		if (event->buttons() == Qt::LeftButton) {
			this->setCursor(QCursor(Qt::ClosedHandCursor));
			selectedShape->x1 = event->x() - decalx;
			selectedShape->y1 = event->y() - decaly;
			if (!selectedShape->line.isNull()) {
				selectedShape->x2 = selectedShape->x1 + event->x() - decalx;
				selectedShape->y2 = selectedShape->y1 + event->y() - decaly;
			}
		// Resize item
		} else if (event->buttons() == Qt::RightButton) {
			this->setCursor(QCursor(Qt::SizeAllCursor));

			// x resize
			if (lastMouseX != event->x()) {
				// bigger
				if (lastMouseX < event->x()) {
					selectedShape->x2 += (event->x() - lastMouseX);
				// smaller
				} else if (selectedShape->x2 >= SizeMinX) {
					selectedShape->x2 -= (lastMouseX - event->x());
				}
			}
			
			// y resize
			if (lastMouseY != event->y()) {
				// bigger
				if (lastMouseX < event->x()) {
					selectedShape->y2 += (event->y() - lastMouseY);
				// smaller
				} else if (selectedShape->y2 >= SizeMinY) {
					selectedShape->y2 -= (lastMouseY - event->y());
				}
			}

			lastMouseX = event->x();
			lastMouseY = event->y();
		}
	}

	QQuickPaintedItem::update();
}

void Scene2D::mouseReleaseEvent(QMouseEvent *event) {
	shapePressed = false;
	this->setCursor(QCursor(Qt::ArrowCursor));

	if (userIsDrawing) {
		userIsDrawing = false;
		drawingRectangle = false;
		drawingLine = false;
		drawingCircle = false;
		drawingTriangle = false;
	}
}

} // namespace Logic
} // namespace ART