/*!
 * \file vector.h
 * \author Camila
 * \date May, 2
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <iostream>
#include <exception>
#include <algorithm>
#include <initializer_list>
#include <iterator>

/*! Implementing a list ADT based on a dynamic arrays data
 * structure. This versions of a list is equivalent to the std::vector.
 */
namespace sc{ // sc: Sequence container
    template <typename T>
    class vector{
        public:
            using size_type = unsigned long; //!< The size type.
            using value_type = T; //!< The value type.
            using pointer = value_type*; //!< Pointer to a value stored in the container.
            using reference = value_type&; //!< Reference to a value stored in the container.
            using const_reference = const value_type&; //!< Const reference to a value stored
        //=== Private data
        private:
            T *data; //!< Storage area. Allocates on the builder.
            size_type size_; //!< Number of elements currently in the vector.
            size_type capacity_; //!< Maximum current vector capacity (if complete, doubles capacity).
        
        //=== Public interface
        public:
        //=== Constructors, Destructors, and Assignment.
            /// Default constructor that creates an empty list.
            vector(){
                data = new T[0];
                size_ = 0;
                capacity_ = 0;
            }

            /// Constructs the list with count default-inserted instances of T.
            explicit vector(size_type count){
                data = new T[count];
                capacity_ = count;
                size_ = 0;
            }

            /// Constructs the list with the contents of the range [first, last).
            template <typename InputIt>
            vector(InputIt first, InputIt last){
                data = new T[(last-first)*2]; //*2 because would end the capacity of the vector.
                size_ = last-first;
                capacity_ = size_*2; //*2 because would end the capacity of the vector.
                for(auto i(0u); i < size_; i++){
                    data[i] = *first;
                    first++;
                }
            }

            /// Copy constructor. Constructs the list with the deep copy of the contents of other.
            vector(const vector& other){
                data = new T[other.capacity_];
                size_ = other.size_;
                capacity_ = other.capacity_;
                for(auto i(0u); i < size_; i++){
                    data[i] = other.data[i];
                }
            }

            /// Constructs the list with the contents of the initializer list init.
            vector(std::initializer_list<T> ilist){
                data = new T[ilist.size()];
                size_ = ilist.size();
                capacity_ = size_;
                //Copy the elements from ilist:
                for(auto i(0u); i < ilist.size(); i++){ //or std::copy(data, data+(ilist.size), ilist);
                    data[i] = *(ilist.begin()+i); //ilist[i];
                }
            }

            /// Destructs the list.
            ~vector(){
                delete [] data;
                size_ = 0;
                capacity_ = 0;
            }
                

            /// Copy assignment operator. Replaces the contents with a copy of the contents of other.
            vector& operator=(const vector& other){
                data = new T[other.capacity_];
                size_ = other.size_;
                capacity_ = other.capacity_;
                for(auto i(0u); i < size_; i++){
                    data[i] = other.data[i];
                }
                return *this; //pointer pointing to the object itself so we can do "a = b = c".
            }

            /// Replaces the contents with those identified by initializer list ilist
            vector& operator=(std::initializer_list<T> ilist){
                data = new T[ilist.size()];
                size_ = ilist.size();
                capacity_ = size_;
                for(auto i(0u); i < ilist.size(); i++){ //or std::copy(data, data+(ilist.size), ilist);
                    data[i] = *(ilist.begin()+i); //ilist[i];
                }
                return *this;
            }

        //=== Common operations to all list implementations
            /// Return the number of elements in the container.
            size_type size() const{
                return size_;
            }

            /// Remove (either logically or physically) all elements from the container.
            void clear(){
                size_ = 0;
            }

            /// Returns true if the container contains no elements, and false otherwise.
            bool empty(){
                return size_ == 0;
            }

            /// Adds value to the front of the list.
            void push_front(const T &value){
                T *first = data;
                T *last = &data[size_];
                vector<T> clone(first, last); //clone receives the data values
                size_ += 1;
                if(size_ >= capacity_){
                    data = new T[size_*2];
                    capacity_ *= 2;
                }
                for(size_t i(1); i < size_; i++){
                    data[i] = clone.data[i-1];
                }
                data[0] = value;
            }
            
