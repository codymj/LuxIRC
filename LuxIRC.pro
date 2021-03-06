######################################################################
# Automatically generated by qmake (3.0) Wed Aug 24 17:34:40 2016
######################################################################

TEMPLATE = app
TARGET = LuxIRC
INCLUDEPATH += .
QT += core widgets network gui
OBJECTS_DIR = ./obj
MOC_DIR = ./moc
UI_DIR = ./src
CONFIG += debug

# Input
HEADERS += src/AboutDlg.h \
           src/AddNetworkDlg.h \
           src/ChangeNickDlg.h \
           src/Channel.h \
           src/Connection.h \
           src/EditNetworkDlg.h \
           src/MainWindow.h \
           src/NetworkDlg.h \
           src/ui_AboutDlg.h \
           src/ui_AddNetworkDlg.h \
           src/ui_ChangeNickDlg.h \
           src/ui_EditNetworkDlg.h \
           src/ui_MainWindow.h \
           src/ui_NetworkDlg.h
FORMS += src/AboutDlg.ui \
         src/AddNetworkDlg.ui \
         src/ChangeNickDlg.ui \
         src/EditNetworkDlg.ui \
         src/MainWindow.ui \
         src/NetworkDlg.ui
SOURCES += src/AboutDlg.cpp \
           src/AddNetworkDlg.cpp \
           src/ChangeNickDlg.cpp \
           src/Channel.cpp \
           src/Connection.cpp \
           src/EditNetworkDlg.cpp \
           src/main.cpp \
           src/MainWindow.cpp \
           src/NetworkDlg.cpp
