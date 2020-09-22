#ifndef Buffer_h
#define Buffer_h

#include "Renderer.h"

#include <vector>
#include <iostream>
#include <iomanip>

template <typename T>
class Buffer
{
    struct Layout
    {
        int componentSize = 0;
        unsigned int type = 0;
        bool normalized = 0;
        const void *entryPointer;
    };

private:
    std::vector<T> _data;
    unsigned int _count = 0;

public:
    unsigned int type = 0;
    unsigned int rendererId = 0;
    Layout layout;

    Buffer();
    Buffer(const T *array, unsigned int size);
    virtual ~Buffer();

    void add(T object);
    void add(T *array, unsigned int size);
    void removeAt(unsigned int position);

    virtual void bind();
    virtual void unbind();

    void setLayout(int componentSize, unsigned int type,bool normalized);

    inline unsigned int getCount() const { return _count; };

    inline std::vector<T> getData() const { return _data; };

    inline const void *getDataEntryPointer() const { return (void *)&_data[0]; };

    friend std::ostream &operator<<(std::ostream &os, const Buffer &buff)
    {
        for (unsigned int i = 0; i < buff.getCount(); i++)
        {
            os << std::fixed << std::setprecision(3) << "[" << i << ", " << buff.getData()[i] << "] ";
        }

        os << "\n"
           << std::flush;
        return os;
    }
};

#endif