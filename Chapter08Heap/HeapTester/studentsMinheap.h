#ifndef MINHEAP_H
#define MINHEAP_H


const char* nameOfStudent();


class MinHeap
{

public:
    MinHeap(int sizeOfArray);
    ~MinHeap();

    void insert(int data);

    void deleteMin();
    int  min();

    void percolateDown(int ix);

    int  size();
    bool isFull() { return m_size >= (m_sizeOfArray-1); }
    bool isEmpty() { return m_size == 0; }

    void clear()   { m_size = 0; }

    int  dataAtIndex(int index) { return n_theArray[index]; }
    void fillArrayWithData(int* newData, int size);
private:

    int  m_sizeOfArray;
    int  *n_theArray;
    int  m_size;




};

#endif // MINHEAP_H
