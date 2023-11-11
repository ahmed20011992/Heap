#include "studentsMinheap.h"
#include "assert.h"



const char* nameOfStudent(){
    return "Ahmed Elhasan";
}

MinHeap::MinHeap(int sizeOfArray)
    :m_sizeOfArray(sizeOfArray)
{    
    n_theArray = new int[m_sizeOfArray];
    m_size = 0;
}

MinHeap::~MinHeap(){
   // TODO
    delete [] n_theArray;
}

void MinHeap::insert(int data){
    // TODO
    assert(!isFull());
    m_size+=1;
    int ixHole =m_size;
    while (ixHole > 1 && n_theArray[ixHole/2] > data){
        n_theArray[ixHole]=n_theArray[ixHole/2];
        ixHole/=2;
    }
    n_theArray[ixHole]=data;
}


int MinHeap::min()
{
    // TODO
    return n_theArray[1];// BUG
}


void MinHeap::deleteMin(){
    assert( !isEmpty() );
    n_theArray[1] = n_theArray[m_size];
     m_size -= 1;
     percolateDown(1);
    // TODO


}


void MinHeap::percolateDown(int ix){
    // TODO
    int value = n_theArray[ix];

      while( ix*2 <= m_size )
        { int ixKid = ix*2;
          if (ixKid!=m_size && n_theArray[ixKid+1]<n_theArray[ixKid])
             ixKid += 1;

          if (n_theArray[ixKid]>=value)
             break;
          n_theArray[ix] = n_theArray[ixKid];
          ix = ixKid;
        }
         n_theArray[ix] = value;
}

int MinHeap::size()
{
    return m_size;
}


// Fyller heapens array med data utan att organisera det i en heap-struktur.
// (detta gör man istället interaktiv)
void MinHeap::fillArrayWithData(int *newData, int size)
{
    assert( size<m_sizeOfArray);

    for (int i=1; i<=size ; i+=1)
        n_theArray[i] = newData[i];
    m_size = size;
}
