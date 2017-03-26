#include <message_widget.hpp>

MessageWidget::MessageWidget(QWidget * parent) {
	auto Format = new QHBoxLayout(this);
	auto message = new QLineEdit(this);
	QLabel* messageLabel = new QLabel("Message:", this);
	Format->addWidget(messageLabel);
	Format->addWidget(message);
	setLayout(Format);
}

void MessageWidget::error(QString message)
{

}

void MessageWidget::info(QString message) {

}