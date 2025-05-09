#include "fieldpatternwidget.h"
#include <QPainter>
#include <iostream>
#include <tuple>

FieldPatternWidget::FieldPatternWidget(QWidget *parent)
    : QWidget(parent)
{}

void FieldPatternWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    const double widgetWidth  = width() - 10;
    const double widgetHeight = height() - 10;
    float side = std::min(widgetHeight, widgetWidth);

    float cellWidth  = side / cols;
    float cellHeight = side / rows;

    // Top-left corner of the square grid
    float originX = 5;  // Center the square with a 5-pixel margin
    float originY = 5;

    // Draw the outer square border
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(originX, originY, cols * cellWidth, rows * cellHeight);

    // Draw units inside each cell
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = originX + col * cellWidth;
            float y = originY + row * cellHeight;
            fpunit.draw(painter, x, y, cellWidth, cellHeight);
        }
    }

    /*
    // Draw fieldPatternLines
    painter.setPen(Qt::red); // Use a different color to distinguish lines
    for (const auto& line : fieldPatternLines) {
        // Map normalized coordinates (-1 to 1) to widget coordinates
        float x1 = originX + (line[0] + 1.0) * (side / 2.0); // Scale and translate x1
        float y1 = originY + (1.0 - line[1]) * (side / 2.0); // Scale, flip, and translate y1
        float x2 = originX + (line[2] + 1.0) * (side / 2.0); // Scale and translate x2
        float y2 = originY + (1.0 - line[3]) * (side / 2.0); // Scale, flip, and translate y2

        painter.drawLine(x1, y1, x2, y2);
    }
    */

    // Draw fieldPatternLines
    painter.setPen(Qt::red); // Use a different color to distinguish lines
    for (const auto& line : rays) {
        // Map normalized coordinates (-1 to 1) to widget coordinates
        float x1 = originX + (line[0] + 1.0) * (side / 2.0); // Scale and translate x1
        float y1 = originY + (1.0 - line[1]) * (side / 2.0); // Scale, flip, and translate y1
        float x2 = originX + (line[2] + 1.0) * (side / 2.0); // Scale and translate x2
        float y2 = originY + (1.0 - line[3]) * (side / 2.0); // Scale, flip, and translate y2

        painter.drawLine(x1, y1, x2, y2);
    }
}


void FieldPatternWidget::calculateRays() {

    // Get the structure of the field pattern
    std::vector<std::array<double, 4>> basePattern = fpunit.getUnitLines();
    fieldPatternLines.clear();

    double cellWidth = 2.0 / cols;
    double cellHeight = 2.0 / rows;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            double cx = -1.0 + (c + 0.5) * cellWidth;
            double cy = -1.0 + (r + 0.5) * cellHeight;

            for (const auto& line : basePattern) {
                double x1 = cx + line[0] * (cellWidth / 2.0);
                double y1 = cy + line[1] * (cellHeight / 2.0);
                double x2 = cx + line[2] * (cellWidth / 2.0);
                double y2 = cy + line[3] * (cellHeight / 2.0);
                fieldPatternLines.push_back({x1, y1, x2, y2});

            }
        }
    }
    //push back the borders of the grid.
    fieldPatternLines.push_back({-1, 1, 1, 1});
    fieldPatternLines.push_back({1, -1, 1, 1});
    fieldPatternLines.push_back({-1, -1, 1, -1});




    rays.clear();
    calculatePositiveRays(-1, start, angle1); //TODO: need a way to determine which angle to start with
    calculateNegativeRays(-1, start, angle1);
}

void FieldPatternWidget::calculatePositiveRays(double start_x, double start_y, double start_angle) {

    //get the nearest collision
    auto [x, y, wall] = detectNearestCollision(start_x, start_y, start_angle);
    std::array<double, 4> ray = {start_x, start_y, x, y};
    auto [iterator, inserted] = rays.insert(ray);
    if (!inserted) {
        return;
    }
    if (wall) {
        //hitting a wall, change the angle to whichever we aren't on
        if (x >= 1) {
            return;
        }
        start_angle = (start_angle == angle1) ? angle2 : angle1;
        calculatePositiveRays(x, y, start_angle);
        calculateNegativeRays(x, y, start_angle);
    }
    else {

        if (y >= 1) {
            return;
        }
        //hitting a ceiling, change the angle to the outgoing positive angle
        double other_angle = (start_angle == angle1) ? angle2 : angle1;
        calculatePositiveRays(x, y, other_angle );
        calculateNegativeRays(x, y, start_angle);
    }
}

