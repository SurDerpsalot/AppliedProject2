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
		QString Err = "Error: failed to parse";
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
				out == "(True)";
			else
				out == "(False)";
			emit info(out);
		}
		else if (output.Node.type == Value)
		{
			str.append("(");
			str.append(std::to_string(output.Node.double_value));
			str.append(")");
			out == QString::fromStdString(str);
			emit info(out);
		}
		else if (output.Node.type == Point)
		{
			str.append("(");
			str.append(std::to_string(std::get<0>(output.Node.Start)));
			str.append(",");
			str.append(std::to_string(std::get<1>(output.Node.Start)));
			str.append(")");
			out.fromStdString(str);
			emit info(out);
		}
		else if (output.Node.type == Line)
		{
			str.append("((");
			str.append(std::to_string(std::get<0>(output.Node.Start)));
			str.append(",");
			str.append(std::to_string(std::get<1>(output.Node.Start)));
			str.append("),(");
			str.append(std::to_string(std::get<0>(output.Node.EndCenter)));
			str.append(",");
			str.append(std::to_string(std::get<1>(output.Node.EndCenter)));
			str.append("))");
			out.fromStdString(str);
			emit info(out);
		}
		else if (output.Node.type == ARC)
		{
			str.append("((");
			str.append(std::to_string(std::get<0>(output.Node.Start)));
			str.append(",");
			str.append(std::to_string(std::get<1>(output.Node.Start)));
			str.append("),(");
			str.append(std::to_string(std::get<0>(output.Node.EndCenter)));
			str.append(",");
			str.append(std::to_string(std::get<1>(output.Node.EndCenter)));
			str.append(") ");
			str.append(std::to_string(output.Node.double_value));
			out.fromStdString(str);
			emit info(out);
		}
		else if (output.Node.type == Symbol)
		{
			str.append("(");
			str.append(output.Node.string_value);
			str.append(")");
			out.fromStdString(str);
			emit info(out);
		}
		else
		{
			Err = "Error: We shouldn't be in this state.";
			emit error(Err);
		}		
	}
}