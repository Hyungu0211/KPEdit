#pragma once
#include <QPlainTextEdit>

class Controller;

class TextWidgetUI : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit TextWidgetUI(QWidget* parent = nullptr);
    void setController(Controller* c);


protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
	// void matchParentheses(); // ¡Ú ÇÙ½É ¾Ë°í¸®Áò (°ýÈ£ Â¦ ¸ÂÃß±â)
    Controller* controller;

    QTextEdit* editor;

};