#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
template<typename T>
class list {
protected:
    class node {
    public:
        /**
         * add data members and constructors & destructor
         */
        T *val;
        node *prv, *nxt;

        node() : val(nullptr), prv(nullptr), nxt(nullptr) {}
        node(const T &v) : prv(nullptr), nxt(nullptr) {
            val = new T(v);
        }
        node(T *v) : val(v), prv(nullptr), nxt(nullptr) {}
        virtual ~node() {
            delete val;
        }
    };

private:
    /**
     * clear before calling copy()
     */
    void copy(const list &other) {
        num = other.num;
        for (node *it = other.head->nxt; it != other.nil; it = it->nxt, tail = tail->nxt) {
            tail->nxt = new node(*it->val);
            tail->nxt->prv = tail;
        }
        tail->nxt = nil, nil->prv = tail;
    }

protected:
    /**
     * add data members for linked list as protected members
     */
    size_t num;
    node *head, *tail, *nil;

    /**
     * insert node cur before node pos
     * return the inserted node cur
     */
    node *insert(node *pos, node *cur) {
        pos->prv->nxt = cur, cur->prv = pos->prv;
        cur->nxt = pos, pos->prv = cur;
        if (pos == nil)
            tail = cur;
        num++;
        return cur;
    }
    /**
     * remove node pos from list (no need to delete the node)
     * return the removed node pos
     */
    node *erase(node *pos) {
        pos->prv->nxt = pos->nxt, pos->nxt->prv = pos->prv;
        if (pos == tail)
            tail = pos->prv;
        num--;
        return pos;
    }

public:
    class const_iterator;
    class iterator {
        friend class list;
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        node *ptr;
        list *ctx;
    public:
        iterator() : ptr(nullptr), ctx(nullptr) {}
        iterator(node *ptr_, list *ctx_) : ptr(ptr_), ctx(ctx_) {}
        bool invalid(list *target) const{
            return target != ctx || !ptr || ptr == ctx->nil;
        }
        /**
         * iter++
         */
        iterator operator++(int) {
            if (!ptr || ptr == ctx->nil)
                throw invalid_iterator();
            iterator ret = *this;
            ptr = ptr->nxt;
            return ret;
        }
        /**
         * ++iter
         */
        iterator & operator++() {
            if (!ptr || ptr == ctx->nil)
                throw invalid_iterator();
            ptr = ptr->nxt;
            return *this;
        }
        /**
         * iter--
         */
        iterator operator--(int) {
            if (!ptr || ptr->prv == ctx->head)
                throw invalid_iterator();
            iterator ret = *this;
            ptr = ptr->prv;
            return ret;
        }
        /**
         * --iter
         */
        iterator & operator--() {
            if (!ptr || ptr->prv == ctx->head)
                throw invalid_iterator();
            ptr = ptr->prv;
            return *this;
        }
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T & operator *() const {
            if (ptr == ctx->nil)
                throw invalid_iterator();
            return *ptr->val;
        }
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const noexcept {
            if (ptr == ctx->nil)
                throw invalid_iterator();
            return ptr->val;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
        bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     * should be able to construct from an iterator.
     */
    class const_iterator {
        friend class list;
    private:
        node *ptr;
        const list *ctx;
    public:
        const_iterator() : ptr(nullptr), ctx(nullptr) {}
        const_iterator(node *ptr_, const class list *ctx_) : ptr(ptr_), ctx(ctx_) {}
        const_iterator(const iterator &other) : ptr(other.ptr), ctx(other.ctx) {}
        /**
         * check whether the iterator is valid
         * maybe used for linked_hashmap
         */
        bool invalid(list *target) const{
            return target != ctx || !ptr || ptr == ctx->nil;
        }
        /**
         * iter++
         */
        const_iterator operator++(int) {
            if (!ptr || ptr == ctx->nil)
                throw invalid_iterator();
            const_iterator ret = *this;
            ptr = ptr->nxt;
            return ret;
        }
        /**
         * ++iter
         */
        const_iterator & operator++() {
            if (!ptr || ptr == ctx->nil)
                throw invalid_iterator();
            ptr = ptr->nxt;
            return *this;
        }
        /**
         * iter--
         */
        const_iterator operator--(int) {
            if (!ptr || ptr->prv == ctx->head)
                throw invalid_iterator();
            const_iterator ret = *this;
            ptr = ptr->prv;
            return ret;
        }
        /**
         * --iter
         */
        const_iterator & operator--() {
            if (!ptr || ptr->prv == ctx->head)
                throw invalid_iterator();
            ptr = ptr->prv;
            return *this;
        }
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        const T & operator *() const {
            if (ptr == ctx->nil)
                throw invalid_iterator();
            return *ptr->val;
        }
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        const T * operator ->() const noexcept {
            if (ptr == ctx->nil)
                throw invalid_iterator();
            return ptr->val;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
        bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    list() : num(0) {
        head = tail = new node;
        tail->nxt = nil = new node, nil->prv = tail;
    }
    list(const list &other) {
        head = tail = new node;
        tail->nxt = nil = new node, nil->prv = tail;
        this->copy(other);
    }
    /**
     * TODO Destructor
     */
    virtual ~list() {
        list<T>::clear();
        delete head;
        delete nil;
    }
    /**
     * TODO Assignment operator
     */
    list &operator=(const list &other) {
        if (this == &other)
            return *this;
        this->clear();
        this->copy(other);
        return *this;
    }
    /**
     * access the first / last element
     * throw container_is_empty when the container is empty.
     */
    const T & front() const {
        if (this->empty())
            throw container_is_empty();
        return *head->nxt->val;
    }
    const T & back() const {
        if (this->empty())
            throw container_is_empty();
        return *tail->val;
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return iterator(head->nxt, this);
    }
    const_iterator cbegin() const {
        return const_iterator(head->nxt, this);
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(nil, this);
    }
    const_iterator cend() const {
        return const_iterator(nil, this);
    }
    /**
     * checks whether the container is empty.
     */
    virtual bool empty() const {
        return head == tail;
    }
    /**
     * returns the number of elements
     */
    virtual size_t size() const {
        return num;
    }

    /**
     * clears the contents
     */
    virtual void clear() {
        for (; tail != head;) {
            node *t = tail;
            tail = tail->prv;
            delete t;
        }
        tail->nxt = nil, nil->prv = tail;
        num = 0;
    }
    /**
     * insert value before pos (pos may be the end() iterator)
     * return an iterator pointing to the inserted value
     * throw if the iterator is invalid
     */
    virtual iterator insert(iterator pos, const T &value) {
        if (pos.ctx != this)
            throw invalid_iterator();
        return iterator(insert(pos.ptr, new node(value)), this);
    }
    /**
     * remove the element at pos (the end() iterator is invalid)
     * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
     * throw if the container is empty, the iterator is invalid
     */
    virtual iterator erase(iterator pos) {
        if (empty())
            throw container_is_empty();
        if (pos.ctx != this || pos.ptr == nil)
            throw invalid_iterator();
        iterator ret = iterator(pos.ptr->nxt, this);
        delete erase(pos.ptr);
        return ret;
    }
    /**
     * adds an element to the end
     */
    void push_back(const T &value) {
        insert(nil, new node(value));
    }
    /**
     * removes the last element
     * throw when the container is empty.
     */
    void pop_back() {
        if (empty())
            throw container_is_empty();
        delete erase(tail);
    }
    /**
     * inserts an element to the beginning.
     */
    void push_front(const T &value) {
        insert(head->nxt, new node(value));
    }
    /**
     * removes the first element.
     * throw when the container is empty.
     */
    void pop_front() {
        if (empty())
            throw container_is_empty();
        delete erase(head->nxt);
    }
    /**
     * sort the values in ascending order with operator< of T
     */
    void sort() {
        T **arr = new T*[num];
        int idx = 0;
        for (node *ptr = head->nxt; ptr != nil; ptr = ptr->nxt)
            arr[idx++] = ptr->val;
        sjtu::sort<T *>(arr, arr + idx, [](T* x, T* y) -> bool { return *x < *y; });
        idx = 0;
        for (node *ptr = head->nxt; ptr != nil; ptr = ptr->nxt)
            ptr->val = arr[idx++];
        delete [] arr;
    }
    /**
     * merge two sorted lists into one (both in ascending order)
     * compare with operator< of T
     * container other becomes empty after the operation
     * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
     * the order of equivalent elements of *this and other does not change.
     * no elements are copied or moved
     */
    void merge(list &other) {
        for (iterator cur = begin(); cur != end() || !other.empty(); ) {
            if (cur == end())
                insert(cur.ptr, other.erase(other.head->nxt));
            else if (other.empty())
                break;
            else if (other.front() < *cur)
                insert(cur.ptr, other.erase(other.head->nxt));
            else cur++;
        }
    }
    /**
     * reverse the order of the elements
     * no elements are copied or moved
     */
    void reverse() {
        if (empty()) return ;
        for (node *cur = head->nxt, *nxt; cur != nil; cur = nxt) {
            nxt = cur->nxt;
            std::swap(cur->prv, cur->nxt);
        }
        std::swap(tail, head->nxt);
        head->nxt->prv = head, tail->nxt = nil, nil->prv = tail;
    }
    /**
     * remove all consecutive duplicate elements from the container
     * only the first element in each group of equal elements is left
     * use operator== of T to compare the elements.
     */
    void unique() {
        if (empty()) return ;
        iterator prv = begin(), it = prv;
        for (it++; it != end();) {
            if (*prv == *it)
                it = this->erase(it);
            else prv = it, it++;
        }
    }
};

}

#endif //SJTU_LIST_HPP
