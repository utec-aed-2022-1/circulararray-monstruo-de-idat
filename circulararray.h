#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
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
    for (int i = 0; i < size(); i++)
        result += std::to_string(this->array[i]) + sep;
    return result;
}

////////////////
template <class T>
void CircularArray<T>::push_front(T data){
    if(!this->is_empty()){
        for(int i = this->back+1; i > this->front; i--){
            this->array[i] = this->array[i-1];
        }
        this->array[0] = data;
        this->back = this->back + 1;
    } else{
        this->array[0] = data;
        this->front = 0;
        this->back = 0;
    }
}

template <class T>
void CircularArray<T>::push_back(T data){
    if(!this->is_empty()){
        this->array[this->back+1] = data;
        this->back = this->back + 1;
    } else{
        this->array[0] = data;
        this->front = 0;
        this->back = 0;
    }
}

template <class T>
void CircularArray<T>::insert(T data, int pos){
    this->array[pos] = this->array(data);
}

template <class T>
T CircularArray<T>::pop_front(){
    if(!this->is_empty()){
        T ret = this->array[0];
        for(int i = this->front; i < this->back; i++){
            this->array[i] = this->array[i+1];
        }
        this->back = this->back - 1;
        return ret;
    } else{
        return this->array[0];
    }
}

template <class T>
T CircularArray<T>::pop_back(){
    if(!this->is_empty()){
        T ret = this->array[this->back];        
        this->back = this->back - 1;
        return ret;
    } else{
        return this->array[0];
    }
}

template <class T>
bool CircularArray<T>::is_full(){
    return ((this->back + 1) % this->capacity == this->front);
}

template <class T>
bool CircularArray<T>::is_empty(){
    return (this->front == -1 && this->back == - 1);
}

template <class T>
int CircularArray<T>::size(){
    return (this->back - this->front) + 1;
}

template <class T>
void CircularArray<T>::clear(){
    this->back = this->front = -1;
}

template <class T>
T &CircularArray<T>::operator[](int){
    return this->array[0];
}

template <class T>
void CircularArray<T>::sort(){    
    if(!this->is_empty()){
        bool isSorted = false;
        T temp;
        while(!isSorted){
            isSorted = true;
            for(int i = this->front; i < this->back; i++){
                if(this->array[i+1]<this->array[i]){
                    temp = this->array[i+1];
                    this->array[i+1] = this->array[i];
                    this->array[i] = temp;
                    isSorted = false;
                }
            }
        }
    }
}

template <class T>
bool CircularArray<T>::is_sorted(){
    if(!this->is_empty()){     
        T minValue = this->array[this->front];
        for(int i = this->front+1; i < this->back; i++){
            if(this->array[i] < minValue){
                return false;
            } else{
                minValue = this->array[i];
            }
        }
        return true;
    }
    return false;
}


template <class T>
void CircularArray<T>::reverse(){
    if(!this->is_empty()){
        T tempArray[this->size()];
        int tempIdx = 0;
        for(int i = this->back+1; i > this->front; i--){
            tempArray[tempIdx] = this->array[i-1];
            tempIdx++;
        }
        for(int i = this->front; i <= this->back; i++){
            this->array[i] = tempArray[i];
        }
    }
}