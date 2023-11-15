QT             += core gui openglwidgets
QMAKE_CXXFLAGS += -Wno-deprecated

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../3DViewer/QtGifImage/src/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += PROJECT_DIR=\\\"$$PWD\\\" HOME_DIR=\\\"$$HOME\\\"

LIBS += -L../libutils/ -lutils

INCLUDEPATH += ../libutils/include/ ../3DViewer ../3DViewer/QtGifImage/src/gifimage

SOURCES += \
    ../3DViewer/main.cpp \
    ../3DViewer/mainwindow.cpp \
    ../3DViewer/openglwidget.cpp \
    ../3DViewer/cube.cpp \
    ../3DViewer/indexbuffer.cpp \
    ../3DViewer/vertexbuffer.cpp \
    ../3DViewer/utl.cpp \
    ../3DViewer/shader.cpp \
    ../3DViewer/settings.cpp

HEADERS += \
    ../libutils/include/utils.h \
    ../libutils/include/utils/matrix.h \
    ../libutils/include/utils/obj_parser.h \
    ../3DViewer/mainwindow.h \
    ../3DViewer/openglwidget.h \
    ../3DViewer/cube.h \
    ../3DViewer/indexbuffer.h \
    ../3DViewer/vertexbuffer.h \
    ../3DViewer/utl.h \
    ../3DViewer/shader.h \
    ../3DViewer/settings.h \
    ../3DViewer/QtGifImage/src/gifimage/qgifimage.h

FORMS += \
    ../3DViewer/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../3DViewer/.config \
    ../3DViewer/cube.obj \
    ../3DViewer/iphone.obj \
    ../3DViewer/f-shader.glsl \
    ../3DViewer/v-shader.glsl
