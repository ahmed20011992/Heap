#include "heaptestwidget.h"
#include "heaptestwidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <assert.h>
#include <QDebug>

#include <QMessageBox>

#include <algorithm>
#include <random>

using namespace std;



QColor HeapTestWidget::colorOfData(int value, bool hilight)
{

    if (value<0)
        return Qt::white;

    int hue = int(value*200/_nbrValues);
    int saturation = hilight ? 128 : 255;
    int v = hilight ? 128 : 255;
    return QColor::fromHsv(hue,saturation,v);


}


QRect HeapTestWidget::rectOfDatabutton(int ixDatabutton)
{
    const int nbrOfButtons = _sizeOfArray-1;
    float d = (float)size().width()/nbrOfButtons;

    int  id = int(0.5 + d);

    float x0 = int(0.5 + ixDatabutton*d);
    float y0 = 0;
    QRect rc(x0,y0, id,id);
    return rc;
}

int HeapTestWidget::indexOfDatabuttonContainingPoint(QPoint pt){
    for (int i=0; i<_sizeOfArray-1 ; i+=1)
        if (rectOfDatabutton(i).contains(pt))
            return i;
    return -1;
}

int HeapTestWidget::indexOfArraycellContainingPoint(QPoint pt){
    for (int i=1; i<_sizeOfArray ; i+=1)
        if (rectOfArrcell(i).contains(pt))
            return i;
    return -1;
}
int HeapTestWidget::indexOfTreecellContainingPoint(QPoint pt){
    for (int i=1; i<_sizeOfArray ; i+=1)
        if (rectOfTreecell(i).contains(pt))
            return i;
    return -1;
}



/*
 *                       1
 *            2                        3
 *       4          5            6           7
 *    8     9    10    11     12    13    14   15
 *  16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 *
 **/

float HeapTestWidget::xCenterOfTreenode(int ix){

   assert( ix>0 && ix<=31 );
   if (ix>=16){
      float w = (float) size().width() / 18;
      return (ix-16)*w + w;
   }
   return (xCenterOfTreenode(2*ix) + xCenterOfTreenode(2*ix+1))/2;
}

QPoint HeapTestWidget::ptCenterOfTreenode(int ix){
   assert( ix>0 && ix<=31 );

   int x = int(xCenterOfTreenode(ix)+0.5);
   int row=0;
   for (int j= ix ; j>0 ; j/=2)
       row+=1;


   float h = size().height() / 9;
   int y = int( 2*h + h*row );

   return QPoint(x,y);
}

QRect HeapTestWidget::rectOfTreecell(int ix){

    int h = rectOfDatabutton(0).height();
    return QRect(-h/2,-h/2, h,h).translated( ptCenterOfTreenode(ix) );
}

QRect HeapTestWidget::rectOfArrcell(int ix){

    float w = (float) size().width()/_sizeOfArray;

    return QRect( ix*w,  rect().bottom()-w, w, w);
}


void HeapTestWidget::paintDatabuttons(QPainter &painter){



    painter.setPen( QPen(Qt::black,1) );

    for (int ix=0; ix<_sizeOfArray-1 ; ix+=1){
        int value = _dataInDatabutton[ix];

        QColor color = colorOfData( value, ix==_indexHoverData );
        painter.setBrush( QBrush(color) );
        QRect rc = rectOfDatabutton(ix);
        painter.drawEllipse(rc);
        if (value>=0){
            painter.drawText(rc, QString::number(value), Qt::AlignVCenter | Qt::AlignHCenter);
        }
    }

}
void HeapTestWidget::paintTree(QPainter &painter){

    painter.setPen( QPen(Qt::black,1) );
    for (int ix=1 ; ix<_sizeOfArray/2 ; ++ix){
        QPoint ptMom  = ptCenterOfTreenode(ix);
        QPoint ptKid1 = ptCenterOfTreenode(2*ix);
        QPoint ptKid2 = ptCenterOfTreenode(2*ix+1);
        painter.drawLine(ptMom, ptKid1);
        painter.drawLine(ptMom, ptKid2);
      }

    for (int ix=1 ; ix<_sizeOfArray ; ++ix){
        if (ix<=_heap.size()){
            int value = _heap.dataAtIndex(ix);
            QColor color = colorOfData(value, ix==_indexHoverArrOrTree);
            painter.setBrush( QBrush(color) );
            QRect rc = rectOfTreecell(ix);
            painter.drawRect(rc);
            painter.drawText(rc, QString::number(value), Qt::AlignVCenter | Qt::AlignHCenter);
        }
        else {
            painter.setBrush( Qt::white);
            painter.drawRect( rectOfTreecell(ix) );
        }
      }

}

