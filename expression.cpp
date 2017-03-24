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
	return (Node.type == exp.Node.type) && (Node.Branch.size() == exp.Node.Branch.size());
}