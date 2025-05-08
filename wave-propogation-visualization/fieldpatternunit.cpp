// unit.cpp
#include "fieldpatternunit.h"

FieldPatternUnit::FieldPatternUnit() {

    //create field pattern
    lines.push_back({-1.0, -0.5, -1.0,  0.5});
    lines.push_back({-1.0, -0.5,  0.0, -0.5});
    lines.push_back({ 0.0, -0.5,  0.0,  0.5});
    lines.push_back({-1.0,  0.5,  0.0,  0.5});
}

void FieldPatternUnit::draw(QPainter &painter, float x, float y, float width, float height) {
    painter.setPen(Qt::black);

    float cx = x + width / 2.0f;
    float cy = y + height / 2.0f;

    for (const auto& line : lines) {
        float x1 = cx + line[0] * (width / 2.0f);
        float y1 = cy + line[1] * (height / 2.0f) * -1;
        float x2 = cx + line[2] * (width / 2.0f);
        float y2 = cy + line[3] * (height / 2.0f) * -1;

        painter.drawLine(x1, y1, x2, y2);
    }
}

void FieldPatternUnit::addLine(double x1, double y1, double x2, double y2) {
    lines.push_back({x1, y1, x2, y2});
}

std::vector<std::array<double, 4>> FieldPatternUnit::getUnitLines() {
    return lines;
}
