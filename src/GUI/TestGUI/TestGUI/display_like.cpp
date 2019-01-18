#include <display_like.h>

past_likes::past_likes(Author a, Client c)
{
    // Create the window
    likes = new QWidget;
    author = new Author(a);
    client = new Client(c);

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(likes);
    scroll->setWidgetResizable(true);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    likes->setMinimumSize(500, 500);

    lay = new QVBoxLayout;
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
    lay_art->addWidget(quit);

    article->setLayout(lay_art);

    return article;
}

void past_likes::open_window()
{
    lay = new QVBoxLayout;
    likes = new QWidget;

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(likes);
    scroll->setWidgetResizable(true);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    likes->setMinimumSize(300, 800);
    scroll->setMinimumSize(300, 800);

    std::vector<std::string> liked_articles = client->getArticles(*author);
    const std::size_t len = liked_articles.size();

    QPushButton *like_button[len];
    QWidget *web[len];

    for (std::size_t i = 0; i < len; i++)
    {
        like_button[i] = new QPushButton;
        web[i] = new QWidget;
    }

    for (std::size_t i = 0; i < len; i++)
    {
        like_button[i]->setText(QString::fromStdString(client->getTitle(liked_articles.at(i)))); // To code getTitle(str id) giving the title of the article having id id

        web[i] = display_article(liked_articles.at(i));

        lay->addWidget(like_button[i]);
        QObject::connect(like_button[i], SIGNAL(clicked()), web[i], SLOT(show()));
    }

    likes->setLayout(lay);
    scroll->show();
}
