#include <window_main.h>

window_main::window_main(info_user &info)
{

    window_int_modif mod(info);
    modif_inter = mod.modif_inter;

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
    // Interior (buttons, text, webpages...)
    QPushButton *like_button = new QPushButton;
    like_button->setIcon(QIcon("/Users/damienbradelle/TestGUI/like.png"));
    QPushButton *dislike_button = new QPushButton;
    dislike_button->setIcon(QIcon("/Users/damienbradelle/TestGUI/dislike.png"));
    QPushButton *indiff_button = new QPushButton;
    QWebEngineView *view = new QWebEngineView;
    view->load(QUrl("https://arxiv.org/abs/1812.03184"));
    l_like->addWidget(view, 0, 0, 1, 0);
    l_like->addWidget(like_button,1,2);
    l_like->addWidget(dislike_button,1,0);
    l_like->addWidget(indiff_button,1,1);
    indiff_button->setIcon(QIcon("/Users/damienbradelle/TestGUI/indiff.png"));
    QLabel *text_info = new QLabel;
    text_info->setText("Lol, coming soon (before 2024)");
    l_info->addWidget(text_info);
    QTextEdit *rec_1_lab = new QTextEdit;
    rec_1_lab->setText("[1812.03857] The role of the time delay in the reflection and transmission of ultrashort electromagnetic pulses on a system of parallel current sheets");
    QPushButton *recom_1 = new QPushButton;
    recom_1->setText("Let's see!");
    QTextEdit *rec_2_lab = new QTextEdit;
    rec_2_lab->setText("[1812.03811] Semiconductor laser mode locking stabilization with optical feedback from a silicon PIC");
    QPushButton *recom_2 = new QPushButton;
    recom_2->setText("Let's see!");
    QTextEdit *rec_3_lab = new QTextEdit;
    rec_3_lab->setText("[1812.03808] Ultrasensitive hybrid optical skin");
    QPushButton *recom_3 = new QPushButton;
    recom_3->setText("Let's see!");
    l_recom->addWidget(rec_1_lab);
    l_recom->addWidget(recom_1);
    l_recom->addWidget(rec_2_lab);
    l_recom->addWidget(recom_2);
    l_recom->addWidget(rec_3_lab);
    l_recom->addWidget(recom_3);
    QPushButton *my_id = new QPushButton;
    my_id->setText("My ID");
    QPushButton *my_like = new QPushButton;
    my_like->setText("My likes");
    QPushButton *my_inte = new QPushButton;
    my_inte->setText("My interests");
    l_param->addWidget(my_id, 0, 0, Qt::AlignCenter);
    l_param->addWidget(my_like, 1, 0, Qt::AlignCenter);
    l_param->addWidget(my_inte, 2, 0, Qt::AlignCenter);
    QLabel *logo_label = new QLabel;
    QPixmap logo_pix =  QPixmap("/Users/damienbradelle/TestGUI/logo_2.png");
    logo_pix.scaledToWidth(100);
    logo_pix.scaledToHeight(100);
    logo_label->setPixmap(logo_pix);
    l_param->addWidget(logo_label, 3, 0, 5, 0, Qt::AlignCenter);
    page_info_scroll->setLayout(l_info);
    page_like_scroll->setLayout(l_like);
    page_recom_scroll->setLayout(l_recom);
    page_param_scroll->setLayout(l_param);
    tabs->addTab(page_info_scroll, "Information");
    tabs->addTab(page_like_scroll, "Let's like!");
    tabs->addTab(page_recom_scroll, "Likeable");
    tabs->addTab(page_param_scroll, "Parameters");
    l_main->addWidget(tabs);
    main->setLayout(l_main);
    QObject::connect(my_inte, SIGNAL(clicked()), modif_inter, SLOT(show()));

}
