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
    drawer_scene.cpp \
    explanations.cpp \
    facade/facade.cpp \
    factory/growth_factory.cpp \
    factory/object_factory.cpp \
    factory/tree_factory.cpp \
    geometry/geometry.cpp \
    gui/widget.cpp \
    main.cpp \
    managers/drawmanager.cpp \
    matrix/matrix.cpp \
    object/camera.cpp \
    object/compositeobject.cpp \
    object/edge.cpp \
    object/model.cpp \
    object/node.cpp \
    object/transformed_model.cpp \
    object/triangle.cpp \
    scene/scene.cpp \
    settings.cpp \
    shading_algorithms/Fong_shading/Fong_shading.cpp \
    shading_algorithms/flat_shading/flat_shading.cpp \
    workers/modelUploader.cpp \
    workers/objecttransformator.cpp \
    z-bufer/z_buffer.cpp

HEADERS += \
    actions/action.h \
    drawer_scene.h \
    exceptions/baseException.h \
    exceptions/builderException.h \
    exceptions/drawerException.h \
    exceptions/objectexception.h \
    exceptions/settingsException.h \
    exceptions/transformerException.h \
    exceptions/uploaderException.h \
    explanations.h \
    facade/facade.h \
    facade/mediator.h \
    factory/growth_factory.h \
    factory/growth_methods.h \
    factory/object_factory.h \
    factory/transform_tree_generate_methods.h \
    factory/tree_factory.h \
    factory/tree_generate_methods.h \
    geometry/geometry.h \
    gui/drawer.h \
    gui/widget.h \
    iterator/iterator.h \
    lighting.h \
    managers/drawmanager.h \
    managers/objectmanager.h \
    matrix/matrix.h \
    object/camera.h \
    object/color.h \
    object/compositeobject.h \
    object/edge.h \
    object/model.h \
    object/node.h \
    object/object.h \
    object/transformed_model.h \
    object/triangle.h \
    scene/scene.h \
    settings.h \
    shading_algorithms/Fong_shading/Fong_shading.h \
    shading_algorithms/flat_shading/flat_shading.h \
    transform_tree_generate_methods.h \
    transformations/transformations.h \
    tree_generate_methods.h \
    tree_params.h \
    workers/modelUploader.h \
    workers/objecttransformator.h \
    z-bufer/z_buffer.h

FORMS += \
    explanation.ui \
    explanations.ui \
    settings.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data/0.txt \
    data/cube.txt \
    data/data (copy).txt


LIBS += -L/usr/local/Cellar/armadillo/9.800.2/lib/ -larmadillo
INCLUDEPATH += /usr/local/Cellar/armadillo/9.800.2/include

INCLUDEPATH += /usr/local/Cellar/boost
