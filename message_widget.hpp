#ifndef MESSAGE_WIDGET_H
#define MESSAGE_WIDGET_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

class MessageWidget :public QWidget {
	Q_OBJECT

public:
	// Default construct a MessageWidget displaying no text
	MessageWidget(QWidget * parent = nullptr);
public slots:
	// a public slot accepting an informational message to display, clearing any error formatting
	void info(QString message);
	// a public slot accepting an error message to display as selected text highlighted with a red background.
	void error(QString message);
	
	
	//Provides read-only display of interpreter messages.
};


#endif // !MESSAGE_WIDGET_H