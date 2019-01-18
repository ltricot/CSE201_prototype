#ifndef AUTO_UPDATE_H
#define AUTO_UPDATE_H

#include <QWebEngineView>
#include <QVBoxLayout>

#include <client.h>

class update_widget : public QObject {

    Q_OBJECT

public:
    QWidget *widget;
    update_widget(std::vector<std::string> v, Client c);

public slots:
    void update_like();
    void update_dislike();

private:
    std::vector<std::string> vector;
    QWebEngineView *view;
    std::size_t rank = 0;
    Client *client;
    QVBoxLayout *l;
};

#endif // AUTO_UPDATE_H
