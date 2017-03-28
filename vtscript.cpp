#include <iostream>
#include "interpreter.hpp"
#include <fstream>

using std::cout;
using std::cin;

int main(int argc, char*argv[])
{
	int Output;
	std::string wrong = "Error";
	Expression Error(wrong);
	if (argc == 1) 
	{
		Interpreter Interp;
		std::string input;
		Expression output;
		while (true)
		{
			cout << "vtscript> ";
			getline(cin, input);
			std::istringstream TokenStream(input);
			Interp.parse(TokenStream);
			try {
				output = Interp.eval();
				if (output.Node.type == Bool)
					if (output.Node.bool_value)
						cout << "(True)" << std::endl;
					else
						cout << "(False)" << std::endl;
				else if (output.Node.type == Value)
					cout << "(" << output.Node.double_value << ")" << std::endl;
				else if (output.Node.type == Point)
					cout << "(" << std::get<0>(output.Node.Start) << "," << std::get<1>(output.Node.Start) << ")" << std::endl;
				else if (output.Node.type == Line)
				{
					cout << "((" << std::get<0>(output.Node.Start) << "," << std::get<1>(output.Node.Start) << "),(" <<
						std::get<0>(output.Node.EndCenter) << "," << std::get<1>(output.Node.EndCenter) << "))" << std::endl;
				}
				else if (output.Node.type == ARC)
				{
					cout << "((" << std::get<0>(output.Node.EndCenter) << "," << std::get<1>(output.Node.EndCenter) << "),(" <<
						std::get<0>(output.Node.Start) << "," << std::get<1>(output.Node.Start) << ") " << output.Node.double_value << ")" << std::endl;
				}
				else if (output.Node.type == Symbol)
					cout << "(" << output.Node.string_value << ")"<<std::endl;
			}
			catch (InterpreterSemanticError & ERR)
			{
				output = Error;
				cout << ERR.what() << std::endl;
				Interp.resetEnviro();
			}
			Output = EXIT_SUCCESS;
		}
	}
	else if (argc == 3)
	{
		std::string input = argv[2];
		Interpreter Interp;
		Expression output;
		std::istringstream TokenStream(input);
		bool worked = Interp.parse(TokenStream);
		if (!worked)
		{
			cout << "Error: Input failed to parse" << std::endl;
			return EXIT_FAILURE;
		}
		try {
			output = Interp.eval();
		}
		catch (InterpreterSemanticError & ERR)
		{
			cout << ERR.what() << std::endl;
			Output = EXIT_FAILURE;
			return Output;
		}
		if (output.Node.type == Bool)
			cout << "(" << output.Node.bool_value << ")" << std::endl;
		else if (output.Node.type == Value)
			cout << "(" << output.Node.double_value << ")" << std::endl;
		Output = EXIT_SUCCESS;
	}
	else if(argc == 2)
	{
		std::ifstream in(argv[1]);
		if (!in.is_open()) 
		{
			cout << "Error" << std::endl;
			Output = EXIT_FAILURE;
		}
		else
		{
			Interpreter Interp;
			Expression output;
			Interp.parse(in);
			try { 
				output = Interp.eval();
			}
			catch (InterpreterSemanticError & ERR)
			{
				cout << "Error" << std::endl;
				Output = EXIT_FAILURE;
			}
			if (output.Node.type == Bool)
				cout << "(" << output.Node.bool_value << ")" << std::endl;
			else if (output.Node.type == Value)
				cout << "(" << output.Node.double_value << ")" << std::endl;
			Output = EXIT_SUCCESS;
			in.close();
		}
	}
	return Output;
}