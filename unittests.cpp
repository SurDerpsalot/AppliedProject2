#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "interpreter.hpp"
#include "expression.hpp"
#include "test_config.hpp"

TEST_CASE("Test Interpreter parser with an expected input", "[interpreter]") {

	std::string program = "(begin (define r 11) (* pi (* r true)))";

	std::istringstream iss(program);

	Interpreter interp;



	REQUIRE(interp.parse(iss));
}

TEST_CASE("Test Interpreter an example", "[interpreter]") {

	std::string program = "(define x (/  (* (+ 1 2) 3) 4))";

	std::istringstream iss(program);

	Interpreter interp;

	REQUIRE(interp.parse(iss));
}

TEST_CASE("Test the Expression overload", "[Expression]")
{
	std::string pass;
	pass = "false";
	Expression d;
	Expression e(4.0);
	Expression f(3);
	Expression g(true);
	Expression h(pass);
	REQUIRE((d == e) == false);
	REQUIRE((e == f) == true);
	REQUIRE((e == g) == false);
	REQUIRE((e == h) == false);
	REQUIRE((g == h) == false);
}

TEST_CASE("Test Interpreter parser with a truncated input", "[interpreter]") {

	{
		std::string program = "(false";
		std::istringstream iss(program);

		Interpreter interp;
		
		REQUIRE(!interp.parse(iss));
	}

	{
		std::string program = "(begin (define r 10) (* pi (* r r((";
		std::istringstream iss(program);

		Interpreter interp;
		REQUIRE(!interp.parse(iss));
	}
}

TEST_CASE("Test Interpreter parser with extra inputs", "[interpreter]") {

	std::string program = "(begin (define r 10) (* pi (* r r))))) )";
	std::istringstream iss(program);

	Interpreter interp;

	REQUIRE(!interp.parse(iss));
}

TEST_CASE("Test Interpreter parser with a non-keyword", "[interpreter]") {

	std::string program = "yarrr";
	std::istringstream iss(program);

	Interpreter interp;

	REQUIRE(!interp.parse(iss));
}

TEST_CASE("Test Interpreter parser with empty expression (no space)", "[interpreter]") {

	std::string program = "()";
	std::istringstream iss(program);

	Interpreter interp;

	REQUIRE(!interp.parse(iss));
}

TEST_CASE("Test Interpreter parsers with bad number string", "[interpreter]") {

	std::string program = "(1afge)";
	std::istringstream iss(program);

	Interpreter interp;

	REQUIRE(!interp.parse(iss));
}

TEST_CASE("Test Expression Builds", "[expression]")
{
	std::string input = "asdf";
	Expression empty;
	Expression boolean(true);
	Expression string(input);
	Expression value(3.2);

	REQUIRE((empty.Node.type == None) == true);
	REQUIRE((boolean.Node.type == Bool)==true);
	REQUIRE((boolean.Node.bool_value == true) == true);
	REQUIRE((string.Node.type == Symbol) == true);
	REQUIRE((string.Node.string_value == "asdf") == true);
	REQUIRE((value.Node.type == Value) == true);
	REQUIRE((value.Node.double_value == 3.2) == true);
}

TEST_CASE("Test Expression overloaded ==", "[expression]")
{
	std::string input = "true";
	Expression Compare1(true);
	Expression Compare2(false);
	Expression Compare3(12);
	Expression Compare4(input);

	REQUIRE((Compare1 == Compare1));
	REQUIRE((Compare1 == Compare2));
	REQUIRE(!(Compare1 == Compare3));
	REQUIRE(!(Compare1 == Compare4));
	REQUIRE((Compare2 == Compare2));
	REQUIRE(!(Compare2 == Compare3));
	REQUIRE(!(Compare2 == Compare4));
	REQUIRE((Compare3 == Compare3));
	REQUIRE(!(Compare3 == Compare4));
	REQUIRE((Compare4 == Compare4));
	
}

TEST_CASE("Test define", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(define a 42)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 42);
}

TEST_CASE("Test if", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(if (< 1 2) 13 14)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 13);
}

TEST_CASE("Test begin", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(begin (define a 42) (if (< 1 2) 13 14))";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 13);
}

TEST_CASE("Test +", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(+ 1 14)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 15);
}

TEST_CASE("Test negate number", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(begin (define a 1) (- a) )";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == -1);
}

TEST_CASE("Test negate 2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(- 2)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == -2);
}

TEST_CASE("Test negate negative number", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(- -2)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 2);
}

TEST_CASE("Test subtraction", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(- 3 2)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 1);
}

TEST_CASE("Test and", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(begin (define a True) (define b True) (and a b))";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test and2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(and True True)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test and3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(and True False)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test or", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(or True False)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test or2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(or True True)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test or3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(or True False False)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test mult", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(* 1 3)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 3);
}

TEST_CASE("Test mult2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(* -2 -2)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 4);
}

TEST_CASE("Test mult3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(* -13 14)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == -182);
}

TEST_CASE("Test div", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(/ 3 1)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 3);
}

TEST_CASE("Test div2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(/ -2 -2)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == 1);
}

TEST_CASE("Test div3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(/ -28 4)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.double_value == -7);
}

TEST_CASE("Test equal", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(= 1 3)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test equal2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(= -133 133)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test equal3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(= 298 298)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test Greater than or Equal", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(>= 1 3)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test Greater than or Equal2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(>= -13 398)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test Greater than or Equal3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(>= 439 15)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test Greater than", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(> 1243 345)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test Greater than2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(> -1238 2)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test Greater than3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(> 1 3)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test Less than or Equal", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(<= 3 1)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test Less than or Equal2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(<= -13 398)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test Less than or Equal3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(<= -439 -15)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test Less than", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(< 1243 345)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test Less than2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(< -1238 2)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test Less than3", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(< 0 3)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}

TEST_CASE("Test Inverter", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(not True)";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == false);
}

TEST_CASE("Test Inverter2", "[environment]")
{
	Interpreter Interp;
	Expression output;
	std::string in = "(not (and True False))";
	std::istringstream input(in);
	Interp.parse(input);
	output = Interp.eval();
	REQUIRE(output.Node.bool_value == true);
}
