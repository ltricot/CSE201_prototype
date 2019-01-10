#ifndef DISPLAY_LIKE_H
#define DISPLAY_LIKE_H
#include <QVBoxLayout>
#include <QPushButton>
#include <QWebEngineView>

class past_likes
{
public:
    past_likes();

    // function that takes the reference of an arXiv article and generates a window showing the article web page
    QWidget* display_article(std::string ref);

    QWidget *likes;
    QWidget *article;
};

#endif // DISPLAY_LIKE_H
