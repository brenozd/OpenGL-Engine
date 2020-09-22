#ifndef Buffer_cpp
#define Buffer_cpp

#include "Buffer.h"

template <typename T>
Buffer<T>::Buffer(){}

template <typename T>
Buffer<T>::Buffer(const T *arrayObject, unsigned int size)
{
    _data.insert(_data.end(), arrayObject, arrayObject+size);
    _count = _data.size();
}

template <typename T>
Buffer<T>::~Buffer(){}

template <typename T>
void Buffer<T>::add(T *arrayObject, unsigned int size)
{
    _data.insert(_data.end(), arrayObject, arrayObject+size);
    _count = _data.size();
}

template <typename T>
void Buffer<T>::add(T object)
{
    _data.push_back(object);
    _count++;
}

template <typename T>
void Buffer<T>::removeAt(unsigned int position)
{
    _data.erase(_data.begin()+position);
    _count--;
}

template <typename T>
void Buffer<T>::bind()
{
}

template <typename T>
void Buffer<T>::unbind()
{
}

template <typename T>
void Buffer<T>::setLayout(int componentSize, unsigned int type,bool normalized)
{
    layout.componentSize = componentSize;
    layout.type = type;
    layout.normalized = normalized;
    layout.entryPointer = getDataEntryPointer();
}

#endif