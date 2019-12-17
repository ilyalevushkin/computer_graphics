#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QMessageBox>
#include "tree_params.h"
#include "exceptions/baseException.h"
#include "exceptions/settingsException.h"
#include <math.h>


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

public:
    tree_params params;
    bool flag;

private:
    Ui::Settings *ui;
    QWidget *w;
};

#endif // SETTINGS_H
