#ifndef WINDOW_HOME_H
#define WINDOW_HOME_H

#include <QApplication>
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
