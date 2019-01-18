#include <window_main.h>

void window_main::delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(10);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

window_main::window_main(info_user &info, Author &author, Client &client)
{
    // Take infos
    window_int_modif mod(info);
    modif_inter = mod.modif_inter;
    window_id id(author);
    info_id = id.id_info;

    // CREATION OF THE MAIN WINDOW
    main = new QWidget; // The window
    main->setWindowTitle("Tinder for Researchers"); // Its title
    main->setMinimumSize(800, 800); // Its size
    QVBoxLayout *l_main = new QVBoxLayout;

    // tabs and scrolls
    QTabWidget *tabs = new QTabWidget(main);
    QScrollArea *page_info_scroll = new QScrollArea;
    QGridLayout *l_info = new QGridLayout;
    QScrollArea *page_like_scroll = new QScrollArea;
    QGridLayout *l_like = new QGridLayout;
    QScrollArea *page_recom_scroll = new QScrollArea;
    QVBoxLayout *l_recom = new QVBoxLayout;
    QScrollArea *page_param_scroll = new QScrollArea;
    QGridLayout *l_param = new QGridLayout;

    QIcon dislike_icon = QIcon(":/img/img/dislike.png");
    QIcon like_icon = QIcon(":/img/img/like.png");




    // LIKE PAGE

    // Like buttons
    QPushButton *like_button = new QPushButton;
    like_button->setIcon(like_icon);
    QPushButton *dislike_button = new QPushButton;
    dislike_button->setIcon(dislike_icon);
    // Take an article
    update_widget *like_widget_view = new update_widget(client.getArticles(author), client);
    l_like->addWidget(like_widget_view->widget, 0, 0, 1, 2);
    l_like->addWidget(dislike_button, 1, 0);
    l_like->addWidget(like_button, 1, 1);
    QObject::connect(like_button, SIGNAL(clicked()), like_widget_view, SLOT(update_like()));
    QObject::connect(dislike_button, SIGNAL(clicked()), like_widget_view, SLOT(update_dislike()));








    // INFO PAGE


    QLabel *text_info = new QLabel;
    text_info->setWordWrap(true);
    text_info->setText("Welcome on the Tinder for researchers (God knows that need it!)\n \
\n \
Here is a brief presentation of the application. \n \
To be simple, we will show you some arXiv articles according to the interests you gave us when you sign in. You will be able to react to them : like, dislike, indifferent.\n \
According to what you like or not, we will recommend you articles : they will be selected just for you and should match with your interests. \
And of course we keep track of all the articles you like.\n \
\n \
How to use the app?\n \
You are currently in the “Information” section but you can move to three other sections.\n \
In “Let’s like!”, we will show you arXiv articles fitting  with your interests. Give your opinion about them using three buttons at the bottom. Of course, only you can see if you like or not an article.\n \
In the “Likeable” section, we give you some articles that you should like according to your past like, don’t hesitate to give your opinion about them!\n \
Finally, in the “parameters”, you can see you ID, modify your interests and see the articles you liked.\n \n \
Enjoy!");
    l_info->addWidget(text_info);


    // LIKEABLE PAGE
    label_update * lab1 = new label_update(client, author);
    label_update * lab2 = new label_update(client, author);
    label_update * lab3 = new label_update(client, author);

    QGridLayout *l_1 = new QGridLayout;
    QWidget *w_1 = new QWidget;
    QPushButton *recom_1 = new QPushButton;
    recom_1->setText("Let's see!");

    QGridLayout *l_2 = new QGridLayout;
    QWidget *w_2 = new QWidget;
    QPushButton *recom_2 = new QPushButton;
    recom_2->setText("Let's see!");

    QGridLayout *l_3 = new QGridLayout;
    QWidget *w_3 = new QWidget;
    QPushButton *recom_3 = new QPushButton;
    recom_3->setText("Let's see!");

    QObject::connect(recom_1, SIGNAL(clicked()), lab1, SLOT(see()));
    QObject::connect(recom_2, SIGNAL(clicked()), lab2, SLOT(see()));
    QObject::connect(recom_3, SIGNAL(clicked()), lab3, SLOT(see()));

    QPushButton *like_button_1 = new QPushButton;
    like_button_1->setIcon(like_icon);
    QPushButton *dislike_button_1 = new QPushButton;
    dislike_button_1->setIcon(dislike_icon);

    QPushButton *like_button_2 = new QPushButton;
    like_button_2->setIcon(like_icon);
    QPushButton *dislike_button_2 = new QPushButton;
    dislike_button_2->setIcon(dislike_icon);

    QPushButton *like_button_3 = new QPushButton;
    like_button_3->setIcon(like_icon);
    QPushButton *dislike_button_3 = new QPushButton;
    dislike_button_3->setIcon(dislike_icon);

    QObject::connect(like_button_1, SIGNAL(clicked()), lab1, SLOT(like()));
    QObject::connect(dislike_button_1, SIGNAL(clicked()), lab1, SLOT(dislike()));

    QObject::connect(like_button_2, SIGNAL(clicked()), lab2, SLOT(like()));
    QObject::connect(dislike_button_2, SIGNAL(clicked()), lab1, SLOT(dislike()));

    QObject::connect(like_button_3, SIGNAL(clicked()), lab3, SLOT(like()));
    QObject::connect(dislike_button_3, SIGNAL(clicked()), lab3, SLOT(dislike()));

    l_1->addWidget(lab1->label, 0, 0, 1, 3);
    l_1->addWidget(dislike_button_1, 1, 0);
    l_1->addWidget(recom_1, 1, 1);
    l_1->addWidget(like_button_1, 1, 2);
    w_1->setLayout(l_1);
    w_1->setMaximumSize(700, 100);
    l_recom->addWidget(w_1);

    l_2->addWidget(lab2->label, 0, 0, 1, 3);
    l_2->addWidget(dislike_button_2, 1, 0);
    l_2->addWidget(recom_2, 1, 1);
    l_2->addWidget(like_button_2, 1, 2);
    w_2->setLayout(l_2);
    w_2->setMaximumSize(700, 100);
    l_recom->addWidget(w_2);

    l_3->addWidget(lab3->label, 0, 0, 1, 3);
    l_3->addWidget(dislike_button_3, 1, 0);
    l_3->addWidget(recom_3, 1, 1);
    l_3->addWidget(like_button_3, 1, 2);
    w_3->setLayout(l_3);
    w_3->setMaximumSize(700, 100);
    l_recom->addWidget(w_3);




    // PARAMETERS

    past_likes *pl = new past_likes(author, client);

    // Buttons
    QPushButton *my_id = new QPushButton;
    my_id->setText("My ID");
    QPushButton *my_like = new QPushButton;
    my_like->setText("My likes");
    QPushButton *my_inte = new QPushButton;
    my_inte->setText("My interests");
    l_param->addWidget(my_id, 0, 0, Qt::AlignCenter);
    l_param->addWidget(my_like, 1, 0, Qt::AlignCenter);
    l_param->addWidget(my_inte, 2, 0, Qt::AlignCenter);
    // Logo
    QLabel *logo_label = new QLabel;
    QPixmap logo_pix =  QPixmap(":/img/img/logo_2.png");
    logo_pix = logo_pix.scaled(300, 300);
    logo_label->setPixmap(logo_pix);
    l_param->addWidget(logo_label, 3, 0, 5, 0, Qt::AlignCenter);
    QObject::connect(my_inte, SIGNAL(clicked()), modif_inter, SLOT(show()));
    QObject::connect(my_id, SIGNAL(clicked()), info_id, SLOT(show()));
    QObject::connect(my_like, SIGNAL(clicked()), pl, SLOT(open_window()));



    // Layout
    page_info_scroll->setLayout(l_info);
    page_like_scroll->setLayout(l_like);
    page_recom_scroll->setLayout(l_recom);
    page_param_scroll->setLayout(l_param);

    // Set up the tabs
    tabs->addTab(page_info_scroll, "Information");
    tabs->addTab(page_like_scroll, "Let's like!");
    tabs->addTab(page_recom_scroll, "Likeable");
    tabs->addTab(page_param_scroll, "Parameters");
    l_main->addWidget(tabs);
    main->setLayout(l_main);
}
