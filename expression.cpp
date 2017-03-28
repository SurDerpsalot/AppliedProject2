#include "expression.hpp"

Expression::Expression()
{
	Node.type = None;
	Node.bool_value = false;
	Node.double_value = 0.0;
	Node.string_value = "";
	Node.Start = std::tuple<double, double> (0, 0);
	Node.EndCenter = std::tuple<double, double>(0, 0);
}

Expression::Expression(bool value) {
	Node.type = Bool;
	Node.bool_value = value;
	Node.double_value = 0.0;
	Node.string_value = "";
	Node.Start = std::tuple<double, double>(0, 0);
	Node.EndCenter = std::tuple<double, double>(0, 0);
}

Expression::Expression(double value) {
	Node.type = Value;
	Node.bool_value = false;
	Node.double_value = value;
	Node.string_value = "";
	Node.Start = std::tuple<double, double>(0, 0);
	Node.EndCenter = std::tuple<double, double>(0, 0);
}

Expression::Expression(int value) {
	Node.type = Value;
	Node.bool_value = false;
	Node.double_value = value;
	Node.string_value = "";
	Node.Start = std::tuple<double, double>(0, 0);
	Node.EndCenter = std::tuple<double, double>(0, 0);
}

Expression::Expression(const std::string & value) {
	Node.type = Symbol;
	Node.bool_value = false;
	Node.double_value = 0.0;
	Node.string_value = value;
	Node.Start = std::tuple<double, double>(0, 0);
	Node.EndCenter = std::tuple<double, double>(0, 0);
}

Expression::Expression(std::tuple<double,double> value) {
	Node.type = Point;
	Node.bool_value = false;
	Node.double_value = 0.0;
	Node.string_value = "";
	Node.Start = value;
	Node.EndCenter = std::tuple<double, double>(0, 0);
}

Expression::Expression(std::tuple<double,double> start, std::tuple<double,double> end) {
	Node.type = Line;
	Node.bool_value = false;
	Node.double_value = 0.0;
	Node.string_value = "";
	Node.Start = start;
	Node.EndCenter = end;
}

Expression::Expression(std::tuple<double,double> center, std::tuple<double,double> start, double angle) {
	Node.type = ARC;
	Node.bool_value = false;
	Node.double_value = angle;
	Node.string_value = "";
	Node.Start = start;
	Node.EndCenter = center;
}

bool Expression::operator==(const Expression & exp) const noexcept 
{
	bool x1, y1, x2, y2, dubval;
	x1 = false;
	y1 = false;
	x2 = false;
	y2 = false;
	dubval = false;
	
	double startx = std::get<0>(Node.Start);
	double starty = std::get<1>(Node.Start);
	double endx = std::get<0>(Node.EndCenter);
	double endy = std::get<1>(Node.EndCenter);

	double estartx = std::get<0>(exp.Node.Start);
	double estarty = std::get<1>(exp.Node.Start);
	double eendx = std::get<0>(exp.Node.EndCenter);
	double eendy = std::get<1>(exp.Node.EndCenter);

	x1 = (std::fabs(startx-estartx) < std::numeric_limits<double>::epsilon());
	x2 = (std::fabs(endx - eendx) < std::numeric_limits<double>::epsilon());
	y1 = (std::fabs(starty-estarty) < std::numeric_limits<double>::epsilon());
	y2 = (std::fabs(endy-eendy) < std::numeric_limits<double>::epsilon());
	dubval = std::fabs(Node.double_value - exp.Node.double_value) < std::numeric_limits<double>::epsilon();


	return ((Node.type == exp.Node.type) && (Node.Branch.size() == exp.Node.Branch.size()) && x1 && x2 && y2 && y1 && dubval);
}