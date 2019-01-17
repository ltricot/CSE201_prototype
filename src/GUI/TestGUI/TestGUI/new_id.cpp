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
    id_itself->setText("TO BE IMPLEMENTED"); // will be replaced by an ID given by the server
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