void HeapTestWidget::paintArray(QPainter &painter){

    for (int ix=0 ; ix<_sizeOfArray ; ++ix){
        if (ix>0 && ix<=_heap.size()){
            int value = _heap.dataAtIndex(ix);
            QColor color = colorOfData(value, ix == _indexHoverArrOrTree);
            painter.setBrush( QBrush(color) );
            QRect rc = rectOfArrcell(ix);
            painter.drawRect(rc);
            painter.drawText(rc, QString::number(value), Qt::AlignVCenter | Qt::AlignHCenter);
        }
        else {
            painter.setBrush( Qt::white);
            painter.drawRect( rectOfArrcell(ix) );
        }
      }

}


void HeapTestWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pt = event->pos();

    int ixHoverData = indexOfDatabuttonContainingPoint(pt);

    int ixHoverTree = indexOfTreecellContainingPoint(pt);
    int ixHoverArr  = indexOfArraycellContainingPoint(pt);
    int ixHoverArrOrTree = std::max(ixHoverArr, ixHoverTree);

    if (ixHoverData != _indexHoverData){
        _indexHoverData = ixHoverData;
        repaint();

    }
    if (ixHoverArrOrTree != _indexHoverArrOrTree){
        _indexHoverArrOrTree = ixHoverArrOrTree;
        setCursor(Qt::ClosedHandCursor);

        repaint();
    }


    if (ixHoverData != -1 && _dataInDatabutton[ixHoverData]!=-1)
        setCursor(Qt::PointingHandCursor);
    else if (ixHoverTree != -1 && ixHoverTree<=_heap.size())
        setCursor(Qt::ClosedHandCursor);
    else setCursor(Qt::ArrowCursor);

}

void HeapTestWidget::mousePressEvent(QMouseEvent *event)
{
    mouseMoveEvent(event);

    if (_indexHoverData>=0){
        int data = _dataInDatabutton[_indexHoverData];
        if (data>=0){
            _dataInDatabutton[_indexHoverData] = -1;
            _heap.insert(data);
            repaint();
        }
    }
    else if (_indexHoverArrOrTree>=0){
        _heap.percolateDown(_indexHoverArrOrTree);
        repaint();
    }

}


void HeapTestWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    QRect rc = rectOfDatabutton(0);
    QFont font = painter.font();
    font.setPixelSize(0.7*rc.width());
    painter.setFont(font);


    painter.fillRect( event->rect(), Qt::white);
    paintDatabuttons(painter);
    paintTree(painter);
    paintArray(painter);
}

HeapTestWidget::HeapTestWidget(QWidget *parent) : QWidget(parent), _heap(_sizeOfArray)
{
    clearHeap();



    setMouseTracking(true);

}

void HeapTestWidget::clearHeap()
{
    _nbrValues = _sizeOfArray*1.5;
    for (int i=0;i<_sizeOfArray ; i+=1)
        _dataInDatabutton[i] = rand() % _nbrValues;

    _indexHoverData = -1;
    _indexHoverArrOrTree = -1;

    _heap.clear();
    repaint();
}

void HeapTestWidget::fillWithRandomData()
{

    for (int i=0;i<_sizeOfArray ; i+=1)
        _dataInDatabutton[i] = rand() % _nbrValues;

    _heap.fillArrayWithData(_dataInDatabutton, _sizeOfArray-1);
    for (int i=0;i<_sizeOfArray ; i+=1)
        _dataInDatabutton[i] = -1;
    repaint();
}

void HeapTestWidget::deleteMin()
{
    if (_heap.size()<=0)
        return;

    int removedElement = _heap.min();
    _heap.deleteMin();

    for (int i=0;i<_sizeOfArray-1; i+=1)
        if ( _dataInDatabutton[i]==-1){
            _dataInDatabutton[i] = removedElement;
            break;
        }
    repaint();
}

void HeapTestWidget::ragnarsTest()
{
    QString name = QString::fromLatin1( nameOfStudent() );

    if (name=="Homer Simpson"){
        QMessageBox::critical(this, "ragnarsTest", "Du är inte Homer Simpson!");
        return;
    }

    QString message = name + ", din kod kommer att testas!";
    QMessageBox::information(this, "ragnarsTest",  message);




    const int maxSize = _sizeOfArray-1;
    int ordered[maxSize];
    int randomized[maxSize];

    for (int i=0; i<maxSize ; ++i)
            ordered[i] = randomized[i] = i/2;


    //srand(108);


    for (int iteration = 0; iteration<10000; iteration+=1){
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(&randomized[0], &randomized[maxSize],g);


        MinHeap studentsHeap(_sizeOfArray);
        for (int i=0;i<maxSize; i+=1)
            studentsHeap.insert(randomized[i]);

        bool ok = true;
        for (int i=0;i<maxSize; i+=1){

            if (studentsHeap.min() != ordered[i]) {
                ok = false;
                QString err = QString("Testen misslyckades på iteration ")
                        + QString::number(iteration) +  ".";
                QMessageBox::critical(this, "ragnarsTest", err);
                return;
            }
            studentsHeap.deleteMin();
        }
    }

    QMessageBox::information(this, "ragnarsTest", "Grattis " + name + " ragnarsTest lyyckades!");

}


