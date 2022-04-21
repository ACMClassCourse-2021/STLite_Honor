#ifndef SJTU_LINKED_HASHMAP_HPP_STD
#define SJTU_LINKED_HASHMAP_HPP_STD

#include <cstddef>
#include <functional>
#include "utility.hpp"
#include "algorithm.hpp"
#include "exceptions.hpp"
#include "list.hpp"

namespace sjtu {
	/**
	 *  Maintains key-value pairs just like MAP
	 *  Dynamically sized hash table who handles collision with linked lists
	 *  Iterators arrange in order of insertion (maintained by base class LIST)
	 */

template <
        class Key,
        class Value,
        class Hash = std::hash<Key>,
        class Equal = std::equal_to<Key>
>
class linked_hashmap : public list<pair<const Key, Value> > {
public:
    using value_type = pair<const Key, Value>;

private:
    class Node : public list<value_type>::node {
    public:
        /**
         * add data members in addition to class node in LIST
         */

    };

    /**
     * singly-linked list used for hash collision
     */
    class BucketList {
    public:
        /**
         * data members, constructors and destructor
         */

        /**
         *  TODO find corresponding Node with key o
         */
        Node * find(const Key &o) {}
        /**
         * TODO insert key-value pair(k, v) into this BucketList
         * return this new Node
         */
        Node * insert(const Key &k, const Value &v) {}
        Node * insert(const value_type &kv) {}
        /**
         * TODO remove the Node with key k from this BucketList (no need to delete)
         * return the removed Node
         */
        Node * erase(const Key &k) {}
    };

    /**
     * add data members as needed and necessary private function such as resize()
     */

public:
    /**
     * iterator is the same as LIST
     */
    using iterator = typename list<value_type>::iterator;
    using const_iterator = typename list<value_type>::const_iterator;

    /**
    * TODO two constructors
    */
    linked_hashmap() {}
    linked_hashmap(const linked_hashmap &other) {}
    /**
	 * TODO assignment operator
	 */
    linked_hashmap &operator=(const linked_hashmap &other) {}
    /**
	 * TODO Destructors
	 */
    ~linked_hashmap() {}
    /**
	 * TODO access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
    Value &at(const Key &key) {}
    const Value &at(const Key &key) const {}
    /**
	 * TODO access specified element
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
    Value &operator[](const Key &key) {}
    /**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
    const Value &operator[](const Key &key) const {}
    /**
	 * TODO override clear() in LIST
	 */
    void clear() override{}
    /**
	 * TODO insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion),
	 *   the second one is true if insert successfully, or false.
	 */
    pair<iterator, bool> insert(const value_type &value) {}
    /**
	 * TODO erase the element at pos.
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
     * return anything, it doesn't matter
	 */
    iterator erase(iterator pos) override{}
    /**
	 * TODO Returns the number of elements with key
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0
	 *     since this container does not allow duplicates.
	 */
    size_t count(const Key &key) const {}
    /**
	 * TODO Finds an element with key equivalent to key.
	 * return iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
    iterator find(const Key &key) {}
    const_iterator find(const Key &key) const {}
};

}

#endif