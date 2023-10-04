/********************************************************************************
** Form generated from reading UI file 'login_form.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_FORM_H
#define UI_LOGIN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login_form
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *giorno;
    QComboBox *boxmesi;
    QSpinBox *anno;
    QSpacerItem *horizontalSpacer;
    QRadioButton *donna;
    QRadioButton *uomo;
    QPushButton *iscriviti;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *Nome;
    QLineEdit *Cognome;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *email2;
    QLineEdit *pwd2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *email;
    QPushButton *accedi;
    QLabel *pwdLabel;
    QLineEdit *pwd;
    QLabel *emailLabel;
    QPushButton *recuperopwd;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *login_form)
    {
        if (login_form->objectName().isEmpty())
            login_form->setObjectName(QString::fromUtf8("login_form"));
        login_form->resize(583, 398);
        centralWidget = new QWidget(login_form);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        giorno = new QSpinBox(centralWidget);
        giorno->setObjectName(QString::fromUtf8("giorno"));
        giorno->setMinimum(1);
        giorno->setMaximum(31);

        horizontalLayout_3->addWidget(giorno);

        boxmesi = new QComboBox(centralWidget);
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->addItem(QString());
        boxmesi->setObjectName(QString::fromUtf8("boxmesi"));

        horizontalLayout_3->addWidget(boxmesi);

        anno = new QSpinBox(centralWidget);
        anno->setObjectName(QString::fromUtf8("anno"));
        anno->setMinimum(1920);
        anno->setMaximum(2019);

        horizontalLayout_3->addWidget(anno);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        donna = new QRadioButton(centralWidget);
        donna->setObjectName(QString::fromUtf8("donna"));
        donna->setChecked(true);

        horizontalLayout_3->addWidget(donna);

        uomo = new QRadioButton(centralWidget);
        uomo->setObjectName(QString::fromUtf8("uomo"));

        horizontalLayout_3->addWidget(uomo);


        verticalLayout_2->addLayout(horizontalLayout_3);

        iscriviti = new QPushButton(centralWidget);
        iscriviti->setObjectName(QString::fromUtf8("iscriviti"));
        iscriviti->setStyleSheet(QString::fromUtf8("background-color: rgb(78, 154, 6);\n"
"color: rgb(238, 238, 236);"));

        verticalLayout_2->addWidget(iscriviti);


        gridLayout->addLayout(verticalLayout_2, 2, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Nome = new QLineEdit(centralWidget);
        Nome->setObjectName(QString::fromUtf8("Nome"));

        horizontalLayout_2->addWidget(Nome);

        Cognome = new QLineEdit(centralWidget);
        Cognome->setObjectName(QString::fromUtf8("Cognome"));

        horizontalLayout_2->addWidget(Cognome);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        email2 = new QLineEdit(centralWidget);
        email2->setObjectName(QString::fromUtf8("email2"));

        verticalLayout_3->addWidget(email2);

        pwd2 = new QLineEdit(centralWidget);
        pwd2->setObjectName(QString::fromUtf8("pwd2"));

        verticalLayout_3->addWidget(pwd2);


        verticalLayout->addLayout(verticalLayout_3);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 74, 135);"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        email = new QLineEdit(widget);
        email->setObjectName(QString::fromUtf8("email"));
        email->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));

        gridLayout_2->addWidget(email, 1, 0, 1, 1);

        accedi = new QPushButton(widget);
        accedi->setObjectName(QString::fromUtf8("accedi"));
        accedi->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 101, 164);\n"
"color: rgb(238, 238, 236);"));

        gridLayout_2->addWidget(accedi, 1, 2, 1, 1);

        pwdLabel = new QLabel(widget);
        pwdLabel->setObjectName(QString::fromUtf8("pwdLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pwdLabel->sizePolicy().hasHeightForWidth());
        pwdLabel->setSizePolicy(sizePolicy);
        pwdLabel->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout_2->addWidget(pwdLabel, 0, 1, 1, 1);

        pwd = new QLineEdit(widget);
        pwd->setObjectName(QString::fromUtf8("pwd"));
        pwd->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));

        gridLayout_2->addWidget(pwd, 1, 1, 1, 1);

        emailLabel = new QLabel(widget);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
        sizePolicy.setHeightForWidth(emailLabel->sizePolicy().hasHeightForWidth());
        emailLabel->setSizePolicy(sizePolicy);
        emailLabel->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        gridLayout_2->addWidget(emailLabel, 0, 0, 1, 1);

        recuperopwd = new QPushButton(widget);
        recuperopwd->setObjectName(QString::fromUtf8("recuperopwd"));
        recuperopwd->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        recuperopwd->setFlat(true);

        gridLayout_2->addWidget(recuperopwd, 2, 0, 1, 2);


        horizontalLayout->addLayout(gridLayout_2);


        gridLayout->addWidget(widget, 0, 1, 1, 1);

        login_form->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(login_form);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 583, 22));
        login_form->setMenuBar(menuBar);
        mainToolBar = new QToolBar(login_form);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        login_form->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(login_form);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        login_form->setStatusBar(statusBar);

        retranslateUi(login_form);

        QMetaObject::connectSlotsByName(login_form);
    } // setupUi

    void retranslateUi(QMainWindow *login_form)
    {
        login_form->setWindowTitle(QCoreApplication::translate("login_form", "login_form", nullptr));
        boxmesi->setItemText(0, QCoreApplication::translate("login_form", "Gennaio", nullptr));
        boxmesi->setItemText(1, QCoreApplication::translate("login_form", "Febbraio", nullptr));
        boxmesi->setItemText(2, QCoreApplication::translate("login_form", "Marzo", nullptr));
        boxmesi->setItemText(3, QCoreApplication::translate("login_form", "Aprile", nullptr));
        boxmesi->setItemText(4, QCoreApplication::translate("login_form", "Maggio", nullptr));
        boxmesi->setItemText(5, QCoreApplication::translate("login_form", "Giugno", nullptr));
        boxmesi->setItemText(6, QCoreApplication::translate("login_form", "Luglio", nullptr));
        boxmesi->setItemText(7, QCoreApplication::translate("login_form", "Agosto", nullptr));
        boxmesi->setItemText(8, QCoreApplication::translate("login_form", "Settembre", nullptr));
        boxmesi->setItemText(9, QCoreApplication::translate("login_form", "Ottobre", nullptr));
        boxmesi->setItemText(10, QCoreApplication::translate("login_form", "Novembre", nullptr));
        boxmesi->setItemText(11, QCoreApplication::translate("login_form", "Dicembre", nullptr));

        donna->setText(QCoreApplication::translate("login_form", "Donna", nullptr));
        uomo->setText(QCoreApplication::translate("login_form", "Uomo", nullptr));
        iscriviti->setText(QCoreApplication::translate("login_form", "Iscriviti", nullptr));
        Nome->setPlaceholderText(QCoreApplication::translate("login_form", "Nome", nullptr));
        Cognome->setPlaceholderText(QCoreApplication::translate("login_form", "Cognome", nullptr));
        email2->setPlaceholderText(QCoreApplication::translate("login_form", "Numero di cellulare o e-mail", nullptr));
        pwd2->setPlaceholderText(QCoreApplication::translate("login_form", "Nuova password", nullptr));
        accedi->setText(QCoreApplication::translate("login_form", "Accedi", nullptr));
        pwdLabel->setText(QCoreApplication::translate("login_form", "Password", nullptr));
        emailLabel->setText(QCoreApplication::translate("login_form", "E-mail o telefono", nullptr));
        recuperopwd->setText(QCoreApplication::translate("login_form", "Non ricordi pi\303\271 come accedere all'account?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login_form: public Ui_login_form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_FORM_H
