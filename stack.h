#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
    public:
        using CircularArray<T>::CircularArray;
        void push_back(T data);
        T pop_back();
};

template <class T>
void StackArray<T>::push_back(T data){
    if(!this->is_empty()){
        this->back = this->back + 1;
        this->array[this->back] = data;
    } else{
        this->array[0] = data;
        this->front = this->back = 0;
    }
}

template <class T>
T StackArray<T>::pop_back(){
    if(!this->is_empty()){
        T poppedValue = this->array[this->back];
        if(this->front == this->back){
            this->front = this->back = -1;
        } else{
            this->back--;
        }
        return poppedValue;
    } else{
        return this->array[0]; // Esto debería dar error.
    }
}