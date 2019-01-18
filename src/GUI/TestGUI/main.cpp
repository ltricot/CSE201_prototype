#include <QMessageBox>
#include <QInputDialog>
#include <QTime>

#include <windows_precise.h>
#include <window_main.h>
#include <window_home.h>
#include <new_id.h>
#include <client.h>




// create a function that wait for a duration of 10 ms in order to slow down while loops
void delay_1()
{
    QTime dieTime= QTime::currentTime().addMSecs(10);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void delay_sec()
{
    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int main(int argc, char *argv[])
{
    // CREATION OF THE APPLICATION
    QApplication app(argc, argv);

    // User profile and create some windows
    info_user info;
    windows_precise windows_precise;
    window_home window_home;
    info = windows_precise.info;

    // Server
    std::string ip; // to give
    int port = 0; // to give
    Client client = Client(ip, port);

    // CREATE THE LOGO
    QPixmap logo =  QPixmap(":/img/img/logo_2.png");
    app.setWindowIcon(logo);


    // CREATION OF THE FIRST WINDOW
    QWidget *home = window_home.home;


    // Graphic effect
    QWidget *charging = new QWidget;
    QPalette palette;
    logo = logo.scaled(700, 700);
    palette.setBrush(QPalette::Background, logo);
    charging->setPalette(palette);
    charging->setMinimumSize(700, 700);
    charging->move(QApplication::desktop()->screen()->rect().center() - charging->rect().center());


    // BEGINNIN OF THE APPLICATION
    int ok = QMessageBox::question(home, "Hello", "Welcome to Tinder for Researchers, let's start", QMessageBox::Ok); // Display a message box

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
                Author author(id.QString::toStdString()); // it does not work, why ? RISK OF ERROR ALSO

                info.update_from_server(client.getLikes(author));
                // display the app
                home->close();
                window_main main(info, author, client);
                charging->show();
                delay_sec();
                charging->hide();
                main.main->move(QApplication::desktop()->screen()->rect().center() - main.main->rect().center()); // center it
                main.main->show();
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
            Author author("id"); // Give id as name, how to give the id ?

            // Home window appears
            home->show();

            // check if the user has finished its choice
            QObject::connect(window_home.validate_button, SIGNAL(clicked()), home, SLOT(hide()));

            // Check every 10ms if the user has validated its choice and display the next windows on each subject
            bool a = true;
            while (a)
            {
                // wait 10ms to avoid saturation
                delay_1();
                // if the user has done his choice
                if (home->isHidden())
                {
                    a = false; // stop the while loop
                    // create a boolean for each checkbox of the main topics
                    bool t_phy = window_home.physics->isChecked();
                    bool t_math = window_home.math->isChecked();
                    bool t_cs = window_home.cs->isChecked();
                    bool t_bio = window_home.bio->isChecked();
                    bool t_fin = window_home.fin->isChecked();
                    bool t_stat = window_home.stat->isChecked();
                    bool t_elec = window_home.eess->isChecked();
                    bool t_econ = window_home.econ->isChecked();

                    // if the user selected at least one of them
                    if (t_phy or t_math or t_cs or t_bio or t_fin or t_stat or t_elec or t_econ)
                    {
                        // display windows for each subject in order to make rpecise chocies
                        if (t_phy)
                        {
                            windows_precise.scroll_phy->show();
                            while (windows_precise.scroll_phy->isHidden() == false)
                            {
                                delay_1();
                                QObject::connect(windows_precise.val_phy, SIGNAL(clicked()), windows_precise.scroll_phy, SLOT(hide()));
                                if (windows_precise.scroll_phy->isHidden())
                                {
                                    t_phy = false;
                                }
                            }
                        }
                        if (t_math and not t_phy)
                        {
                            windows_precise.scroll_math->show();
                            while (windows_precise.scroll_math->isHidden() == false)
                            {
                                delay_1();
                                QObject::connect(windows_precise.val_math, SIGNAL(clicked()), windows_precise.scroll_math, SLOT(hide()));
                                if (windows_precise.scroll_math->isHidden())
                                {
                                    t_math = false;
                                }
                            }
                        }
                        if (t_cs and not t_phy and not t_math)
                        {
                            windows_precise.scroll_cs->show();
                            while (windows_precise.scroll_cs->isHidden() == false)
                            {
                                delay_1();
                                QObject::connect(windows_precise.val_cs, SIGNAL(clicked()), windows_precise.scroll_cs, SLOT(hide()));
                                if (windows_precise.scroll_cs->isHidden())
                                {
                                    t_cs = false;
                                }
                            }
                        }
                        if (t_bio and not t_phy and not t_math and not t_cs)
                        {
                            windows_precise.scroll_bio->show();
                            while (windows_precise.scroll_bio->isHidden() == false)
                            {
                                delay_1();
                                QObject::connect(windows_precise.val_bio, SIGNAL(clicked()), windows_precise.scroll_bio, SLOT(hide()));
                                if (windows_precise.scroll_bio->isHidden())
                                {
                                    t_bio = false;
                                }
                            }
                        }
                        if (t_fin and not t_phy and not t_math and not t_cs and not t_bio)
                        {
                            windows_precise.scroll_fin->show();
                            while (windows_precise.scroll_fin->isHidden() == false)
                            {
                                delay_1();
                                QObject::connect(windows_precise.val_fin, SIGNAL(clicked()), windows_precise.scroll_fin, SLOT(hide()));
                                if (windows_precise.scroll_fin->isHidden())
                                {
                                    t_fin = false;
                                }
                            }
                        }
                        if (t_stat and not t_phy and not t_math and not t_cs and not t_bio and not t_fin)
                        {
                            windows_precise.scroll_stat->show();
                            while (windows_precise.scroll_stat->isHidden() == false)
                            {
                                delay_1();
                                QObject::connect(windows_precise.val_stat, SIGNAL(clicked()), windows_precise.scroll_stat, SLOT(hide()));
                                if (windows_precise.scroll_stat->isHidden())
                                {
                                    t_stat = false;
                                }
                            }
                        }
                        if (t_elec and not t_phy and not t_math and not t_cs and not t_bio and not t_fin and not t_stat)
                        {
                            windows_precise.scroll_eess->show();
                            while (windows_precise.scroll_eess->isHidden() == false)
                            {
                                delay_1();
                                QObject::connect(windows_precise.val_eess, SIGNAL(clicked()), windows_precise.scroll_eess, SLOT(hide()));
                                if (windows_precise.scroll_eess->isHidden())
                                {
                                    t_elec = false;
                                }
                            }
                        }
                        if (t_econ and not t_phy and not t_math and not t_cs and not t_bio and not t_fin and not t_stat and not t_elec)
                        {
                            windows_precise.scroll_econ->show();
                            while (windows_precise.scroll_econ->isHidden() == false)
                            {
                                delay_1();
                                QObject::connect(windows_precise.val_econ, SIGNAL(clicked()), windows_precise.scroll_econ, SLOT(hide()));
                                if (windows_precise.scroll_econ->isHidden())
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
                 client.putLikes(author, info.info); // Give it to the server
                }
            }

            window_main main(info, author, client);
            main.main->move(QApplication::desktop()->screen()->rect().center() - main.main->rect().center()); // center it

            // Create the window to give a new ID to the user
            new_id id;
            QWidget *ID = id.ID;
            ID->show();

            bool b = true;
            while (b)
            {
                delay_1();
                if (ID->isHidden())
                {
                    b = false;
                    ID->close();
                    home->close();
                    charging->show();
                    delay_sec();
                    charging->hide();
                    main.main->show();
                }
            }
            }
        }
    return app.exec();
}
