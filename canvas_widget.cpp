#include <canvas_widget.hpp>



// Default construct a CanvasWidget
CanvasWidget::CanvasWidget(QWidget * parent) {
	QGraphicsView canvas(Paint);
}

// A public slot that accepts a signal in the form of a QGraphicsItem pointer containing an 
// object derived from QGraphicsItem to draw
void CanvasWidget::addGraphic(QGraphicsItem * item){
	Paint->addItem(item);
}

//also read only stuff