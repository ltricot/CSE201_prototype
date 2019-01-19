#include <new_id.h>

new_id::new_id()
{
    // Create the window
    ID = new QWidget;

    // Create the layout
    QVBoxLayout *ID_layout = new QVBoxLayout;

    // Create a label for the text
    QLabel *text_id = new QLabel;
    text_id->setText("Here is your user ID. Please note it carefully, you will use it to connect next time.");
    text_id->setFont(QFont("Courrier", 15));
    ID_layout->addWidget(text_id);

    // Create a label for the ID
    QLabel *id_itself = new QLabel;
    std::vector<std::string> possible_id;
    possible_id.push_back("314159");
    possible_id.push_back("000420");
    possible_id.push_back("772017");
    possible_id.push_back("772023");
    possible_id.push_back("161803");
    possible_id.push_back("772016");
    possible_id.push_back("221129");
    possible_id.push_back("487142");

    int k = rand() % possible_id.size();
    std::string id = possible_id[k];

    id_itself->setText(QString::fromStdString(id));
    id_itself->setFont(QFont("Courrier", 25, QFont::Bold));
    id_itself->setAlignment(Qt::AlignCenter);
    ID_layout->addWidget(id_itself);

    // Create a button
    QPushButton *val_id = new QPushButton;
    val_id->setText("I have noted my ID and I continue");
    ID_layout->addWidget(val_id);

    // set up
    ID->setLayout(ID_layout);
    QObject::connect(val_id, SIGNAL(clicked()), ID, SLOT(hide()));
}
