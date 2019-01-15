# Copyright (c) 2018, UChicago Argonne, LLC
# See LICENSE file.

# Qt template
TEMPLATE = app

# Project name
TARGET = PyScanWidget

# Qt components
QT += core \
    gui \
	widgets

QMAKE_EXT_CPP += .c


###################################################	
#                             						  #
# Modify paths for 3rd party libraries below.     #
#                             						  #
###################################################


#######################################################

# Destination build directory
DESTDIR = ./bin

# Release or Debug
CONFIG += debug
CONFIG += ordered
CONFIG += console
DEFINES += WITH_DOM 
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Include paths
INCLUDEPATH += src

# System dependent library paths
macx {
}
unix:!macx {
LIBS += -ldl
}
win32 {
INCLUDEPATH += $${EPICS_BASE}\\include\\compiler\\msvc

QMAKE_CXXFLAGS += /D__STDC__=0 /D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECATE /DEPICS_BUILD_DLL /DEPICS_CALL_DLL
QMAKE_LFLAGS += /STACK:41943040,41943040

#debug
QMAKE_CXXFLAGS += /D_ITERATOR_DEBUG_LEVEL=2
#release
QMAKE_CXXFLAGS += /D_ITERATOR_DEBUG_LEVEL=0
}


# Location for intermediate files
MOC_DIR += ./generated
OBJECTS_DIR += ./generated

# Resource file
RESOURCES = PyScanWidget.qrc

# Include actual project
include(PyScanWidget.pri)
