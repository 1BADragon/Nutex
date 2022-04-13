#pragma once

#include <mutex>
#include <optional>

namespace nu {

template<typename T>
class RLockRef {
public:
    RLockRef(T *parent, typename T::value_type *value) :
        _parent(parent), _value(value)
    {}

    ~RLockRef() {
        _parent->runlock();
    }

    const typename T::value_type &operator*() {
        return *_value;
    }

    const typename T::value_type *operator->() {
        return _value;
    }

private:
    T *_parent;
    typename T::value_type *_value;
};

template<typename T>
class WLockRef {
public:
    WLockRef(T *parent, typename T::value_type *value) :
        _parent(parent), _value(value)
    {}

    ~WLockRef() {
        _parent->wunlock();
    }

    typename T::value_type &operator*() {
        return *_value;
    }

    typename T::value_type *operator->() {
        return _value;
    }

private:
    T *_parent;
    typename T::value_type *_value;
};

template<typename T, typename MutexType = std::mutex>
class RWLock {
public:
    using value_type = T;
    using rref_type = RLockRef<RWLock<T, MutexType>>;
    using wref_type = WLockRef<RWLock<T, MutexType>>;


    template<typename ...Args>
    RWLock(Args ...args)
        : _val(args...), _mut(), _read_lock_cnt(0)
    {

    }

    ~RWLock()
    {
        auto ref = this->write();
    }




private:
    T _val;
    MutexType _mut;
    int _read_lock_cnt;

    friend rref_type;
    friend wref_type;

    void runlock() {

    }

    void wunlock() {

    }
};

}
