#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QMessageBox>
#include "tree_params.h"
#include "exceptions/baseException.h"
#include "exceptions/settingsException.h"
#include <math.h>

#include "explanations.h"

#include <QColorDialog>

enum Settings_ID {Dot_ID = 0, Length_ID = 1, Radius_ID = 2, Accuracy_ID = 3, Koef_ID = 4, Angle_ID = 5};


struct Range
{
    double from;
    double to;
};

class Check_settings
{
public:
    Check_settings() {
        dot.from = -300;
        dot.to = 300;

        length.from = 0;
        length.to = 300;

        radius.from = 0;
        radius.to = 100;

        accuracy.from = 0;
        accuracy.to = 100;

        koef.from = 0;
        koef.to = 10;

        angle.from = -360;
        angle.to = 360;
    }
    Check_settings(Range dot, Range length, Range radius, Range accuracy, Range koef, Range angle) {
        this->dot = dot;
        this->length = length;
        this->radius = radius;
        this->accuracy = accuracy;
        this->koef = koef;
        this->angle = angle;
    }
    ~Check_settings() = default;


    void Set_new_settings(Range dot, Range length, Range radius, Range accuracy, Range koef, Range angle)
    {
        this->dot = dot;
        this->length = length;
        this->radius = radius;
        this->accuracy = accuracy;
        this->koef = koef;
        this->angle = angle;
    }

    void Set_new_setting(Range setting, int choice)
    {
        switch (choice) {
        case Dot_ID:
        {
            this->dot = setting;
            break;
        }
        case Length_ID:
        {
            this->length = setting;
            break;
        }
        case Radius_ID:
        {
            this->radius = setting;
            break;
        }
        case Accuracy_ID:
        {
            this->accuracy = setting;
            break;
        }
        case Koef_ID:
        {
            this->koef = setting;
            break;
        }
        case Angle_ID:
        {
            this->angle = setting;
            break;
        }
        }
    }

     bool check_setting(QString setting, int choice);

private:

    bool checking(QString setting, Range param);
    bool convert_to_double(QString coord);

    Range dot;
    Range length;
    Range radius;
    Range accuracy;
    Range koef;
    Range angle;
};


namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

signals:
    void flagChanged(Settings*);

private slots:
    void on_Confirm_clicked();

    void on_Cancel_clicked();

    void fill_tree_params();

    void on_tree_color_clicked();

    void on_explanation_clicked();

public:
    tree_params params;
    bool flag;

private:
    Ui::Settings *ui;
    QWidget *w;
    QColor tree_color;
};

#endif // SETTINGS_H
