#include <iostream> 

using namespace std; 

template<typename T> 
class Vector {

  private: 
    size_t capacity = 10; 
    size_t elements = 0; 
    T *arr = new T[capacity];

    void resize_arr(const size_t size) {
      capacity = size; 
      T *newArr = new T[capacity]; 

      for(int i = 0; i < capacity / 2; i++) 
        newArr[i] = arr[i];

      delete[] arr;

      arr = newArr; 
    }

  public: 
    ~Vector() {
      delete[] arr;
    }

    void push_back(T val) {
      if(elements == capacity) 
        resize_arr(capacity * 2);

      arr[elements] = val; 
      elements++; 
    }

    void remove_top() {
      if(elements == 0)
        throw logic_error("vector empty");

      elements--;
    }

    void remove(const size_t &index) {
      if(index < 0 || index > elements - 1)
        throw logic_error("invalid index"); 

      for(int i = index; i < elements - 1; i++) { //if removed element is not at index 0 or vec.size() - 1, elements above need to be shifted down
        T tmp = arr[i]; 
        arr[i] = arr[i - 1]; 
        arr[i - 1] = tmp; 
      } 

      elements--; 
    }

    T& operator[](const size_t &index) {
      return arr[index];
    }

    const T& operator[](const size_t &index) const {
      return arr[index];
    }

    void clear() {
      elements = 0; 
    }

    size_t size() const {
      return elements; 
    }
};


