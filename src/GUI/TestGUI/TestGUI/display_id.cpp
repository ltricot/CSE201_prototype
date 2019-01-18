#include <display_id.h>

window_id::window_id(Author author)
{
    // Window
    id_info = new QWidget; // window
    id_info->setMinimumSize(400, 150);

    // Layout
    QVBoxLayout *id_lay = new QVBoxLayout; // its layout
    id_info->setWindowTitle("My account: ID"); // Its title

    // Labels
    QLabel *id_text = new QLabel;
    id_text->setText("Your ID is:");
    id_lay->addWidget(id_text);
    QLabel *id_itself = new QLabel;
    id_itself->setText(QString::fromStdString(author.name)); // will be replaced by an ID given by the server
    id_itself->setFont(QFont("Courrier", 25, QFont::Bold));
    id_itself->setAlignment(Qt::AlignCenter);

    // Set up
    id_lay->addWidget(id_itself);
    id_info->setLayout(id_lay);
}
