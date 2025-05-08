#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FieldPatterns)
{
    ui->setupUi(this);

    // Connect the change of the rows/cols setter to the graph for GraphWidget
    connect(ui->rows_setter, QOverload<int>::of(&QSpinBox::valueChanged), ui->graph, &GridWidget::setRows);
    connect(ui->column_setter, QOverload<int>::of(&QSpinBox::valueChanged), ui->graph, &GridWidget::setCols);

    // Connect the change of the rows/cols setter to the graph for FieldPatternWidget
    connect(ui->rows_setter, QOverload<int>::of(&QSpinBox::valueChanged), ui->fieldpatterngraph, &FieldPatternWidget::setRows);
    connect(ui->column_setter, QOverload<int>::of(&QSpinBox::valueChanged), ui->fieldpatterngraph, &FieldPatternWidget::setCols);

    // Initialize grid with current spin box values
    ui->graph->setRows(ui->rows_setter->value());
    ui->graph->setCols(ui->column_setter->value());

    // Connect the change of the angles setter to the graph
    connect(ui->angle1_setter, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->graph, &GridWidget::setAngle1);
    connect(ui->angle2_setter, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->graph, &GridWidget::setAngle2);

    // Initialize grid with current spin box values
    ui->graph->setAngle1(ui->angle1_setter->value());
    ui->graph->setAngle2(ui->angle2_setter->value());

    // Connect the refresh button for GraphWidget
    connect(ui->refresh_button, &QPushButton::clicked, ui->graph, &GridWidget::refresh);

    // Connect the refresh button for FieldPatternWidget
    connect(ui->refresh_button, &QPushButton::clicked, ui->fieldpatterngraph, &FieldPatternWidget::refresh);

    // Connect the start point
    connect(ui->startPoint_setter, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->graph, &GridWidget::setStart);

}



MainWindow::~MainWindow()
{
    delete ui;
}
