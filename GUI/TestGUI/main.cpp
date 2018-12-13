#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QProcess>
#include <QString>
#include <QInputDialog>
#include <QCheckBox>
#include <QLabel>
#include <QTime>
#include <QScrollBar>
#include <QScrollArea>
#include <QTabWidget>
#include <info_user.h>
#include <iostream>
#include <QGridLayout>
#include <QWebEngineView>
#include <QSizePolicy>


// create a function that wait for a duration of 10 ms in order to slow down while loops
void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(10);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int main(int argc, char *argv[])
{


    // CREATION OF THE APPLICATION
    QApplication app(argc, argv);


    // CREATE THE LOGO
    QIcon logo =  QIcon("/Users/damienbradelle/TestGUI/logo_2.png");



    // CREATION OF THE FIRST WINDOW
    QWidget *home = new QWidget; // The window
    home->setWindowIcon(logo); // The icon of the app
    QVBoxLayout *layout = new QVBoxLayout; // its layout
    // Create the text that is going to be displayed in the window home
    QLabel *title = new QLabel; // the title and its parameters
    title->setText("What are you ineterested in?");
    title->setFont(QFont("Courrier", 15, QFont::Bold));
    // Give a title to the window home
    home->setWindowTitle("Interests");
    // Create some checkboxes associated tot the topics of arXiv
    QCheckBox *physics = new QCheckBox("Physics");
    QCheckBox *maths = new QCheckBox("Mathematics");
    QCheckBox *cs = new QCheckBox("Computer Science");
    QCheckBox *bio = new QCheckBox("Quantitative Biology");
    QCheckBox *fin = new QCheckBox("Quantitative Finance");
    QCheckBox *stat = new QCheckBox("Statistics");
    QCheckBox *elec = new QCheckBox("Electrical Engineering and Systems Science");
    QCheckBox *econ = new QCheckBox("Economics");
    // Create the button to valilade
    QPushButton *validate_button = new QPushButton("Validate");
    // Add all the elements to the layout (button, checkboxes and text)
    layout->addWidget(title);
    layout->addWidget(physics);
    layout->addWidget(maths);
    layout->addWidget(cs);
    layout->addWidget(bio);
    layout->addWidget(fin);
    layout->addWidget(stat);
    layout->addWidget(elec);
    layout->addWidget(econ);
    layout->addWidget(validate_button);
    // Set the layout in the window and its minimal size
    home->setLayout(layout);
    home->setMinimumSize(500, 200);



    // CREATE AND CONFIGURE A WINDOW FOR EACH SUBJECT
    // Create a new window and a layout for each subject with a scroll area
    QWidget *precise_phy = new QWidget;
    precise_phy->setWindowIcon(logo);
    QVBoxLayout *l_p_phy = new QVBoxLayout;
    QScrollArea *scroll_phy = new QScrollArea;
    scroll_phy->setWidget(precise_phy);
    scroll_phy->setWidgetResizable(true);
    scroll_phy->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget *precise_math = new QWidget;
    precise_math->setWindowIcon(logo);
    QVBoxLayout *l_p_math = new QVBoxLayout;
    QScrollArea *scroll_math = new QScrollArea;
    scroll_math->setWidget(precise_math);
    scroll_math->setWidgetResizable(true);
    scroll_math->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget *precise_cs = new QWidget;
    precise_cs->setWindowIcon(logo);
    QVBoxLayout *l_p_cs = new QVBoxLayout;
    QScrollArea *scroll_cs = new QScrollArea;
    scroll_cs->setWidget(precise_cs);
    scroll_cs->setWidgetResizable(true);
    scroll_cs->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget *precise_bio = new QWidget;
    precise_bio->setWindowIcon(logo);
    QVBoxLayout *l_p_bio = new QVBoxLayout;
    QScrollArea *scroll_bio = new QScrollArea;
    scroll_bio->setWidget(precise_bio);
    scroll_bio->setWidgetResizable(true);
    scroll_bio->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget *precise_fin = new QWidget;
    precise_fin->setWindowIcon(logo);
    QVBoxLayout *l_p_fin = new QVBoxLayout;
    QScrollArea *scroll_fin = new QScrollArea;
    scroll_fin->setWidget(precise_fin);
    scroll_fin->setWidgetResizable(true);
    scroll_fin->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget *precise_stat = new QWidget;
    precise_stat->setWindowIcon(logo);
    QVBoxLayout *l_p_stat = new QVBoxLayout;
    QScrollArea *scroll_stat = new QScrollArea;
    scroll_stat->setWidget(precise_stat);
    scroll_stat->setWidgetResizable(true);
    scroll_stat->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget *precise_eess = new QWidget;
    precise_eess->setWindowIcon(logo);
    QVBoxLayout *l_p_eess = new QVBoxLayout;
    QScrollArea *scroll_eess = new QScrollArea;
    scroll_eess->setWidget(precise_eess);
    scroll_eess->setWidgetResizable(true);
    scroll_eess->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget *precise_econ = new QWidget;
    precise_econ->setWindowIcon(logo);
    QVBoxLayout *l_p_econ = new QVBoxLayout;
    QScrollArea *scroll_econ = new QScrollArea;
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
    QPushButton *val_phy = new QPushButton;
    val_phy->setText("Validate");
    QPushButton *val_math = new QPushButton;
    val_math->setText("Validate");
    QPushButton *val_cs = new QPushButton;
    val_cs->setText("Validate");
    QPushButton *val_bio = new QPushButton;
    val_bio->setText("Validate");
    QPushButton *val_fin = new QPushButton;
    val_fin->setText("Validate");
    QPushButton *val_stat = new QPushButton;
    val_stat->setText("Validate");
    QPushButton *val_eess = new QPushButton;
    val_eess->setText("Validate");
    QPushButton *val_econ = new QPushButton;
    val_econ->setText("Validate");




    // CREATION OF THE MAIN WINDOW
    QWidget *main = new QWidget; // The window
    main->setWindowIcon(logo);
    main->setWindowTitle("App name"); // Its title
    main->setMinimumSize(500, 500); // Its size
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
    QPushButton *quit_button = new QPushButton; // A push button to leave the app
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
    quit_button->setText("Quit");
    QLabel *text_info = new QLabel;
    text_info->setText("Lol, coming soon (before 2024)");
    l_info->addWidget(text_info);
    l_info->addWidget(quit_button);
    QPushButton *recom_1 = new QPushButton;
    recom_1->setText("[1812.03857] The role of the time delay in the reflection and transmission of ultrashort electromagnetic pulses on a system of parallel current sheets");
    QPushButton *recom_2 = new QPushButton;
    recom_2->setText("[1812.03811] Semiconductor laser mode locking stabilization with optical feedback from a silicon PIC");
    QPushButton *recom_3 = new QPushButton;
    recom_3->setText("[1812.03808] Ultrasensitive hybrid optical skin");
    l_recom->addWidget(recom_1);
    l_recom->addWidget(recom_2);
    l_recom->addWidget(recom_3);
    QPushButton *my_id = new QPushButton;
    my_id->setText("My ID");
    QPushButton *my_like = new QPushButton;
    my_like->setText("My likes");
    QPushButton *my_inte = new QPushButton;
    my_inte->setText("My interests");
    QPushButton *my_delete = new QPushButton;
    my_delete->setText("Delete my account");
    l_param->addWidget(my_id, 0, 0);
    l_param->addWidget(my_like, 0, 1);
    l_param->addWidget(my_inte, 1, 0);
    l_param->addWidget(my_delete, 1, 1);
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
    QObject::connect(quit_button, SIGNAL(clicked()), qApp, SLOT(quit()));



    // BEGINNIN OF THE APPLICATION
    int ok = QMessageBox::question(home, "Hello", "Welcome to our app, let's start", QMessageBox::Ok); // Display a message box
    if (ok == QMessageBox::Ok) // Check that the button has been clicked and manage the different cases
    {
        int answer = QMessageBox::question(home, "Log in", "Have you an account?", QMessageBox::Yes | QMessageBox::No); // Open a message box that ask if the user want to log in or sign in
        if (answer == QMessageBox::Yes) // First case : it is a pre-existent user
        {
            // Ask for the ID and store it in "id"
            bool ok = false;
            QString id = QInputDialog::getText(home, "Log in", "Please enter your ID", QLineEdit::Normal, QString(), &ok);

            // if the button has been clicked and that the ID is not empty (we may add if the ID is in id_list ?)
            if (ok && !id.isEmpty())
            {
                // take the list of int associated to this ID from the data base and update info_user with
                info_user info;
                int a[154]; // will be replaced by the list from server
                info.update_from_server(a);
                // display the app
                home->close();
                main->show();
            }
            // If the ID is empty
            else
            {
                // Display an error message in a critical box
                QMessageBox::critical(home, "Error", "ID error");
            }
        }
        else // Second case : it is a new user
        {
            QMessageBox::information(home, "Sign in", "We are going to ask you a few questions about your interests, please answer carefully"); // Display an information box

            // Create an array to store user info
            info_user info;

            // Home window appears
            home->show();

            //Astro
            {
            QLabel *astro = new QLabel();
            astro->setText("Astrophysics");
            astro->setFont(QFont("Courrier", 12, QFont::Bold));
            l_p_phy->addWidget(astro);
            l_p_phy->addWidget(info.checkboxes[0]);
            l_p_phy->addWidget(info.checkboxes[1]);
            l_p_phy->addWidget(info.checkboxes[2]);
            l_p_phy->addWidget(info.checkboxes[3]);
            l_p_phy->addWidget(info.checkboxes[4]);
            l_p_phy->addWidget(info.checkboxes[5]);
            }
            //Condensed
            {
            QLabel *cond_mat = new QLabel();
            cond_mat->setText("Condensed Matter");
            cond_mat->setFont(QFont("Courrier", 12, QFont::Bold));
            l_p_phy->addWidget(cond_mat);
            l_p_phy->addWidget(info.checkboxes[6]);
            l_p_phy->addWidget(info.checkboxes[7]);
            l_p_phy->addWidget(info.checkboxes[8]);
            l_p_phy->addWidget(info.checkboxes[9]);
            l_p_phy->addWidget(info.checkboxes[10]);
            l_p_phy->addWidget(info.checkboxes[11]);
            l_p_phy->addWidget(info.checkboxes[12]);
            l_p_phy->addWidget(info.checkboxes[13]);
            l_p_phy->addWidget(info.checkboxes[14]);
            }
            //Non-linear
            {
            QLabel *non_lin = new QLabel();
            non_lin->setText("Nonlinear Sciences");
            non_lin->setFont(QFont("Courrier", 12, QFont::Bold));
            l_p_phy->addWidget(non_lin);
            l_p_phy->addWidget(info.checkboxes[15]);
            l_p_phy->addWidget(info.checkboxes[16]);
            l_p_phy->addWidget(info.checkboxes[17]);
            l_p_phy->addWidget(info.checkboxes[18]);
            l_p_phy->addWidget(info.checkboxes[19]);
            }
            //Physics
            {
            QLabel *phys = new QLabel();
            phys->setText("Physics");
            phys->setFont(QFont("Courrier", 12, QFont::Bold));
            l_p_phy->addWidget(phys);
            l_p_phy->addWidget(info.checkboxes[20]);
            l_p_phy->addWidget(info.checkboxes[21]);
            l_p_phy->addWidget(info.checkboxes[22]);
            l_p_phy->addWidget(info.checkboxes[23]);
            l_p_phy->addWidget(info.checkboxes[24]);
            l_p_phy->addWidget(info.checkboxes[25]);
            l_p_phy->addWidget(info.checkboxes[26]);
            l_p_phy->addWidget(info.checkboxes[27]);
            l_p_phy->addWidget(info.checkboxes[28]);
            l_p_phy->addWidget(info.checkboxes[29]);
            l_p_phy->addWidget(info.checkboxes[30]);
            l_p_phy->addWidget(info.checkboxes[31]);
            l_p_phy->addWidget(info.checkboxes[32]);
            l_p_phy->addWidget(info.checkboxes[33]);
            l_p_phy->addWidget(info.checkboxes[34]);
            l_p_phy->addWidget(info.checkboxes[35]);
            l_p_phy->addWidget(info.checkboxes[36]);
            l_p_phy->addWidget(info.checkboxes[37]);
            l_p_phy->addWidget(info.checkboxes[38]);
            l_p_phy->addWidget(info.checkboxes[39]);
            l_p_phy->addWidget(info.checkboxes[40]);
            l_p_phy->addWidget(info.checkboxes[41]);
            }
            //Others
            {
            QLabel *ot = new QLabel();
            ot->setText("Other");
            ot->setFont(QFont("Courrier", 12, QFont::Bold));
            l_p_phy->addWidget(ot);
            l_p_phy->addWidget(info.checkboxes[42]);
            l_p_phy->addWidget(info.checkboxes[43]);
            l_p_phy->addWidget(info.checkboxes[44]);
            l_p_phy->addWidget(info.checkboxes[45]);
            l_p_phy->addWidget(info.checkboxes[46]);
            l_p_phy->addWidget(info.checkboxes[47]);
            l_p_phy->addWidget(info.checkboxes[48]);
            l_p_phy->addWidget(info.checkboxes[49]);
            l_p_phy->addWidget(info.checkboxes[50]);
            l_p_phy->addWidget(val_phy);
            }
            // maths
            {
            l_p_math->addWidget(info.checkboxes[51]);
            l_p_math->addWidget(info.checkboxes[52]);
            l_p_math->addWidget(info.checkboxes[53]);
            l_p_math->addWidget(info.checkboxes[54]);
            l_p_math->addWidget(info.checkboxes[55]);
            l_p_math->addWidget(info.checkboxes[56]);
            l_p_math->addWidget(info.checkboxes[57]);
            l_p_math->addWidget(info.checkboxes[58]);
            l_p_math->addWidget(info.checkboxes[59]);
            l_p_math->addWidget(info.checkboxes[60]);
            l_p_math->addWidget(info.checkboxes[61]);
            l_p_math->addWidget(info.checkboxes[62]);
            l_p_math->addWidget(info.checkboxes[63]);
            l_p_math->addWidget(info.checkboxes[64]);
            l_p_math->addWidget(info.checkboxes[65]);
            l_p_math->addWidget(info.checkboxes[66]);
            l_p_math->addWidget(info.checkboxes[67]);
            l_p_math->addWidget(info.checkboxes[68]);
            l_p_math->addWidget(info.checkboxes[69]);
            l_p_math->addWidget(info.checkboxes[70]);
            l_p_math->addWidget(info.checkboxes[71]);
            l_p_math->addWidget(info.checkboxes[72]);
            l_p_math->addWidget(info.checkboxes[73]);
            l_p_math->addWidget(info.checkboxes[74]);
            l_p_math->addWidget(info.checkboxes[75]);
            l_p_math->addWidget(info.checkboxes[76]);
            l_p_math->addWidget(info.checkboxes[77]);
            l_p_math->addWidget(info.checkboxes[78]);
            l_p_math->addWidget(info.checkboxes[79]);
            l_p_math->addWidget(info.checkboxes[80]);
            l_p_math->addWidget(info.checkboxes[81]);
            l_p_math->addWidget(info.checkboxes[82]);
            l_p_math->addWidget(val_math);
            }
            // Computer science
            {
            l_p_cs->addWidget(info.checkboxes[83]);
            l_p_cs->addWidget(info.checkboxes[84]);
            l_p_cs->addWidget(info.checkboxes[85]);
            l_p_cs->addWidget(info.checkboxes[86]);
            l_p_cs->addWidget(info.checkboxes[87]);
            l_p_cs->addWidget(info.checkboxes[88]);
            l_p_cs->addWidget(info.checkboxes[89]);
            l_p_cs->addWidget(info.checkboxes[90]);
            l_p_cs->addWidget(info.checkboxes[91]);
            l_p_cs->addWidget(info.checkboxes[92]);
            l_p_cs->addWidget(info.checkboxes[93]);
            l_p_cs->addWidget(info.checkboxes[94]);
            l_p_cs->addWidget(info.checkboxes[95]);
            l_p_cs->addWidget(info.checkboxes[96]);
            l_p_cs->addWidget(info.checkboxes[97]);
            l_p_cs->addWidget(info.checkboxes[98]);
            l_p_cs->addWidget(info.checkboxes[99]);
            l_p_cs->addWidget(info.checkboxes[100]);
            l_p_cs->addWidget(info.checkboxes[101]);
            l_p_cs->addWidget(info.checkboxes[102]);
            l_p_cs->addWidget(info.checkboxes[103]);
            l_p_cs->addWidget(info.checkboxes[104]);
            l_p_cs->addWidget(info.checkboxes[105]);
            l_p_cs->addWidget(info.checkboxes[106]);
            l_p_cs->addWidget(info.checkboxes[107]);
            l_p_cs->addWidget(info.checkboxes[108]);
            l_p_cs->addWidget(info.checkboxes[109]);
            l_p_cs->addWidget(info.checkboxes[110]);
            l_p_cs->addWidget(info.checkboxes[111]);
            l_p_cs->addWidget(info.checkboxes[112]);
            l_p_cs->addWidget(info.checkboxes[113]);
            l_p_cs->addWidget(info.checkboxes[114]);
            l_p_cs->addWidget(info.checkboxes[115]);
            l_p_cs->addWidget(info.checkboxes[116]);
            l_p_cs->addWidget(info.checkboxes[117]);
            l_p_cs->addWidget(info.checkboxes[118]);
            l_p_cs->addWidget(info.checkboxes[119]);
            l_p_cs->addWidget(info.checkboxes[120]);
            l_p_cs->addWidget(info.checkboxes[121]);
            l_p_cs->addWidget(info.checkboxes[122]);
            l_p_cs->addWidget(val_cs);
            }
            // Bio
            {
            l_p_bio->addWidget(info.checkboxes[123]);
            l_p_bio->addWidget(info.checkboxes[124]);
            l_p_bio->addWidget(info.checkboxes[125]);
            l_p_bio->addWidget(info.checkboxes[126]);
            l_p_bio->addWidget(info.checkboxes[127]);
            l_p_bio->addWidget(info.checkboxes[128]);
            l_p_bio->addWidget(info.checkboxes[129]);
            l_p_bio->addWidget(info.checkboxes[130]);
            l_p_bio->addWidget(info.checkboxes[131]);
            l_p_bio->addWidget(info.checkboxes[132]);
            l_p_bio->addWidget(val_bio);
            }
            // Finance
            {
            l_p_fin->addWidget(info.checkboxes[133]);
            l_p_fin->addWidget(info.checkboxes[134]);
            l_p_fin->addWidget(info.checkboxes[135]);
            l_p_fin->addWidget(info.checkboxes[136]);
            l_p_fin->addWidget(info.checkboxes[137]);
            l_p_fin->addWidget(info.checkboxes[138]);
            l_p_fin->addWidget(info.checkboxes[139]);
            l_p_fin->addWidget(info.checkboxes[140]);
            l_p_fin->addWidget(info.checkboxes[141]);
            l_p_fin->addWidget(val_fin);
            }
            // Statistics
            {
            l_p_stat->addWidget(info.checkboxes[142]);
            l_p_stat->addWidget(info.checkboxes[143]);
            l_p_stat->addWidget(info.checkboxes[144]);
            l_p_stat->addWidget(info.checkboxes[145]);
            l_p_stat->addWidget(info.checkboxes[146]);
            l_p_stat->addWidget(info.checkboxes[147]);
            l_p_stat->addWidget(val_stat);
            }
            // EESS
            {
            l_p_eess->addWidget(info.checkboxes[148]);
            l_p_eess->addWidget(info.checkboxes[149]);
            l_p_eess->addWidget(info.checkboxes[150]);
            l_p_eess->addWidget(val_eess);
            }
            // Economics
            {
            l_p_econ->addWidget(info.checkboxes[151]);
            l_p_econ->addWidget(info.checkboxes[152]);
            l_p_econ->addWidget(info.checkboxes[153]);
            l_p_econ->addWidget(val_econ);
            }
            // set the layout for each window
            precise_phy->setLayout(l_p_phy);
            precise_math->setLayout(l_p_math);
            precise_cs->setLayout(l_p_cs);
            precise_bio->setLayout(l_p_bio);
            precise_fin->setLayout(l_p_fin);
            precise_stat->setLayout(l_p_stat);
            precise_eess->setLayout(l_p_eess);
            precise_econ->setLayout(l_p_econ);

            // check if the user has finished its choice
            QObject::connect(validate_button, SIGNAL(clicked()), home, SLOT(hide()));

            // Check every 10ms if the user has validated its choice and display the next windows on each subject
            bool a = true;
            while (a)
            {
                // wait 10ms to avoid saturation
                delay();
                // if the user has done his choice
                if (home->isHidden())
                {
                    a = false; // stop the while loop
                    // create a boolean for each checkbox of the main topics
                    bool t_phy = physics->isChecked();
                    bool t_math = maths->isChecked();
                    bool t_cs = cs->isChecked();
                    bool t_bio = bio->isChecked();
                    bool t_fin = fin->isChecked();
                    bool t_stat = stat->isChecked();
                    bool t_elec = elec->isChecked();
                    bool t_econ = econ->isChecked();
                    // if the user selected at least one of them
                    if (t_phy or t_math or t_cs or t_bio or t_fin or t_stat or t_elec or t_econ)
                    {
                        // display windows for each subject in order to make rpecise chocies
                        if (t_phy)
                        {
                            scroll_phy->show();
                            while (scroll_phy->isHidden() == false)
                            {
                                delay();
                                QObject::connect(val_phy, SIGNAL(clicked()), scroll_phy, SLOT(hide()));
                                if (scroll_phy->isHidden())
                                {
                                    t_phy = false;
                                }
                            }
                        }
                        if (t_math and not t_phy)
                        {
                            scroll_math->show();
                            while (scroll_math->isHidden() == false)
                            {
                                delay();
                                QObject::connect(val_math, SIGNAL(clicked()), scroll_math, SLOT(hide()));
                                if (scroll_math->isHidden())
                                {
                                    t_math = false;
                                }
                            }
                        }
                        if (t_cs and not t_phy and not t_math)
                        {
                            scroll_cs->show();
                            while (scroll_cs->isHidden() == false)
                            {
                                delay();
                                QObject::connect(val_cs, SIGNAL(clicked()), scroll_cs, SLOT(hide()));
                                if (scroll_cs->isHidden())
                                {
                                    t_cs = false;
                                }
                            }
                        }
                        if (t_bio and not t_phy and not t_math and not t_cs)
                        {
                            scroll_bio->show();
                            while (scroll_bio->isHidden() == false)
                            {
                                delay();
                                QObject::connect(val_bio, SIGNAL(clicked()), scroll_bio, SLOT(hide()));
                                if (scroll_bio->isHidden())
                                {
                                    t_bio = false;
                                }
                            }
                        }
                        if (t_fin and not t_phy and not t_math and not t_cs and not t_bio)
                        {
                            scroll_fin->show();
                            while (scroll_fin->isHidden() == false)
                            {
                                delay();
                                QObject::connect(val_fin, SIGNAL(clicked()), scroll_fin, SLOT(hide()));
                                if (scroll_fin->isHidden())
                                {
                                    t_fin = false;
                                }
                            }
                        }
                        if (t_stat and not t_phy and not t_math and not t_cs and not t_bio and not t_fin)
                        {
                            scroll_stat->show();
                            while (scroll_stat->isHidden() == false)
                            {
                                delay();
                                QObject::connect(val_stat, SIGNAL(clicked()), scroll_stat, SLOT(hide()));
                                if (scroll_stat->isHidden())
                                {
                                    t_stat = false;
                                }
                            }
                        }
                        if (t_elec and not t_phy and not t_math and not t_cs and not t_bio and not t_fin and not t_stat)
                        {
                            scroll_eess->show();
                            while (scroll_eess->isHidden() == false)
                            {
                                delay();
                                QObject::connect(val_eess, SIGNAL(clicked()), scroll_eess, SLOT(hide()));
                                if (scroll_eess->isHidden())
                                {
                                    t_elec = false;
                                }
                            }
                        }
                        if (t_econ and not t_phy and not t_math and not t_cs and not t_bio and not t_fin and not t_stat and not t_elec)
                        {
                            scroll_econ->show();
                            while (scroll_econ->isHidden() == false)
                            {
                                delay();
                                QObject::connect(val_econ, SIGNAL(clicked()), scroll_econ, SLOT(hide()));
                                if (scroll_econ->isHidden())
                                {
                                    t_econ = false;
                                }
                            }
                        }
                    }
                    // display an error if none has been selected
                    else
                    {
                        int u = QMessageBox::critical(home, "Choice error", "You have to select at least an interest", QMessageBox::Ok);
                        if (u == QMessageBox::Ok)
                        {
                            home->show();
                            a = true;
                        }
                    }
                 info.update(); // update the user info
                 // Give it to the server
                }
            }

            // Create the window to give a new ID to the user
            QWidget *ID = new QWidget;
            QVBoxLayout *ID_layout = new QVBoxLayout;
            QLabel *text_id = new QLabel;
            text_id->setText("Here is your user ID. Please note it carefully, you will use it to connect next time.");
            text_id->setFont(QFont("Courrier", 15));
            ID_layout->addWidget(text_id);
            QLabel *id_itself = new QLabel;
            id_itself->setText("000000000"); // will be replaced by an ID given by the server
            id_itself->setFont(QFont("Courrier", 25, QFont::Bold));
            ID_layout->addWidget(id_itself);
            QPushButton *val_id = new QPushButton;
            val_id->setText("I have noted my ID and I continue");
            ID_layout->addWidget(val_id);
            ID->setLayout(ID_layout);
            ID->show();
            QObject::connect(val_id, SIGNAL(clicked()), ID, SLOT(hide()));

            bool b = true;
            while (b)
            {
                delay();
                if (ID->isHidden())
                {
                    b = false;
                    ID->close();
                    home->close();
                    main->show();
                }
            }
            }
        }
    return app.exec();
}
