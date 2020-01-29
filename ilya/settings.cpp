#include "settings.h"
#include "ui_settings.h"
#include <iostream>

Settings::Settings(QWidget *parent) :
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    w = parent;
    flag = false;
    tree_color.setRgb(255,0,0);
    QString style = "background: rgb(%1, %2, %3);";
    ui->tree_color->setStyleSheet(style.arg(tree_color.red()).arg(tree_color.green()).arg(tree_color.blue()));
}

Settings::~Settings()
{
    delete ui;
}

bool Check_settings::convert_to_double(QString coord)
{
    bool ok;
    coord.toDouble(&ok);
    return ok;
}


bool Check_settings::checking(QString setting, Range param)
{
    if (convert_to_double(setting))
    {
        double number = setting.toDouble();
        if (number > param.to || number < param.from)
        {
            return false;
        }
        return true;
    }
    return false;
}

bool Check_settings::check_setting(QString setting, int choice)
{
    switch (choice) {
    case Dot_ID:
    {
        return checking(setting, this->dot);
    }
    case Length_ID:
    {
        return checking(setting, this->length);
    }
    case Radius_ID:
    {
        return checking(setting, this->radius);
    }
    case Accuracy_ID:
    {
        return checking(setting, this->accuracy);
    }
    case Koef_ID:
    {
        return checking(setting, this->koef);
    }
    case Angle_ID:
    {
        return checking(setting, this->angle);
    }
    default:
    {
        return false;
    }
    }
}


double convert_to_rad(double alpha)
{
    return M_PI * alpha / 180;
}


void Settings::fill_tree_params()
{
    QString x,y,z,length,r_length,l_length,r_start,l_start,alpha,alpha1,alpha2, radius, accuracy;
    x = ui->edt_dot_x->text();
    y = ui->edt_dot_y->text();
    z = ui->edt_dot_z->text();
    length = ui->edt_length->text();
    r_length = ui->edt_k->text();
    l_length = ui->edt_l->text();
    r_start = ui->edt_r_start->text();
    l_start = ui->edt_l_start->text();
    alpha = ui->edt_alpha->text();
    alpha1 = ui->edt_alpha1->text();
    alpha2 = ui->edt_alpha2->text();
    radius = ui->edt_radius->text();
    accuracy = ui->edt_accuracy->text();

    Check_settings check;
    tree_params fill_params;

    try
    {
        if (check.check_setting(x, Dot_ID) && check.check_setting(y, Dot_ID) && check.check_setting(z, Dot_ID))
        {
            if (check.check_setting(length, Length_ID))
            {
                if (check.check_setting(radius, Radius_ID))
                {
                    if (check.check_setting(accuracy, Accuracy_ID))
                    {
                        if (check.check_setting(r_length, Koef_ID) &&
                                check.check_setting(l_length, Koef_ID) &&
                                check.check_setting(r_start, Koef_ID) &&
                                check.check_setting(l_start, Koef_ID))
                        {

                            if (check.check_setting(alpha, Angle_ID) &&
                                    check.check_setting(alpha1, Angle_ID) &&
                                    check.check_setting(alpha2, Angle_ID))
                            {
                                fill_params.dot.x = x.toDouble();
                                fill_params.dot.y = x.toDouble();
                                fill_params.dot.z = x.toDouble();

                                fill_params.body.length = length.toDouble();

                                fill_params.body.radius = radius.toDouble();

                                fill_params.body.accuracy = accuracy.toDouble();

                                fill_params.koef.r_length = r_length.toDouble();
                                fill_params.koef.l_length = l_length.toDouble();
                                fill_params.koef.r_start = r_start.toDouble();
                                fill_params.koef.l_start = l_start.toDouble();

                                fill_params.angles.alpha = convert_to_rad(alpha.toDouble());
                                fill_params.angles.alpha1 = convert_to_rad(alpha1.toDouble());
                                fill_params.angles.alpha2 = convert_to_rad(alpha2.toDouble());
                                fill_params.tree_clr.clr = this->tree_color;
                                params = fill_params;
                                emit flagChanged(this);
                            }
                            else
                            {
                                throw settingsException("Mistake in angle input");
                            }
                        }
                        else
                        {
                            throw settingsException("Mistake in koef input");
                        }
                    }
                    else
                    {
                        throw settingsException("Mistake in accuracy input");
                    }
                }
                else
                {
                    throw settingsException("Mistake in radius input");
                }
            }
            else
            {
                throw settingsException("Mistake in length of tree input");
            }
        }
        else
        {
            throw settingsException("Mistake in start_dot input");
        }
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}

void Settings::on_Confirm_clicked()
{
    w->setEnabled(true);
    fill_tree_params();
    this->close();
}

void Settings::on_Cancel_clicked()
{
    w->setEnabled(true);
    this->close();
}

void Settings::on_tree_color_clicked()
{
    this->tree_color = QColorDialog::getColor();

    QString style = "background: rgb(%1, %2, %3);";
    ui->tree_color->setStyleSheet(style.arg(tree_color.red()).arg(tree_color.green()).arg(tree_color.blue()));
}

void Settings::on_explanation_clicked()
{
    try
    {
        Explanations *exp = new Explanations(this);
        exp->show();

        this->setEnabled(false);
    }
    catch (BaseException& e)
    {
        QMessageBox::warning(this, "Error", QString(e.what()));
    }
}
