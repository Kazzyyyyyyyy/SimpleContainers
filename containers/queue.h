#include <iostream> 

using namespace std; 

template<typename T> 
class Queue {

  private: 
    size_t capacity = 10;
    size_t head = 0; 
    size_t tail = 0; 

    T *arr = new T[capacity];

    void resize_arr(const size_t size) {
      capacity = size; 
      T *newArr = new T[capacity];

      for(int i = head; i < tail; i++) 
        newArr[i - head] = arr[i];

      delete[] arr; 

      tail = tail - head;
      head = 0;
      arr = newArr;
    }

  public: 
    void push(T val) {
      if(tail == capacity && tail - head > capacity / 2) //actually makes the array bigger 
        resize_arr(capacity * 2); 
      else if(tail == capacity) //just removes "used" elements, but capacity stays the same
        resize_arr(capacity);


      arr[tail] = val; 
      tail++; 
    }

    T pop() {
      if(tail - head == 0) 
        throw logic_error("queue empty"); 

      head++; 
      return arr[head - 1];
    }

    T top() const {
      if(tail - head == 0) 
        throw logic_error("queue empty");

      return arr[head];
    }

    size_t size() const {
      return tail - head;
    }
}; 
