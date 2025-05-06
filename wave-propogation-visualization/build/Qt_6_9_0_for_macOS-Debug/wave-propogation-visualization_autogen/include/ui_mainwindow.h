/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "gridwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpinBox *column_setter;
    GridWidget *graph;
    QLabel *rows_label;
    QLabel *column_label;
    QDoubleSpinBox *doubleSpinBox_2;
    QSpinBox *rows_setter;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label;
    QLabel *graph_label;
    QMenuBar *menubar;
    QMenu *menuapp_name;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 603);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        column_setter = new QSpinBox(centralwidget);
        column_setter->setObjectName("column_setter");
        column_setter->setMinimum(2);
        column_setter->setMaximum(20);
        column_setter->setValue(5);

        gridLayout->addWidget(column_setter, 2, 1, 1, 1);

        graph = new GridWidget(centralwidget);
        graph->setObjectName("graph");
        graph->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(graph, 0, 1, 1, 1);

        rows_label = new QLabel(centralwidget);
        rows_label->setObjectName("rows_label");

        gridLayout->addWidget(rows_label, 1, 0, 1, 1);

        column_label = new QLabel(centralwidget);
        column_label->setObjectName("column_label");

        gridLayout->addWidget(column_label, 2, 0, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(centralwidget);
        doubleSpinBox_2->setObjectName("doubleSpinBox_2");
        doubleSpinBox_2->setValue(45.000000000000000);

        gridLayout->addWidget(doubleSpinBox_2, 4, 1, 1, 1);

        rows_setter = new QSpinBox(centralwidget);
        rows_setter->setObjectName("rows_setter");
        rows_setter->setMinimum(2);
        rows_setter->setMaximum(20);
        rows_setter->setValue(5);

        gridLayout->addWidget(rows_setter, 1, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(centralwidget);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setValue(0.000000000000000);

        gridLayout->addWidget(doubleSpinBox, 3, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 3, 0, 1, 1);

        graph_label = new QLabel(centralwidget);
        graph_label->setObjectName("graph_label");

        gridLayout->addWidget(graph_label, 0, 0, 1, 1);

        gridLayout->setColumnStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menuapp_name = new QMenu(menubar);
        menuapp_name->setObjectName("menuapp_name");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuapp_name->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        rows_label->setText(QCoreApplication::translate("MainWindow", "Rows", nullptr));
        column_label->setText(QCoreApplication::translate("MainWindow", "Columns", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Start Angle", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Start Point", nullptr));
        graph_label->setText(QCoreApplication::translate("MainWindow", "Graph", nullptr));
        menuapp_name->setTitle(QCoreApplication::translate("MainWindow", "app name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
