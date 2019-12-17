#include "settings.h"
#include "ui_settings.h"
#include <iostream>

Settings::Settings(QWidget *parent) :
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    w = parent;
    flag = false;
}

Settings::~Settings()
{
    delete ui;
}

bool convert_to_double(QString coord)
{
    bool ok;
    coord.toDouble(&ok);
    return ok;
}

bool check_dot(QString coord)
{
    if (convert_to_double(coord))
    {
        double number = coord.toDouble();
        if (number > 300 || number < -300)
        {
            return false;
        }
        return true;
    }
    return false;
}

bool check_length(QString length)
{
    if (convert_to_double(length))
    {
        double number = length.toDouble();
        if (number > 300 || number <= 0)
        {
            return false;
        }
        return true;
    }
    return false;
}

bool check_koef(QString koef)
{
    if (convert_to_double(koef))
    {
        double number = koef.toDouble();
        if (number > 10 || number <= 0)
        {
            return false;
        }
        return true;
    }
    return false;
}

bool check_angle(QString angle)
{
    if (convert_to_double(angle))
    {
        double number = angle.toDouble();
        if (number > 360 || number < -360)
        {
            return false;
        }
        return true;
    }
    return false;
}


double convert_to_rad(double alpha)
{
    return M_PI * alpha / 180;
}


void Settings::fill_tree_params()
{
    QString x,y,z,length,r_length,l_length,r_start,l_start,alpha,alpha1,alpha2;
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
    try
    {
        if (check_dot(x) && check_dot(y) && check_dot(z))
        {
            tree_params fill_params;
            fill_params.dot.x = x.toDouble();
            fill_params.dot.y = x.toDouble();
            fill_params.dot.z = x.toDouble();
            if (check_length(length))
            {
                fill_params.body_length.length = length.toDouble();
                if (check_koef(r_length) && check_koef(l_length) && check_koef(r_start) && check_koef(l_start))
                {
                    fill_params.koef.r_length = r_length.toDouble();
                    fill_params.koef.l_length = l_length.toDouble();
                    fill_params.koef.r_start = r_start.toDouble();
                    fill_params.koef.l_start = l_start.toDouble();
                    if (check_angle(alpha) && check_angle(alpha1) && check_angle(alpha2))
                    {
                        fill_params.angles.alpha = convert_to_rad(alpha.toDouble());
                        fill_params.angles.alpha1 = convert_to_rad(alpha1.toDouble());
                        fill_params.angles.alpha2 = convert_to_rad(alpha2.toDouble());
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
