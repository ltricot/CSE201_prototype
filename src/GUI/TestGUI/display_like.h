#ifndef DISPLAY_LIKE_H
#define DISPLAY_LIKE_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QWebEngineView>
#include <QScrollArea>
#include <QApplication>

#include <client.h>

class past_likes : public QObject {

    Q_OBJECT

public:
    past_likes(Author a, Client c);

    // function that takes the reference of an arXiv article and generates a window showing the article web page
    QWidget* display_article(std::string ref);

    QWidget *article;

public slots:
    void open_window();

private:
    Author *author;
    Client *client;
    QVBoxLayout *lay;
    QWidget *likes;
};

#endif // DISPLAY_LIKE_H
