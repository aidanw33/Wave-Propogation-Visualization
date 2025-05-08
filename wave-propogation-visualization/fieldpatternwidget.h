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
        void refresh();

    protected:
        void paintEvent(QPaintEvent *event) override;


    private:
        int rows = 5; //default value
        int cols = 5; //default value
        FieldPatternUnit fpunit;
        std::vector<std::array<double, 4>> fieldPatternLines;
        void calculateRays();
        void detectNearestCollision(double, double, double);
        std::optional<std::pair<double, double>> getIntersection(double x1, double y1, double x2, double y2,double x, double y, double slope);

};

#endif // FIELDPATTERNWIDGET_H
