/********************************************************************************
** Form generated from reading UI file 'letsgo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LETSGO_H
#define UI_LETSGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Letsgo
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *Letsgo)
    {
        if (Letsgo->objectName().isEmpty())
            Letsgo->setObjectName(QString::fromUtf8("Letsgo"));
        Letsgo->resize(961, 545);
        Letsgo->setMinimumSize(QSize(961, 0));
        Letsgo->setSizeGripEnabled(false);
        pushButton = new QPushButton(Letsgo);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(400, 240, 93, 28));
        pushButton->setMinimumSize(QSize(93, 0));
        pushButton->setIconSize(QSize(172, 64));

        retranslateUi(Letsgo);

        QMetaObject::connectSlotsByName(Letsgo);
    } // setupUi

    void retranslateUi(QDialog *Letsgo)
    {
        Letsgo->setWindowTitle(QApplication::translate("Letsgo", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("Letsgo", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Letsgo: public Ui_Letsgo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LETSGO_H
