#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KPEdit.h"

class KPEdit : public QMainWindow
{
    Q_OBJECT

public:
    KPEdit(QWidget *parent = nullptr);
    ~KPEdit();

private slots:
    void on_NewFileButton_clicked();
    void on_OpenButton_clicked();
    void on_CloseButton_clicked();
    void on_SaveButton_clicked();
    void on_SaveasButton_clicked();
    void on_ExitButton_clicked();
    void on_UndoButton_clicked();
    void on_RedoButton_clicked();
    void on_CopyButton_clicked();
    void on_CutButton_clicked();
    void on_PasteButton_clicked();
    void on_FindReplaceButton_clicked();
    void on_AutoSaveButton_clicked();

private:
    Ui::KPEditClass ui;
};

