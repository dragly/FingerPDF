FORMS         = window.ui
HEADERS       = documentwidget.h \
                window.h \
    imageloader.h
SOURCES       = documentwidget.cpp \
                main.cpp \
                window.cpp \
    imageloader.cpp

CONFIG          += link_pkgconfig
PKGCONFIG       += poppler-qt4
INCLUDEPATH  += /usr/include/poppler/qt4
LIBS         += -L/usr/lib -lpoppler-qt4
