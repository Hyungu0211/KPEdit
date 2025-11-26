#pragma once
#include <QtWidgets/QMainWindow>
#include <QAction>
#include "TextWidgetUI.h"
#include "Controller.h"
#include "AutoSaveManager.h"
#include "FindDialog.h"

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
    void onFindRequested(const QString& find);
    void onReplaceRequested(const QString& find, const QString& replace);
    void onReplaceAllRequested(const QString& find, const QString& replace);
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

    int lastFindPos = -1; // 마지막으로 찾은 단어 위치
    QString lastFindText; // 마지막으로 검색한 텍스트

    TextWidgetUI* textWidget;
    Controller* controller;
    AutoSaveManager* autoSaveManager;
    int prevTextLength = 0;
    FindDialog* findDialog;

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