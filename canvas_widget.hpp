#ifndef CANVAS_WIDGET_H
#define CANVAS_WIDGET_H

#include <QWidget>
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
class CanvasWidget :public QWidget {
	Q_OBJECT
public:
	// Default construct a CanvasWidget
	CanvasWidget(QWidget * parent = nullptr);
public slots:
	// A public slot that accepts a signal in the form of a QGraphicsItem pointer containing an 
	// object derived from QGraphicsItem to draw
	void addGraphic(QGraphicsItem * item);

	//also read only stuff
private:
	QGraphicsScene *scene = new QGraphicsScene(this);
	QGraphicsView* canvas = new QGraphicsView(this);
};


#endif // !CANVAS_WIDGET_H