#pragma once
#include <QtWidgets/QMainWindow>
#include <QAction>
#include "TextWidgetUI.h"
#include "Controller.h"
#include "AutoSaveManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();
    void onFind();
    void onSettings();
    void onRequestAutoSave();
    void onTextChanged();


	// title 갱신 헬퍼
    void updateWindowTitle();

private:
    void createActions();
    void createMenus();
    bool fileLoaded; //파일이 불러와져있는지 확인 
    bool checkSave(); // 저장 확인 헬퍼

    TextWidgetUI* textWidget;
    Controller* controller;
    AutoSaveManager* autoSaveManager;
    int prevTextLength = 0;

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