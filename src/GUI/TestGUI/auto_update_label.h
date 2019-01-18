#ifndef AUTO_UPDATE_LABEL_H
#define AUTO_UPDATE_LABEL_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QPushButton>

#include <client.h>


class label_update : public QObject {

    Q_OBJECT

public:
    QLabel *label;

    label_update(Client c, Author &a);

public slots:

    void like();

    void dislike();

    void see();

private:

    Client *client;
    Author *author;
    Paper *paper;
};

#endif // AUTO_UPDATE_LABEL_H
