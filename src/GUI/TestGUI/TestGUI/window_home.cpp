#include <window_home.h>

window_home::window_home()
{
    // Create the window
    home = new QWidget;
    home->move(QApplication::desktop()->screen()->rect().center() - home->rect().center());
    home->setWindowTitle("Interests");
    home->setMinimumSize(500, 200);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;

    // A Label for the text
    QLabel *title = new QLabel;
    title->setText("What are you ineterested in?");
    title->setFont(QFont("Courrier", 15, QFont::Bold));

    // Create some checkboxes associated tot the topics of arXiv
    physics = new QCheckBox("Physics");
    math = new QCheckBox("Mathematics");
    cs = new QCheckBox("Computer Science");
    bio = new QCheckBox("Quantitative Biology");
    fin = new QCheckBox("Quantitative Finance");
    stat = new QCheckBox("Statistics");
    eess = new QCheckBox("Electrical Engineering and Systems Science");
    econ = new QCheckBox("Economics");

    // Create the button to valilade
    validate_button = new QPushButton("Validate");

    // Add all the elements to the layout (button, checkboxes and text)
    layout->addWidget(title);
    layout->addWidget(physics);
    layout->addWidget(math);
    layout->addWidget(cs);
    layout->addWidget(bio);
    layout->addWidget(fin);
    layout->addWidget(stat);
    layout->addWidget(eess);
    layout->addWidget(econ);
    layout->addWidget(validate_button);

    // Set the layout
    home->setLayout(layout);
}
