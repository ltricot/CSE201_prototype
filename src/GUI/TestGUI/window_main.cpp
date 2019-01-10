#include <window_main.h>

window_main::window_main(info_user &info)
{
    // Take infos
    window_int_modif mod(info);
    modif_inter = mod.modif_inter;
    window_id id;
    info_id = id.id_info;
    past_likes likes_0;
    likes = likes_0.likes;

    // CREATION OF THE MAIN WINDOW
    main = new QWidget; // The window
    main->setWindowTitle("App name"); // Its title
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

    // Like buttons
    QPushButton *like_button = new QPushButton;
    like_button->setIcon(QIcon("/Users/damienbradelle/TestGUI/like.png"));
    QPushButton *dislike_button = new QPushButton;
    dislike_button->setIcon(QIcon("/Users/damienbradelle/TestGUI/dislike.png"));
    QPushButton *indiff_button = new QPushButton;
    indiff_button->setIcon(QIcon("/Users/damienbradelle/TestGUI/indiff.png"));

    // Webpage display
    QWebEngineView *view = new QWebEngineView;
    view->load(QUrl("https://arxiv.org/abs/1812.03184"));

    // Layout of the like page
    l_like->addWidget(view, 0, 0, 1, 0);
    l_like->addWidget(like_button,1,2);
    l_like->addWidget(dislike_button,1,0);
    l_like->addWidget(indiff_button,1,1);

    // For the info page
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

    // For the likeable page
    QLabel *rec_1_lab = new QLabel;
    QGridLayout *l_1 = new QGridLayout;
    QWidget *w_1 = new QWidget;
    rec_1_lab->setWordWrap(true);
    rec_1_lab->setText("[1812.03857] The role of the time delay in the reflection and transmission of ultrashort electromagnetic pulses on a system of parallel current sheets");
    QPushButton *recom_1 = new QPushButton;
    recom_1->setText("Let's see!");
    likes_0.display_article("1812.03857");
    QObject::connect(recom_1, SIGNAL(clicked()), likes_0.article, SLOT(show()));
    QPushButton *like_button_1 = new QPushButton;
    like_button_1->setIcon(QIcon("/Users/damienbradelle/TestGUI/like.png"));
    QPushButton *dislike_button_1 = new QPushButton;
    dislike_button_1->setIcon(QIcon("/Users/damienbradelle/TestGUI/dislike.png"));
    l_1->addWidget(rec_1_lab, 0, 0, 1, 3);
    l_1->addWidget(dislike_button_1, 1, 0);
    l_1->addWidget(recom_1, 1, 1);
    l_1->addWidget(like_button_1, 1, 2);
    w_1->setLayout(l_1);
    w_1->setMaximumSize(700, 100);
    l_recom->addWidget(w_1);

    QLabel *rec_2_lab = new QLabel;
    QGridLayout *l_2 = new QGridLayout;
    QWidget *w_2 = new QWidget;
    rec_2_lab->setText("[1812.03811] Semiconductor laser mode locking stabilization with optical feedback from a silicon PIC");
    QPushButton *recom_2 = new QPushButton;
    likes_0.display_article("1812.03811");
    QObject::connect(recom_2, SIGNAL(clicked()), likes_0.article, SLOT(show()));
    recom_2->setText("Let's see!");
    QPushButton *like_button_2 = new QPushButton;
    like_button_2->setIcon(QIcon("/Users/damienbradelle/TestGUI/like.png"));
    QPushButton *dislike_button_2 = new QPushButton;
    dislike_button_2->setIcon(QIcon("/Users/damienbradelle/TestGUI/dislike.png"));
    l_2->addWidget(rec_2_lab, 0, 0, 1, 3);
    l_2->addWidget(dislike_button_2, 1, 0);
    l_2->addWidget(recom_2, 1, 1);
    l_2->addWidget(like_button_2, 1, 2);
    w_2->setLayout(l_2);
    w_2->setMaximumSize(700, 100);
    l_recom->addWidget(w_2);

    QLabel *rec_3_lab = new QLabel;
    QGridLayout *l_3 = new QGridLayout;
    QWidget *w_3 = new QWidget;
    rec_3_lab->setText("[1812.03808] Ultrasensitive hybrid optical skin");
    likes_0.display_article("1812.03808");
    QPushButton *recom_3 = new QPushButton;
    recom_3->setText("Let's see!");
    QObject::connect(recom_3, SIGNAL(clicked()), likes_0.article, SLOT(show()));
    QPushButton *like_button_3 = new QPushButton;
    like_button_3->setIcon(QIcon("/Users/damienbradelle/TestGUI/like.png"));
    QPushButton *dislike_button_3 = new QPushButton;
    dislike_button_3->setIcon(QIcon("/Users/damienbradelle/TestGUI/dislike.png"));
    l_3->addWidget(rec_3_lab, 0, 0, 1, 3);
    l_3->addWidget(dislike_button_3, 1, 0);
    l_3->addWidget(recom_3, 1, 1);
    l_3->addWidget(like_button_3, 1, 2);
    w_3->setLayout(l_3);
    w_3->setMaximumSize(700, 100);
    l_recom->addWidget(w_3);

    // Parameters
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
    QPixmap logo_pix =  QPixmap("/Users/damienbradelle/TestGUI/logo_2.png");
    logo_pix.scaledToWidth(100);
    logo_pix.scaledToHeight(100);
    logo_label->setPixmap(logo_pix);
    l_param->addWidget(logo_label, 3, 0, 5, 0, Qt::AlignCenter);
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
    QObject::connect(my_inte, SIGNAL(clicked()), modif_inter, SLOT(show()));
    QObject::connect(my_id, SIGNAL(clicked()), info_id, SLOT(show()));
    QObject::connect(my_like, SIGNAL(clicked()), likes, SLOT(show()));
}
