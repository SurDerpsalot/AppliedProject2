#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
enum AtomType { None, Bool, Symbol, Value, Point, Line, Arc };

class Expression{
public:

	struct Variant {
		AtomType type;
		bool bool_value;
		double double_value;
		std::tuple<double, double> Start;
		std::tuple<double, double> EndCenter;
		std::string string_value;
		std::vector<Expression* > Branch;
	};
	Variant Node;
	// Default construct an Expression of type None
	Expression();

	// Construct an Expression with a single Boolean atom with value
	Expression(bool value);

	// Construct an Expression with a single Number atom with value
	Expression(double value);
	Expression(int value);

	// Construct an Expression with a single Symbol atom with value
	Expression(const std::string & value);

	// Construct an Expression with a single Point atom with value
	Expression(std::tuple<double,double> value);

	// Construct an Expression with a single Line atom with starting point 'start'
	// and ending point 'end'
	Expression(std::tuple<double,double> start, std::tuple<double,double> end);

	// Construct an Expression with a single Arc atom with center point 'center',
	// starting point 'start' and spanning angle 'angle' in radians
	Expression(std::tuple<double,double> center, std::tuple<double,double> start, double angle);

	// Equality operator for two Expressions, two expressions are equal if they have the same 
	// type, atom value, and number of arguments
	bool operator==(const Expression & exp) const noexcept;
	//bool operator&&(const Expression & exp) const noexcept;
private:

};
#endif