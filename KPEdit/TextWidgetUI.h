#pragma once
#include <QPlainTextEdit>
#include <QKeyEvent>

class TextWidgetUI : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit TextWidgetUI(QWidget* parent = nullptr);

protected:
    // 키 입력 이벤트를 가로채서 처리하는 함수
    void keyPressEvent(QKeyEvent* event) override;

private:
    // 추후 추가: SyntaxChecker* m_syntaxChecker;
};