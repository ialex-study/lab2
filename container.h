#ifndef CONTAINER_H
#define CONTAINER_H

template <class Object>
class Container
{
    Object **arr;
    int arrSize, currentSize = 0;
public:
    Container(int size = 0);

    void addObj(Object *obj);
    Object* getObj(int pos);
    Object* removeObj(int pos);
    int getArrSize();
    int getCurrentSize();
    void deleteAll();
    void setObject(Object* obj, int pos);

    Object* operator[](int pos);
};

#endif // CONTAINER_H
