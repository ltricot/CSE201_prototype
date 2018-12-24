#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QScrollArea>
#include <QWebEngineView>
#include <QTextEdit>

#include <window_int_modif.h>
#include <display_id.h>


class window_main
{
    public:
        window_main(info_user &info);
        QWidget *main;
        QWidget *modif_inter;
        QWidget *info_id;

};
#endif // WINDOW_MAIN_H
