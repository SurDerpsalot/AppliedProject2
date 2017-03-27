#ifndef Q_GRAPHICS_ARC_ITEM_H
#define Q_GRAPHICS_ARC_ITEM_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <math.h>

class QGraphicsArcItem : public QGraphicsEllipseItem {
	
public:
	QGraphicsArcItem(double xd, double yd, double length,QRectF rectan, double span, QGraphicsEllipseItem*parent = nullptr);
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
private:
	QRectF rectangle;
	double startAngle, spanAngle;
};


#endif // !Q_Graphics_Arc_Item_H
