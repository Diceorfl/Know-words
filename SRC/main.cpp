#include "know_words.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    know_words w;
    w.show();
    return a.exec();
}
