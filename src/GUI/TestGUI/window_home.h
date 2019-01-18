#ifndef WINDOW_HOME_H
#define WINDOW_HOME_H

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDesktopWidget>
#include <QCheckBox>
#pragma once


class window_home
{
    public:
        window_home();
        QWidget *home;
        QPushButton *validate_button;
        QCheckBox *physics;
        QCheckBox *math;
        QCheckBox *cs;
        QCheckBox *bio;
        QCheckBox *fin;
        QCheckBox *stat;
        QCheckBox *eess;
        QCheckBox *econ;

};
#endif // WINDOW_HOME_H
