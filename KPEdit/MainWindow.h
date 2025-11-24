#pragma once
#include <QtWidgets/QMainWindow>
#include <QAction>
#include "TextWidgetUI.h"
#include "Controller.h"

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

	// title ∞ªΩ≈ «Ô∆€
    void updateWindowTitle();

private:
    void createActions();
    void createMenus();
    bool checkSave(); // ¿˙¿Â »Æ¿Œ «Ô∆€

    TextWidgetUI* textWidget;
    Controller* controller;

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