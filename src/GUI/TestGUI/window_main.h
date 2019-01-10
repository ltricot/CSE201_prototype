#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QScrollArea>
#include <QTextEdit>

#include <window_int_modif.h>
#include <display_id.h>
#include <display_like.h>


class window_main
{
    public:
        window_main(info_user &info);
        QWidget *main;
        QWidget *modif_inter;
        QWidget *info_id;
        QWidget * likes;

};
#endif // WINDOW_MAIN_H
