#ifndef WINDOWS_H
#define WINDOWS_H
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

#include <info_user.h>
#pragma once


class windows_precise
{
    public:
        windows_precise();
        QScrollArea *scroll_phy;
        QScrollArea *scroll_math;
        QScrollArea *scroll_cs;
        QScrollArea *scroll_bio;
        QScrollArea *scroll_fin;
        QScrollArea *scroll_stat;
        QScrollArea *scroll_eess;
        QScrollArea *scroll_econ;
        QPushButton *val_phy;
        QPushButton *val_math;
        QPushButton *val_cs;
        QPushButton *val_bio;
        QPushButton *val_fin;
        QPushButton *val_stat;
        QPushButton *val_eess;
        QPushButton *val_econ;
        info_user info;

};



#endif // WINDOWS_H
