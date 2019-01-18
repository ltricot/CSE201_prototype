#ifndef INFO_PAGE_H
#define INFO_PAGE_H

#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>

QScrollArea* info_scrool_generation() {

QScrollArea *page_info_scroll = new QScrollArea;
QGridLayout *l_info = new QGridLayout;

QLabel *text_info = new QLabel;
text_info->setWordWrap(true);
text_info->setText("Welcome on the Tinder for researchers (God knows that need it!)\n \
\n \
Here is a brief presentation of the application. \n \
To be simple, we will show you some arXiv articles according to the interests you gave us when you sign in. You will be able to react to them : like, dislike, indifferent.\n \
According to what you like or not, we will recommend you articles : they will be selected just for you and should match with your interests. \
And of course we keep track of all the articles you like.\n \
\n \
How to use the app?\n \
You are currently in the “Information” section but you can move to three other sections.\n \
In “Let’s like!”, we will show you arXiv articles fitting  with your interests. Give your opinion about them using three buttons at the bottom. Of course, only you can see if you like or not an article.\n \
In the “Likeable” section, we give you some articles that you should like according to your past like, don’t hesitate to give your opinion about them!\n \
Finally, in the “parameters”, you can see you ID, modify your interests and see the articles you liked.\n \n \
Enjoy!");
l_info->addWidget(text_info);

page_info_scroll->setLayout(l_info);

return page_info_scroll;
}

#endif // INFO_PAGE_H
