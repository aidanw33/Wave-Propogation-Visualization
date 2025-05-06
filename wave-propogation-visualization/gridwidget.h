#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

class GridWidget : public QWidget {
    Q_OBJECT

public:
    explicit GridWidget(QWidget *parent = nullptr);
    void setRows(int);
    void setCols(int);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int rows = 5; //default value
    int cols = 5; //default value
    double start_point = rows / 2; //default start point
    double start_angle = 45; //default start angle
    std::vector<std::array<double, 4>> rays;  //rays to draw onto the grid
    std::vector<std::array<double, 4>> calculateRays(double start_point, double start_angle); //calculates the rays from a starting point and angle
    void calculatePositiveRays(double start_point_x, double start_point_y, double start_angle, double height_array[], double length_array[]);
    void calculateNegativeRays(double start_point_x, double start_point_y, double start_angle, double height_array[], double length_array[]);

};

#endif // GRIDWIDGET_H
