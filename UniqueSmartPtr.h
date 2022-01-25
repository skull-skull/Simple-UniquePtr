#pragma once

template<class T>
class UniqueSmartPtr final
{
public:
    UniqueSmartPtr(T* Pointer);
    UniqueSmartPtr(UniqueSmartPtr<T>&& NewUSPointer);
    UniqueSmartPtr(const UniqueSmartPtr<T>& NewUSPointer) = delete;

    ~UniqueSmartPtr();

    bool operator bool() const;
    UniqueSmartPtr<T>& operator=(UniqueSmartPtr<T>&& NewUSPoiner);
    UniqueSmartPtr<T>& operator=(UniqueSmartPtr<T>& NewUSPoiner) = delete;
    T& operator*();
    T* operator->();

    T* Release();
    T* Get();
    void Reset(T* NewSource);

private:
    void CleanUp();

    T* Source
};

template<class T>
inline T* UniqueSmartPtr<T>::Release()
{
    T* RetVal = Source;
    CleanUp();
    return RetVal;
}

template<class T>
inline T* UniqueSmartPtr<T>::Get()
{
    return Source;
}

template<class T>
inline void UniqueSmartPtr<T>::Reset(T* NewSource)
{
    CleanUp();
    Source = NewSource;
}

template<class T>
inline void UniqueSmartPtr<T>::CleanUp()
{
    if (Source)
    {
        delete Source;
        Source = nullptr;
    }
}

template<class T>
inline UniqueSmartPtr<T>::UniqueSmartPtr(T* Ptr)
    : Source(Ptr)
{
}

template<class T>
inline UniqueSmartPtr<T>::UniqueSmartPtr(UniqueSmartPtr<T>&& NewUSPointer)
    : Source(NewUSPointer.Release())
{
}

template<class T>
inline UniqueSmartPtr<T>::operator bool() const
{
    return Source ? true : false;
}

template<class T>
inline UniqueSmartPtr<T>& UniqueSmartPtr<T>::operator=(UniqueSmartPtr<T>&& NewUSPoiner)
{
    if (this == &NewUSPoiner)
        return *this;

    CleanUp();
    Source = NewUSPoiner.Release();

    return *this;
}

template<class T>
inline T& UniqueSmartPtr<T>::operator*()
{
    return *Source;
}

template<class T>
inline T* UniqueSmartPtr<T>::operator->()
{
    return Source;
}


template<class T>
inline UniqueSmartPtr<T>::~UniqueSmartPtr()
{
    CleanUp();
}
