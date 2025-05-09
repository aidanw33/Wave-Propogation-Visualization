#ifndef FIELDPATTERNWIDGET_H
#define FIELDPATTERNWIDGET_H

#include <QWidget>
#include "fieldpatternunit.h"


class FieldPatternWidget : public QWidget {
    Q_OBJECT

    public:
        explicit FieldPatternWidget(QWidget *parent = nullptr);
        void setRows(int);
        void setCols(int);
        void setAngle1(double);
        void setAngle2(double);
        void setStart(double);
        void refresh();

    protected:
        void paintEvent(QPaintEvent *event) override;


    private:
        int rows = 5; //default value
        int cols = 5; //default value
        double start = 0; //default start point
        double angle1 = 45; //default start angle
        double angle2 = 45; //default start angle
        FieldPatternUnit fpunit;
        std::vector<std::array<double, 4>> fieldPatternLines;
        void calculateRays();
        void calculatePositiveRays(double, double, double);
        void calculateNegativeRays(double, double, double);
        std::tuple<double, double, bool> detectNearestCollision(double, double, double);
        std::optional<std::pair<double, double>> getIntersection(double x1, double y1, double x2, double y2,double x, double y, double slope);
        struct ArrayHash {std::size_t operator()(const std::array<double, 4>& arr) const;};
        struct ArrayEqual {bool operator()(const std::array<double, 4>& a, const std::array<double, 4>& b) const;};
        std::unordered_set<std::array<double, 4>, ArrayHash, ArrayEqual> rays; //create a set to store the vectors in


};

#endif // FIELDPATTERNWIDGET_H
