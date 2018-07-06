#ifndef ds_set_h_
#define ds_set_h_
#include <utility> // pair class

#define DEBUG true
/*
 * NOTE: State Order Notation for each function implementation
*/

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

    // make friend to access private ptr_
    friend class ds_set<T>;
};

//-----------------------------------------------------------------------------
// DS SET CLASS
template <class T>
class ds_set {
  private:
    // REPRESENTATION
    TreeNode<T>* root_;
    int size_;
    TreeNode<T>& copy_tree(TreeNode<T>* old_tree) {/*TODO*/}
    void destroy_tree(TreeNode<T>* p) {/*TODO*/}
    iterator find(const T& key_value, TreeNode<T>* p) {
      /*TODO*/
    }
    std::pair<iterator, bool> insert(const T& key_value, TreeNode<T>*& p){/*TODO*/}
    void erase (T const& key_value, TreeNode<T>*&p) {/*TODO*/}
    void print_in_order(std::ostream& ostr, const TreeNode<T>* p) const {
      if (p) {
        print_in_order(ostr, p->left);
        ostr << p->value << std::endl;
        print_in_order(ostr, p->right);
      }
    }
  public:
    // CONSTRUCTORS
    ds_set () : root_(NULL), size(0) {}
    ds_set(const ds_set<T>& old) : size_(old.size_) {
      root_ = this->copy_tree(old.root_);
    }
    ~ds_set() {this->destroy_tree(root_); root_=NULL;}

    // OPERATOR OVERLOADING
    ds_set& operator= (const ds_set<T>& old) {
      if (&old != this) {
        this->destroy_tree(root_);
        root_ = this->copy_tree(old.root_);
        size_ = old.size_;
      }
      return *this;
    }
    /* O(1) */bool operator== (const ds_set<T>& old) {return old.root_ == this->root_;}
    /* O(1) */bool operator!= (const ds_set<T>& old) {return old.root_ != this->root_;}
    friend std::ostream& operator<< (std::ostream& ostr, const ds_set<T>& s){
      s.rpint_in_order(ostr, s.root_);
      return ostr;
    }

    typedef tree_iterator<T> iterator;
    /* O(!) */int size() const {return size_; }

    iterator find(const T& key_value) { return find(key_value, root_); }
    std::pair<iterator, bool> insert(const T& key_value) { return insert(key_value, root_); }
    int erase(T const& key_value) { return erase(key_value, root_); }

    // ITERATORS
    iterator begin () const {
      // TODO
      return 0;
    }
    iterator end () const { return iterator(0); }
};

template <class T>
std::pair<iterator, bool> ds_set::insert(const T& key_value, TreeNode<T>*& p) {
  /*
  * Insert Function:
    - Check if the value exists.
        - If so, return a pair with an iterator pointing to the value, and bool value of  false
        - Otherwise, insert the element into the set and return the iterator pointing to it, and a bool value of true
  */
  iterator to_find = find(key_value, p);
  if ( to_find != iterator(0) ) {
    // if the item does not exist in the set
    // 1. Create a new tree node for key_value
    TreeNode<T>* insert_node = new TreeNode<T>(key_value);

    // 2. Find where in the tree the item belongs and add it
    TreeNode<T>* node = root_;
    bool node_found = false;
    while (!node_found) {
      if ( node->value < key_value ) {
        if (node->left != 0) node = node->left;
        else node_found = true;
      }
      else if ( node->value > key_value ) {
        if (node->right != 0) node = node->right;
        else node_found = true;
      }
    }

    // adding it -- lesser value on left, greater value on right
    if ( node->value > key_value ) node->left = insert_node;
    else if ( node->value < key_value ) node->right = insert_node;

    return make_pair(iterator(insert_node), true);

    // 3. Increment size value
    ++this->size_;
  } else {
    // it the item exists in the set, return pair of the iterator item and bool val of false
    return make_pair(to_find, false);
  }
}

#endif
