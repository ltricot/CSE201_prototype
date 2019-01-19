#ifndef WINDOW_INT_MODIF_H
#define WINDOW_INT_MODIF_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QTabWidget>
#pragma once

#include <info_user.h>

class window_int_modif {
public:
    QWidget *modif_inter;
    window_int_modif(info_user &info);
};

#endif // WINDOW_INT_MODIF_H
