#include <iostream>
#include <vector> 

template <typename T,size_t dim> 
class BNode{
  public:
    using value_t = T;
    static const short trait=1;
    BNode():size(0){
      children[0]=nullptr;
    }
    ~Bnode(){}
    BNode* children[dim+1];
    value_t  values[dim];
    int size;
};

template<typename T,typename value_t>
int binarySearch(T* node,value_t x){
  int l=0;
  int r=node->size-1;
  while(l<r){
    int med=l+(r-l)/2;
    if(node->values[med]<v)
      l=med+1;
    else
      r=med;
  }
  return l;
}


template<typename T,typename value_t>
int linearSearch(T* node,value_t x){
  int l=0;
  int r=node->size;
  for(;l<r;l++){
    if(node->values[l]>=)
      return l;
  }
  return l;
}

template<typename T ,int Q>
struct TreeHelper{
  using Node = T;
  using value_t = typename Node::value_t;
  static void insert(Node* node, value_t x){
    std::cout<<"Entro a normal\n";
  }
};

template<typename T>
struct TreeHelper<T,1>{
  using Node = T;
  using value_t = typename Node::value_t;
  static void insert(Node* node, value_t x){
    std::cout<<"Entro a dim1 \n";
  }
  static bool search(value_t x,Node** node){
    return 0;
  }
};

template <typename T>
class BTree {
public: 
  using value_t = typename T::value_t;
  using Node = T;
  //using functor_t = typename T::functor_t ;

  Node* root;

  BTree(void):root(nullptr){}

  ~BTree(void){
  }

  void insert(const value_t& val = 0){
    TreeHelper<Node,Node::trait>::insert(root,val);
  }

  bool find(const value_t = 0) const{
    // TODO :: SEARCH
    // search(x); inside each page
    return false;
  }
  void print(){
  }


};

template <typename _T>
std::ostream& operator<<(std::ostream& out, BTree<_T> tree){
  tree.print();// (out)
  return out;
}

int main() {
  using b_3int_node = BNode<int,3>;
  using b_3int_tree =  BTree<b_3int_node>;
  b_3int_tree btree;
  btree.insert(3);

  return 0;
}

