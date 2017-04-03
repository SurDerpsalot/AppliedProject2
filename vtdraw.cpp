#include <QApplication>
#include <main_window.hpp>
#include <iostream>


int main(int argc, char*argv[])
{
	QApplication app(argc, argv);
	if (argc == 1)
	{
		MainWindow window;
		window.show();
		return app.exec();
	}
	if (argc == 2)
	{
		std::string filename = argv[1];
		MainWindow window(filename);
		window.show();
		return app.exec();
	}
		return EXIT_FAILURE;
}