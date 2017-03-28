#include <canvas_widget.hpp>



// Default construct a CanvasWidget
CanvasWidget::CanvasWidget(QWidget * parent):QWidget(parent) {
	
	QHBoxLayout* layout = new QHBoxLayout(this);
	canvas->setScene(scene);
	canvas->setSceneRect(-300, -200, 600, 400);
	layout->addWidget(canvas);
	setLayout(layout);

}

// A public slot that accepts a signal in the form of a QGraphicsItem pointer containing an 
// object derived from QGraphicsItem to draw
void CanvasWidget::addGraphic(QGraphicsItem * item){
	
	scene->addItem(item);

}

//also read only stuff