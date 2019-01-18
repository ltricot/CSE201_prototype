#include <auto_update.h>

void update_widget::update_like()
{
    view->load(QUrl(QString::fromStdString("https://arxiv.org/abs/" + vector[rank])));
    std::vector<std::string> l;
    l.push_back(vector[rank - 1]);
    client->putArticles(l);
    rank ++;
}


void update_widget::update_dislike()
{
    view->load(QUrl(QString::fromStdString("https://arxiv.org/abs/" + vector[rank])));
    rank ++;
}

update_widget::update_widget(std::vector<std::string> v, Client c)
{
    widget = new QWidget;
    vector = v;
    client = new Client(c);
    l = new QVBoxLayout;
    view = new QWebEngineView;
    l->addWidget(view);
    widget->setLayout(l);
    update_dislike();
}