void FieldPatternWidget::calculateNegativeRays(double start_x, double start_y, double start_angle) {

    //get the nearest collision
    auto [x, y, wall] = detectNearestCollision(start_x, start_y, -start_angle);
    std::array<double, 4> ray = {start_x, start_y, x, y};
    auto [iterator, inserted] = rays.insert(ray);
    if (!inserted) {
        return;
    }
    if (wall) {
        //hitting a wall, change the angle to whichever we aren't on
        if (x >= 1) {
            return;
        }
        start_angle = (start_angle == angle1) ? angle2 : angle1;
        calculatePositiveRays(x, y, start_angle);
        calculateNegativeRays(x, y, start_angle);
    }
    else {
        if (y <= -1) {
            return;
        }
        //hitting a floor, change the angle to the outgoing negative angle
        double other_angle = (start_angle == angle1) ? angle2 : angle1;
        calculatePositiveRays(x, y, start_angle );
        calculateNegativeRays(x, y, other_angle);
    }
}

std::tuple<double, double, bool> FieldPatternWidget::detectNearestCollision(double start_point_x, double start_point_y, double start_angle) {
    double slope = std::tan(start_angle * M_PI / 180.0);

    double min_distance = 4; //random number greater than sqrt(8)
    double inter_x = -1; //random number
    double inter_y = -1; //random number
    bool wall = 0;

    for (const auto& line : fieldPatternLines) {
        double x1 = line[0];
        double y1 = line[1];
        double x2 = line[2];
        double y2 = line[3];

        //skip over impossibile to collide with segments

        /*

        if (start_point_x + 1e16 > x1 && start_point_x + 1e16 > x2) {
            continue;
        }
        if (start_angle > 0 && start_point_y + 1e16 > y1 && start_point_y + 1e16 > y2) {
            continue;
        }
        if (start_angle < 0 && start_point_y - 1e16 < y1 && start_point_y - 1e16 < y2) {
            continue;
        }

        */
        auto result = getIntersection(x1, y1, x2, y2, start_point_x, start_point_y, slope);
        if (result) {
            if (x1 - 1e15 <= result->first && result->first <= x2 + 1e15 && y1-1e15 <= result->second && result->second <= y2+1e15) {

                double x_dist = result->first - start_point_x;
                double y_dist = result->second - start_point_y;
                double distance = std::sqrt(x_dist * x_dist + y_dist * y_dist);
                if (distance < min_distance) {
                    min_distance = distance;
                    inter_x = result->first;
                    inter_y = result->second;

                    if (x1 == x2) {
                        wall = true;
                    }
                    else {
                        wall = false;
                    }
                }
            }
        }
    }

    return std::make_tuple(inter_x, inter_y, wall);


}

std::optional<std::pair<double, double>> FieldPatternWidget::getIntersection(
    double x1, double y1, double x2, double y2,
    double x, double y, double slope
    ) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    // Early exit if the starting point (x, y) is extremely close to the segment
    auto pointOnSegment = [](double x1, double y1, double x2, double y2, double px, double py) {
        double cross = std::abs((px - x1) * (y2 - y1) - (py - y1) * (x2 - x1));
        if (cross > 1e-15) return false; // Not on the line

        double dot = (px - x1) * (x2 - x1) + (py - y1) * (y2 - y1);
        if (dot < 0) return false;

        double lenSq = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
        if (dot > lenSq) return false;

        return true;
    };

    if (pointOnSegment(x1, y1, x2, y2, x, y)) {
        return std::nullopt;
    }

    double denom = dy - slope * dx;
    if (std::abs(denom) < 1e-10) {
        // Lines are parallel
        return std::nullopt;
    }

    double u = (y - y1 + slope * (x1 - x)) / denom;
    if (u < 0.0 || u > 1.0) {
        // Intersection is outside the segment
        return std::nullopt;
    }

    double intersectX = x1 + u * dx;
    double intersectY = y1 + u * dy;

    if (intersectX <= x) {
        return std::nullopt;
    }

    return std::make_pair(intersectX, intersectY);
}

void FieldPatternWidget::setRows(int r) {
    rows = r;
}

void FieldPatternWidget::setCols(int c) {
    cols = c;
}

void FieldPatternWidget::setAngle1(double angle) {
    angle1 = angle;
}

void FieldPatternWidget::setAngle2(double angle) {
    angle2 = angle;
}

void FieldPatternWidget::setStart(double start_point) {
    start = start_point;
}

void FieldPatternWidget::refresh() {
    calculateRays();
    update();
}


std::size_t FieldPatternWidget::ArrayHash::operator()(const std::array<double, 4>& arr) const {
    std::size_t seed = 0;
    for (double val : arr) {
        long long intVal = static_cast<long long>(std::round(val * 1e6));
        seed ^= std::hash<long long>()(intVal) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

bool FieldPatternWidget::ArrayEqual::operator()(const std::array<double, 4>& a, const std::array<double, 4>& b) const {
    const double eps = 1e-6;
    for (int i = 0; i < 4; ++i) {
        if (std::abs(a[i] - b[i]) > eps)
            return false;
    }
    return true;
}

