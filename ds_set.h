#ifndef ds_set_h_
#define ds_set_h_

#define DEBUG true

//-----------------------------------------------------------------------------
// TREE NODE CLASS
template <class T>
class TreeNode {
  public:
    // CONSTRUCTORS
    TreeNode() : left(NULL), right(NULL) {}
    TreeNode(const T& init) : value(init), left(NULL), right(NULL) {}

    // REPRESENTATION
    T value;
    TreeNode* left;
    TreeNode* right;
};

template <class T> class ds_set;
//-----------------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class T>
class tree_iterator {
  private:
    // REPRESENTATION
    TreeNode<T>* ptr_;
  public:
    // CONSTRUCTORS
    tree_iterator() : ptr_(NULL) {}
    tree_iterator(TreeNode<T>* p) : ptr_(p) {}
    tree_iterator(const tree_iterator& old) : ptr_(old.ptr_) {}
    ~tree_iterator() {}

    // OPERATOR OVERLOADING
    tree_iterator& operator=(const tree_iterator& old) {ptr_=old.ptr; return *this;}
    const T& operator*() const {return ptr_->value; }
    // iterators equal if ptr is same, not if value is same
    bool operator== (const tree_iterator& r) { return ptr_ == r.ptr_; }
    bool operator!= (const tree_iterator& r) { return ptr_ != r.ptr_; }
    // TODO: increment and decrement operator overloads
    tree_iterator<T>& operator++ (int) { // itr++
      return 0;
    }
    tree_iterator<T>& operator++ { // ++iter
      return 0;
    }
    tree_iterator<T>& operator-- (int) { // itr--
      return 0;
    }
    tree_iterator<T>& operator-- { // --iter
      return 0;
    }
};

//-----------------------------------------------------------------------------
// DS SET CLASS

#endif
