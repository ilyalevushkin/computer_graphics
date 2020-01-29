#include "explanations.h"
#include "ui_explanations.h"

Explanations::Explanations(QWidget *parent) :
    ui(new Ui::Explanations)
{
    ui->setupUi(this);
    w = parent;
}

Explanations::~Explanations()
{
    delete ui;
}

void Explanations::on_back_clicked()
{
    w->setEnabled(true);
    this->close();
}
