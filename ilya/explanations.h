#ifndef EXPLANATIONS_H
#define EXPLANATIONS_H

#include <QWidget>

namespace Ui {
class Explanations;
}

class Explanations : public QWidget
{
    Q_OBJECT

public:
    explicit Explanations(QWidget *parent = nullptr);
    ~Explanations();

private slots:
    void on_back_clicked();

private:
    Ui::Explanations *ui;
    QWidget *w;
};

#endif // EXPLANATIONS_H
