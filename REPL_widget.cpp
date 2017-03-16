// Default construct a REPLWidget
REPLWidget(QWidget * parent = nullptr);

// A signal that sends the current edited text as a QString when the return key is pressed.
void lineEntered(QString);

//should have a history mechanism w/ up and down arrows going through previous inputs.