            /// Adds value to the end of the list.
            void push_back(const T &value){
                size_ += 1;
                if(size_ < capacity_){
                    data[size_-1] = value;
                }
                else{
                    T *first = data;
                    T *last;
                    last = &data[size_];
                    vector<int> clone(first, last);
                    data = new T[size_*2];
                    for(auto i(0u); i < size_-1; i++){
                        data[i] = clone.data[i];
                    }
                    data[size_-1] = value;
                    capacity_ *= 2;
                }
            }

            /// Removes the object at the end of the list.
            void pop_back(){
                if(size_ > 0){
                    size_ -= 1;
                }
            }

            /// Removes the object at the front of the list.
            void pop_front(){
                if(size_ > 0){
                    for(size_t i(1); i < size_; i++){
                        data[i-1] = data[i];
                    }
                    size_ -= 1;
                }
            }

            /// Returns the object at the end of the list.
            const T& back() const{
                return data[size_-1];
            }

            /// Returns the object at the end of the list.
            T& back(){
                return data[size_-1];
            }

            /// Returns the object at the beginning of the list.
            const T& front() const{
                return data[0];
            }

            /// Returns the object at the beginning of the list.
            T& front(){
                return data[0];
            }

            /// Replaces the content of the list with count copies of value.
            void assign(size_type count, const T& value){
                if(capacity_ < count){
                    data = new T[count];
                    capacity_ = count;
                }

                for(auto i(0u); i < count; i++){
                    data[i] = value;
                }

                size_ = count;
            }

        //=== Operations exclusive to dynamic array implementation
            /// Returns the object at the index pos in the array, with no bounds-checking.
            T & operator[](size_type pos){
                return data[pos];
            }

            /// Returns the object at the index pos in the array, with no bounds-checking.
            const T & operator[](size_type pos) const{
                return data[pos];
            }

            /// Returns the object at the index pos in the array, with bounds-checking.
            /*!
            * @throw Generates `out_of_range` exception if you enter the position 
            * beyond the bounds of the list.
            */
            T & at(size_type pos){
                if(pos >= size_){
                    throw std::out_of_range("[vector::at()] Position entered beyond vector boundaries.");
                }
                return data[pos];
            }

            /// Returns the object at the index pos in the array, with bounds-checking.
            /*!
            * @throw Generates `out_of_range` exception if you enter the position 
            * beyond the bounds of the list.
            */
            const T & at(size_t pos) const{
                if(pos >= size_){
                    throw std::out_of_range("[vector::at()] Position entered beyond vector boundaries.");
                }
                return data[pos];
            }

            /// Return the internal storage capacity of the array.
            size_type capacity() const{
                return capacity_;
            }

            /// Increase the storage capacity of the array to the value `new_cap` if it is greater than the current capacity()
            void reserve(size_t new_cap){
                if(new_cap <= capacity_) return; //do nothing
                T *first = data;
                T *last = &data[size_];
                vector<int> clone(first, last);
                data = new T[new_cap];
                for(auto i(0u); i < size_; i++){
                    data[i] = clone.data[i];
                }
                capacity_ = new_cap;
            }

            /// Requests the removal of unused capacity. It is a non-binding request to reduce capacity() to size().
            void shrink_to_fit(){
                capacity_ = size_;
            }            
            
        //=== Iterators
            class iterator{ //From category "Biderectional"
                public:
                    typedef T& reference; //!< Reference to the value type.
                    typedef T* pointer; //!< Pointer to the value type.
                    typedef T value_type; //!< Value type the iterator points to.
                    /// Difference type used to calculated distance between iterators.
                    typedef std::ptrdiff_t difference_type;
                    /// Identifies the iterator category to algorithms from STL
                    typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.
                //=== Private data
                private:
                    T *it;
                //=== Public interface
                public:
                    /// Constructor
                    iterator(T *ptr = nullptr) : it{ptr}{
                       /*empty*/
                    }

                //=== Iterator operations
                    /// Advances iterator to the next location within the vector: ++it
                    iterator operator++(void){
                        //Returns new iterator that points to the next address
                        return iterator(++it);
                        //or ++ptr; return *this;
                    }

                    /// Advances iterator to the next location within the vector: it++
                    iterator operator++(int){
                        it++;
                        return iterator(it-1);
                    }

