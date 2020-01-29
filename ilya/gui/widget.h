#ifndef WIDGET_H
#define WIDGET_H

#include "../../build-oleg-Desktop_x86_darwin_generic_mach_o_64bit-Debug/ui_widget.h"
#include "../actions/action.h"
#include "../facade/mediator.h"
#include "../exceptions/baseException.h"
#include "drawer.h"
#include "../settings.h"
#include "../factory/tree_generate_methods.h"
#include "../drawer_scene.h"

#include <QColorDialog>

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>

#include <iostream>
#include <memory>
#include <string>
#include <cstring>

#define DEFAULT_MODEL_COUNT 100


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
    void timerEvent(QTimerEvent* event) override
    {
        if (direction_flag)
        {
            if (model_index == model_counts - 2)
            {
                killTimer(myTimerId);
                ui->play->setEnabled(false);
                ui->reverse->setEnabled(true);
                ui->stop->setEnabled(false);
            }
            model_index += 1;
            this->updateCanvas();
        }
        else
        {
            if (model_index == 0)
            {
                killTimer(myTimerId);
                ui->reverse->setEnabled(false);
                ui->play->setEnabled(true);
                ui->stop->setEnabled(false);
            }
            model_index -= 1;
            this->updateCanvas();
        }
    }

private slots:
    void on_AddButton_clicked();
    void on_DeleteButton_clicked();
    void on_LoadButton_clicked();
    void on_CameraBox_currentIndexChanged(int index);
    void set_focus_on_scene();
    //void on_ModelBox_currentIndexChanged(int);

    void on_generate_new_clicked();

    void create_tree(Settings*);


    void on_generate_growth_clicked();

    void on_previous_clicked();

    void on_next_clicked();

    void on_stop_clicked();

    void on_play_clicked();

    void on_AddBaseCamera_clicked();

    void on_delete_model_clicked();

    void on_end_modeling_clicked();

    void on_font_color_clicked();

    void on_reverse_clicked();

    void on_save_new_clicked();

private:
    Ui::Widget *ui;

    void exec_base_camera_rotations(ssize_t previousIndexCamera);

    static constexpr double offset = 10;
    static constexpr double scaleCoeff = 1.5;
    static constexpr double angle = M_PI / 18;
    static constexpr double intense_value = 0.1;
    static constexpr double big_intense_value = 0.5;

    int myTimerId;

    int k_rotate;
    double l_intensity;
    tree_params params;
    Point l;
    Rotation_ID rotation_flag;
    int model_index;
    int model_counts;
    bool direction_flag;

    QColor font_color;

    Drawer_Scene* canvas;
    Mediator actionController;
};

#endif // WIDGET_H
