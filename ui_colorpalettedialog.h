/********************************************************************************
** Form generated from reading UI file 'colorpalettedialog.ui'
**
** Created: Fri 29. Jul 12:00:26 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORPALETTEDIALOG_H
#define UI_COLORPALETTEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ColorPaletteDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *blue;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *black;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *ColorPaletteDialog)
    {
        if (ColorPaletteDialog->objectName().isEmpty())
            ColorPaletteDialog->setObjectName(QString::fromUtf8("ColorPaletteDialog"));
        ColorPaletteDialog->resize(297, 154);
        gridLayout_3 = new QGridLayout(ColorPaletteDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(ColorPaletteDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        blue = new QRadioButton(groupBox);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setChecked(true);

        horizontalLayout_2->addWidget(blue);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/Blue-Red_256x256.png")));

        horizontalLayout_2->addWidget(label);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        black = new QRadioButton(groupBox);
        black->setObjectName(QString::fromUtf8("black"));

        horizontalLayout_3->addWidget(black);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/res/Black-White_256x256.png")));

        horizontalLayout_3->addWidget(label_2);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(15, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(ColorPaletteDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout, 1, 0, 1, 1);


        retranslateUi(ColorPaletteDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ColorPaletteDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ColorPaletteDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ColorPaletteDialog);
    } // setupUi

    void retranslateUi(QDialog *ColorPaletteDialog)
    {
        ColorPaletteDialog->setWindowTitle(QApplication::translate("ColorPaletteDialog", "Color palette dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ColorPaletteDialog", "Color palettes", 0, QApplication::UnicodeUTF8));
        blue->setText(QApplication::translate("ColorPaletteDialog", "Blue - red", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        black->setText(QApplication::translate("ColorPaletteDialog", "Black - white", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ColorPaletteDialog: public Ui_ColorPaletteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORPALETTEDIALOG_H
