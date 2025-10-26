#include <iostream> 

using namespace std;

template<typename T> 
class PriorityQueue {

  private: 
    struct PriorityItem {
      int prio; 
      T val; 
    };

    size_t elements = 0; 
    size_t capacity = 10; 
    PriorityItem *arr = new PriorityItem[capacity]; 
    const bool reverse; 

    void sort_new_item_in(const int &prio) {
      if(elements == 0)
        return; 

      for(int i = elements; i >= 1; i--) {
        if(has_higher_priority(arr[i - 1].prio, prio)) // if the correct index is found (determined by priority), stop shifting
          break; 

        PriorityItem tmp = arr[i]; 
        arr[i] = arr[i - 1]; 
        arr[i - 1] = tmp; 
      }
    }
    
    bool has_higher_priority(const int &arrPrio, const int &prio) const {
        return reverse ? (arrPrio > prio) : (arrPrio < prio);
    }

    void resize_arr(const size_t size) {
      capacity = size; 
      PriorityItem *newArr = new PriorityItem[capacity]; 

      for(int i = 0; i < capacity / 2; i++)
        newArr[i] = arr[i];

      delete[] arr;

      arr = newArr; 
    }    

    
  public: 
    PriorityQueue(const bool rev = false) : reverse(rev) {}

    ~PriorityQueue() {
      delete[] arr; 
    }

    void push(int prio, T val) {
      if(elements >= capacity) // array full, resize to not overflow
        resize_arr(capacity * 2);
      
      arr[elements].prio = prio;
      arr[elements].val = val; 

      sort_new_item_in(prio); 

      elements++; 
    }

    T pop() {
      if(elements == 0)
        throw logic_error("queue empty");

      elements--; // makes the element inaccessable and with next push it gets replaced => is way way faster than actually removing it

      return arr[elements].val; 
    }

    T top() const {
      if(elements == 0)
        throw logic_error("queue empty");

      return arr[elements - 1].val;
    }

    void clear() {
      elements = 0; //again, elements are inaccessable now and get overwritten with next push 
    }

    size_t size() const {
      return elements;
    }

}; 