                    /// Pre increment: --it
                    iterator operator--(void){
                        return iterator (--it);
                    }

                    /// Post increment: it--
                    iterator operator--(int){
                        iterator temp(it); // Creates a temporary iterator with the current address.
                        it++;
                        return temp;
                    }

                    /// Return a reference to the object located at the position pointed by the iterator
                    reference operator*(void){ //*it = x;
                        return *it;
                    }

                    /// Return a reference to the object located at the position pointed by the iterator
                    const T& operator*(void) const{ //x = *it;
                        return *it;
                    }
                    
                    /// Return the difference between two iterators.
                    difference_type operator-(const iterator &rhs){
                        return it - rhs.it;
                    }

                    /// Return a iterator pointing to the n-th successor in the vector from it.
                    friend iterator operator+(int n, iterator it){
                        return it.it + n;
                    }
                    
                    /// Return a iterator pointing to the n-th successor in the vector from it.
                    friend iterator operator+(iterator it, int n){
                        return it.it + n;
                    }

                    /// Return a iterator pointing to the n-th predecessor in the vector from it
                    friend iterator operator-(int n, iterator it){
                        return it.it - n;
                    }

                    /// Return a iterator pointing to the n-th predecessor in the vector from it
                    friend iterator operator-(iterator it, int n){
                        return it.it - n;
                    }

                    /// Return a pointer to the location in the vector the it points to.
                    iterator operator->(){
                        return *it;
                    }

                    /// Returns true if both iterators refer to the same location within the vector, and false otherwise.
                    bool operator==(const iterator &ptr) const{
                        return this->it == ptr.it;
                    }

                    /// Returns true if both iterators refer to a different location within the vector, and false otherwise.
                    bool operator!=(const iterator &ptr) const{
                        return this->it != ptr.it;
                    }

            };
            class const_iterator{
                //=== Private data
                private:
                    const T *it;
                //=== Public interface
                public:
                    /// Constructor
                    const_iterator(const T *ptr = nullptr) : it{ptr}{
                       /*empty*/
                    }     

                //=== Const_iterator operations
                    /// Advances iterator to the next location within the vector: ++it
                    const_iterator operator++(void){
                        //Returns new iterator that points to the next address
                        return const_iterator(++it);
                        //or ++ptr; return *this;
                    }

                    /// Advances iterator to the next location within the vector: it++
                    const_iterator operator++(int){
                        it++;
                        return const_iterator(it-1);
                    }

                    /// Pre increment: --it
                    const_iterator operator--(void){
                        return const_iterator(--it);
                    }

                    /// Post increment: it--
                    const_iterator operator--(int){
                        const_iterator temp(it);
                        it++;
                        return temp;
                    }

                    /// Return a reference to the object located at the position pointed by the const_iterator.
                    reference operator*(void){ //*it = x;
                        return *it;
                    }

                    /// Return a reference to the object located at the position pointed by the const_iterator.
                    const T& operator*(void) const{ //x = *it;
                        return *it;
                    }    
            };

        //=== Getting an iterator
            /// Returns an iterator pointing to the first item in the list
            iterator begin(){
                return iterator(&data[0]);
            }

            /// Returns an iterator pointing to the end mark in the list
            iterator end(){
                return iterator(&data[size_]);
            }

            /// Returns a constant iterator pointing to the first item in the list.
            const_iterator cbegin(){
                return const_iterator(&data[0]);
            }

            /// Returns a constant iterator pointing to the end mark in the list
            const_iterator cend(){
                return const_iterator(&data[size_]);
            }


        //=== List container operations that require iterators
            /// Adds value into the list before the position given by the iterator pos
            iterator insert(iterator pos, const T & value){
                int tamanho = pos - begin();
                // if(tamanho > capacity_) return NULL;
                iterator first = &data[tamanho];
                iterator last = &data[size_];
                vector<T> clone(first, last); //clone receives the data values
                size_ +=  1;
                if(size_ >= capacity_){
                    sc::vector<T> secondClone(&data[0], &data[size_-1]);
                    data = new T[size_*2];
                    capacity_ *= 2;
                    for(auto i(0u); i < size_-1; i++){
                        data[i] = secondClone.data[i];
                    }
                }
                int cont = 0;
                data[tamanho] = value;
                for(auto i(&data[tamanho+1]); i < &data[size_]; i++){
                    *i = clone.data[cont];
                    cont++;
                }
                return pos;
            }

