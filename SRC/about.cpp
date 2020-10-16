#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setWindowTitle("About Dictionary");
}

about::~about()
{
    delete ui;
}

void about::on_word_count_line_textChanged(const QString &arg1)
{
    ui->word_count_line->setText(arg1);
}

void about::on_max_word_length_line_textChanged(const QString &arg1)
{
    ui->max_word_length_line->setText(arg1);
}

void about::on_max_word_line_textChanged(const QString &arg1)
{
    ui->max_word_line->setText(arg1);
}

void about::on_max_matches_line_textChanged(const QString &arg1)
{
    ui->max_matches_line->setText(arg1);
}

void about::on_matches_textEdit_textChanged(const QString &matches)
{
    ui->matches_textEdit->append(matches);
}
