#include "widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setUpCanvas();
    ui->ModelBox->addItem("All models");
    k_rotate = 1;
    l_intensity = 1;
    l = {0,0,1};
    rotation_flag = Model_ID;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    try
    {
        ssize_t index = ui->ModelBox->currentIndex() - 1;
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
    /*this->canvas = new QGraphicsScene;
    canvas->setBackgroundBrush(Qt::white);
    canvas->setSceneRect(-350,-350,700,700);
    ui->Canvas->installEventFilter(this);
    ui->Canvas->setScene(canvas);*/

    this->canvas->installEventFilter(this);
    this->canvas->update();

    ui->AddButton->click();
}

void Widget::updateCanvas()
{
    //this->canvas->clear();
    ModelDrawer drawer(this->canvas, l, l_intensity);

    size_t index = size_t(ui->CameraBox->currentIndex());
    actions::ModelDrawAction action(drawer, index);
    actionController.executeAction(action);
}

void Widget::on_AddButton_clicked()
{
    try
    {
        actions::CameraAddAction action(0, 0, 0);
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
        QString filePath = QFileDialog::getOpenFileName(this, "Open model", "", \
                                                        "Wavefront (*.txt)");
        if (filePath.isEmpty())
        {
            QMessageBox::warning(this, "Error", "No file choosen");
            return;
        }

        actions::ModelUploadAction action(filePath.toStdString());
        actionController.executeAction(action);

        ui->ModelBox->addItem("Model " + QString::number(ui->ModelBox->count()));
        ui->ModelBox->setCurrentIndex(ui->ModelBox->count() - 1);

        this->updateCanvas();
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

/*create_tre(Settings *set)
{
    QMessageBox::warning(this, "Well done!", QString());
}*/

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
    actions::ModelUploadFromGenerateAction action(set->params);
    actionController.executeAction(action);

    ui->ModelBox->addItem("Model " + QString::number(ui->ModelBox->count()));
    ui->ModelBox->setCurrentIndex(ui->ModelBox->count() - 1);

    ssize_t indexCamera = ui->CameraBox->currentIndex();
    actions::CameraRotateAction action2(-angle * 9, 0, 0, indexCamera);
    actionController.executeAction(action2);

    actions::CameraShiftAction action3(0, 0, - 5 * this->offset, indexCamera);
    actionController.executeAction(action3);

    actions::CameraScaleAction action4(scaleCoeff * 1.5, scaleCoeff * 1.5, scaleCoeff * 1.5, indexCamera);
    actionController.executeAction(action4);

    this->updateCanvas();
}
