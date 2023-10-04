#ifndef LOGIN_FORM_H
#define LOGIN_FORM_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QList>
#include <QDialog>
#include <QComboBox>
#include <QFileInfo>
#include <QTableView>
#include <QStandardItemModel>

namespace Ui {
class login_form;
}

class login_form : public QMainWindow
{
    Q_OBJECT

public:
    explicit login_form(QWidget *parent = nullptr);
    ~login_form();
    bool controlloEmailTel(std::string);
    void crea_file();

private slots:
    void on_accedi_clicked();

    void on_recuperopwd_clicked();

    void on_iscriviti_clicked();

private:
    Ui::login_form *ui;
};

#endif // LOGIN_FORM_H
