# list

 doubly-linked list

## 基本要求

用双向链表实现`list`类，提供操作链表相关的迭代器。

提供`algorithm`库内一些不支持非连续空间存储数据结构的函数的实现。

## 接口说明

* 构造与析构：支持默认构造，拷贝构造。

* `list &operator=(const list &other)`

  提供从另一个list赋值的操作，将`other`的数据拷贝之后赋值过来

* `front()` & `back()`

  返回链表头部内容和尾部内容

* `empty()`：链表是否为空

* `size()`：返回链表长度

* `clear()`：清空链表内容

* `insert(iterator pos, const T &value)`

  在`pos`之前插入值为`value`的节点，返回这个节点对应的迭代器

* `erase(iterator pos)`

  删除在`pos`位置的节点，返回下一个节点对应的迭代器

* `push_back()` & `push_front()`

  从尾部或者头部插入节点

* `pop_back()` & `pop_front()`

  从尾部或者头部删除一个节点

* `sort()`：将链表内容排序（升序）

* `merge()`：和合并两个链表，保证两个链表升序，合并完之后要求升序

* `reverse()`：将链表反向

* `unique()`：对于每个连续相同的数据，只保留第一个，删除其他相同数据

## 提示

* 不保证模板类型有默认构造函数，处理方法同`vector`。保证模板类型有`operator<`和`operator==`的定义。
* `sort()`，`merge()` **允许**数据的拷贝和移动， `reverse()`要求**不**拷贝或者移动数据。

* 提供`algorithm.hpp`，可以使用`sjtu::sort()`，接口为数组起始和终止位置以及一个比较函数（参考代码）。
  * 可以尝试显示的实例化，例如`sjtu::sort<T>()`调用。