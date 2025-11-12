#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KPEdit.h"

class KPEdit : public QMainWindow
{
    Q_OBJECT

public:
    KPEdit(QWidget *parent = nullptr);
    ~KPEdit();

private:
    Ui::KPEditClass ui;
};

