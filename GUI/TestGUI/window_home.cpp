#include <window_home.h>

window_home::window_home()
{

    home = new QWidget; // The window
    home->move(QApplication::desktop()->screen()->rect().center() - home->rect().center()); // center the window
    QVBoxLayout *layout = new QVBoxLayout; // its layout
    // Create the text that is going to be displayed in the window home
    QLabel *title = new QLabel; // the title and its parameters
    title->setText("What are you ineterested in?");
    title->setFont(QFont("Courrier", 15, QFont::Bold));
    // Give a title to the window home
    home->setWindowTitle("Interests");
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
    // Set the layout in the window and its minimal size
    home->setLayout(layout);
    home->setMinimumSize(500, 200);
}
