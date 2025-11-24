#include "TextWidgetUI.h"
#include <QTextBlock>
#include <stack>
#include <QTimer>

using namespace std;

TextWidgetUI::TextWidgetUI(QWidget* parent)
    : QPlainTextEdit(parent), controller(nullptr)
{
    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(12);
    setFont(font);
    setLineWrapMode(QPlainTextEdit::NoWrap);
}

void TextWidgetUI::setController(Controller* c) {
    controller = c;
}

void TextWidgetUI::keyPressEvent(QKeyEvent* event)
{
    // 1. Qt 기본 동작 수행 (입력, 삭제, Undo 등 다 알아서 함)
    QPlainTextEdit::keyPressEvent(event);

    //// 2. 괄호 짝 맞추기 알고리즘 발동 조건 체크
    //QString text = event->text();
    //if (!text.isEmpty()) {
    //    char c = text.at(0).toLatin1();
    //    if (c == '}' || c == ')' || c == ']') {
    //        matchParentheses();
    //    }
    //}
}
