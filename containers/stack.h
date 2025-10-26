#include <iostream> 

using namespace std; 

template<typename T> 
class Stack {
  
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
    ~Stack() {
      delete[] arr; 
    }

    void push(T val) {
      if(elements == capacity) 
        resize_arr(capacity * 2);

      arr[elements] = val; 
      elements++; 
    }

    T pop() {
      if(elements == 0)
        throw logic_error("stack empty"); 

      elements--; 
      return arr[elements]; 
    }

    T top() const {
      if(elements == 0)
        throw logic_error("stack empty"); 

      return arr[elements - 1]; 
    }

    size_t size() const {
      return elements; 
    }

    void clear() {
      elements = 0; 
    }
};

/* 
 * first ever container I made, thought I just leave it here
 *
class Stack {
  private: 
    struct ListNode {
      ListNode *prev; 

      T val; 

      ListNode(T v) : val(v), prev(nullptr) {} 
    };

    int elements = 0; 
    ListNode *curr = nullptr;
  
  public: 
    ~Stack() {
      while(curr != nullptr) {
        ListNode *prev = curr->prev; 
 
        delete curr; 

        curr = prev; 
      }
    }

    void push(int val) {
      elements++;

      ListNode *tmp = curr; //saves curr

      curr = new ListNode(val); 
      
      curr->prev = tmp; //sets curr->prev the old curr
    }


    T pop() {
      if(elements == 0) 
        throw logic_error("stack empty"); 

      elements--; 
      
      ListNode *prev = curr->prev;
      
      T val = curr->val; 
      
      delete curr; 

      curr = prev; 

      return val;
    }

    T top() {
      if(elements == 0)
        throw logic_error("stack empty"); 

      return curr->val; 
    }

    int size() {
      return elements; 
    }
};
*/
