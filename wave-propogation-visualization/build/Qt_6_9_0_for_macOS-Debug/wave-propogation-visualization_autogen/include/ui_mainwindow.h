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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "gridwidget.h"

QT_BEGIN_NAMESPACE

class Ui_FieldPatterns
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QDoubleSpinBox *angle2_setter;
    QLabel *column_label;
    QLabel *angle2_label;
    QLabel *rows_label;
    QDoubleSpinBox *angle1_setter;
    QPushButton *refresh_button;
    QSpinBox *column_setter;
    GridWidget *graph;
    QSpinBox *rows_setter;
    QLabel *startPoint_label;
    QLabel *graph_label;
    QDoubleSpinBox *startPoint_setter;
    QLabel *angle1_label;
    QMenuBar *menubar;
    QMenu *menuapp_name;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FieldPatterns)
    {
        if (FieldPatterns->objectName().isEmpty())
            FieldPatterns->setObjectName("FieldPatterns");
        FieldPatterns->resize(800, 603);
        centralwidget = new QWidget(FieldPatterns);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        angle2_setter = new QDoubleSpinBox(centralwidget);
        angle2_setter->setObjectName("angle2_setter");
        angle2_setter->setValue(45.000000000000000);

        gridLayout->addWidget(angle2_setter, 5, 1, 1, 1);

        column_label = new QLabel(centralwidget);
        column_label->setObjectName("column_label");

        gridLayout->addWidget(column_label, 2, 0, 1, 1);

        angle2_label = new QLabel(centralwidget);
        angle2_label->setObjectName("angle2_label");

        gridLayout->addWidget(angle2_label, 5, 0, 1, 1);

        rows_label = new QLabel(centralwidget);
        rows_label->setObjectName("rows_label");

        gridLayout->addWidget(rows_label, 1, 0, 1, 1);

        angle1_setter = new QDoubleSpinBox(centralwidget);
        angle1_setter->setObjectName("angle1_setter");
        angle1_setter->setValue(45.000000000000000);

        gridLayout->addWidget(angle1_setter, 4, 1, 1, 1);

        refresh_button = new QPushButton(centralwidget);
        refresh_button->setObjectName("refresh_button");

        gridLayout->addWidget(refresh_button, 6, 0, 1, 2);

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

        rows_setter = new QSpinBox(centralwidget);
        rows_setter->setObjectName("rows_setter");
        rows_setter->setMinimum(2);
        rows_setter->setMaximum(20);
        rows_setter->setValue(5);

        gridLayout->addWidget(rows_setter, 1, 1, 1, 1);

        startPoint_label = new QLabel(centralwidget);
        startPoint_label->setObjectName("startPoint_label");

        gridLayout->addWidget(startPoint_label, 3, 0, 1, 1);

        graph_label = new QLabel(centralwidget);
        graph_label->setObjectName("graph_label");

        gridLayout->addWidget(graph_label, 0, 0, 1, 1);

        startPoint_setter = new QDoubleSpinBox(centralwidget);
        startPoint_setter->setObjectName("startPoint_setter");
        startPoint_setter->setValue(0.000000000000000);

        gridLayout->addWidget(startPoint_setter, 3, 1, 1, 1);

        angle1_label = new QLabel(centralwidget);
        angle1_label->setObjectName("angle1_label");

        gridLayout->addWidget(angle1_label, 4, 0, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 10);
        FieldPatterns->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FieldPatterns);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menuapp_name = new QMenu(menubar);
        menuapp_name->setObjectName("menuapp_name");
        FieldPatterns->setMenuBar(menubar);
        statusbar = new QStatusBar(FieldPatterns);
        statusbar->setObjectName("statusbar");
        FieldPatterns->setStatusBar(statusbar);

        menubar->addAction(menuapp_name->menuAction());

        retranslateUi(FieldPatterns);

        QMetaObject::connectSlotsByName(FieldPatterns);
    } // setupUi

    void retranslateUi(QMainWindow *FieldPatterns)
    {
        FieldPatterns->setWindowTitle(QCoreApplication::translate("FieldPatterns", "Field Patterns", nullptr));
        column_label->setText(QCoreApplication::translate("FieldPatterns", "Columns", nullptr));
        angle2_label->setText(QCoreApplication::translate("FieldPatterns", "Angle 2", nullptr));
        rows_label->setText(QCoreApplication::translate("FieldPatterns", "Rows", nullptr));
        refresh_button->setText(QCoreApplication::translate("FieldPatterns", "Refresh", nullptr));
        startPoint_label->setText(QCoreApplication::translate("FieldPatterns", "Start Point", nullptr));
        graph_label->setText(QCoreApplication::translate("FieldPatterns", "Graph", nullptr));
        angle1_label->setText(QCoreApplication::translate("FieldPatterns", "Angle 1", nullptr));
        menuapp_name->setTitle(QCoreApplication::translate("FieldPatterns", "app name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FieldPatterns: public Ui_FieldPatterns {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
