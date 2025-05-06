#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

class GridWidget : public QWidget {
    Q_OBJECT

public:
    explicit GridWidget(QWidget *parent = nullptr);
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
    void calculateRays(double start_point, double start_angle); //calculates the rays from a starting point and angle
    void calculatePositiveRays(double start_point_x, double start_point_y, double start_angle, double height_array[], double length_array[]);
    void calculateNegativeRays(double start_point_x, double start_point_y, double start_angle, double height_array[], double length_array[]);
    struct ArrayHash {std::size_t operator()(const std::array<double, 4>& arr) const;};
    struct ArrayEqual {bool operator()(const std::array<double, 4>& a, const std::array<double, 4>& b) const;};
    std::unordered_set<std::array<double, 4>, ArrayHash, ArrayEqual> rays; //create a set to store the vectors in

};

#endif // GRIDWIDGET_H
