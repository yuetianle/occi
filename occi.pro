TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=c++11

#INCLUDEPATH += /home/lee/workspace/c++/occi/lib/lib/incl
#LIBS += -L  /home/lee/workspace/c++/occi/lib/lib -locci -lociei -locijdbc11 -lclntsh -lnnz11
#LIBS += /home/lee/workspace/c++/occi/lib/lib/libocci.so
#LIBS += /home/lee/workspace/c++/occi/lib/lib/libociei.so
#LIBS += /home/lee/workspace/c++/occi/lib/lib/libocijdbc11.so
#LIBS += /home/lee/workspace/c++/occi/lib/lib/libclntsh.so
#LIBS += /home/lee/workspace/c++/occi/lib/lib/libnnz11.so
SOURCES += main.cpp \
        cocciobj.cpp \
    coccicommon.cpp \
    coccipool.cpp \
    crecord.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    cocciobj.h \
    coccicommon.h \
    coccipool.h \
    crecord.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/lib/release/ -locci -lociei -locijdbc11 -lclntsh -lnnz11

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/lib/debug/ -locci -lociei -locijdbc11 -lclntsh -lnnz11

else:unix: LIBS += -L$$PWD/lib/lib/ -locci -lociei -locijdbc11 -lclntsh -lnnz11

INCLUDEPATH += $$PWD/lib/incl
DEPENDPATH += $$PWD/lib/incl
