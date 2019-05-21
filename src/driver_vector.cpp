#include <iostream>
#include <cassert>
#include <cstring>
#include "../include/vector.h"

/*!
 * Test set with `assert`.
 */
int main(void){
//=== [2.1] Constructors, Destructors, and Assignment
    /// #Test 1: vector();
        sc::vector<int> v1;
        assert(v1.size() == 0);
        assert(v1.capacity() == 0);
    /// #Test 2: explicit vector(size_type count);
        sc::vector<int> v2(4);
        assert(v2.size() == 0);
        assert(v2.capacity() == 4);
    /// #Test 7: vector& operator=(const vector& other);
        sc::vector<int> v3;
        v3 = v2;
        assert(v3.size() == 0);
        assert(v3.capacity() == 4);
    /// #Test 5: vector(std::initializer_list<T> ilist);
        sc::vector<int>array_v4{1,2,3};
        assert(array_v4.size() == 3);
        assert(array_v4.capacity() == 3);
    /// #Test 8: vector& operator=(std::initializer_list<T> ilist);
        v3 = array_v4;
        assert(v3.size() == 3);
        assert(v3.capacity() == 3);
    /// #Test 3: vector(InputIt first, InputIt last);
        int *first = &array_v4[0];
        int *last = &array_v4[3];
        sc::vector<int> v(first, last);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 3);
        assert(v.size() == 3);
        assert(v.capacity() == 6);
    /// #Test 4: vector(const vector& other);
        sc::vector<int>v5(array_v4);
        assert(v5.size() == 3);
        assert(v5.capacity() == 3); //6 because was doubled
    /// #Test 6: ∼vector();

//=== [2.2] Common operations to all list implementations
    /// #Test 1: size_type size() const; -> tested previously
    /// #Test 2: void clear();
        v5.clear();
        assert(v5.size() == 0);
        assert(v5.capacity() == 3);
    /// #Test 3: bool empty();
        assert(v2.empty() == true);
        assert(v1.empty() == true);
        assert(v5.empty() == true); //v5 was cleaned
    /// #Test 4: void push_front(const T &value);
        sc::vector<int>v6{3,4,5};
        v6.push_front(2);
        assert(v6[0] == 2);
        assert(v6[1] == 3);
        assert(v6[2] == 4);
        assert(v6[3] == 5);
    /// #Test 5: void push_back(const T &value);
        sc::vector<int>v7{2,3,4};
        v7.push_back(5);
        assert(v7[0] == 2);
        assert(v7[1] == 3);
        assert(v7[2] == 4);
        assert(v7[3] == 5);
        assert(v7.size() == 4);
    /// #Test 6: void pop_back();
        sc::vector<int> v8{9,8,7,6};
        v8.pop_back();
        assert(v8.size() == 3);
    /// Test #7: void pop_front();
        v8.pop_front();
        assert(v8.size() == 2);
        assert(v8[0] == 8);
        assert(v8[1] == 7);
    /// Test #8: const T& back() const;
        assert(v7.back() == 5);
        assert(v1.back() == 0);
    /// Test #9: const T& front() const;
        assert(v7.front() == 2);
    /// Test #10: void assign(sizet_type count, const T &value);
        sc::vector<int> v9{1,2};
        v9.assign(5, 566);
        assert(v9.size() == 5);
        assert(v9.capacity() == 5);
        assert(v9[0] == 566);

//=== [2.3] Operations exclusive to dynamic array implementation
    /// Test #1: T & operator[](size_type pos);
        assert(v9[0] == 566);
    /// Test #2: T & at (size_type pos);
        assert(v9.at(0) == 566);
        // assert(v9.at(5) == 566); //Commented because causes intended error
    /// Test #3: size_type capacity() const;
        assert(v9.capacity() == 5);
    /// Test #4: void reserve(size_type new_cap);
        v9.reserve(8);
        assert(v9.capacity() == 8);
        v9.reserve(2);
        assert(v9.capacity() == 8);

