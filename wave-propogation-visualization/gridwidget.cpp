#include "gridwidget.h"
#include <QPainter>

GridWidget::GridWidget(QWidget *parent)
    : QWidget(parent)
{}

void GridWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    const float widgetWidth  =  width() - 10;
    const float widgetHeight =  height() - 10;
    float side = std::min(widgetHeight, widgetWidth);

    // Compute cell size
    float cellWidth  = static_cast<float>(side / cols);
    float cellHeight = static_cast<float>(side / rows);

    // Draw checkerboard pattern
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // Alternate colors based on row+col
            if ((row + col) % 2 == 0)
                painter.setBrush(QColor(200, 200, 200));  // light gray
            else
                painter.setBrush(QColor(100, 100, 100));  // dark gray

            painter.setPen(Qt::NoPen);  // No border while filling
            painter.drawRect(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
        }
    }

    // Draw lines over the checkerboard
    painter.setPen(Qt::black);
    for (int row = 0; row <= rows; ++row) {
        painter.drawLine(0, row * cellHeight, side, row * cellHeight);
    }

    for (int col = 0; col <= cols; ++col) {
        painter.drawLine(col * cellWidth, 0, col * cellWidth, side);
    }


}

void GridWidget::setRows(int r) {
    rows = r;
    update();
}

void GridWidget::setCols(int c) {
    cols = c;
    update();
}
