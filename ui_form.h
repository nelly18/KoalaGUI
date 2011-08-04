/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created: Wed 3. Aug 23:10:49 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QSpinBox *spinBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QListView *listView;
    QLabel *label;
    QSpinBox *spinBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QCheckBox *checkBox;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(490, 493);
        Form->setWindowOpacity(1);
        spinBox = new QSpinBox(Form);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(347, 59, 61, 20));
        spinBox->setMaximum(5);
        layoutWidget = new QWidget(Form);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 9, 294, 131));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 10, 0, 0);
        listView = new QListView(layoutWidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout_2->addWidget(listView, 0, 0, 1, 2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        spinBox_2 = new QSpinBox(layoutWidget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        gridLayout_2->addWidget(spinBox_2, 1, 1, 1, 1);

        gridLayout_2->setRowMinimumHeight(0, 1);
        gridLayout_2->setRowMinimumHeight(1, 50);
        radioButton = new QRadioButton(Form);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(360, 110, 82, 17));
        radioButton_2 = new QRadioButton(Form);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(360, 140, 82, 17));
        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(80, 270, 351, 80));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 331, 51));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 0, 4, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 0, 3, 1, 1);

        checkBox = new QCheckBox(Form);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);
        checkBox->setGeometry(QRect(80, 180, 70, 17));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form", "TextLabel", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("Form", "RadioButton", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("Form", "RadioButton", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Form", "GroupBox", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form", "TextLabel", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form", "PushButton", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form", "TextLabel", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("Form", "CheckBox", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
