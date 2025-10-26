#include <cstddef>
using namespace std; 

struct PositionNode {
  int y; 
  int x;

  PositionNode *next; 

  PositionNode(int getY, int getX) : y(getY), x(getX), next(nullptr) {}
};


class HashSet {
 
  private: 
    size_t capacity;
    size_t elements; 
    PositionNode **bucket; 

    bool compare_keys(const PositionNode *p1, const PositionNode *p2); 
    int hash(const PositionNode *p); 
    void add_to_bucket(PositionNode p);
    void rehash();
    PositionNode *get_element(const PositionNode &p); 

  public: 
    HashSet(size_t cap = 10);
    ~HashSet();
 
    void put(const PositionNode &p);
    void remove(const PositionNode &p);
    bool contains(const PositionNode &p);
    size_t entrys() const;
}; 

