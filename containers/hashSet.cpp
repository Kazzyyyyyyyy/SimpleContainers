#include <iostream>
#include "hashSet.h"

using namespace std; 
 
HashSet::HashSet(size_t cap) : capacity(cap), elements (0) {
  bucket = new PositionNode*[capacity];

  for(int i = 0; i < capacity; i++) 
    bucket[i] = nullptr; 
}

//free everything to prevent memory leaks/errors 
HashSet::~HashSet() {
  for(int i = 0; i < capacity; i++) {
    if(bucket[i] != nullptr) {
      PositionNode *tmp = bucket[i]; 
      while(tmp != nullptr) {
        PositionNode *next = tmp->next; 
        delete tmp; 
        tmp = next; 
      }
    }
  }

  delete[] bucket; 
}

bool HashSet::compare_keys(const PositionNode *p1, const PositionNode *p2) {
  return p1->y == p2->y && p1->x == p2->x; 
}

int HashSet::hash(const PositionNode *p) {
  int hashValue = (p->y * 73856093) ^ (p->x * 19349663);  //use two different big prime-numbers and XOR for better distribution and fast calc

  return abs(hashValue) % capacity; 
}

//adds new element to the front of bucket => (O(1))
void HashSet::add_to_bucket(PositionNode p) {
  int keyValue = hash(&p); 
      
  if(bucket[keyValue] != nullptr) {
    PositionNode *tmp = bucket[keyValue];

    while(tmp != nullptr) {
      if(compare_keys(tmp, &p))
        return; //if key alr exists, return to prevent multiple entrys with the same value

      tmp = tmp->next;
    }
  }

  PositionNode *head = new PositionNode({p.y, p.x}); 

  head->next = bucket[keyValue]; 

  bucket[keyValue] = head; 

  elements++;
}

//double capacity and reorder all nodes for faster runtime
void HashSet::rehash() {
  capacity *= 2; 
  PositionNode **newBucket = new PositionNode*[capacity];

  for(int i = capacity / 2; i < capacity; i++) //init new space first, we need this because when rehashing we set the Node at the beginning of bucket[index]. 
	newBucket[i] = nullptr;                    //If it wouldnt be nullptr, this wouldnt work, because head->next would be NULL (or something else)
    
  for(int i = 0; i < capacity / 2; i++) {
    newBucket[i] = nullptr; 

    if(bucket[i] != nullptr) {
      PositionNode *curr = bucket[i];

      while(curr != nullptr) {
        int keyValue = hash(curr); 

        PositionNode *tmp = curr->next;

        curr->next = newBucket[keyValue];
        newBucket[keyValue] = curr; 

        curr = tmp; 
      }
    }
  }

  delete[] bucket; 
  bucket = newBucket; 
}

PositionNode *HashSet::get_element(const PositionNode &p) {
  int keyValue = hash(&p); 
  PositionNode *tmp = bucket[keyValue]; 

  while(tmp != nullptr) {
    if(compare_keys(tmp, &p)) 
      return tmp; 
    
    tmp = tmp->next; 
  }

  return nullptr;
}

void HashSet::put(const PositionNode &p) {
  float loadFactor = (float)elements / capacity; 
  if(loadFactor > 0.7) //rehash if bucket gets to full for better runtime
    rehash(); 

  add_to_bucket(p); 
}

//uses standard "dummy method" to find and remove element, throws if not found
void HashSet::remove(const PositionNode &p) {
  int keyValue = hash(&p); 

  PositionNode *dummy = new PositionNode({ INT_MIN, INT_MIN }); 
  dummy->next = bucket[keyValue]; 
  PositionNode *tmp = dummy; 

  while(tmp->next != nullptr) {
    if(compare_keys(tmp->next, &p)) {
      PositionNode *delTmp = tmp->next; 
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

bool HashSet::contains(const PositionNode &p) {
  PositionNode *el = get_element(p); 
  return el != nullptr;
}

size_t HashSet::entrys() const {
  return elements;
}


