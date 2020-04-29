#include <iostream>
#include <vector> 
#include <queue> 
#include <algorithm> 
#include <ctime> 

template <typename T,size_t dim=3> 
class BNode{
  public:
    using value_t = T;
    static const short trait=1;
    BNode():size(0),isLeaf(true),parent(nullptr){}
    ~BNode(){}
    BNode* parent;
    BNode* children[dim+1];
    value_t  values[dim];
    bool isLeaf;
    int size;
};

template<typename T,typename value_t>
int binarySearch(T** node,value_t value){
  int l=0;
  int r=(*node)->size;
  while(l<r){
    int med=l+(r-l)/2;
    if((*node)->values[med]<value)
      l=med+1;
    else
      r=med;
  }
  return l;
}

template<typename T,typename value_t>
int linearSearch(T** node,value_t value){
  int l=0;
  int r=(*node)->size;
  for(;l<r;l++){
    if((*node)->values[l]>=value)
      return l;
  }
  return l;
}
template<typename T>
void inorder_print(T* node){

  if(!node->isLeaf)
      inorder_print<T>(node->children[0]);

  for(int i=0;i<node->size;i++){
    std::cout<<node->values[i]<<" ";
    if(!node->isLeaf)
      inorder_print<T>(node->children[i+1]);
  }

}

template<typename T>
void preorder_print(T* node){
  for(int i=0;i<node->size;i++){
    std::cout<<node->values[i]<<" ";
  }
  std::cout<<"\n";
  if(!node->isLeaf){
    for(int i=0;i<=node->size;i++){
      preorder_print<T>(node->children[i]);
      std::cout<<"\t";
    }
  }
}


template<typename T>
void postorder_print(T* node){
  if(!node->isLeaf){
    for(int i=0;i<=node->size;i++)
      postorder_print<T>(node->children[i]);
  }
  std::cout<<"\t";
  for(int i=0;i<node->size;i++){
    std::cout<<node->values[i]<<" ";
  }
}

//Other behavior
template<typename T ,int Q>
struct TreeHelper{
  using Node = T;
  using value_t = typename Node::value_t;
  static void insert(Node* node, value_t value){
    std::cout<<"Entro a normal\n";
  }
};

template<typename T,typename value_t>
void insertNonFull(T** node,value_t value,T* new_son){
  int index=(*node)->size;
  while(index>0 && (*node)->values[index-1]>value){
    std::swap((*node)->values[index-1],(*node)->values[index]);
    std::swap((*node)->children[index],(*node)->children[index+1]);
    index--;
  }
   (*node)->values[index]=value;
   (*node)->children[index+1]=new_son;
   (*node)->size++;

}

template<typename T,typename value_t>
void insertFull(T** node,value_t value,T* new_son,int sizeT){

  using Node = T;

  int dim=(*node)->size;

  Node* node_bro=new Node;
  node_bro->isLeaf=(*node)->isLeaf;

  std::vector<value_t> _values(dim+1);
  std::vector<Node*> _children(dim+2);

  _children[0]=(*node)->children[0];
  for(int i=0;i<dim;i++){
    _values[i]=(*node)->values[i];
    _children[i+1]=(*node)->children[i+1];
  }

  int pos=dim;
  while(_values[pos-1]>value && pos>0){
    std::swap(_values[pos-1],_values[pos]);
    std::swap(_children[pos],_children[pos+1]);
    pos--;
  }

  _values[pos]=value;
  _children[pos+1]=new_son;


  int i;
  for(i=0;i<dim/2;i++){
    (*node)->values[i]=_values[i];
    (*node)->children[i]=_children[i];
  }
  (*node)->children[i]=_children[i];
  (*node)->size=dim/2;

  value_t value_aux=_values[i];
  i++;

  if(!node_bro->isLeaf){
    node_bro->children[0]=_children[i];
    node_bro->children[0]->parent=node_bro;
  }
    
  for(int j=0;i<=dim;i++,j++){
    node_bro->values[j]=_values[i];
    if(!node_bro->isLeaf){
      node_bro->children[j+1]=_children[i+1];
      node_bro->children[j+1]->parent=node_bro;
    }
    node_bro->size++;
  }

  if((*node)->parent){
    node_bro->parent=(*node)->parent;
    *node=(*node)->parent;
    if((*node)->size==sizeT){
      insertFull<Node,value_t>(node,value_aux,node_bro,sizeT);
    }
    else{
      insertNonFull<Node,value_t>(node,value_aux,node_bro);
    }
  }
  else{
    Node* root=new Node;
    root->isLeaf=false;
    root->values[0]=value_aux;
    root->size++;
    root->children[0]=*node;
    root->children[1]=node_bro;
    (*node)->parent=root;
    node_bro->parent=root;
    *node=root;
  }

}

