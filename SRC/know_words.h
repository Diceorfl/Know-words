#ifndef KNOW_WORDS_H
#define KNOW_WORDS_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMap>
#include <QRandomGenerator>
#include "about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class know_words; }
QT_END_NAMESPACE

class know_words : public QMainWindow
{
    Q_OBJECT

public:
    know_words(QWidget *parent = nullptr);
    ~know_words();

private slots:
    void on_add_dictionary_button_clicked();

    void on_search_button_clicked();

    void on_sort_button_clicked();

    void on_random_button_clicked();

    void on_font_size_spinBox_valueChanged();

    void on_about_dictionary_button_clicked();

private:
    Ui::know_words *ui;
    QMap<QString,QString> Dict;
    QString maxword;
    QString max_matches_word;
    about *windowabout;
    bool close_flag = false;

    void set_button_status(bool);
    void set_dictionary_status(QString);
    void read_dictionary(QString);
    void lengthiest_word();
    void maximum_matches();
    void clear();
    QString search(QString);
};
#endif // KNOW_WORDS_H
