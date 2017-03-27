#include "qt_interpreter.hpp"

QtInterpreter::QtInterpreter(QObject*parent) {
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
		output = interp->eval();
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
		else
		{
			Err = "Error : We shouldn't be in this state.";
			emit error(Err);
		}		
		
	}
}