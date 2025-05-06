#include "gridwidget.h"
#include <QPainter>
#include <iostream>

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

            painter.setPen(Qt::black);  // No border while filling
            painter.drawRect(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
        }
    }

    // Draw the rays onto the checkboard pattern
    painter.setPen(QPen(Qt::red, 1));  // red rays, 2px thick

    for (const auto& ray : rays) {
        double x1 = ray[0];
        double y1 = ray[1];
        double x2 = ray[2];
        double y2 = ray[3];

        // Transform from logical [-1, 1] to pixel space
        double px1 = ((x1 + 1.0) / 2.0) * side;
        double py1 = ((1.0 - (y1 + 1.0) / 2.0)) * side;
        double px2 = ((x2 + 1.0) / 2.0) * side;
        double py2 = ((1.0 - (y2 + 1.0) / 2.0)) * side;

        painter.drawLine(QPointF(px1, py1), QPointF(px2, py2));
    }
}

void GridWidget::setRows(int r) {
    rows = r;
    update();
}

void GridWidget::setCols(int c) {
    cols = c;
    update();
    calculateRays(0, 45.0);
}

std::vector<std::array<double, 4>> GridWidget::calculateRays(double start_point, double start_angle) {

    //Create the matrixes which will be used to find the intersection point
    double total_height = 2;
    double height_array[rows + 1];

    for(int i = 0; i < rows + 1; ++i) {
        height_array[i] = -1 + (i * (total_height/rows));
    }

    double total_length = 2;
    double length_array[cols + 1];

    for(int i = 0; i < cols + 1; ++i) {
        length_array[i] = -1 + (i * (total_length/cols));
    }

    rays.clear();

    //Calculate intersection points
    calculatePositiveRays(-1, start_point, start_angle, height_array, length_array);
    calculateNegativeRays(-1, start_point, start_angle * (-1), height_array, length_array);

    return rays;

}


void GridWidget::calculatePositiveRays(double start_point_x, double start_point_y, double start_angle, double height_array[], double length_array[]){
    double ceiling = -2;
    double wall    =  2;
    for(int i = 0; i < rows + 1; ++i) {
        if (height_array[i] > start_point_y){
            ceiling = height_array[i];
            break;
        }
    }
    for(int i = 0; i < cols + 1; ++i) {
        if (length_array[i] > start_point_x){
            wall = length_array[i];
            break;
        }
    }

    //calculate the point that will collide with the ceiling
    double slope = std::tan(start_angle * M_PI / 180.0);
    double ceiling_x = (start_point_y - ceiling - (slope*start_point_x))/(-1 * slope);

    //calculate the point that will collide with the wall
    double wall_y = ((-1 * slope) * (start_point_x - wall)) + start_point_y;

    //find out which one is closer
    double wall_distance    = std::sqrt((wall - start_point_x)*(wall - start_point_x) + (wall_y - start_point_y)*(wall_y - start_point_y));
    double ceiling_distance = std::sqrt((ceiling_x - start_point_x)*(ceiling_x - start_point_x) + (ceiling - start_point_y)*(ceiling - start_point_y));

    //add a line to the closer distance
    if (wall_distance < ceiling_distance) {
        std::array<double, 4> ray = {start_point_x, start_point_y, wall, wall_y};
        rays.push_back(ray);
    }
    else {
        std::array<double, 4> ray = {start_point_x, start_point_y, ceiling_x, ceiling};
        rays.push_back(ray);
    }


    return;

}
void GridWidget::calculateNegativeRays(double start_point_x, double start_point_y, double start_angle, double height_array[], double length_array[]){

}
