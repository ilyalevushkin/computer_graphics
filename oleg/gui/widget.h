#ifndef WIDGET_H
#define WIDGET_H

#include "../../build-oleg-Desktop_x86_darwin_generic_mach_o_64bit-Debug/ui_widget.h"
#include "../actions/action.h"
#include "../facade/mediator.h"
#include "../exceptions/baseException.h"
#include "drawer.h"
#include "../settings.h"
#include "tree_generate_methods.h"
#include "../drawer_scene.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>

#include <iostream>
#include <memory>


enum Rotation_ID {Model_ID = 0, Camera_ID = 1, Light_ID = 2};

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

protected:
    virtual void keyPressEvent(QKeyEvent*) override;
    void setUpCanvas();
    void updateCanvas();

private slots:
    void on_AddButton_clicked();
    void on_DeleteButton_clicked();
    void on_LoadButton_clicked();
    void on_CameraBox_currentIndexChanged(int index);

    void on_generate_new_clicked();

    void create_tree(Settings*);


private:
    Ui::Widget *ui;

    static constexpr double offset = 10;
    static constexpr double scaleCoeff = 1.5;
    static constexpr double angle = M_PI / 18;
    static constexpr double intense_value = 0.1;
    static constexpr double big_intense_value = 0.5;

    int k_rotate;
    double l_intensity;
    Point l;
    Rotation_ID rotation_flag;

    Drawer_Scene* canvas;
    Mediator actionController;
};

#endif // WIDGET_H
