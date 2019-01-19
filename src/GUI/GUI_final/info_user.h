#ifndef INFO_USER_H
#define INFO_USER_H
#include <QCheckBox>
#pragma once

// create a class info_user that will store the choices of the user
class info_user{
    public:

        // Create a list a checkboxes
        QCheckBox *checkboxes[154];

        // generator fill up the storage with 0
        info_user();

        // Iterating over the checkboxes list and fills the storage accordingly i.e. 0 for unchecked and 1 for checked
        void update();

        // Iterating over the storage list it updates the status of the checkboxes i.e. checks it if 1 and unchecks it if 0
        void update_from_server(std::vector<std::string> a);

        // give the associated checkbox
        QCheckBox* give_check(int a);

        // Create a list of 0 and 1
        std::vector<std::string> info;

};
#endif // INFO_USER_H
