#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QScrollArea>
#include <QTextEdit>

#include <window_int_modif.h>
#include <display_id.h>
#include <display_like.h>
#include <counter.h>
#include <auto_update.h>
#include <auto_update_label.h>
#pragma once


class window_main
{
    public:
        window_main(info_user &info, Author &author, Client &client);
        void delay();
        QWidget *main;
        QWidget *modif_inter;
        QWidget *info_id;
        QWidget *likes;

};
#endif // WINDOW_MAIN_H
