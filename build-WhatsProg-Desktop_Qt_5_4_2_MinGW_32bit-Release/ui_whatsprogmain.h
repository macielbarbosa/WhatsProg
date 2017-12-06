/********************************************************************************
** Form generated from reading UI file 'whatsprogmain.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHATSPROGMAIN_H
#define UI_WHATSPROGMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WhatsProgMain
{
public:
    QAction *actionNovo;
    QAction *actionConectar;
    QAction *actionDesconectar;
    QAction *actionTrocar_senha;
    QAction *actionSair;
    QAction *actionNova_conversa;
    QAction *actionRemover_conversa;
    QAction *actionApagar_mensagens;
    QAction *actionWhatsProg;
    QAction *actionQt_Creator;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *labelConversas;
    QTableView *tableViewConversas;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelMensagens;
    QTableView *tableViewMensagens;
    QLabel *labelMensagem;
    QLineEdit *lineEditMensagem;
    QMenuBar *menuBar;
    QMenu *menuUsu_rio;
    QMenu *menuConversa;
    QMenu *menuMensagens;
    QMenu *menuSobre;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WhatsProgMain)
    {
        if (WhatsProgMain->objectName().isEmpty())
            WhatsProgMain->setObjectName(QStringLiteral("WhatsProgMain"));
        WhatsProgMain->resize(900, 700);
        actionNovo = new QAction(WhatsProgMain);
        actionNovo->setObjectName(QStringLiteral("actionNovo"));
        actionConectar = new QAction(WhatsProgMain);
        actionConectar->setObjectName(QStringLiteral("actionConectar"));
        actionDesconectar = new QAction(WhatsProgMain);
        actionDesconectar->setObjectName(QStringLiteral("actionDesconectar"));
        actionDesconectar->setEnabled(false);
        actionTrocar_senha = new QAction(WhatsProgMain);
        actionTrocar_senha->setObjectName(QStringLiteral("actionTrocar_senha"));
        actionSair = new QAction(WhatsProgMain);
        actionSair->setObjectName(QStringLiteral("actionSair"));
        actionSair->setEnabled(true);
        actionNova_conversa = new QAction(WhatsProgMain);
        actionNova_conversa->setObjectName(QStringLiteral("actionNova_conversa"));
        actionNova_conversa->setEnabled(false);
        actionRemover_conversa = new QAction(WhatsProgMain);
        actionRemover_conversa->setObjectName(QStringLiteral("actionRemover_conversa"));
        actionRemover_conversa->setEnabled(false);
        actionApagar_mensagens = new QAction(WhatsProgMain);
        actionApagar_mensagens->setObjectName(QStringLiteral("actionApagar_mensagens"));
        actionApagar_mensagens->setEnabled(false);
        actionWhatsProg = new QAction(WhatsProgMain);
        actionWhatsProg->setObjectName(QStringLiteral("actionWhatsProg"));
        actionQt_Creator = new QAction(WhatsProgMain);
        actionQt_Creator->setObjectName(QStringLiteral("actionQt_Creator"));
        centralWidget = new QWidget(WhatsProgMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelConversas = new QLabel(centralWidget);
        labelConversas->setObjectName(QStringLiteral("labelConversas"));
        labelConversas->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelConversas);

        tableViewConversas = new QTableView(centralWidget);
        tableViewConversas->setObjectName(QStringLiteral("tableViewConversas"));

        verticalLayout->addWidget(tableViewConversas);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelMensagens = new QLabel(centralWidget);
        labelMensagens->setObjectName(QStringLiteral("labelMensagens"));
        labelMensagens->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(labelMensagens);

        tableViewMensagens = new QTableView(centralWidget);
        tableViewMensagens->setObjectName(QStringLiteral("tableViewMensagens"));

        verticalLayout_2->addWidget(tableViewMensagens);


        gridLayout->addLayout(verticalLayout_2, 0, 2, 1, 1);

        labelMensagem = new QLabel(centralWidget);
        labelMensagem->setObjectName(QStringLiteral("labelMensagem"));

        gridLayout->addWidget(labelMensagem, 1, 0, 1, 1);

        lineEditMensagem = new QLineEdit(centralWidget);
        lineEditMensagem->setObjectName(QStringLiteral("lineEditMensagem"));

        gridLayout->addWidget(lineEditMensagem, 1, 1, 1, 2);

        WhatsProgMain->setCentralWidget(centralWidget);
        labelMensagem->raise();
        lineEditMensagem->raise();
        menuBar = new QMenuBar(WhatsProgMain);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 21));
        menuUsu_rio = new QMenu(menuBar);
        menuUsu_rio->setObjectName(QStringLiteral("menuUsu_rio"));
        menuConversa = new QMenu(menuBar);
        menuConversa->setObjectName(QStringLiteral("menuConversa"));
        menuMensagens = new QMenu(menuBar);
        menuMensagens->setObjectName(QStringLiteral("menuMensagens"));
        menuSobre = new QMenu(menuBar);
        menuSobre->setObjectName(QStringLiteral("menuSobre"));
        WhatsProgMain->setMenuBar(menuBar);
        statusBar = new QStatusBar(WhatsProgMain);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WhatsProgMain->setStatusBar(statusBar);

        menuBar->addAction(menuUsu_rio->menuAction());
        menuBar->addAction(menuConversa->menuAction());
        menuBar->addAction(menuMensagens->menuAction());
        menuBar->addAction(menuSobre->menuAction());
        menuUsu_rio->addAction(actionNovo);
        menuUsu_rio->addAction(actionConectar);
        menuUsu_rio->addAction(actionDesconectar);
        menuUsu_rio->addSeparator();
        menuUsu_rio->addAction(actionSair);
        menuConversa->addAction(actionNova_conversa);
        menuConversa->addAction(actionRemover_conversa);
        menuMensagens->addAction(actionApagar_mensagens);
        menuSobre->addAction(actionWhatsProg);
        menuSobre->addAction(actionQt_Creator);

        retranslateUi(WhatsProgMain);

        QMetaObject::connectSlotsByName(WhatsProgMain);
    } // setupUi

    void retranslateUi(QMainWindow *WhatsProgMain)
    {
        WhatsProgMain->setWindowTitle(QApplication::translate("WhatsProgMain", "Mensageiro", 0));
        actionNovo->setText(QApplication::translate("WhatsProgMain", "Novo ...", 0));
        actionConectar->setText(QApplication::translate("WhatsProgMain", "Conectar ...", 0));
        actionDesconectar->setText(QApplication::translate("WhatsProgMain", "Desconectar", 0));
        actionTrocar_senha->setText(QApplication::translate("WhatsProgMain", "Trocar senha ...", 0));
        actionSair->setText(QApplication::translate("WhatsProgMain", "Sair", 0));
        actionNova_conversa->setText(QApplication::translate("WhatsProgMain", "Nova conversa ...", 0));
        actionRemover_conversa->setText(QApplication::translate("WhatsProgMain", "Remover conversa", 0));
        actionApagar_mensagens->setText(QApplication::translate("WhatsProgMain", "Apagar mensagens", 0));
        actionWhatsProg->setText(QApplication::translate("WhatsProgMain", "WhatsProg", 0));
        actionQt_Creator->setText(QApplication::translate("WhatsProgMain", "Qt Creator", 0));
        labelConversas->setText(QApplication::translate("WhatsProgMain", "CONVERSAS", 0));
        labelMensagens->setText(QApplication::translate("WhatsProgMain", "MENSAGENS", 0));
        labelMensagem->setText(QApplication::translate("WhatsProgMain", "Mensagem:", 0));
        menuUsu_rio->setTitle(QApplication::translate("WhatsProgMain", "Usu\303\241rio", 0));
        menuConversa->setTitle(QApplication::translate("WhatsProgMain", "Conversas", 0));
        menuMensagens->setTitle(QApplication::translate("WhatsProgMain", "Mensagens", 0));
        menuSobre->setTitle(QApplication::translate("WhatsProgMain", "Sobre", 0));
    } // retranslateUi

};

namespace Ui {
    class WhatsProgMain: public Ui_WhatsProgMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHATSPROGMAIN_H