template<typename T>
struct TreeHelper<T,1>{
  using Node = T;
  using value_t = typename Node::value_t;

  static void insert(Node** node, value_t value,size_t dim){


    if((*node)->size==0){
      (*node)->values[0]=value;
      (*node)->size++;
      return;
    }
    search(value,node);


    if((*node)->size==dim){
      insertFull<Node,value_t>(node,value,nullptr,dim);
    }
    else{
      insertNonFull<Node,value_t>(node,value,nullptr);
    }
  }

  
  static bool search(value_t value,Node** node){
    if((*node)->size==0)
      return false;

    bool ans=false;
    int pos;
    while(!(*node)->isLeaf){
      pos=binarySearch<Node,value_t>(node,value);
      if(pos<(*node)->size){
        if((*node)->values[pos]==value)
          ans=true;
      }
      *node=(*node)->children[pos];
    }
    if(ans)
      return ans;
    pos=binarySearch<Node,value_t>(node,value);
    if(pos>=(*node)->size)
      return false;
    return (*node)->values[pos]==value;
  }

  static void print(Node* root){
    inorder_print<Node>(root);
  }
};

template <typename T>
class BTree {
  size_t dim;
  void up(){
    while(root->parent)
      root=root->parent;
  }
public: 
  using value_t = typename T::value_t;
  using Node = T;

  Node* root;

  BTree(void){ 
    root=new Node;
    dim=sizeof(T::values)/sizeof(value_t);
  }

  void deleteRecursive(Node* node){
    if(node->isLeaf){
      delete node;
      return;
    }
    for(int i=0;i<=node->size;i++)
      deleteRecursive(node->children[i]);
  }
  ~BTree(void){
    deleteRecursive(root);
  }

  void insert(const value_t& val){
    TreeHelper<Node,Node::trait>::insert(&root,val,dim);
    up();
  }

  bool find(const value_t& value){
    bool ans=TreeHelper<Node,Node::trait>::search(value,&root);
    up();
    return ans;
  }

  //std::ostream& operator<<(std::ostream&,const BTree&);

};

  template<typename _T>
  std::ostream& operator<<(std::ostream& out, const BTree<_T> & tree){
    TreeHelper<_T,_T::trait>::print(tree.root);
    return out;
  }


int main() {

  srand(time(NULL));
  int size=300;

  //Prueba con binttree
  using b_4int_node = BNode<int,4>;
  using b_4int_tree =  BTree<b_4int_node>;
  b_4int_tree btree;
  std::vector<int> v(size);

  for(int i =0;i<size;i++)
    v[i]=rand()%10000+1;

  for(int i =0;i<size;i++){
    std::cout<<"\nvalue entereed ::"<<v[i]<<std::endl;
    btree.insert(v[i]);
  }

  for(int i =0;i<size;i++)
    std::cout<<v[i]<<" is "<<btree.find(v[i])<<std::endl;
  std::cout<<btree<<std::endl;


  //Prueba con bfloattree
  using b_3float_node = BNode<float,3>;
  using b_3float_tree =  BTree<b_3float_node>;
  b_3float_tree btree2;

  float a=5.0;
  std::vector<float> v2(size);
  for(int i =0;i<size;i++)
    v2[i]=(float(rand())/float((RAND_MAX)) * a);

  for(int i =0;i<size;i++){
    std::cout<<"\nvalue entereed ::"<<v2[i]<<std::endl;
    btree2.insert(v2[i]);
  }

  for(int i =0;i<size;i++)
    std::cout<<v2[i]<<" is "<<btree2.find(v2[i])<<std::endl;
  std::cout<<btree2<<std::endl;

  return 0;
}

