#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QLayout>
#include <QLabel>
#include <QWidget>
#include <canvas_widget.hpp>
#include <message_widget.hpp>
#include <canvas_widget.hpp>
#include <repl_widget.hpp>
#include <QVBoxLayout>
#include <qt_interpreter.hpp>

class MainWindow : public QWidget {
	Q_OBJECT

public:
	// Default construct a MainWindow
	MainWindow(QWidget * parent = nullptr);

	// Default construct a MainWidow, using filename as the script file to attempt to preload
	MainWindow(std::string filename, QWidget * parent = nullptr);

};

#endif