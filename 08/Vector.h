#ifndef Vector_h
#define Vector_h

#include <algorithm>

template <class T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;
    
    pointer allocate(size_type count) {
        pointer result = static_cast<pointer>(malloc(count * sizeof(value_type)));
        if (!result)
            throw std::bad_alloc();
        return result;
    }
    void deallocate(pointer ptr, size_type count) {
        free(ptr);
    }
    
    size_t max_size() const noexcept {
        return -1;
    }
};


template <typename T>
class Iterator {
    T* ptr_;
public:
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;
    
    explicit Iterator(T* ptr): ptr_(ptr) {
    }
    
    Iterator(const Iterator& it) : ptr_(it.ptr_) {
    }
    
    bool operator==(const Iterator<T>& other) const {
        return ptr_ == other.ptr_;
    }
    
    bool operator!=(const Iterator<T>& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Iterator<T>& other) const {
        return ptr_ < other.ptr_;
    }
    
    bool operator>(const Iterator<T>& other) const {
        return other < *this;
    }
    
    bool operator<=(const Iterator<T>& other) const {
        return !(*this > other);
    }
    
    bool operator>=(const Iterator<T>& other) const {
        return !(*this < other);
    }
    
    reference operator*() const {
        return *ptr_;
    }
    
    pointer operator->() const {
        return ptr_;
    }
    
    reference operator[](difference_type i) {
        return ptr_[i];
    }
    
    Iterator& operator++() {
        ++ptr_;
        return *this;
    }
    
    Iterator& operator--() {
        --ptr_;
        return *this;
    }
    
    Iterator operator++(int) {
        Iterator tmp(*this);
        ++ptr_;
        return tmp;
    }
    
    Iterator operator--(int) {
        Iterator tmp(*this);
        --ptr_;
        return tmp;
    }
    
    difference_type operator-(const Iterator& it) const {
        return ptr_-it.ptr_;
    }
    
    Iterator operator+(difference_type i) const {
        return Iterator(ptr_+i);
    }
    
    Iterator operator-(difference_type i) const {
        return Iterator(ptr_-i);
    }
};


template <class T, class Alloc = Allocator<T>>
class Vector {
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using allocator_type = Alloc;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<Iterator<T>>;
    
    Vector():
        alloc_(Alloc()),
        size_(0),
        capacity_(1),
        data_(alloc_.allocate(capacity_))
    {
    }
    
    explicit Vector(size_type count):
        alloc_(Alloc()),
        size_(count),
        capacity_(std::max(count, 1ul)),
        data_(alloc_.allocate(capacity_))
    {
        for (size_type i = 0; i < size_; ++i)
            std::allocator_traits<Alloc>::construct(alloc_, data_+i);
    }
    
    Vector(size_type count, const value_type& default_value):
        alloc_(Alloc()),
        size_(count),
        capacity_(std::max(count, 1ul)),
        data_(alloc_.allocate(capacity_))
    {
        for (size_type i = 0; i < size_; ++i)
            std::allocator_traits<Alloc>::construct(alloc_, data_+i, default_value);
    }
    
    Vector(std::initializer_list<value_type> init):
        alloc_(Alloc()),
        size_(init.size()),
        capacity_(std::max(init.size(), 1ul)),
        data_(alloc_.allocate(capacity_))
    {
        for (size_type i = 0; i < size_; ++i)
            std::allocator_traits<Alloc>::construct(alloc_, data_+i, *(init.begin()+i));
    }
    
    iterator begin() noexcept {
        return iterator(data_);
    }

    iterator end() noexcept {
        return iterator(data_+size_);
    }
    
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }
    
    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }
    
    reference operator[](size_type pos) {
        return data_[pos];
    }

    const_reference operator[](size_type pos) const {
        return data_[pos];
    }

    void push_back(value_type&& value) {
        if(size_ == capacity_)
            reserve(2 * capacity_);
        std::allocator_traits<Alloc>::construct(alloc_, data_ + size_++, std::move(value));
    }
    
    void push_back(const value_type& value) {
        if(size_ == capacity_)
            reserve(2 * capacity_);
        std::allocator_traits<Alloc>::construct(alloc_, data_ + size_++, value);
    }
    
    void pop_back() {
        std::allocator_traits<Alloc>::destroy(alloc_, data_ + --size_);
    }
    
    void clear() {
        for (size_type i = 0; i < size_; ++i)
            std::allocator_traits<Alloc>::destroy(alloc_, data_ + i);
        size_ = 0;
    }
    
    void reserve(size_type count) {
        if (count <= capacity_)
            return;
        T* new_data(alloc_.allocate(count));
        for (size_type i = 0; i < size_; ++i) {
            std::allocator_traits<Alloc>::construct(alloc_, new_data + i, std::move(*(data_ + i)));
            std::allocator_traits<Alloc>::destroy(alloc_, data_ + i);
        }
        capacity_ = count;
        data_ = new_data;
    }
    
    void resize(size_type new_size) {
        _resize(new_size);
    }
    
    void resize(size_type new_size, const value_type& default_value) {
        _resize(new_size, default_value);
    }
    
    bool empty() const noexcept {
        return size_ == 0;
    }
    
    size_type size() const noexcept {
        return size_;
    }
    
    ~Vector() {
        clear();
        alloc_.deallocate(data_, capacity_);
    }
    
private:
    Alloc alloc_;
    size_type size_;
    size_type capacity_;
    T* data_;
    
    template<typename... Args>
    void _resize(size_type new_size, Args... args) {
        reserve(new_size);
        
        for (size_type i = size_; i < new_size; ++i) {
            std::allocator_traits<Alloc>::construct(alloc_, data_ + i, args...);
        }
        for (size_type i = new_size; i < size_ ; ++i) {
            std::allocator_traits<Alloc>::destroy(alloc_, data_ + i);
        }
        size_ = new_size;
    }
    
};

#endif /* Vector_h */
