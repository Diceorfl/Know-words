#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();

public slots:
    void on_word_count_line_textChanged(const QString &arg1);

    void on_max_word_length_line_textChanged(const QString &arg1);

    void on_max_word_line_textChanged(const QString &arg1);

    void on_max_matches_line_textChanged(const QString &arg1);

public:
    void on_matches_textEdit_textChanged(const QString &matches);

private:
    Ui::about *ui;
};

#endif // ABOUT_H
