#include <windows_precise.h>

windows_precise::windows_precise()
{

    // Create the user profile
    info = info_user();


    // CREATE AND CONFIGURE A WINDOW FOR EACH SUBJECT
    // Create a new window and a layout for each subject with a scroll area
    QWidget *precise_phy = new QWidget;
    QVBoxLayout *l_p_phy = new QVBoxLayout;
    scroll_phy = new QScrollArea;
    scroll_phy->setWidget(precise_phy);
    scroll_phy->setWidgetResizable(true);
    scroll_phy->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget *precise_math = new QWidget;
    QVBoxLayout *l_p_math = new QVBoxLayout;
    scroll_math = new QScrollArea;
    scroll_math->setWidget(precise_math);
    scroll_math->setWidgetResizable(true);
    scroll_math->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget *precise_cs = new QWidget;
    QVBoxLayout *l_p_cs = new QVBoxLayout;
    scroll_cs = new QScrollArea;
    scroll_cs->setWidget(precise_cs);
    scroll_cs->setWidgetResizable(true);
    scroll_cs->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget *precise_bio = new QWidget;
    QVBoxLayout *l_p_bio = new QVBoxLayout;
    scroll_bio = new QScrollArea;
    scroll_bio->setWidget(precise_bio);
    scroll_bio->setWidgetResizable(true);
    scroll_bio->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget *precise_fin = new QWidget;
    QVBoxLayout *l_p_fin = new QVBoxLayout;
    scroll_fin = new QScrollArea;
    scroll_fin->setWidget(precise_fin);
    scroll_fin->setWidgetResizable(true);
    scroll_fin->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget *precise_stat = new QWidget;
    QVBoxLayout *l_p_stat = new QVBoxLayout;
    scroll_stat = new QScrollArea;
    scroll_stat->setWidget(precise_stat);
    scroll_stat->setWidgetResizable(true);
    scroll_stat->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget *precise_eess = new QWidget;
    QVBoxLayout *l_p_eess = new QVBoxLayout;
    scroll_eess = new QScrollArea;
    scroll_eess->setWidget(precise_eess);
    scroll_eess->setWidgetResizable(true);
    scroll_eess->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget *precise_econ = new QWidget;
    QVBoxLayout *l_p_econ = new QVBoxLayout;
    scroll_econ = new QScrollArea;
    scroll_econ->setWidget(precise_econ);
    scroll_econ->setWidgetResizable(true);
    scroll_econ->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    // Create a text for each subject and add it to the layout associated
    QLabel *title_phy = new QLabel();
    title_phy->setText("More precisely in physics:");
    title_phy->setFont(QFont("Courrier", 15, QFont::Bold));
    l_p_phy->addWidget(title_phy);

    QLabel *title_math = new QLabel();
    title_math->setText("More precisely in mathematics:");
    title_math->setFont(QFont("Courrier", 15, QFont::Bold));
    l_p_math->addWidget(title_math);

    QLabel *title_cs = new QLabel();
    title_cs->setText("More precisely in computer science:");
    title_cs->setFont(QFont("Courrier", 15, QFont::Bold));
    l_p_cs->addWidget(title_cs);

    QLabel *title_bio = new QLabel();
    title_bio->setText("More precisely in quantitative biology:");
    title_bio->setFont(QFont("Courrier", 15, QFont::Bold));
    l_p_bio->addWidget(title_bio);

    QLabel *title_fin = new QLabel();
    title_fin->setText("More precisely in quantitative finance:");
    title_fin->setFont(QFont("Courrier", 15, QFont::Bold));
    l_p_fin->addWidget(title_fin);

    QLabel *title_stat = new QLabel();
    title_stat->setText("More precisely in statistics:");
    title_stat->setFont(QFont("Courrier", 15, QFont::Bold));
    l_p_stat->addWidget(title_stat);

    QLabel *title_elec = new QLabel();
    title_elec->setText("More precisely in Electrical Engineering and Systems Science:");
    title_elec->setFont(QFont("Courrier", 15, QFont::Bold));
    l_p_eess->addWidget(title_elec);

    QLabel *title_econ = new QLabel();
    title_econ->setText("More precisely in economics:");
    title_econ->setFont(QFont("Courrier", 15, QFont::Bold));
    l_p_econ->addWidget(title_econ);


    // Give a title to each window and create a new button validate for each of them
    precise_phy->setWindowTitle("About your interests in physics");
    precise_math->setWindowTitle("About your interests in mathematics");
    precise_cs->setWindowTitle("About your interests in computer science");
    precise_bio->setWindowTitle("About your interests in quantitative biology");
    precise_fin->setWindowTitle("About your interests in quantitative finance");
    precise_stat->setWindowTitle("About your interests in statistics");
    precise_eess->setWindowTitle("About your interests in electrical engineering and systems science");
    precise_econ->setWindowTitle("About your interests in economics");

    val_phy = new QPushButton;
    val_phy->setText("Validate");
    val_math = new QPushButton;
    val_math->setText("Validate");
    val_cs = new QPushButton;
    val_cs->setText("Validate");
    val_bio = new QPushButton;
    val_bio->setText("Validate");
    val_fin = new QPushButton;
    val_fin->setText("Validate");
    val_stat = new QPushButton;
    val_stat->setText("Validate");
    val_eess = new QPushButton;
    val_eess->setText("Validate");
    val_econ = new QPushButton;
    val_econ->setText("Validate");

    //Astro
    QLabel *astro = new QLabel();
    astro->setText("Astrophysics");
    astro->setFont(QFont("Courrier", 12, QFont::Bold));
    l_p_phy->addWidget(astro);
    for (int i = 0; i < 6; i++)
    {
        l_p_phy->addWidget(info.checkboxes[i]);
    }

    //Condensed
    QLabel *cond_mat = new QLabel();
    cond_mat->setText("Condensed Matter");
    cond_mat->setFont(QFont("Courrier", 12, QFont::Bold));
    l_p_phy->addWidget(cond_mat);
    for (int i = 6; i < 15; i++)
    {
        l_p_phy->addWidget(info.checkboxes[i]);
    }

    //Non-linear
    QLabel *non_lin = new QLabel();
    non_lin->setText("Nonlinear Sciences");
    non_lin->setFont(QFont("Courrier", 12, QFont::Bold));
    l_p_phy->addWidget(non_lin);
    for (int i = 15; i < 20; i++)
    {
        l_p_phy->addWidget(info.checkboxes[i]);
    }

    //Physics
    QLabel *phys = new QLabel();
    phys->setText("Physics");
    phys->setFont(QFont("Courrier", 12, QFont::Bold));
    l_p_phy->addWidget(phys);
    for (int i = 20; i < 42; i++)
    {
        l_p_phy->addWidget(info.checkboxes[i]);
    }

    //Others
    QLabel *ot = new QLabel();
    ot->setText("Other");
    ot->setFont(QFont("Courrier", 12, QFont::Bold));
    l_p_phy->addWidget(ot);
    for (int i = 42; i < 51; i++)
    {
        l_p_phy->addWidget(info.checkboxes[i]);
    }
    l_p_phy->addWidget(val_phy);

    // maths
    for (int i = 51; i < 83; i++)
    {
        l_p_math->addWidget(info.checkboxes[i]);
    }
    l_p_math->addWidget(val_math);

    // Computer science
    for (int i = 83; i < 123; i++)
    {
        l_p_cs->addWidget(info.checkboxes[i]);
    }
    l_p_cs->addWidget(val_cs);

    // Bio
    for (int i = 123; i < 133; i++)
    {
        l_p_bio->addWidget(info.checkboxes[i]);
    }
    l_p_bio->addWidget(val_bio);

    // Finance
    for (int i = 133; i < 142; i++)
    {
        l_p_fin->addWidget(info.checkboxes[i]);
    }
    l_p_fin->addWidget(val_fin);

    // Statistics
    for (int i = 142; i < 148; i++)
    {
       l_p_stat->addWidget(info.checkboxes[i]);
    }
    l_p_stat->addWidget(val_stat);

    // EESS
    for (int i = 148; i < 151; i++)
    {
       l_p_eess->addWidget(info.checkboxes[i]);
    }
    l_p_eess->addWidget(val_eess);

    // Economics
    for (int i = 151; i < 154; i++)
    {
       l_p_econ->addWidget(info.checkboxes[i]);
    }
    l_p_econ->addWidget(val_econ);

    // set the layout for each window
    precise_phy->setLayout(l_p_phy);
    precise_math->setLayout(l_p_math);
    precise_cs->setLayout(l_p_cs);
    precise_bio->setLayout(l_p_bio);
    precise_fin->setLayout(l_p_fin);
    precise_stat->setLayout(l_p_stat);
    precise_eess->setLayout(l_p_eess);
    precise_econ->setLayout(l_p_econ);
}
