#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FieldPatterns)
{
    ui->setupUi(this);

    // Connect the change of the rows/cols setter to the graph
    connect(ui->rows_setter, QOverload<int>::of(&QSpinBox::valueChanged), ui->graph, &GridWidget::setRows);
    connect(ui->column_setter, QOverload<int>::of(&QSpinBox::valueChanged), ui->graph, &GridWidget::setCols);

    // Initialize grid with current spin box values
    ui->graph->setRows(ui->rows_setter->value());
    ui->graph->setCols(ui->column_setter->value());

    // Connect the change of the angles setter to the graph
    connect(ui->angle1_setter, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->graph, &GridWidget::setAngle1);
    connect(ui->angle2_setter, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->graph, &GridWidget::setAngle2);

    // Initialize grid with current spin box values
    ui->graph->setAngle1(ui->angle1_setter->value());
    ui->graph->setAngle2(ui->angle2_setter->value());

    // Connect the refresh button
    connect(ui->refresh_button, &QPushButton::clicked, ui->graph, &GridWidget::refresh);

    // Connect the start point
    connect(ui->startPoint_setter, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->graph, &GridWidget::setStart);

}



MainWindow::~MainWindow()
{
    delete ui;
}
