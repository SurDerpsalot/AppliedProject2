#include <main_window.hpp>
#include <message_widget.hpp>
#include <canvas_widget.hpp>
#include <repl_widget.hpp>

// Default construct a MainWindow
MainWindow::MainWindow(QWidget * parent){
	auto layout = new QVBoxLayout(this);
	auto message = new MessageWidget;
	auto canvas = new CanvasWidget;
	auto REPL = new REPLWidget;
	//message->setObjectName("MessageLine");
	this->setMinimumSize(600, 800);
	canvas->setMinimumHeight(300);
	canvas->setMinimumWidth(400);
	layout->addWidget(message);
	layout->addWidget(canvas);
	layout->addWidget(REPL);
	layout->setAlignment(Qt::AlignCenter);
	setLayout(layout);
}

// Default construct a MainWidow, using filename as the script file to attempt to preload
MainWindow::MainWindow(std::string filename, QWidget * parent){

}