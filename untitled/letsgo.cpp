#include "letsgo.h"
#include "ui_letsgo.h"

Letsgo::Letsgo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Letsgo)
{
    ui->setupUi(this);
}

Letsgo::~Letsgo()
{
    delete ui;
}

void Letsgo::on_pushButton_clicked()
{
    this->accept();
}

