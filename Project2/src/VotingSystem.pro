QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ballot.cc \
    ballot_file_processor.cc \
    candidate.cc \
    logger.cc \
    plurality_election.cc \
    plurality_election_record.cc \
    stv_election.cc \
    stv_election_record.cc \
    voting_info.cc \
    voting_system.cc

HEADERS += \
    ballot.h \
    ballot_file_processor.h \
    candidate.h \
    logger.h \
    plurality_election.h \
    plurality_election_record.h \
    stv_election.h \
    stv_election_record.h \
    voting_info.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
