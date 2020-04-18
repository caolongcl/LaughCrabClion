//#pragma once
//
//#include <cstddef>
//#include "MemoryManager.hpp"
//
//namespace PopEngine {
///**************************
// ******reference : STL ****
// **************************/
//template<typename T>
//class Allocator {
//public:
//    using size_type         = size_t;
//    using difference_type   = ptrdiff_t;
//    using pointer           = T *;
//    using const_pointer     = const T *;
//    using reference         = T &;
//    using const_reference   = const T &;
//    using value_type        = T;
//
//    Allocator() {}
//
//    Allocator(const Allocator &) {}
//
//    template<typename T1>
//    Allocator(const Allocator<T1> &) {}
//
//    ~Allocator() {}
//
//    pointer address(reference x) const { return &x; }
//
//    const_pointer address(const_reference x) const { return &x; }
//
//    T *allocate(size_type n, const void * = 0) {
//        return n != 0 ? static_cast<T *>(Memory()->allocate(n * sizeof(T))) : nullptr;
//    }
//
//    void deallocate(pointer p, size_type n) {
//        Memory()->deallocate(p, n * sizeof(T));
//    }
//
//    size_type max_size() const {
//        return size_t(-1) / sizeof(T);
//    }
//
//    template<typename... Arguments>
//    void construct(pointer p, Arguments... parameters) {
//        new(p) T(parameters...);
//    }
//
//    /* T need copy/move copy construct*/
//    void construct(pointer p, const T &val) {
//        new(p) T(val);
//    }
//
//    void destroy(pointer p) { p->~T(); }
//};
//}
