#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
    public:
        using CircularArray<T>::CircularArray;
        void push_back(T data);
        T pop_front();
};

template <class T>
void QueueArray<T>::push_back(T data){
    if(!this->is_empty()){
        this->back = this->back + 1;
        this->array[this->back] = data;
    } else{
        this->array[0] = data;
        this->front = this->back = 0;
    }
}

template <class T>
T QueueArray<T>::pop_front(){
    if(!this->is_empty()){
        T poppedValue = this->array[this->front];
        for(int i = 1; i < this->back+1; i++){
            this->array[i-1] = this->array[i];
        }
        this->back--;
        return poppedValue;
    }

    return this->array[0];
}