#include "expression.hpp"

Expression::Expression()
{
	Node.type = None;
	Node.bool_value = false;
	Node.double_value = 0.0;
	Node.string_value = "";
}

Expression::Expression(bool value) {
	Node.type = Bool;
	Node.bool_value = value;
	Node.double_value = 0.0;
	Node.string_value = "";

}

Expression::Expression(double value) {
	Node.type = Value;
	Node.bool_value = false;
	Node.double_value = value;
	Node.string_value = "";
}

Expression::Expression(int value) {
	Node.type = Value;
	Node.bool_value = false;
	Node.double_value = value;
	Node.string_value = "";
}

Expression::Expression(const std::string & value) {
	Node.type = Symbol;
	Node.bool_value = false;
	Node.double_value = 0.0;
	Node.string_value = value;
}

Expression::Expression(std::tuple<double,double> value) {

}

Expression::Expression(std::tuple<double,double> start, std::tuple<double,double> end) {

}

Expression::Expression(std::tuple<double,double> center, std::tuple<double,double> start, double angle) {

}



bool Expression::operator==(const Expression & exp) const noexcept 
{
	return (Node.type == exp.Node.type) && (Node.Branch.size() == exp.Node.Branch.size());
}