#include "fieldpatternwidget.h"
#include <QPainter>
#include <iostream>

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
    std::cout << "here" << std::endl;
    detectNearestCollision(0, 0, 45);

}

void FieldPatternWidget::detectNearestCollision(double start_point_x, double start_point_y, double start_angle) {
    double slope = std::tan(start_angle * M_PI / 180.0);

    double distance = 2;
    double inter_x = -1;
    double inter_y = -1;

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
            std::cout << "Intersection at: (" << result->first << ", " << result->second << ")\n";
            //if (x1 < result->first && result->first < x2 && )
        } else {
            std::cout << "No intersection.\n";
        }

    }


}

std::optional<std::pair<double, double>> FieldPatternWidget::getIntersection(double x1, double y1, double x2, double y2,double x, double y, double slope) {
    double dx = x2 - x1;
    double dy = y2 - y1;

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
    return std::make_pair(intersectX, intersectY);
}

void FieldPatternWidget::setRows(int r) {
    rows = r;
}

void FieldPatternWidget::setCols(int c) {
    cols = c;
}

void FieldPatternWidget::refresh() {
    calculateRays();
    update();
}

