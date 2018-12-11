#ifndef INFO_USER_H
#define INFO_USER_H
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
#include <random>
#include <QTabWidget>

// create a class info_user that will store the choices of the user
class info_user{
    public:

        // Create a list a checkboxes
        QCheckBox *checkboxes[154];

        // generator fill up the storage with 0
        info_user();

        // the update function take the checkboxes in input and fill the storage info with 0 and 1
        void update();

        // take the list of 0 and 1 (equivalent to info) from the server and update checkboxes
        void update_from_server(int a[154]);


    private:
        // Create a list of 0 and 1
        int info[154];

};
#endif // INFO_USER_H
