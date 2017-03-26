#ifndef REPL_WIDGET_H
#define REPL_WIDGET_H

#include <QWidget>
#include <message_widget.hpp>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QKeyEvent>
class QLineEdit;

class REPLWidget : public QWidget {
	Q_OBJECT
public:
	// Default construct a REPLWidget
	REPLWidget(QWidget * parent = nullptr);

protected:
	void keyPressEvent(QKeyEvent * event);


 signals:
	// A signal that sends the current edited text as a QString when the return key is pressed.
	void lineEntered(QString);

	//should have a history mechanism w/ up and down arrows going through previous inputs.
private:
	QLineEdit* REPL = new QLineEdit(this);
	std::vector<QString> History;
	size_t Index;
};

#endif // !REPL_WIDGET_H




