#ifndef VECTOR_H
#define VECTOR_H

/*! Implementing a list ADT based on a dynamic arrays data
 * structure. This versions of a list is equivalent to the std::vector.
 */
namespace sc{ // sc: Sequence container
    template <typename T>
    class vector{
        public:
            using size_type = unsigned long; //!< The size type.
            using value_type = T; //!< The value type.
        //=== Private data
        public:
            T *data; //aloca durante o construtor.
            size_type size_; //!< Número de elementos atualmente no vector.
            size_type capacity_; //!< Capacidade máxima atual do vector (se completar dobra a capacidade/memória).
        
        //=== Public interface
        public:
        //=== [I] Constructors, Destructors, and Assignment.
            /// Default constructor that creates an empty list.
            vector(){
                data = new T[0];
                size_ = 0;
                capacity_ = 0;
            }

            /// Constructs the list with count default-inserted instances of T.
            explicit vector(size_type count){
                data = new T[count];
                capacity_ = count*2;
                size_ = count;
                for(auto i(0u); i < size_; i++){
                    data[i] = 0;
                }
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
                data = new T[other.size_*2]; //*2 because would end the capacity of the vector.
                size_ = other.size_;
                capacity_ = size_*2; //*2 because would end the capacity of the vector.
                for(auto i(0u); i < size_; i++){
                    data[i] = other.data[i];
                }
            }

            /// Constructs the list with the contents of the initializer list init.
            vector(std::initializer_list<T> ilist){
                data = new T[ilist.size()*2]; //*2 because would end the capacity of the vector.
                size_ = ilist.size();
                capacity_ = size_*2; //*2 because would end the capacity of the vector.
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
                data = new T[other.size_*2]; //*2 because would end the capacity of the vector.
                size_ = other.size_;
                // if(size_ == 0)
                //     capacity_ = other.capacity_;
                // else
                    capacity_ = size_*2; //*2 because would end the capacity of the vector.
                for(auto i(0u); i < size_; i++){
                    data[i] = other.data[i];
                }
                return *this; //pointer pointing to the object itself so we can do "a = b = c".
            }

            /// Replaces the contents with those identified by initializer list ilist
            vector& operator=(std::initializer_list<T> ilist){
                data = new T[ilist.size()*2]; //*2 because would end the capacity of the vector.
                size_ = ilist.size();
                capacity_ = size_*2; //*2 because would end the capacity of the vector.
                for(auto i(0u); i < ilist.size(); i++){ //or std::copy(data, data+(ilist.size), ilist);
                    data[i] = *(ilist.begin()+i); //ilist[i];
                }
                return *this;
            }

        //=== [II] Common operations to all list implementations
            /// Return the number of elements in the container.
            size_type size() const{
                return size_;
            }

            /// Remove (either logically or physically) all elements from the container.
            void clear(){
                for(auto i(0u); i < size_; i++){
                    data[i] = 0;
                }
                size_ = 0;
            }

            /// Returns true if the container contains no elements, and false otherwise.
            bool empty(){
                if(size_ == 0)
                    return true;
                else
                    return false;
            }

            /// Adds value to the front of the list.
            void push_front(const T &value){
                T *first = data;
                T *last;
                last = &data[size_];
                vector<T> clone(first, last); //clone receives the data values
                size_ += 1;
                if(size_ >= capacity_){
                    data = new T[size_*2];
                    capacity_ *= 2;
                }
                for(auto i(1); i < size_; i++){
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
                size_ -= 1;
            }

            /// Removes the object at the front of the list.
            void pop_front(){
                for(auto i(1); i < size_; i++){
                    data[i-1] = data[i];
                }
                size_ -= 1;
            }

            /// Returns the object at the end of the list.
            const T& back() const{
                return data[size_-1];
            }

            /// Returns the object at the beginning of the list.
            const T& front() const{
                return data[0];
            }

            /// Replaces the content of the list with count copies of value.
            void assign(size_type count, const T& value){

            }
    };
}


#endif