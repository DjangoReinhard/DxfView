QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# This code depends on zenity.
# sudo apt-get install zenity

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -g

SOURCES += \
    abstract3dcontrol.cpp \
    dxfcontrol.cpp \
    libocc/draw_primitives.cpp \
    libocc/opencascade.cpp \
    libdata/variable.cpp \
    libspline/bezier_spline.cpp \
    libspline/cubic_spline.cpp \
    libspline/spline.cpp \
    libdxfrw/drw_classes.cpp \
    libdxfrw/drw_entities.cpp \
    libdxfrw/drw_header.cpp \
    libdxfrw/drw_objects.cpp \
    libdxfrw/intern/drw_dbg.cpp \
    libdxfrw/intern/drw_textcodec.cpp \
    libdxfrw/intern/dwgbuffer.cpp \
    libdxfrw/intern/dwgreader.cpp \
    libdxfrw/intern/dwgreader15.cpp \
    libdxfrw/intern/dwgreader18.cpp \
    libdxfrw/intern/dwgreader21.cpp \
    libdxfrw/intern/dwgreader24.cpp \
    libdxfrw/intern/dwgreader27.cpp \
    libdxfrw/intern/dwgutil.cpp \
    libdxfrw/intern/dxfreader.cpp \
    libdxfrw/intern/dxfwriter.cpp \
    libdxfrw/intern/rscodec.cpp \
    libdxfrw/libdwgr.cpp \
    libdxfrw/libdxfrw.cpp \
    dx_data.cpp \
    dxfHelper.cpp \
    stepcontrol.cpp
HEADERS += \
    AbstractUIHelper.h \
    abstract3dcontrol.h \
    dxfcontrol.h \
    libocc/draw_primitives.h \
    libocc/opencascade.h \
    libdata/variable.h \
    libdialog/portable-file-dialogs.h \
    libdxfrw/drw_base.h \
    libdxfrw/drw_classes.h \
    libdxfrw/drw_entities.h \
    libdxfrw/drw_header.h \
    libdxfrw/drw_interface.h \
    libdxfrw/drw_objects.h \
    libdxfrw/intern/drw_cptable932.h \
    libdxfrw/intern/drw_cptable936.h \
    libdxfrw/intern/drw_cptable949.h \
    libdxfrw/intern/drw_cptable950.h \
    libdxfrw/intern/drw_cptables.h \
    libdxfrw/intern/drw_dbg.h \
    libdxfrw/intern/drw_textcodec.h \
    libdxfrw/intern/dwgbuffer.h \
    libdxfrw/intern/dwgreader.h \
    libdxfrw/intern/dwgreader15.h \
    libdxfrw/intern/dwgreader18.h \
    libdxfrw/intern/dwgreader21.h \
    libdxfrw/intern/dwgreader24.h \
    libdxfrw/intern/dwgreader27.h \
    libdxfrw/intern/dwgutil.h \
    libdxfrw/intern/dxfreader.h \
    libdxfrw/intern/dxfwriter.h \
    libdxfrw/intern/rscodec.h \
    libdxfrw/libdwgr.h \
    libdxfrw/libdxfrw.h \
    libspline/bezier_spline.h \
    libspline/cubic_spline.h \
    libspline/spline.h \
    mainwindow.h \
    dx_data.h \
    dxfHelper.h \
    stepcontrol.h
FORMS += \
    mainwindow.ui
OBJECTS_DIR = ./build_o

# Local include paths.
INCLUDEPATH +=  libocc/ \
                libdxfrw/ \
                libspline/ \
                libdata/ \
                libdialog/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
DISTFILES += \

# this copies the configuration files etc to the build direcory. So user has only to edit the source directory.
copydata.commands = $(COPY_DIR) $$PWD/* $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

# Opencascade
LIBS+= -L/usr/local/lib/ \

INCLUDEPATH +=  /usr/local/include/opencascade/ \
                /usr/include/ \

# compiled libs .so files:
# LIBS += -lorocos-kdl

# compiled libs .so files:
LIBS += -lTKPrim
LIBS += -lTKernel
LIBS += -lTKMath -lTKTopAlgo -lTKService
LIBS += -lTKG2d -lTKG3d -lTKV3d -lTKOpenGl
LIBS += -lTKBRep -lTKXSBase -lTKGeomBase
LIBS += -lTKMeshVS -lTKXSDRAW
LIBS += -lTKLCAF -lTKXCAF -lTKCAF
LIBS += -lTKCDF -lTKBin -lTKBinL -lTKBinXCAF -lTKXml -lTKXmlL -lTKXmlXCAF
# -- IGES support
LIBS += -lTKIGES
# -- STEP support
LIBS += -lTKSTEP -lTKXDESTEP -lTKXDEIGES
# -- STL support
LIBS += -lTKSTL
# -- OBJ/glTF support
LIBS += -lTKRWMesh
# -- VRML support
LIBS += -lTKVRML

RESOURCES += \
    icons.qrc

# qmake DxfView.pro CONFIG+=configA
configA {
TARGET = DxfView
SOURCES += main.cpp \
    mainwindow.cpp
}

# qmake DxfView.pro CONFIG+=configB
configB {
TARGET = test/TestDxfReader
SOURCES += test/TestDxfReader.cpp \
    mainwindow.cpp
}
