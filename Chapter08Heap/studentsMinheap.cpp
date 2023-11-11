#include "studentsMinheap.h"
#include "assert.h"



const char* nameOfStudent(){
    return "Homer Simpson";
}

MinHeap::MinHeap(int sizeOfArray)
    :_sizeOfArray(sizeOfArray)
{    
    _theArray = new int[_sizeOfArray];
    _size = 0;
}



void MinHeap::insert(int data){
    assert( !isFull() );   // krascha om full
    _size += 1;
    int ixHole = _size;
    while (ixHole>1 && _theArray[ixHole/2]>data){
        _theArray[ixHole] = _theArray[ixHole/2];
        ixHole /= 2;
    }
    _theArray[ixHole]=data;
}


int MinHeap::min()
{
    assert( _size>0);
    return _theArray[1];
}


void MinHeap::deleteMin(){
    assert( !isEmpty() );
    _theArray[1] = _theArray[_size];
    _size -= 1;
    percolateDown(1);
}


void MinHeap::percolateDown(int ix){
    int hole = ix;
    int value = _theArray[hole];

    while( 2*hole <= _size )
      { int left  = 2*hole;
        int right = left + 1;
        int best = right<=_size && _theArray[right]<_theArray[left]
                           ? right
                           : left;

        if (_theArray[best]>=value)
           break;
        _theArray[hole] = _theArray[best];
        hole = best;
      }
    _theArray[hole] = value;
}

int MinHeap::size()
{
    return _size;
}


// Fyller heapens array med data utan att organisera det i en heap-struktur.
// (detta gör man istället interaktiv)
void MinHeap::fillArrayWithData(int *newData, int size)
{
    assert( size<_sizeOfArray);

    for (int i=1; i<=size ; i+=1)
        _theArray[i] = newData[i];
    _size = size;
}
