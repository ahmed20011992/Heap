#ifndef HEAPTESTWIDGET_H
#define HEAPTESTWIDGET_H

#include <QWidget>
#include "studentsMinheap.h"


class HeapTestWidget : public QWidget
{
    Q_OBJECT


    static const int _sizeOfArray = 32;
    int _dataInDatabutton[_sizeOfArray];
    int _indexHoverData;
    //int _indexHoverTree;
    int _indexHoverArrOrTree;
    int _nbrValues;

    MinHeap _heap;

    QColor colorOfData(int value, bool hilight);



    QRect rectOfDatabutton(int ixDatabutton);
    QRect rectOfTreecell(int ix);
    //QRect rectOfArrcell(int ix);

    void paintEvent(QPaintEvent *event) override;


    QPoint ptCenterOfTreenode(int ix);
    float xCenterOfTreenode(int ix);

    QRect rectOfArrcell(int ix);
    void paintArray(QPainter &painter);

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    int indexOfDatabuttonContainingPoint(QPoint pt);
    int indexOfArraycellContainingPoint(QPoint pt);
    int indexOfTreecellContainingPoint(QPoint pt);

    void paintDatabuttons(QPainter &painter);
public:
    explicit HeapTestWidget(QWidget *parent = nullptr);

    void clearHeap();
    void fillWithRandomData();
    void deleteMin();
    void ragnarsTest();

signals:

public slots:
private slots:
    void paintTree(QPainter &painter);
};

#endif // HEAPTESTWIDGET_H
