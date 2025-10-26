#include <iostream> 

using namespace std; 

struct Position {
  int y;
  int x; 

  Position(int getY, int getX) : y(getY), x(getX) {}
}; 

template<typename T> 
class HashMap {
 
  private: 
    struct ListNode {
      Position key;
      T val; 

      ListNode *next; 

      ListNode(Position k, T v) : key(k), val(v), next(nullptr) {}
    }; 

    size_t capacity = 10;
    size_t elements = 0; 
    ListNode **bucket = new ListNode*[capacity]; 

    bool compare_keys(const Position &k1, const Position &k2) {
      return k1.y == k2.y && k1.x == k2.x; 
    }

    //calculates hashValue based on value and prime numbers for better distribution
    int hash(const Position &key) {
      int hashValue = (key.y * 73856093) ^ (key.x * 19349663);  //use two different big prime-numbers and XOR for better distribution and fast calc

      return abs(hashValue) % capacity; 
    }

    //adds new element to the front of bucket => (O(1))
    void add_to_bucket(Position key, T val) {
      int keyValue = hash(key); 
      
      if(bucket[keyValue] != nullptr) { 
        ListNode *tmp = bucket[keyValue]; 

        while(tmp != nullptr) {
          if(compare_keys(tmp->key, key)) {
            tmp->val = val; //if key alr exists, replace its value instead of adding a new Node to prevent multiple Nodes with the same key
            return; 
          }  

          tmp = tmp->next; 
        }
      }

      ListNode *head = new ListNode(key, val); 

      head->next = bucket[keyValue]; 

      bucket[keyValue] = head; 
    }

    //double capacity and reorder all nodes for faster runtime
    void rehash() {
      capacity *= 2; 
      ListNode **newBucket = new ListNode*[capacity];

      for(int i = capacity / 2; i < capacity; i++) //init new space first, we need this because when rehashing we set the Node at the beginning of bucket[index]. 
         newBucket[i] = nullptr;                   //If it wouldnt be nullptr, this wouldnt work, becuase head->next would be NULL (or something else)
         
      for(int i = 0; i < capacity / 2; i++) {
        newBucket[i] = nullptr; 

        if(bucket[i] != nullptr) {
          ListNode *curr = bucket[i];

          while(curr != nullptr) {
            int keyValue = hash(curr->key); 

            ListNode *tmp = curr->next;

            curr->next = newBucket[keyValue];
            newBucket[keyValue] = curr; 

            curr = tmp; 
          }
        }
      }

      delete[] bucket; 
      bucket = newBucket; 
    }

    ListNode *get_element(const Position &key) {
      int keyValue = hash(key); 
      ListNode *tmp = bucket[keyValue]; 

      while(tmp != nullptr) {
        if(compare_keys(tmp->key, key)) 
          return tmp; 
        
        tmp = tmp->next;
      }

      return nullptr; 
    }

  public: 
    HashMap() {
      for(int i = 0; i < capacity; i++) 
        bucket[i] = nullptr; 
    }

    //free everything to prevent memory leaks/errors 
    ~HashMap() {
      for(int i = 0; i < capacity; i++) {
        if(bucket[i] != nullptr) {
          ListNode *tmp = bucket[i]; 
          while(tmp != nullptr) {
            ListNode *next = tmp->next; 

            delete tmp; 

            tmp = next; 
          }
        }
      }
 
      delete[] bucket; 
    }

    void put(const Position &key, const T &val) {
      float loadFactor = (float)elements / capacity; 
      if(loadFactor > 0.7) //rehash if bucket gets to full for better runtime
        rehash(); 
 
      add_to_bucket(key, val); 
      elements++;
    }

    //uses standard "dummy method" to find and remove a Node, throws if not found
    void remove(const Position &key) {
      int keyValue = hash(key); 

      ListNode *dummy = new ListNode({ INT_MIN, INT_MIN }, T{}); 
      dummy->next = bucket[keyValue]; 
      ListNode *tmp = dummy; 

      while(tmp->next != nullptr) {
        if(compare_keys(tmp->next->key, key)) {
          ListNode *delTmp = tmp->next; 
          tmp->next = tmp->next->next; 

          delete delTmp; 

          bucket[keyValue] = dummy->next; 
          delete dummy;
          
          elements--; 
          return;
        }
        
        tmp = tmp->next;
      }

      throw logic_error("entry not found"); 
    }

    T get(const Position &key) {
      ListNode *el = get_element(key);
      
      if(el == nullptr) 
        throw logic_error("entry not found");

      return el->val; 
    }

    void update(const Position &key, T val) {
      ListNode *el = get_element(key); 
      
      if(el == nullptr) 
        throw logic_error("entry not found");
      
      el->val = val; 
    }

    bool contains(const Position &key) {
      ListNode *el = get_element(key); 

      return el != nullptr;
    }

    size_t entrys() const {
      return elements;
    }
}; 
