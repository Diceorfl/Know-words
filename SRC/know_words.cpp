#include "know_words.h"
#include "ui_know_words.h"

know_words::know_words(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::know_words)
{
    ui->setupUi(this);
    ui->search_button->setEnabled(false);
    ui->random_button->setEnabled(false);
    ui->about_dictionary_button->setEnabled(false);
    ui->dictionary_status_label->setText("No Dictionary");
    ui->font_size_spinBox->setValue(40);
}

know_words::~know_words()
{
    delete ui;
}

//Finding words that have a given look after sorting
QString know_words::search(QString str)
{
    QStringList similar_words;
    for(auto word:Dict.keys())
        if(str == Dict[word])
            similar_words.push_back(word);
    return similar_words.join('\n');
}

void know_words::clear()
{
    Dict.clear();
    max_matches_word = "";
    maxword = "";
}


//The function checks the added file
void know_words::on_add_dictionary_button_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr,"","*.txt","");
    QFile dictionary(path);
    if(path.isEmpty()) return;
    if(!dictionary.exists() || !dictionary.open(QIODevice::ReadOnly))
    {
        set_button_status(false);
        set_dictionary_status("");
        return;
    }
    clear();
    set_dictionary_status(dictionary.fileName());
    dictionary.close();
    read_dictionary(path);
    set_button_status(true);
}


//The function set true if the dictionary is loaded else false
void know_words::set_button_status(bool flag)
{
    ui->search_button->setEnabled(flag);
    ui->random_button->setEnabled(flag);
    ui->about_dictionary_button->setEnabled(flag);
}

//The function set "dictionary name" if the dictionary is loaded else "No Dictionary"
void know_words::set_dictionary_status(QString dictionary_name)
{
    if(dictionary_name.isEmpty())
    {
        ui->dictionary_status_label->setText("No Dictionary");
        return;
    }
    QFileInfo dict_info(dictionary_name);
    ui->dictionary_status_label->setText("Dictionary " + dict_info.baseName().toUpper());
}

//The function read a file with a dictionary and
//get information like lengthiest word and maximum matches
void know_words::read_dictionary(QString path)
{
    QFile dictionary(path);
    dictionary.open(QIODevice::ReadOnly);
    QTextStream stream(&dictionary);
    while(!stream.atEnd())
    {
        QString key = stream.readLine();
        QString value = key;
        std::sort(value.begin(),value.end());
        Dict.insert(key,value); //stores a word and its sorted variant
    }
    dictionary.close();
    lengthiest_word();
    maximum_matches();
}

//Search function for the lengthiest word in the dictionary
void know_words::lengthiest_word()
{
    for(auto word: Dict.keys())
        if(word.size() > maxword.size())
            maxword = word;
}

//Search function for the word
//with the maximum number of matches in a sorted form
void know_words::maximum_matches()
{
    QList<QString> val = Dict.values();
    std::sort(val.begin(),val.end());
    int counter = 1;
    int maxcount = counter;
    for(int i = 0; i < val.size() - 1; ++i)
    {
        if(val[i] == val[i+1])
        {
            counter++;
            continue;
        }
        if(counter > maxcount)
        {
            maxcount = counter;
            max_matches_word = val[i];
        }
        counter = 1;
    }
}

//Finding a word from the input and outputting it
void know_words::on_search_button_clicked()
{
    ui->output_text_edit->clear();
    QString str = ui->input_text_edit->toPlainText();
    std::sort(str.begin(),str.end());
    ui->output_text_edit->append(search(str));
}

//Sorting the word entered by the user
void know_words::on_sort_button_clicked()
{
    ui->output_text_edit->clear();
    QString str = ui->input_text_edit->toPlainText();
    std::sort(str.begin(),str.end());
    ui->input_text_edit->setText(str);
}

//A random word from the dictionary in sorted form
void know_words::on_random_button_clicked()
{
    ui->output_text_edit->clear();
    int n = QRandomGenerator::global()->bounded(Dict.size());
    ui->input_text_edit->setText(Dict[Dict.keys()[n]]);
}

//Font size in input and output
void know_words::on_font_size_spinBox_valueChanged()
{
    QFont font;
    font.setPointSize((ui->font_size_spinBox->text()).toInt());
    ui->input_text_edit->setFont(font);
    ui->output_text_edit->setFont(font);
}

//Showing info about dictionary in a special window
void know_words::on_about_dictionary_button_clicked()
{
    if(close_flag)
    {
        windowabout->close();
        close_flag = false;
    }
    close_flag = true;
    windowabout = new about(this);
    windowabout->on_word_count_line_textChanged(QString::number(Dict.size()));
    windowabout->on_max_word_length_line_textChanged(QString::number(maxword.size()));
    windowabout->on_max_word_line_textChanged(maxword);
    QString words = search(max_matches_word);
    windowabout->on_max_matches_line_textChanged(QString::number(words.split('\n').size()));
    windowabout->on_matches_textEdit_textChanged(words);
    windowabout->show();
}
