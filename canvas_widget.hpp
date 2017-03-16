// Default construct a CanvasWidget
CanvasWidget(QWidget * parent = nullptr);

// A public slot that accepts a signal in the form of a QGraphicsItem pointer containing an 
// object derived from QGraphicsItem to draw
void addGraphic(QGraphicsItem * item);

//also read only stuff