//=== [2.4] Operator overloading — non-member functions
    /// Test #1: bool operator==(const vector& lhs, const vector& rhs);
    sc::vector<int> v10{1,2};
    sc::vector<int> v11{1};
    bool var = v10 == v11;
    assert(var == 0);
//=== [3] Iterators
//=== [3.1] Getting an iterator
    ///iterator end();
        sc::vector<int> vv{1, 2, 3};
        for(int i = 0; i < *(vv.end()-1); i++){
            vv.push_back(4);
        }
        assert(vv[0] == 1);
        assert(vv[1] == 2);
        assert(vv[2] == 3);
        assert(vv[3] == 4);
        assert(vv[4] == 4);
        assert(vv[5] == 4);
        assert(vv[6] == 4);
        assert(vv.size() == 7);
//=== [3.2] Iterator operations
    /// operator++();
        int *it;
        it = &v10[0];
        assert(*(++it) == 2);
    /// operator*();
        *it = 1;
        assert(*it == 1);
        assert(v10[1] == 1);
    /// operator-();
        int *it2;
        it2 = &v10[0];
        assert(it - it2 == 1);
    /// friend operator+(int n, iterator it); & friend operator+(iterator it, int n);
        sc::vector<int> v12{4,5,6};
        int *it3, *it4;
        it3 = &v12[0];
        it4 = it3+2;
        assert(*it4 == 6);
        it4 = it3+1;
        assert(*it4 == 5);
    /// friend operator-(int n, iterator it); & friend operator-(iterator it, int n);
        it3 = &v12[2];
        it4 = it3-2;
        assert(*it4 == 4);
    /// iterator operator==();
        int *it5;
        it5 = &v12[1];
        bool isEqual;
        isEqual = (it3 == it5);
        assert(isEqual == false);
    /// iterator operator!=()
        isEqual = (it3 != it5);
        assert(isEqual == true);
//=== [3.3] List container operations that require iterators
    /// iterator insert(iterator pos, const T & value);
        sc::vector<int> vec = { 10, 20, 30, 40 }; 
        vec.insert(vec.begin()+2, 3); 
        assert(vec[0] == 10);
        assert(vec[1] == 20);
        assert(vec[2] == 3);
        assert(vec[3] == 30);
        assert(vec[4] == 40);
        assert(vec.size() == 5);
    /// iterator insert(iterator pos, InItr first, InItr last);
        sc::vector<int> vec1 = {10, 20, 30, 40}; 
        sc::vector<int>vec2{1, 2}; 
        vec2.insert(vec2.begin()+2,vec1.begin(),vec1.end()); 
        assert(vec2[0] == 1);
        assert(vec2[1] == 2);
        assert(vec2[2] == 10);
        assert(vec2[3] == 20);
        assert(vec2[4] == 30);
        assert(vec2[5] == 40);
        assert(vec2.size() == 6);
    /// iterator insert(const_iterator pos, std::initializer_list<T> ilist);
        sc::vector<int> v13 = {10, 20, 30}; 
        v13.insert(v13.end(), {40, 50});
        assert(v13.size() == 5);
        assert(v13[3] = 40);
        assert(v13[4] = 50);
    /// iterator erase(iterator pos);
        sc::vector<int> vectorr{1,2,3,4,5,6};
        vectorr.erase(&vectorr[2]);
        assert(vectorr[2] == 4);
        assert(vectorr.size() == 5);
    /// iterator erase(iterator first, iterator last);
        sc::vector<int> vect{1,2,3,4,5,6};
        vect.erase(vect.begin(), vect.begin()+4);
        assert(vect.size() == 2);
        assert(vect[0] == 5);
        assert(vect[1] == 6);
    /// void assign(std::initializer_list<T> ilist);
        sc::vector<int> myList{1};
        myList.assign( {1, 2, 3, 4} );
        assert(myList.size() == 4);
        assert(myList[0] == 1);
        assert(myList[1] == 2);
        assert(myList[2] == 3);
        assert(myList[3] == 4);        
}
