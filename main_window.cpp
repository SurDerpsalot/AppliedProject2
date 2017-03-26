#include <main_window.hpp>

// Default construct a MainWindow
MainWindow::MainWindow(QWidget * parent){
	auto window = new QWidget(this);
	auto layout = new QVBoxLayout(window);
	auto message = new MessageWidget;
	auto canvas = new CanvasWidget;
	auto REPL = new REPLWidget;
	auto interpret = new QtInterpreter;
	connect(REPL, &REPLWidget::lineEntered, interpret, &QtInterpreter::parseAndEvaluate);
	connect(interpret, &QtInterpreter::info,message, &MessageWidget::info);
	connect(interpret, &QtInterpreter::error, message, &MessageWidget::error);
	this->setMinimumSize(800, 600);
	canvas->setMinimumHeight(500);
	canvas->setMinimumWidth(800);
	layout->addWidget(message);
	layout->addWidget(canvas);
	layout->addWidget(REPL);
	window->setLayout(layout);
	
}

// Default construct a MainWidow, using filename as the script file to attempt to preload
MainWindow::MainWindow(std::string filename, QWidget * parent){

}