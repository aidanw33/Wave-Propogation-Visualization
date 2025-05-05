#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the change of the rows/cols setter to the graph
    connect(ui->rows_setter, QOverload<int>::of(&QSpinBox::valueChanged), ui->graph, &GridWidget::setRows);
    connect(ui->column_setter, QOverload<int>::of(&QSpinBox::valueChanged), ui->graph, &GridWidget::setCols);

    // Initialize grid with current spin box values
    ui->graph->setRows(ui->rows_setter->value());
    ui->graph->setCols(ui->column_setter->value());

}



MainWindow::~MainWindow()
{
    delete ui;
}
