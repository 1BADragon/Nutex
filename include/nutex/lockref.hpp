#pragma once


namespace nu {

template <typename T>
class LockRef {
public:
    LockRef(T *parent, typename T::value_type *value) :
        _parent(parent), _value(value)
    {}

    ~LockRef() {
        _parent->unlock();
    }

    typename T::value_type& operator*() {
        return *_value;
    }

    typename T::value_type* operator->() {
        return _value;
    }

private:
    T *_parent;
    typename T::value_type *_value;
};

}
