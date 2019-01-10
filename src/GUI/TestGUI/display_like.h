#ifndef DISPLAY_LIKE_H
#define DISPLAY_LIKE_H
#include <QVBoxLayout>
#include <QPushButton>
#include <QWebEngineView>

class past_likes
{
public:
    past_likes();

    QWidget* display_article(std::string ref);

    QWidget *likes;
    QWidget *article;
};

#endif // DISPLAY_LIKE_H
