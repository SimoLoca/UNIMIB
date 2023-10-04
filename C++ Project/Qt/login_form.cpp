#include "login_form.h"
#include "ui_login_form.h"

#include <fstream>
#include <regex>

login_form::login_form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login_form)
{
    ui->setupUi(this);
}

login_form::~login_form()
{
    delete ui;
}

void login_form::on_accedi_clicked()
{
    QString mailtel = ui->email->text();
    QString pwd = ui->pwd->text();
    QTableView *view = new QTableView();

    if (mailtel=="admin@pas.com" && pwd=="admin") {
        QStandardItemModel *model = new QStandardItemModel;
        QFile file("database.csv");
        if (file.open(QIODevice::ReadOnly)) {
            int lineindex = 0;
            QTextStream in(&file);
            while (!in.atEnd()) {
                // legge una riga separata da \n
                QString fileLine = in.readLine();
                // separa la riga in token con ; come separatore
                QStringList lineToken = fileLine.split(";", QString::SkipEmptyParts);
                // carica dati in model
                for (int j = 0; j < lineToken.size(); j++) {
                    QString value = lineToken.at(j);
                    QStandardItem *item = new QStandardItem(value);
                    model->setItem(lineindex, j, item);
                }
                lineindex++;
            }
            file.close();
        }
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nome"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cognome"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email/Tel"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Pwd"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("M"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("F"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Giorno"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Mese"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Anno"));
        view->setModel(model);
        view->show();
    } else {
        QFile f("database.csv");
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in(&f);
        while(!in.atEnd()){
            int i = 0;
            QString l = f.readLine();
            QList<QString> ls = l.split(';');
            while (i<ls.length()){
                if (ls.at(i)==mailtel) {
                    if (ls.at(3)==pwd){
                        QMessageBox msgBox;
                        msgBox.setText("Accesso riuscito");
                        msgBox.exec();
                    } else {
                        QMessageBox msgBox;
                        msgBox.setText("Accesso negato");
                        msgBox.exec();
                    }
                }
                i++;
            }
        }
        f.close();
    }
}

// come scelta implementativa il recupero pwd viene fatto solo controllando l'esistenza della mail
void login_form::on_recuperopwd_clicked()
{
    bool bmail = false;
    QString mailtel = ui->email->text();
    QFile f("database.csv");
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&f);
    while(!in.atEnd()){
        int i = 0;
        QString l = f.readLine();
        QList<QString> ls = l.split(';');
        while (i<ls.length()){
            if (ls.at(i)==mailtel)
                bmail=true;
            i++;
        }
    }
    if (bmail == true) {
        QMessageBox msgBox;
        msgBox.setText("e-mail con procedura di ripristino inviata");
        msgBox.exec();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Utente non trovato, procedura di recupero fallita");
        msgBox.exec();
    }
    f.close();

}

void login_form::on_iscriviti_clicked()
{
    crea_file();
    bool presente = false;
    std::string nome = ui->Nome->text().toStdString();
    std::string cognome = ui->Cognome->text().toStdString();
    std::string email = ui->email2->text().toStdString();
    std::string pwd = ui->pwd2->text().toStdString();
    bool maschio = ui->uomo->isChecked();
    bool femmina = ui->donna->isChecked();
    int giorno = ui->giorno->value();
    std::string mese = ui->boxmesi->currentText().toStdString();
    int anno = ui->anno->value();

    if (nome=="" || cognome=="" || email=="" || pwd=="") {
        QMessageBox::warning(this, "Attenzione", "Iscrizione negata, nessun dato inserito");
    } else {
        if(!controlloEmailTel(email) || (mese=="Febbraio" && giorno>28) || ((mese=="Aprile" || mese=="Maggio" || mese == "Settembre" || mese =="Novembre")  && giorno>30)) {
            QMessageBox::warning(this, "Attenzione", "Formato non valido!");
        } else {
            QString emm = ui->email2->text();
            QFile f("database.csv");
            if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QTextStream in(&f);
            while(!in.atEnd()){
                int i = 0;
                QString l = f.readLine();
                QList<QString> ls = l.split(';');
                while (i<ls.length()){
                    if (ls.at(i)==emm)
                        presente=true;
                    i++;
                }
            }
            f.close();

            if (presente == true) {
                QMessageBox::warning(this, "Attenzione", "utente presente");
            } else {
                std::ofstream of;
                of.open("database.csv", std::ios::app);
                of <<nome<<";"<<cognome<<";"<<email<< ";"<<pwd<<";"<<maschio<<";"<<femmina<<";"<<giorno<<";"<<mese<<";"<<anno<<std::endl;
                of.close();
                QMessageBox msgBox;
                msgBox.setText("Registrazione avvenuta");
                msgBox.exec();
            }
        }
    }
}

void login_form::crea_file() {
    std::ofstream of;
    of.open("database.csv", std::ios::app);
}

bool login_form::controlloEmailTel(std::string m) {
    const std::regex pattern("^[_a-z0-9-]+(.[_a-z0-9-]+)*@[a-z0-9-]+(.[a-z0-9-]+)*(.[a-z]{2,4})$");
    const std::regex pattern2("^[0-9]{10}$");

    bool x = std::regex_match(m, pattern);
    bool x2 = std::regex_match(m, pattern2);

    if (x==1){
        return x;
    } else if(x2==1){
        return x2;
    } else {
        return false;
    }
}
