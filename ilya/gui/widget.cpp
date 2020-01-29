#include "widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    model_index = -1;
    font_color = Qt::white;
    QString style = "background: rgb(%1, %2, %3);";
    ui->font_color->setStyleSheet(style.arg(font_color.red()).arg(font_color.green()).arg(font_color.blue()));
    this->setUpCanvas();
    //ui->ModelBox->addItem("All models");
    k_rotate = 1;
    l_intensity = 1;
    l = {0,0,1};
    rotation_flag = Model_ID;
    direction_flag = true;
    //connect(ui->ModelBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ModelBox_currentIndexChanged(int)));
    model_counts = DEFAULT_MODEL_COUNT;
    ui->speed->setRange(0, 99);
    ui->speed->setSingleStep(0.1);
    connect(ui->speed, SIGNAL(valueChanged(double)), this, SLOT(set_focus_on_scene()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::set_focus_on_scene()
{
    ui->scene->setFocus();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    try
    {
        ssize_t index = this->model_index;
        ssize_t indexCamera = ui->CameraBox->currentIndex();

        if (event->key() == Qt::Key_A)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelShiftAction action(-this->offset, 0, 0, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraShiftAction action2(-this->offset, 0, 0, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                break;
            }
            }
        }
        else if (event->key() == Qt::Key_S)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelShiftAction action(0, this->offset, 0, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraShiftAction action2(0, this->offset, 0, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                break;
            }
            }
        }
        else if (event->key() == Qt::Key_D)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelShiftAction action(this->offset, 0, 0, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraShiftAction action2(this->offset, 0, 0, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                break;
            }
            }
        }
        else if (event->key() == Qt::Key_W)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelShiftAction action(0, -this->offset, 0, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraShiftAction action2(0, -this->offset, 0, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                break;
            }
            }
        }
        else if (event->key() == Qt::Key_Q)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelShiftAction action(0, 0, this->offset, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraShiftAction action2(0, 0, this->offset, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                break;
            }
            }
        }
        else if (event->key() == Qt::Key_E)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelShiftAction action(0, 0, -this->offset, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraShiftAction action2(0, 0, -this->offset, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                break;
            }
            }
        }
        else if (event->key() == Qt::Key_R)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelScaleAction action(scaleCoeff, scaleCoeff, scaleCoeff, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraScaleAction action2(scaleCoeff, scaleCoeff, scaleCoeff, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                break;
            }
            }
        }
        else if (event->key() == Qt::Key_T)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelScaleAction action(1 / scaleCoeff, 1 / scaleCoeff, 1 / scaleCoeff, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraScaleAction action2(1 / scaleCoeff, 1 / scaleCoeff, 1 / scaleCoeff, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                break;
            }
            }
        }
        else if (event->key() == Qt::Key_Z)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelRotateAction action(angle * k_rotate, 0, 0, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraRotateAction action2(angle * k_rotate, 0, 0, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                l.rotate(angle * k_rotate, 0, 0);
                break;
            }
            }
            k_rotate = 1;
        }
        else if (event->key() == Qt::Key_X)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelRotateAction action(0, angle * k_rotate, 0, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraRotateAction action2(0, angle * k_rotate, 0, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                l.rotate(0, angle * k_rotate, 0);
                break;
            }
            }
            k_rotate = 1;
        }
        else if (event->key() == Qt::Key_C)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelRotateAction action(0, 0, angle * k_rotate, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraRotateAction action2(0, 0, angle * k_rotate, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                l.rotate(0, 0, angle * k_rotate);
                break;
            }
            }
            k_rotate = 1;
        }
        else if (event->key() == Qt::Key_V)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelRotateAction action(-angle * k_rotate, 0, 0, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraRotateAction action2(-angle * k_rotate, 0, 0, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                l.rotate(-angle * k_rotate, 0, 0);
                break;
            }
            }
            k_rotate = 1;
        }
        else if (event->key() == Qt::Key_B)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelRotateAction action(0, -angle * k_rotate, 0, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraRotateAction action2(0, -angle * k_rotate, 0, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                l.rotate(0, -angle * k_rotate, 0);
                break;
            }
            }
            k_rotate = 1;
        }
        else if (event->key() == Qt::Key_N)
        {
            switch(rotation_flag)
            {
            case Model_ID:
            {
                actions::ModelRotateAction action(0, 0, -angle * k_rotate, index);
                actionController.executeAction(action);
                break;
            }
            case Camera_ID:
            {
                actions::CameraRotateAction action2(0, 0, -angle * k_rotate, indexCamera);
                actionController.executeAction(action2);
                break;
            }
            case Light_ID:
            {
                l.rotate(0, 0, -angle * k_rotate);
                break;
            }
            }
            k_rotate = 1;
        }
        else if (event->key() == Qt::Key_Shift)
        {
            if (k_rotate != 1)
            {
                k_rotate = 1;
            }
            else
            {
                k_rotate = 9;
            }
        }
        else if (event->key() == Qt::Key_Control)
        {
            if (rotation_flag == Model_ID)
            {
                rotation_flag = Camera_ID;
            }
            else if (rotation_flag == Camera_ID)
            {
                rotation_flag = Light_ID;
            }
            else if (rotation_flag == Light_ID)
            {
                rotation_flag = Model_ID;
            }
        }
        else if (event->key() == Qt::Key_I)
        {
            l_intensity += intense_value;
        }
        else if (event->key() == Qt::Key_K)
        {
            l_intensity -= intense_value;
        }
        else if (event->key() == Qt::Key_O)
        {
            l_intensity += big_intense_value;
        }
        else if (event->key() == Qt::Key_L)
        {
            l_intensity -= big_intense_value;
        }
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }

    this->updateCanvas();
}

