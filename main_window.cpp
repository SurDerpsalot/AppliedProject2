#include <main_window.hpp>

// Default construct a MainWindow
MainWindow::MainWindow(QWidget * parent): QWidget(parent){
	auto layout = new QVBoxLayout(this);
	auto message = new MessageWidget;
	auto canvas = new CanvasWidget;
	auto REPL = new REPLWidget;
	auto interpret = new QtInterpreter;
	
	connect(REPL, &REPLWidget::lineEntered, interpret, &QtInterpreter::parseAndEvaluate);
	connect(interpret, &QtInterpreter::info,message, &MessageWidget::info);
	connect(interpret, &QtInterpreter::error, message, &MessageWidget::error);
	connect(interpret, &QtInterpreter::drawGraphic, canvas, &CanvasWidget::addGraphic);
	
	this->setMinimumSize(800, 600);
	layout->addWidget(message);
	layout->addWidget(canvas);
	layout->addWidget(REPL);
	setLayout(layout);
	
}

// Default construct a MainWidow, using filename as the script file to attempt to preload
MainWindow::MainWindow(std::string filename, QWidget * parent){
	auto layout = new QVBoxLayout(this);
	auto message = new MessageWidget;
	auto canvas = new CanvasWidget;
	auto REPL = new REPLWidget;
	auto interpret = new QtInterpreter;

	connect(REPL, &REPLWidget::lineEntered, interpret, &QtInterpreter::parseAndEvaluate);
	connect(interpret, &QtInterpreter::info, message, &MessageWidget::info);
	connect(interpret, &QtInterpreter::error, message, &MessageWidget::error);
	connect(interpret, &QtInterpreter::drawGraphic, canvas, &CanvasWidget::addGraphic);

	this->setMinimumSize(800, 600);
	layout->addWidget(message);
	layout->addWidget(canvas);
	layout->addWidget(REPL);
	setLayout(layout);
	QString input = QString::fromStdString(filename);
	QFile file(input);
	if (!file.open(QIODevice::ReadOnly))
	{
		std::cout << "Error: file could not be opened." << std::endl;
		throw;
	}
	QTextStream in(&file);
	QString Command;
	while (!in.atEnd())
	{
		QString once = in.readAll();
		interpret->parseAndEvaluate(once);
	}
}