#include <window_int_modif.h>

window_int_modif::window_int_modif(info_user &info)
{
    // CREATE A WINDOW FOR INTERESTS MODIFICATION
    modif_inter = new QWidget;
    QWidget *modif_phy = new QWidget;
    QVBoxLayout *l_mod_phy = new QVBoxLayout;
    QWidget *modif_math = new QWidget;
    QVBoxLayout *l_mod_math = new QVBoxLayout;
    QWidget *modif_cs = new QWidget;
    QVBoxLayout *l_mod_cs = new QVBoxLayout;
    QWidget *modif_bio = new QWidget;
    QVBoxLayout *l_mod_bio = new QVBoxLayout;
    QWidget *modif_fin = new QWidget;
    QVBoxLayout *l_mod_fin = new QVBoxLayout;
    QWidget *modif_stat = new QWidget;
    QVBoxLayout *l_mod_stat = new QVBoxLayout;
    QWidget *modif_eess = new QWidget;
    QVBoxLayout *l_mod_eess = new QVBoxLayout;
    QWidget *modif_econ = new QWidget;
    QVBoxLayout *l_mod_econ = new QVBoxLayout;
    modif_inter->setMinimumSize(400, 400);
    QVBoxLayout *modif_lay = new QVBoxLayout;
    QTabWidget *tabs_int = new QTabWidget;

    // Add the widgets
    for (int i = 0; i < 51; i ++)
    {
        l_mod_phy->addWidget(info.checkboxes[i]);
    }
    modif_phy->setLayout(l_mod_phy);
    tabs_int->addTab(modif_phy, "Physics");
    for (int i = 51; i < 83; i ++)
    {
        l_mod_math->addWidget(info.checkboxes[i]);
    }
    modif_math->setLayout(l_mod_math);
    tabs_int->addTab(modif_math, "Mathematics");
    for (int i = 83; i < 123; i ++)
    {
        l_mod_cs->addWidget(info.checkboxes[i]);
    }
    modif_cs->setLayout(l_mod_cs);
    tabs_int->addTab(modif_cs, "Computer science");
    for (int i = 123; i < 133; i ++)
    {
        l_mod_bio->addWidget(info.checkboxes[i]);
    }
    modif_bio->setLayout(l_mod_bio);
    tabs_int->addTab(modif_bio, "Quantitative biology");
    for (int i = 133; i < 142; i ++)
    {
        l_mod_fin->addWidget(info.checkboxes[i]);
    }
    modif_fin->setLayout(l_mod_fin);
    tabs_int->addTab(modif_fin, "Quantitative finance");
    for (int i = 142; i < 148; i ++)
    {
        l_mod_stat->addWidget(info.checkboxes[i]);
    }
    modif_stat->setLayout(l_mod_stat);
    tabs_int->addTab(modif_stat, "Statistics");
    for (int i = 148; i < 151; i ++)
    {
        l_mod_eess->addWidget(info.checkboxes[i]);
    }
    modif_eess->setLayout(l_mod_eess);
    tabs_int->addTab(modif_eess, "Electrical engineering and systems science");
    for (int i = 151; i < 154; i ++)
    {
        l_mod_econ->addWidget(info.checkboxes[i]);
    }
    modif_econ->setLayout(l_mod_econ);
    tabs_int->addTab(modif_econ, "Economics");

    // Add the tabs
    modif_lay->addWidget(tabs_int);

    // Create the button
    QPushButton *save_int_button = new QPushButton;
    save_int_button->setText("Save");
    modif_lay->addWidget(save_int_button);

    // Layout and button connection
    modif_inter->setLayout(modif_lay);
    QObject::connect(save_int_button, SIGNAL(clicked()), modif_inter, SLOT(hide()));
}
