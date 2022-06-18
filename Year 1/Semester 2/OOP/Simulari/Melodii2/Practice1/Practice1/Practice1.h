#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Practice1.h"

class Practice1 : public QMainWindow
{
    Q_OBJECT

public:
    Practice1(QWidget *parent = nullptr);
    ~Practice1();

private:
    Ui::Practice1Class ui;
};
