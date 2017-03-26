#include <message_widget.hpp>

MessageWidget::MessageWidget(QWidget * parent) {
	auto Format = new QHBoxLayout(this);
	mess->setReadOnly(true);
	QLabel* messageLabel = new QLabel("Message:", this);
	Format->addWidget(messageLabel);
	Format->addWidget(mess);
	setLayout(Format);
}

void MessageWidget::error(QString message)
{
	mess->clear();
	mess->setText(message);
	//QPalette *Redhiglight = new QPalette(Qt::red);
	//Redhiglight->setColor(QPalette::Highlight, Qt::red);
	//mess->setPalette(*Redhiglight);
	mess->selectAll();
}

void MessageWidget::info(QString message) {
	mess->clear();
	mess->setText(message);
	
	//QPalette *normalhighlight = new QPalette(Qt::white);
	//normalhighlight->setColor(QPalette::Highlight, Qt::white);
	//mess->setPalette(*normalhighlight);
}