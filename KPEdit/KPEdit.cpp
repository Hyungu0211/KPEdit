#include "KPEdit.h"

KPEdit::KPEdit(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.NewFile, &QAction::triggered, this, &KPEdit::on_SaveButton_clicked);
    connect(ui.Open, &QAction::triggered, this, &KPEdit::on_OpenButton_clicked);
    connect(ui.Close, &QAction::triggered, this, &KPEdit::on_CloseButton_clicked);
    connect(ui.Save, &QAction::triggered, this, &KPEdit::on_SaveButton_clicked);
    connect(ui.Save_as, &QAction::triggered, this, &KPEdit::on_SaveasButton_clicked);
    connect(ui.Exit, &QAction::triggered, this, &KPEdit::on_ExitButton_clicked);
    connect(ui.Undo, &QAction::triggered, this, &KPEdit::on_UndoButton_clicked);
    connect(ui.Redo, &QAction::triggered, this, &KPEdit::on_RedoButton_clicked);
    connect(ui.Copy, &QAction::triggered, this, &KPEdit::on_CopyButton_clicked);
    connect(ui.Cut, &QAction::triggered, this, &KPEdit::on_CutButton_clicked);
    connect(ui.Paste, &QAction::triggered, this, &KPEdit::on_PasteButton_clicked);
    connect(ui.Find_Replace, &QAction::triggered, this, &KPEdit::on_FindReplaceButton_clicked);
    connect(ui.AutoSave, &QAction::triggered, this, &KPEdit::on_AutoSaveButton_clicked);

}

KPEdit::~KPEdit()
{}

void KPEdit::on_NewFileButton_clicked() {
   
}


void KPEdit::on_OpenButton_clicked() {
   
}

void KPEdit::on_CloseButton_clicked() {
    
}

void KPEdit::on_SaveButton_clicked() {
  
}

void KPEdit::on_SaveasButton_clicked() {
    
}

void KPEdit::on_ExitButton_clicked() {
   
}

void KPEdit::on_UndoButton_clicked() {
    
}

void KPEdit::on_RedoButton_clicked() {
    
}

void KPEdit::on_CopyButton_clicked() {
    
}

void KPEdit::on_CutButton_clicked() {
    
}

void KPEdit::on_PasteButton_clicked() {
   
}

void KPEdit::on_FindReplaceButton_clicked() {
 
}

void KPEdit::on_AutoSaveButton_clicked() {

}

