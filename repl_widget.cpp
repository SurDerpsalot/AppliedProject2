#include <repl_widget.hpp>


// Default construct a REPLWidget
REPLWidget::REPLWidget(QWidget * parent) {
	auto RealRepl = new QHBoxLayout(this);
	auto REPL = new QLineEdit(this);
	QLabel * replLabel = new QLabel("vtscript>", this);
	//replLabel->setBuddy(REPL);
	RealRepl->addWidget(replLabel);
	RealRepl->addWidget(REPL);
	setLayout(RealRepl);

}

// A signal that sends the current edited text as a QString when the return key is pressed.


//should have a history mechanism w/ up and down arrows going through previous inputs.
