#include "TextWidgetUI.h"
#include <QFont>

TextWidgetUI::TextWidgetUI(QWidget* parent)
    : QPlainTextEdit(parent)
{
    // 1. 폰트 설정 (코딩용 폰트)
    QFont font;
    font.setFamily("Consolas");
    font.setFixedPitch(true);
    font.setPointSize(11);
    setFont(font);

    // 2. 줄 바꿈 안 함 (소스 코드 편집기 특성)
    setLineWrapMode(QPlainTextEdit::NoWrap);
}

void TextWidgetUI::keyPressEvent(QKeyEvent* event)
{
    // 1. 부모 클래스(QPlainTextEdit)의 기본 입력 기능 수행
    QPlainTextEdit::keyPressEvent(event);

    // 2. TODO: 여기에 '괄호 짝 맞추기' 로직이나 
    //    Controller에게 입력을 전달하는 코드를 추가할 예정
}