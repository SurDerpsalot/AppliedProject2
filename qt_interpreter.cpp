#include <qt_interpreter.hpp>
#include <qgraphics_arc_item.hpp>

QtInterpreter::QtInterpreter(QObject*parent) {
	interp = new Interpreter;
	interp->resetEnviro();
}

void QtInterpreter::parseAndEvaluate(QString entry) {
	std::string in = entry.toStdString();
	std::istringstream input(in);
	bool worked = interp->parse(input);
	if (!worked)
	{
		QString Err = "Error : Input failed to parse";
		emit error(Err);
	}
	else
	{
		Expression output;
		QString out, Err;
		std::string str;
		size_t i = 0;
		try {
			output = interp->eval();
			draw();
		}
		catch (InterpreterSemanticError &ERR)
		{
			out = ERR.what();
			emit error(out);
		}
			if (output.Node.type == Bool)
			{
				if (output.Node.bool_value)
					out = "(True)";
				else
					out = "(False)";
				emit info(out);
			}
			else if (output.Node.type == Value)
			{
				out = QString("(%1)").arg(output.Node.double_value);
				emit info(out);
			}
			else if (output.Node.type == Point)
			{
				out = QString("(%1,%2)").arg(std::get<0>(output.Node.Start)).arg(std::get<1>(output.Node.Start));
				emit info(out);
			}
			else if (output.Node.type == Line)
			{
				out = QString("((%1,%2),(%3,%4))").arg(std::get<0>(output.Node.Start)).arg(std::get<1>(output.Node.Start))
					.arg(std::get<0>(output.Node.EndCenter)).arg(std::get<1>(output.Node.EndCenter));
				emit info(out);
			}
			else if (output.Node.type == ARC)
			{
				out = QString("((%1,%2),(%3,%4) %5)").arg(std::get<0>(output.Node.Start)).arg(std::get<1>(output.Node.Start))
					.arg(std::get<0>(output.Node.EndCenter)).arg(std::get<1>(output.Node.EndCenter)).arg(output.Node.double_value);
				emit info(out);
			}
			else if (output.Node.type == Symbol)
			{
				str.append("(");
				str.append(output.Node.string_value);
				str.append(")");
				out = QString::fromStdString(str);
				emit info(out);
			}
	}
}

void QtInterpreter::draw()
{
	Expression DrawingItem;
	while (interp->Enviro.DrawMe.size() != 0)
	{
		DrawingItem = interp->Enviro.DrawMe.back();
		interp->Enviro.DrawMe.pop_back();
		if (DrawingItem.Node.type == Point)
		{
			QGraphicsItem * point = new QGraphicsEllipseItem(std::get<0>(DrawingItem.Node.Start) - 1, std::get<1>(DrawingItem.Node.Start) - 1, 1, 1);
			emit drawGraphic(point);
		}
		else if (DrawingItem.Node.type == Line)
		{
			QGraphicsItem * line = new QGraphicsLineItem(std::get<0>(DrawingItem.Node.Start), std::get<1>(DrawingItem.Node.Start),
				std::get<0>(DrawingItem.Node.EndCenter), std::get<1>(DrawingItem.Node.EndCenter));
			emit drawGraphic(line);
		}
		else if (DrawingItem.Node.type == ARC)
		{
			double xd, yd, span,length;
			xd = std::get<0>(DrawingItem.Node.Start) - std::get<0>(DrawingItem.Node.EndCenter);
			yd = std::get<1>(DrawingItem.Node.Start) - std::get<1>(DrawingItem.Node.EndCenter);
			
			length = sqrt((xd*xd)+ (yd*yd));
			
			QRectF rectangle = QRectF(std::get<0>(DrawingItem.Node.EndCenter) - length, std::get<1>(DrawingItem.Node.EndCenter) - length, length * 2, length * 2);
			
			span = DrawingItem.Node.double_value;
			
			QGraphicsArcItem * ark = new QGraphicsArcItem(xd,yd,length,rectangle,span);
			emit drawGraphic(ark);
		}
		else
			throw InterpreterSemanticError("Error : unknown item trying to be added");
	}
	
}