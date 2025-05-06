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
    painter.setPen(QPen(Qt::red, 1));  // red rays, 1px thick

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
}

void GridWidget::setCols(int c) {
    cols = c;
}

void GridWidget::setAngle1(double angle) {
    angle1 = angle;
}

void GridWidget::setAngle2(double angle) {
    angle2 = angle;
}

void GridWidget::setStart(double start_point) {
    start = start_point;
}

void GridWidget::refresh() {
    calculateRays(start, angle1);
    update();
}

void GridWidget::calculateRays(double start_point, double start_angle) {

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
    calculateNegativeRays(-1, start_point, start_angle, height_array, length_array);
}


void GridWidget::calculatePositiveRays(double start_point_x, double start_point_y, double start_angle, double height_array[], double length_array[]){
    double ceiling = 1;
    double wall    = 1;
    for(int i = 0; i < rows + 1; ++i) {
        if (height_array[i] > start_point_y){ //NOLINT
            ceiling = height_array[i];
            break;
        }
    }
    for(int i = 0; i < cols + 1; ++i) {
        if (length_array[i] > start_point_x){ //NOLINT
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
        auto [iterator, inserted] = rays.insert(ray);
        if (!inserted) {
            return;
        }
    }
    else {
        std::array<double, 4> ray = {start_point_x, start_point_y, ceiling_x, ceiling};
        auto [iterator, inserted] = rays.insert(ray);
        if (!inserted) {
            return;
        }    }

    //add a line recursively
    if (wall_distance < ceiling_distance) {
        if (wall < 1) {
            //hitting a wall, change the angle to whichever we aren't on
            start_angle = (start_angle == angle1) ? angle2 : angle1;
            calculatePositiveRays(wall, wall_y, start_angle, height_array, length_array);
            calculateNegativeRays(wall, wall_y, start_angle, height_array, length_array);
        }
    }
    else {
        if (ceiling < 1) {
            double alt_angle = (start_angle == angle1) ? angle2 : angle1;
            calculatePositiveRays(ceiling_x, ceiling, alt_angle, height_array, length_array);
            calculateNegativeRays(ceiling_x, ceiling, start_angle, height_array, length_array);
        }
    }


    return;

}
void GridWidget::calculateNegativeRays(double start_point_x, double start_point_y, double start_angle, double height_array[], double length_array[]){
    double floor = -1;
    double wall    =  1;
    for(int i = rows; i >= 0; --i) {
        if (height_array[i] < start_point_y){ //NOLINT
            floor = height_array[i];
            break;
        }
    }
    for(int i = 0; i < cols + 1; ++i) {
        if (length_array[i] > start_point_x){ //NOLINT
            wall = length_array[i];
            break;
        }
    }

    //calculate the point that will collide with the floor
    double slope = ((std::tan(start_angle * M_PI / 180.0)) * -1);
    double floor_x = (start_point_y - floor - (slope*start_point_x))/(-1 * slope);

    //calculate the point that will collide with the wall
    double wall_y = ((-1 * slope) * (start_point_x - wall)) + start_point_y;

    //find out which one is closer
    double wall_distance    = std::sqrt((wall - start_point_x)*(wall - start_point_x) + (wall_y - start_point_y)*(wall_y - start_point_y));
    double floor_distance = std::sqrt((floor_x - start_point_x)*(floor_x - start_point_x) + (floor - start_point_y)*(floor - start_point_y));

    //add a line to the closer distance
    if (wall_distance < floor_distance) {
        std::array<double, 4> ray = {start_point_x, start_point_y, wall, wall_y};
        auto [iterator, inserted] = rays.insert(ray);
        if (!inserted) {
            return;
        }    }
    else {
        std::array<double, 4> ray = {start_point_x, start_point_y, floor_x, floor};
        auto [iterator, inserted] = rays.insert(ray);
        if (!inserted) {
            return;
        }    }

    //add a line recursively
    if (wall_distance < floor_distance) {
        if (wall < 1) {
            //hitting a wall, change the angle to whichever we aren't on
            start_angle = (start_angle == angle1) ? angle2 : angle1;
            calculateNegativeRays(wall, wall_y, start_angle, height_array, length_array);
            calculatePositiveRays(wall, wall_y, start_angle, height_array, length_array);
        }
    }
    else {
        if (floor > -1) {
            double alt_angle = (start_angle == angle1) ? angle2 : angle1;
            calculateNegativeRays(floor_x, floor, alt_angle, height_array, length_array);
            calculatePositiveRays(floor_x, floor, start_angle, height_array, length_array);
        }
    }


    return;
}

std::size_t GridWidget::ArrayHash::operator()(const std::array<double, 4>& arr) const {
    std::size_t seed = 0;
    for (double val : arr) {
        long long intVal = static_cast<long long>(std::round(val * 1e6));
        seed ^= std::hash<long long>()(intVal) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

bool GridWidget::ArrayEqual::operator()(const std::array<double, 4>& a, const std::array<double, 4>& b) const {
    const double eps = 1e-6;
    for (int i = 0; i < 4; ++i) {
        if (std::abs(a[i] - b[i]) > eps)
            return false;
    }
    return true;
}
