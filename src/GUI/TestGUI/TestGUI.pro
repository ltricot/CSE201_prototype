QT += widgets
QT += webenginewidgets
CONFIG+=sdk_no_version_check

SOURCES += \
    main.cpp \
    window_main.cpp \
    window_home.cpp \
    windows_precise.cpp \
    info_user.cpp \
    window_int_modif.cpp \
    new_id.cpp \
    display_id.cpp \
    display_like.cpp \
    client.cpp \
    auto_update.cpp \
    auto_update_label.cpp

HEADERS += \
    info_user.h \
    window_main.h \
    window_home.h \
    windows_precise.h \
    window_int_modif.h \
    new_id.h \
    display_id.h \
    display_like.h \
    client.h \
    json.h \
    primitives.h \
    auto_update.h \
    auto_update_label.h

RESOURCES += \
    resources.qrc
