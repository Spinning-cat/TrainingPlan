/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTableWidget *resultTable;
    QTableWidget *coursesTable;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_9;
    QDoubleSpinBox *needCredit2;
    QDoubleSpinBox *needCredit3;
    QDoubleSpinBox *needCredit1;
    QLineEdit *credit2;
    QLabel *label_3;
    QLineEdit *credit3;
    QDoubleSpinBox *needCredit4;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_2;
    QLineEdit *credit1;
    QLineEdit *credit4;
    QPushButton *getTrainingPlan;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_3;
    QPushButton *editCourse;
    QPushButton *confirmButton;
    QPushButton *addCourse;
    QPushButton *deleteCourse;
    QGridLayout *gridLayout_2;
    QPushButton *searchCourse;
    QLineEdit *keyword;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1107, 819);
        MainWindow->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        resultTable = new QTableWidget(centralwidget);
        resultTable->setObjectName(QString::fromUtf8("resultTable"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(resultTable->sizePolicy().hasHeightForWidth());
        resultTable->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Heiti SC"));
        font.setPointSize(14);
        font.setKerning(true);
        resultTable->setFont(font);
        resultTable->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        resultTable->horizontalHeader()->setCascadingSectionResizes(false);
        resultTable->verticalHeader()->setCascadingSectionResizes(true);

        gridLayout_4->addWidget(resultTable, 1, 0, 1, 1);

        coursesTable = new QTableWidget(centralwidget);
        coursesTable->setObjectName(QString::fromUtf8("coursesTable"));
        sizePolicy.setHeightForWidth(coursesTable->sizePolicy().hasHeightForWidth());
        coursesTable->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Heiti SC"));
        font1.setPointSize(14);
        coursesTable->setFont(font1);
        coursesTable->setAlternatingRowColors(true);
        coursesTable->horizontalHeader()->setCascadingSectionResizes(false);
        coursesTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout_4->addWidget(coursesTable, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);


        gridLayout_4->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_9, 0, 1, 1, 1);

        needCredit2 = new QDoubleSpinBox(centralwidget);
        needCredit2->setObjectName(QString::fromUtf8("needCredit2"));

        gridLayout->addWidget(needCredit2, 7, 1, 1, 1);

        needCredit3 = new QDoubleSpinBox(centralwidget);
        needCredit3->setObjectName(QString::fromUtf8("needCredit3"));

        gridLayout->addWidget(needCredit3, 8, 1, 1, 1);

        needCredit1 = new QDoubleSpinBox(centralwidget);
        needCredit1->setObjectName(QString::fromUtf8("needCredit1"));

        gridLayout->addWidget(needCredit1, 2, 1, 1, 1);

        credit2 = new QLineEdit(centralwidget);
        credit2->setObjectName(QString::fromUtf8("credit2"));
        sizePolicy1.setHeightForWidth(credit2->sizePolicy().hasHeightForWidth());
        credit2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(credit2, 7, 2, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        credit3 = new QLineEdit(centralwidget);
        credit3->setObjectName(QString::fromUtf8("credit3"));
        sizePolicy1.setHeightForWidth(credit3->sizePolicy().hasHeightForWidth());
        credit3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(credit3, 8, 2, 1, 1);

        needCredit4 = new QDoubleSpinBox(centralwidget);
        needCredit4->setObjectName(QString::fromUtf8("needCredit4"));

        gridLayout->addWidget(needCredit4, 9, 1, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_4, 8, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_6, 9, 0, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_2, 7, 0, 1, 1);

        credit1 = new QLineEdit(centralwidget);
        credit1->setObjectName(QString::fromUtf8("credit1"));
        sizePolicy1.setHeightForWidth(credit1->sizePolicy().hasHeightForWidth());
        credit1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(credit1, 2, 2, 1, 1);

        credit4 = new QLineEdit(centralwidget);
        credit4->setObjectName(QString::fromUtf8("credit4"));
        sizePolicy1.setHeightForWidth(credit4->sizePolicy().hasHeightForWidth());
        credit4->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(credit4, 9, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        getTrainingPlan = new QPushButton(centralwidget);
        getTrainingPlan->setObjectName(QString::fromUtf8("getTrainingPlan"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(getTrainingPlan->sizePolicy().hasHeightForWidth());
        getTrainingPlan->setSizePolicy(sizePolicy3);
        getTrainingPlan->setMaximumSize(QSize(250, 45));

        verticalLayout_2->addWidget(getTrainingPlan, 0, Qt::AlignmentFlag::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        editCourse = new QPushButton(centralwidget);
        editCourse->setObjectName(QString::fromUtf8("editCourse"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(editCourse->sizePolicy().hasHeightForWidth());
        editCourse->setSizePolicy(sizePolicy4);
        editCourse->setMaximumSize(QSize(250, 45));

        gridLayout_3->addWidget(editCourse, 5, 0, 1, 1);

        confirmButton = new QPushButton(centralwidget);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));
        sizePolicy4.setHeightForWidth(confirmButton->sizePolicy().hasHeightForWidth());
        confirmButton->setSizePolicy(sizePolicy4);
        confirmButton->setMaximumSize(QSize(250, 45));

        gridLayout_3->addWidget(confirmButton, 7, 0, 1, 1);

        addCourse = new QPushButton(centralwidget);
        addCourse->setObjectName(QString::fromUtf8("addCourse"));
        sizePolicy4.setHeightForWidth(addCourse->sizePolicy().hasHeightForWidth());
        addCourse->setSizePolicy(sizePolicy4);
        addCourse->setMaximumSize(QSize(250, 45));

        gridLayout_3->addWidget(addCourse, 2, 0, 1, 1);

        deleteCourse = new QPushButton(centralwidget);
        deleteCourse->setObjectName(QString::fromUtf8("deleteCourse"));
        sizePolicy4.setHeightForWidth(deleteCourse->sizePolicy().hasHeightForWidth());
        deleteCourse->setSizePolicy(sizePolicy4);
        deleteCourse->setMaximumSize(QSize(250, 45));

        gridLayout_3->addWidget(deleteCourse, 8, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(-1);
        searchCourse = new QPushButton(centralwidget);
        searchCourse->setObjectName(QString::fromUtf8("searchCourse"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(searchCourse->sizePolicy().hasHeightForWidth());
        searchCourse->setSizePolicy(sizePolicy5);
        searchCourse->setMaximumSize(QSize(16777215, 45));

        gridLayout_2->addWidget(searchCourse, 1, 1, 1, 1);

        keyword = new QLineEdit(centralwidget);
        keyword->setObjectName(QString::fromUtf8("keyword"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(keyword->sizePolicy().hasHeightForWidth());
        keyword->setSizePolicy(sizePolicy6);
        keyword->setMinimumSize(QSize(0, 18));
        keyword->setMaximumSize(QSize(16777215, 45));

        gridLayout_2->addWidget(keyword, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);


        verticalLayout_3->addLayout(verticalLayout_2);


        gridLayout_5->addLayout(verticalLayout_3, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1107, 38));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\347\274\226\346\216\222", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\347\256\241\347\220\206", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\345\272\224\344\277\256\345\255\246\345\210\206", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\205\254\345\205\261\345\237\272\347\241\200\350\257\276+\345\256\236\350\267\265\345\277\205\344\277\256\350\257\276\345\255\246\345\210\206", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\344\270\223\344\270\232\351\200\211\344\277\256\350\257\276\345\255\246\345\210\206", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\256\236\350\267\265\351\200\211\344\277\256\350\257\276\345\255\246\345\210\206", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\237\271\345\205\273\350\256\241\345\210\222\347\224\237\346\210\220", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\344\270\223\344\270\232\345\237\272\347\241\200\350\257\276\345\255\246\345\210\206", nullptr));
        getTrainingPlan->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\345\237\271\345\205\273\350\256\241\345\210\222\350\241\250", nullptr));
        editCourse->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\350\257\276\347\250\213", nullptr));
        confirmButton->setText(QCoreApplication::translate("MainWindow", "\347\241\256\350\256\244\344\277\256\346\224\271", nullptr));
        addCourse->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\257\276\347\250\213", nullptr));
        deleteCourse->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\257\276\347\250\213", nullptr));
        searchCourse->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
