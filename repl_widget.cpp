#include <repl_widget.hpp>

// Default construct a REPLWidget
REPLWidget::REPLWidget(QWidget * parent) {
	auto RealRepl = new QHBoxLayout(this);
	QLabel * replLabel = new QLabel("vtscript>", this);
	RealRepl->addWidget(replLabel);
	RealRepl->addWidget(REPL);
	setLayout(RealRepl);
}


void REPLWidget::keyPressEvent(QKeyEvent * event) {
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
	{
		QString hold = REPL->text();
		History.push_back(hold);
		Index = History.size();
		REPL->clear();
		emit lineEntered(hold);
	}
	else if (event->key() == Qt::Key_Up) {
		if (Index != 0)
		{
			Index = Index - 1;
			REPL->clear();
			QString insert = History.at(Index);
			REPL->setText(insert);
		}
		
	}
	else if (event->key() == Qt::Key_Down) {
		Index = Index + 1;
		if (Index >= History.size()) {
			Index = History.size();
			REPL->clear();
		}
		else{
			REPL->clear();
			QString insert = History.at(Index);
			REPL->setText(insert);
		}
	}
}

//should have a history mechanism w/ up and down arrows going through previous inputs.
