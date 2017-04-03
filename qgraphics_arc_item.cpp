#include <qgraphics_arc_item.hpp>

QGraphicsArcItem::QGraphicsArcItem(double xd, double yd, double length,QRectF rectan, double span, QGraphicsEllipseItem* parent):QGraphicsEllipseItem(rectan) {
	spanAngle = span *(180 / (atan2(0, -1))) * 16;
	startAngle = asin(yd / length) * 16 * (180/(atan2(0,-1)));
	if (xd < 0) {
		spanAngle = spanAngle*-1;
	}
	if (yd < 0) {
		startAngle = -startAngle;
	}
	rectangle = rectan;
	this->setStartAngle(startAngle);
	this->setSpanAngle(spanAngle);
}

void QGraphicsArcItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->drawArc(rectangle, startAngle, spanAngle);
}