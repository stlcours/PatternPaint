QT += core widgets

TARGET = libblinky
TEMPLATE = lib

OBJECTS_DIR = .tmp
MOC_DIR = .tmp
RCC_DIR = .tmp
UI_DIR = .tmp

include(../libusb.pri)

HEADERS += \
    fixture.h \
    matrixfixture.h \
    colormode.h \
    brightnessmodel.h\
    pattern.h \
    patternmodel.h \
    patternwriter.h \
    patternframemodel.h \
    patternframeundocommand.h \
    patternscrollmodel.h \
    patternscrollundocommand.h \
    blinkycontroller.h \
    controllerinfo.h \
    blinkyuploader.h \
    blinkytapecontrollerinfo.h \
    avr109commands.h \
    serialcommand.h \
    lightbuddycommands.h \
    blinkypendantcommands.h

SOURCES +=  \
    fixture.cpp \
    matrixfixture.cpp \
    colormode.cpp \
    brightnessmodel.cpp \
    pattern.cpp \
    patternwriter.cpp \
    patternframemodel.cpp \
    patternframeundocommand.cpp \
    patternscrollmodel.cpp \
    patternscrollundocommand.cpp \
    blinkycontroller.cpp \
    controllerinfo.cpp \
    blinkytapecontrollerinfo.cpp \
    avr109commands.cpp \
    serialcommand.cpp \
    lightbuddycommands.cpp \
    blinkypendantcommands.cpp

# For platforms that have serial ports
# TODO: Pull hard-coded references to BlinkyTape from the gui, allowing this section to be switchable
#has_serial {
    QT += serialport

    HEADERS += \
        blinkypendantuploader.h \
        blinkytapeuploader.h \
        serialcommandqueue.h \
        avruploaddata.h \
        blinkytape.h \
        lightbuddyuploader.h \
        PatternPlayer_Sketch.h \
        ProductionSketch.h \
        usbutils.h

    SOURCES += \
        blinkypendantuploader.cpp \
        blinkytapeuploader.cpp \
        serialcommandqueue.cpp \
        avruploaddata.cpp \
        blinkytape.cpp \
        lightbuddyuploader.cpp \
        usbutils.cpp

#}
