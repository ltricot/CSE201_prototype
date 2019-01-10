#include <display_like.h>

past_likes::past_likes()
{
    // Create the window
    likes = new QWidget;
    likes->setMinimumSize(500, 500);
    QVBoxLayout *lay = new QVBoxLayout;

    // Likes
    QPushButton *like_1 = new QPushButton;
    like_1->setText("[1812.03857] The role of the time delay in the reflection and transmission of ultrashort electromagnetic pulses on a system of parallel current sheets");
    lay->addWidget(like_1);
    QWidget *wind = display_article("1812.03857");
    QObject::connect(like_1, SIGNAL(clicked()), wind, SLOT(show()));

    // Button to leave
    QPushButton *close = new QPushButton;
    close->setText("Quit");
    lay->addWidget(close);

    likes->setLayout(lay);
    QObject::connect(close, SIGNAL(clicked()), likes, SLOT(hide()));
}

QWidget* past_likes::display_article(std::string ref)
{
    article = new QWidget;
    article->setMinimumSize(700, 700);
    QVBoxLayout *lay_art = new QVBoxLayout;

    QWebEngineView *view = new QWebEngineView;
    QString url = QString::fromStdString("https://arxiv.org/abs/" + ref);
    view->load(QUrl(url));
    lay_art->addWidget(view);

    QPushButton *quit = new QPushButton;
    quit->setText("Back");
    QObject::connect(quit, SIGNAL(clicked()), article, SLOT(hide()));
    QObject::connect(quit, SIGNAL(clicked()), likes, SLOT(show()));
    lay_art->addWidget(quit);

    article->setLayout(lay_art);

    return article;
}
