/********************************************************************************
** Form generated from reading UI file 'novaconversa.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOVACONVERSA_H
#define UI_NOVACONVERSA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NovaConversa
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditUsuario;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NovaConversa)
    {
        if (NovaConversa->objectName().isEmpty())
            NovaConversa->setObjectName(QStringLiteral("NovaConversa"));
        NovaConversa->resize(282, 111);
        gridLayout = new QGridLayout(NovaConversa);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(NovaConversa);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEditUsuario = new QLineEdit(NovaConversa);
        lineEditUsuario->setObjectName(QStringLiteral("lineEditUsuario"));

        horizontalLayout->addWidget(lineEditUsuario);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(NovaConversa);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(NovaConversa);
        QObject::connect(buttonBox, SIGNAL(accepted()), NovaConversa, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NovaConversa, SLOT(reject()));

        QMetaObject::connectSlotsByName(NovaConversa);
    } // setupUi

    void retranslateUi(QDialog *NovaConversa)
    {
        NovaConversa->setWindowTitle(QApplication::translate("NovaConversa", "Dialog", 0));
        label->setText(QApplication::translate("NovaConversa", "Nome do usu\303\241rio:", 0));
    } // retranslateUi

};

namespace Ui {
    class NovaConversa: public Ui_NovaConversa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOVACONVERSA_H
