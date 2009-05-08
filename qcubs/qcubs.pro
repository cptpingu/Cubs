# -------------------------------------------------
# Project created by QtCreator 2009-05-03T02:04:09
# -------------------------------------------------
TARGET = qcubs
TEMPLATE = app
SOURCES += main.cc \
    QCubsEditor/QCubsEditor.cc \
    QCubsEditor/CubsHighlighter.cc \
    MainWindow/MainWindow.cc \
    MainWindow/MainWindowBuild.cc \
    DialogWait/DialogWait.cc
HEADERS += MainWindow/MainWindow.hh \
    QCubsEditor/QCubsEditor.hh \
    QCubsEditor/CubsHighlighter.hh \
    DialogWait/DialogWait.hh
FORMS += MainWindow/MainWindow.ui \
    DialogWait/DialogWait.ui
debug:CONFIG += console
