#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H


#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QProcess>
#include <QString>
#include <QInputDialog>
#include <QCheckBox>
#include <QLabel>
#include <QTime>
#include <QScrollBar>
#include <QScrollArea>
#include <QTabWidget>
#include <info_user.h>
#include <iostream>
#include <QGridLayout>
#include <QWebEngineView>
#include <QSizePolicy>
#include <QTextEdit>
#include <QDesktopWidget>
#include <window_int_modif.h>


class window_main
{
    public:
        window_main(info_user &info);
        QWidget *main;
        QWidget *modif_inter;

};
#endif // WINDOW_MAIN_H