            /// Inserts elements from the range [first; last) before pos
            template < typename InItr>
            iterator insert(iterator pos, InItr first, InItr last){
                if(size_t(pos - begin()) <= size_){
                    int tamanho = pos - begin();
                    int diff = last-first;
                    T *aux = new T[end() - pos];
                    std::copy(pos, end(), aux);
                    if(size_+(diff) > capacity_){
                        reserve((size_+(diff))*2);
                        capacity_ = (size_+(diff))*2;
                    }
                    size_ += diff;
                    while(first != last){
                        data[tamanho] = *first;
                        first++;
                        tamanho++;
                    }
                    int idx = 0;
                    for(size_t i = tamanho; i < size_; i++){
                        data[i] = aux[idx];
                        idx++;
                    }
                    delete [] aux;
                    return pos;
                }
                return end();
            }

            /// Inserts elements from the initializer list ilist before pos
            iterator insert(iterator pos, std::initializer_list<T> ilist){
                if(size_t(pos - begin()) <= size_){
                    int tamanho = pos - begin();
                    T *aux = new T[end() - pos];
                    std::copy(pos, end(), aux);
                    if(ilist.size()+size_ > capacity_){
                        reserve((ilist.size()+size_)*2);
                        capacity_ = (ilist.size()+size_)*2;
                    }
                    size_ += ilist.size();

                    auto first = ilist.begin();
                    auto last = ilist.end();

                    while(first != last){
                        data[tamanho] = *first;
                        first++;
                        tamanho++;
                    }
                    int idx = 0;
                    for(size_t i = tamanho; i < size_; i++){
                        data[i] = aux[idx];
                        idx++;
                    }
                    delete [] aux;
                    return pos;
                }
                return end();
            }

            /// Removes the object at position pos
            iterator erase(iterator pos){
                for(auto i(&data[pos-data]); i < &data[size_-1]; i++){
                    *i = *(i+1);
                }
                size_ -= 1;
                return pos;
            }
            
            /// Removes elements in the range [first; last)
            iterator erase(iterator first, iterator last){
                int tamanhoF = first - begin();
                int tamanhoL = last - begin();
                int distance = end() - last;
                int cont = 0;
                while(cont < distance){
                    data[tamanhoF] = data[tamanhoL];
                    tamanhoF += 1;
                    tamanhoL += 1;
                    cont += 1;
                }
                size_ -= last - first;
                return first;
            }

            /// Replaces the contents of the list with the elements from the initializer list ilist
            void assign(std::initializer_list<T> ilist){
                data = new T[ilist.size()*2];
                size_ = ilist.size();
                capacity_ = size_*2;
                for(auto i(0u); i < ilist.size(); i++){ //or std::copy(data, data+(ilist.size), ilist);
                    data[i] = *(ilist.begin()+i); //ilist[i];
                }
            }

            friend std::ostream& operator<<(std::ostream& os, const vector& v){
                os << "[ ";
                std::copy(&v.data[0], &v.data[v.size_], std::ostream_iterator<T>(os, " "));
                os << "| ";
                std::copy(&v.data[v.size_], &v.data[v.capacity_], std::ostream_iterator<T>(os, " "));
                os << "]";

                return os;
            }

    };
    //=== Operator overloading — non-member functions
        /// Checks if the contents of lhs and rhs are equal.
        template <typename T>
        bool operator==(const sc::vector<T>& lhs, const sc::vector<T>& rhs){
            if(lhs.size() == rhs.size()){
                for(size_t i = 0; i < lhs.size(); i++){
                    if(lhs[i] != rhs[i])
                        return false;
                }
                return true;
            }
            else{
                return false;
            }
        }

        /// Similar to the previous operator, but the opposite result.
        template <typename T>
        bool operator!=(const sc::vector<T>& lhs, const sc::vector<T>& rhs){
            if(lhs.size() == rhs.size()){
                for(size_t i = 0; i < lhs.size(); i++){
                    if(lhs[i] != rhs[i])
                        return true;
                }
                return false;
            }
            else{
                return true;
            }
        }
}

#endif