#ifndef MemHelper_H
#define MemHelper_H

namespace slow_logger
{
    template<class T>
    void freePointer(T*& pointer)
    {
        if (pointer)
        {
            delete pointer;
            pointer = NULL;
        }
    }

    template <class TYPE> void deleteObject(TYPE *data)
    {
        if (data) delete  data;
    }

    template <class TYPE> void deleteVector(TYPE *data)
    {
        if (data) delete[]data;
    }

#define UNCOPYABLE(C) \
public:              \
    C(const C&) = delete;      \
    C& operator= (const C&) = delete;

}

#endif
