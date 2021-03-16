#include "container.h"

template <class Object>
Container<Object>::Container(int size)
    : arrSize(size)
{
    arr = new Object*[size];
}
template <class Object>
void Container<Object>::addObj(Object *obj)
{
    if(currentSize == arrSize) {
        arrSize++;
        Object **temp = arr;
        arr = new Object*[arrSize];
        for(int i = 0; i < arrSize - 1; i++)
        {
            arr[i] = temp[i];
        }
        arr[currentSize++] = obj;
        for(int i = 0; i< arrSize - 1; i++)
            delete temp[i];
        delete[] temp;
    }
    else {
        arr[currentSize++] = obj;
    }
}
template <class Object>
Object* Container<Object>::getObj(int pos)
{
    return arr[pos];
}
template <class Object>
Object* Container<Object>::removeObj(int pos)
{
    Object* obj = arr[pos];
    Object** temp = arr;
    arr = new Object*[--arrSize];
    currentSize--;
    for(int i = 0, k = 0; i < currentSize + 1; i++)
    {
        if(i != pos)
            arr[k++] = temp[i];
    }
    delete[] temp;
    return obj;
}
template <class Object>
int Container<Object>::getArrSize()
{
    return arrSize;
}
template <class Object>
int Container<Object>::getCurrentSize()
{
    return currentSize;
}
template <class Object>
void Container<Object>::deleteAll()
{
    for(int i = 0; i < currentSize; i++)
    {
        delete arr[i];
    }
    currentSize = 0;
}
template <class Object>
Object* Container<Object>::operator[](int pos)
{
    return arr[pos];
}
template <class Object>
void Container<Object>::setObject(Object* obj, int pos)
{
    arr[pos] = obj;
}
