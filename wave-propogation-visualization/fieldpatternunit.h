// unit.h
#ifndef FIELDPATTERNUNIT_H
#define FIELDPATTERNUNIT_H

#include <QPainter>

class FieldPatternUnit {
    public:
        FieldPatternUnit();
        void draw(QPainter &painter, float x, float y, float width, float height);
        std::vector<std::array<double, 4>> getUnitLines();

    private:
        std::vector<std::array<double, 4>> lines;  // Each line: {x1, y1, x2, y2}
        void addLine(double x1, double y1, double x2, double y2);

};

#endif // UNIT_H
