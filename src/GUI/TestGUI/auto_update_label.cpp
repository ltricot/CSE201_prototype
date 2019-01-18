#include <auto_update_label.h>

label_update::label_update(Client c, Author &a)
{
    label = new QLabel;
    client = new Client(c.ip, c.port);
    Author author = Author(a);
    paper = new Paper(client->getRecommendation(author));
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    label->setText(QString::fromStdString(paper->id));
}

void label_update::see()
{
    QWidget *article = new QWidget;
    article->setMinimumSize(700, 700);
    QVBoxLayout *lay_art = new QVBoxLayout;

    QWebEngineView *view = new QWebEngineView;
    QString url = QString::fromStdString("https://arxiv.org/abs/" + paper->id);
    view->load(QUrl(url));
    lay_art->addWidget(view);

    QPushButton *quit = new QPushButton;
    quit->setText("Back");
    QObject::connect(quit, SIGNAL(clicked()), article, SLOT(hide()));
    lay_art->addWidget(quit);

    article->setLayout(lay_art);

    article->show();
}

void label_update::like()
{
    std::vector<std::string> l;
    l.push_back(paper->id);
    client->putArticles(l);
    //paper = new Paper(client->getRecommendation(*author)); // This line crashes
    label->setText(QString::fromStdString(paper->id));
}

void label_update::dislike()
{
    //paper = new Paper(client->getRecommendation(*author)); // This one too
    label->setText(QString::fromStdString(paper->id));
}
