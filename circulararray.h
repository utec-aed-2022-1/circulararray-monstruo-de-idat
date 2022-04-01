#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
protected:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();
    CircularArray(int _capacity); // Crea un array sin datos con una capacidad determinada
    virtual ~CircularArray(); // Liberar memoria del array

    void push_front(T data); // Agrega un elemento al comienzo 
    void push_back(T data); // Agrega un elemento al final
    void insert(T data, int pos); // Inserta el elemento en la posición indicada
    T pop_front(); // Remueve el elemento al comienzo
    T pop_back(); // Remueve el elemento al final
    bool is_full(); // Retorna True si el array está lleno o no
    bool is_empty(); // Retorna True si el array está vacía o no

    int size(); // Retorna el tamaño del array (en funcion de back, front y capacity)
    void clear(); // Elimina todos los elementos del array
    T &operator[](int);
    void sort();
    bool is_sorted();
    void reverse();

    string to_string(string sep=" "); // Retorna un string con todos los elementos separados por "sep"

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = "";
    int idx = this->front;
    for (int i = 0; i < size(); i++){
        result += std::to_string(this->array[idx]) + sep;
        idx = this->next(idx);
    }
        
    return result;
}

////////////////
template <class T>
void CircularArray<T>::push_front(T data){
    if(!this->is_empty()){
        this->front = this->prev(this->front);
        this->array[this->front] = data;
    } else{
        this->array[0] = data;
        this->front = this->back = 0;
    }
        
    //     for(int i = this->back+1; i > this->size; i--){
    //         this->array[i] = this->array[i-1];
    //     }
    //     this->array[0] = data;
    //     this->back = this->back + 1;
    // } else{
    //     this->array[0] = data;
    //     this->front = 0;
    //     this->back = 0;
}

template <class T>
void CircularArray<T>::push_back(T data){
    if(!this->is_empty()){
        this->back = this->next(this->back);
        this->array[this->back] = data;
    } else{
        this->array[0] = data;
        this->front = this->back = 0;
    }

    // if(!this->is_empty()){
    //     this->array[this->back+1] = data;
    //     this->back = this->back + 1;
    // } else{
    //     this->array[0] = data;
    //     this->front = 0;
    //     this->back = 0;
    // }
}

template <class T>
void CircularArray<T>::insert(T data, int pos){
    if(pos < this->size() && !this->is_empty()){
        int idx = this->front;
        for(int i = 0; i < pos; i++){
            idx = this->next(idx);
        }
        this->array[idx] = data;
    }
    // else -> Esto debería dar error.
}

template <class T>
T CircularArray<T>::pop_front(){
    if(!this->is_empty()){
        T poppedValue = this->array[this->front];
        if(this->front == this->back){
            this->front = this->back = -1;
        } else{
            this->front = this->next(this->front);
        }
        return poppedValue;
    } else{
        return this->array[0]; // Esto debería dar error.
    }
}

template <class T>
T CircularArray<T>::pop_back(){
    if(!this->is_empty()){
        T poppedValue = this->array[this->back];
        if(this->front == this->back){
            this->front = this->back = -1;
        } else{
            this->back = this->prev(this->back);
        }
        return poppedValue;
    } else{
        return this->array[0]; // Esto debería dar error.
    }
}

template <class T>
bool CircularArray<T>::is_full(){
    return ((this->back + 1) == this->front);
}

template <class T>
bool CircularArray<T>::is_empty(){
    return (this->front == -1 && this->back == -1);
}

template <class T>
int CircularArray<T>::size(){
    int f, b;
    f = this->front;
    b = this->back;
    return (f < b) ? b - f + 1 : capacity - f + b + 1 ;
}

template <class T>
void CircularArray<T>::clear(){
    this->back = this->front = -1;
}

template <class T>
T &CircularArray<T>::operator[](int index){
    if(index < this->size() && !this->is_empty()){
        int idx = this->front;
        for(int i = 0; i < index; i++){
            idx = this->next(idx);
        }
        return this->array[idx];
    }
    return this->array[0]; // Esto debería dar error.
}

template <class T>
void CircularArray<T>::sort(){    
    if(!this->is_empty()){
        bool isSorted = false;
        T temp;
        while(!isSorted){
            isSorted = true;
            int idx = this->front;
            for(int i = 0; i < this->size()-1; i++){
                if(this->array[this->next(idx)]<this->array[idx]){
                    temp = this->array[this->next(idx)];
                    this->array[this->next(idx)] = this->array[idx];
                    this->array[idx] = temp;
                    isSorted = false;
                }
                idx = this->next(idx);
            }
        }
    }
}

template <class T>
bool CircularArray<T>::is_sorted(){
    if(!this->is_empty()){     
        int idx = this->front;
        for(int i = 0; i < this->size()-1; i++){
            if(this->array[idx] > this->array[this->next(idx)]){
                return false;
            }
            idx = this->next(idx);
        }
        return true;
    }
    return false;
}


template <class T>
void CircularArray<T>::reverse(){
    if(!this->is_empty()){
        T tempArray[this->size()];
        int idx = this->back;
        for(int i = 0; i < this->size(); i++){
            tempArray[i] = this->array[idx];
            idx = this->prev(idx);            
        }
        idx = this->front;
        for(int i = 0; i < this->size(); i++){
            this->array[idx] = tempArray[i];
            idx = this->next(idx);
        }
    }
}