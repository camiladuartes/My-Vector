#include <iostream>
#include <cassert>
#include <cstring>
#include "../include/vector.h"

/*!
 * Test set with `assert`.
 */
int main(void){
/// 2.1 Constructors, Destructors, and Assignment
// #Test 1: vector();
    sc::vector<int> v1;
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);
// #Test 2: explicit vector(size_type count);
    sc::vector<int> v2(4);
    assert(v2.size() == 4);
    assert(v2.capacity() == 8);
// #Test 7: vector& operator=(const vector& other);
    sc::vector<int> v3;
    v3 = v2;
    assert(v3.size() == 4);
    assert(v3.capacity() == 8); //ocupped all vector with 0, than the vector was doubled
// #Test 5: vector(std::initializer_list<T> ilist);
    sc::vector<int>array_v4{1,2,3};
    assert(array_v4.size() == 3);
    assert(array_v4.capacity() == 6);
// #Test 8: vector& operator=(std::initializer_list<T> ilist);
    v3 = array_v4;
    assert(v3.size() == 3);
    assert(v3.capacity() == 6);
// #Test 3: vector(InputIt first, InputIt last);
    int *first = &array_v4[0];
    int *last = &array_v4[3];
    sc::vector<int> v(first, last);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(v.size() == 3);
    assert(v.capacity() == 6);
// #Test 4: vector(const vector& other);
    sc::vector<int>v5(array_v4);
    assert(v5.size() == 3);
    assert(v5.capacity() == 6); //6 because was doubled
// #Test 6: ∼vector();

/// 2.2 Common operations to all list implementations
// #Test 1: size_type size() const; -> tested previously
// #Test 2: void clear();
    v5.clear();
    assert(v5.size() == 0);
    assert(v5.capacity() == 6);
// #Test 3: bool empty();
    assert(v2.empty() == false);
    assert(v1.empty() == true);
    assert(v5.empty() == true); //v5 was cleaned
// #Test 4: void push_front(const T &value);
    sc::vector<int>v6{3,4,5};
    v6.push_front(2);
    assert(v6[0] == 2);
    assert(v6[1] == 3);
    assert(v6[2] == 4);
    assert(v6[3] == 5);
// #Test 5: void push_back(const T &value);
    sc::vector<int>v7{2,3,4};
    v7.push_back(5);
    assert(v7[0] == 2);
    assert(v7[1] == 3);
    assert(v7[2] == 4);
    assert(v7[3] == 5);
    assert(v7.size() == 4);
// #Test 6: void pop_back();
    sc::vector<int> v8{9,8,7,6};
    v8.pop_back();
    assert(v8.size() == 3);
//Test #7: void pop_front();
    v8.pop_front();
    assert(v8.size() == 2);
    assert(v8[0] == 8);
    assert(v8[1] == 7);
//Test #8: const T& back() const;
    assert(v7.back() == 5);
    assert(v1.back() == 0);
//Test #9: const T& front() const;
    assert(v7.front() == 2);
//Test #10: void assign(sizet_type count, const T &value);
    sc::vector<int> v9{1,2};
    v9.assign(5, 566);
    assert(v9.size() == 5);
    assert(v9.capacity() == 5);
    assert(v9[0] == 566);

/// 2.3 Operations exclusive to dynamic array implementation
// Test #1: T & operator[](size_type pos);
    assert(v9[0] == 566);
// Test #2: T & at (size_type pos);
    assert(v9.at(0) == 566);
    // assert(v9.at(5) == 566); //Commented because causes intended error
//Test #3: size_type capacity() const;
    assert(v9.capacity() == 5);
}