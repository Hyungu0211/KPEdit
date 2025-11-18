#pragma once
#include <QtWidgets/QMainWindow>
#include <QAction>
#include "TextWidgetUI.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    // --- 파일 메뉴 ---
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();

    // --- 편집 메뉴 ---
    void onUndo();
    void onRedo();
    void onFind();

    // --- 설정 메뉴 ---
    void onSettings(); // 다이얼로그를 띄울 함수

private:
    void createActions();
    void createMenus();

    TextWidgetUI* m_textWidget;

    // 액션 목록
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* exitAction;

    QAction* undoAction;
    QAction* redoAction;
    QAction* findAction;

    QAction* settingsAction;
};