void Widget::setUpCanvas()
{
    this->canvas = ui->scene;

    this->canvas->installEventFilter(this);
    this->canvas->update();

    ui->AddBaseCamera->setEnabled(true);
    ui->AddBaseCamera->click();
    ui->AddBaseCamera->setEnabled(false);
}

void Widget::updateCanvas()
{
    ModelDrawer drawer(this->canvas, l, l_intensity, font_color);

    size_t cameraIndex = size_t(ui->CameraBox->currentIndex());
    actions::ModelDrawAction action(drawer, cameraIndex, model_index);
    actionController.executeAction(action);
}

void Widget::on_AddButton_clicked()
{
    try
    {
        ssize_t indexCamera = ui->CameraBox->currentIndex();
        actions::NextCameraAddAction action(indexCamera);
        actionController.executeAction(action);

        ui->CameraBox->addItem("Camera " + QString::number(ui->CameraBox->count()));
        ui->CameraBox->setCurrentIndex(ui->CameraBox->count() - 1);
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}

void Widget::on_DeleteButton_clicked()
{
    try
    {
        if (ui->CameraBox->count() == 1)
            return;

        actions::CameraRemoveAction action(ui->CameraBox->currentIndex());
        actionController.executeAction(action);

        ui->CameraBox->removeItem(ui->CameraBox->currentIndex());
        ui->CameraBox->setCurrentIndex(0);

        /*actions::ModelRemoveAction action2(ui->ModelBox->currentIndex());
        actionController.executeAction(action2);

        ui->ModelBox->removeItem(ui->ModelBox->currentIndex());
        ui->ModelBox->setCurrentIndex(0);*/
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}

void Widget::on_LoadButton_clicked()
{
    try
    {
        QString filePath = QFileDialog::getOpenFileName(this, "Open model", "/Users/ilalevuskin/Qt_projects/oleg/data/", \
                                                        "Wavefront (*.txt)");
        if (filePath.isEmpty())
        {
            QMessageBox::warning(this, "Error", "No file choosen");
            return;
        }

        actions::ModelUploadAction action(filePath.toStdString(), &this->params);
        actionController.executeAction(action);

        this->model_index += 1;

        this->updateCanvas();


        //model
        ui->delete_model->setEnabled(true);
        ui->save_new->setEnabled(true);
        //camera
        ui->AddButton->setEnabled(true);
        ui->DeleteButton->setEnabled(true);
        ui->AddBaseCamera->setEnabled(true);

        //growth
        ui->generate_growth->setEnabled(true);

        //load
        ui->generate_new->setEnabled(false);
        ui->LoadButton->setEnabled(false);
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}

void Widget::on_CameraBox_currentIndexChanged(int index)
{
    this->updateCanvas();
}

void Widget::on_generate_new_clicked()
{
    try
    {
        Settings *set = new Settings(this);
        set->show();

        this->setEnabled(false);

        connect(set, SIGNAL(flagChanged(Settings*)), this, SLOT(create_tree(Settings*)));
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}


void Widget::create_tree(Settings *set)
{
    this->params = set->params;
    actions::ModelUploadFromGenerateAction action(this->params);
    actionController.executeAction(action);

    this->model_index += 1;

    //model
    ui->delete_model->setEnabled(true);
    ui->save_new->setEnabled(true);
    //camera
    ui->AddButton->setEnabled(true);
    ui->DeleteButton->setEnabled(true);
    ui->AddBaseCamera->setEnabled(true);

    //growth
    ui->generate_growth->setEnabled(true);

    //load
    ui->generate_new->setEnabled(false);
    ui->LoadButton->setEnabled(false);

    this->updateCanvas();
}

void Widget::on_generate_growth_clicked()
{
    actions::ModelRemoveAction action(0);
    actionController.executeAction(action);

    actions::ModelingGenerateAction action2(this->params, this->model_counts);
    actionController.executeAction(action2);

    this->model_index = 0;

    ui->delete_model->setEnabled(false);
    ui->generate_new->setEnabled(false);
    ui->LoadButton->setEnabled(false);
    ui->speed->setEnabled(true);

    ui->generate_growth->setEnabled(false);
    ui->play->setEnabled(true);
    ui->stop->setEnabled(false);
    ui->next->setEnabled(true);
    ui->previous->setEnabled(true);
    ui->end_modeling->setEnabled(true);
    ui->reverse->setEnabled(true);

    this->updateCanvas();
    //ui->ModelBox->removeItem(ui->ModelBox->currentIndex());
    //ui->ModelBox->setCurrentIndex(0);
}

void Widget::on_previous_clicked()
{
    if (this->model_index > 0)
    {
        this->model_index -= 1;
        this->updateCanvas();
    }
}

void Widget::on_next_clicked()
{
    if (this->model_index < this->model_counts - 1)
    {
        this->model_index += 1;
        this->updateCanvas();
    }
}

void Widget::on_stop_clicked()
{
    killTimer(myTimerId);
    ui->stop->setEnabled(false);
    ui->play->setEnabled(true);
    ui->reverse->setEnabled(true);
    ui->end_modeling->setEnabled(true);
}

void Widget::on_play_clicked()
{
    this->direction_flag = true;
    ui->stop->setEnabled(true);
    ui->play->setEnabled(false);
    ui->reverse->setEnabled(false);
    ui->end_modeling->setEnabled(false);
    myTimerId = startTimer(int(double(100) / ui->speed->value()));
}

void Widget::exec_base_camera_rotations(ssize_t previousIndexCamera)
{
    ssize_t indexCamera = previousIndexCamera + 1;
    actions::CameraRotateAction action2(-angle * 9, 0, 0, indexCamera);
    actionController.executeAction(action2);

    actions::CameraShiftAction action3(0, 0, - 5 * this->offset, indexCamera);
    actionController.executeAction(action3);

    actions::CameraScaleAction action4(scaleCoeff * 1.5, scaleCoeff * 1.5, scaleCoeff * 1.5, indexCamera);
    actionController.executeAction(action4);
}

void Widget::on_AddBaseCamera_clicked()
{
    try
    {
        actions::CameraAddAction action;
        actionController.executeAction(action);

        exec_base_camera_rotations(ui->CameraBox->count() - 1);

        ui->CameraBox->addItem("Camera " + QString::number(ui->CameraBox->count()));
        ui->CameraBox->setCurrentIndex(ui->CameraBox->count() - 1);

    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}

void Widget::on_delete_model_clicked()
{
    try
    {
        if (model_index < 0) {return;}
        actions::ModelRemoveAction action(this->model_index);
        actionController.executeAction(action);

        this->model_index -= 1;

        ui->generate_new->setEnabled(true);
        ui->LoadButton->setEnabled(true);

        ui->delete_model->setEnabled(false);
        ui->save_new->setEnabled(false);

        ui->AddButton->setEnabled(false);
        ui->DeleteButton->setEnabled(false);
        ui->AddBaseCamera->setEnabled(false);

        this->updateCanvas();
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}

void Widget::on_end_modeling_clicked()
{
    for (int i = this->model_counts - 2; i >= 0; i--)
    {
        actions::ModelRemoveAction action(i);
        actionController.executeAction(action);
        this->model_index = 0;
    }

    ui->delete_model->setEnabled(true);
    ui->generate_growth->setEnabled(true);
    ui->play->setEnabled(false);
    ui->stop->setEnabled(false);
    ui->next->setEnabled(false);
    ui->previous->setEnabled(false);
    ui->end_modeling->setEnabled(false);
    ui->reverse->setEnabled(false);
    ui->speed->setEnabled(false);

    this->updateCanvas();
}

void Widget::on_font_color_clicked()
{
    this->font_color = QColorDialog::getColor();
    QString style = "background: rgb(%1, %2, %3);";
    ui->font_color->setStyleSheet(style.arg(font_color.red()).arg(font_color.green()).arg(font_color.blue()));
    this->updateCanvas();
}

void Widget::on_reverse_clicked()
{
    this->direction_flag = false;
    ui->stop->setEnabled(true);
    ui->play->setEnabled(false);
    ui->reverse->setEnabled(false);
    ui->end_modeling->setEnabled(false);
    myTimerId = startTimer(int(double(100) / ui->speed->value()));
}

void write_param(QFile &f, double par)
{
    char digits[100];
    strcpy(digits, to_string(par).c_str());
    f.write(digits);
}

void write_param(QFile &f, int par)
{
    char digits[100];
    strcpy(digits, to_string(par).c_str());
    f.write(digits);
}

double convert_rad_to_angle(double rad)
{
    return rad * 180 / M_PI;
}

void write_params(QFile &f, tree_params p)
{
    write_param(f, p.dot.x);
    f.write(" ");
    write_param(f, p.dot.y);
    f.write(" ");
    write_param(f, p.dot.z);
    f.write(" ");
    write_param(f, convert_rad_to_angle(p.angles.alpha));
    f.write(" ");
    write_param(f, convert_rad_to_angle(p.angles.alpha1));
    f.write(" ");
    write_param(f, convert_rad_to_angle(p.angles.alpha2));
    f.write(" ");
    write_param(f, p.koef.r_length);
    f.write(" ");
    write_param(f, p.koef.l_length);
    f.write(" ");
    write_param(f, p.koef.r_start);
    f.write(" ");
    write_param(f, p.koef.l_start);
    f.write(" ");
    write_param(f, p.body.length);
    f.write(" ");
    write_param(f, p.body.radius);
    f.write(" ");
    write_param(f, p.body.accuracy);
    f.write(" ");
    write_param(f, p.tree_clr.clr.red());
    f.write(" ");
    write_param(f, p.tree_clr.clr.green());
    f.write(" ");
    write_param(f, p.tree_clr.clr.blue());
}

void Widget::on_save_new_clicked()
{
    try
    {
        QString filePath = QFileDialog::getSaveFileName(this, "Save file", "/Users/ilalevuskin/Qt_projects/oleg/data/", \
                                                        "Wavefront (*.txt)");
        if (filePath.isEmpty())
        {
            QMessageBox::warning(this, "Error", "No file choosen");
            return;
        }

        QFile f(filePath);
        f.open(QIODevice::WriteOnly);
        write_params(f, params);
        f.close();
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}
