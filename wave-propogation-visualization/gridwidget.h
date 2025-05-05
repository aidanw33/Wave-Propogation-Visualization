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
};

#endif // GRIDWIDGET_H
