#include <QApplication>
#include <main_window.hpp>
#include <QGraphicsScene>
#include <QGraphicsView>


int main(int argc, char*argv[])
{
	QApplication app(argc, argv);

	MainWindow window;

	window.show();

	return app.exec();
}