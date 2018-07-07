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
    TreeNode() : left(0), right(0), parent(0) {}
    TreeNode(const T& init) : value(init), left(0), right(0), parent(0) {}

    // REPRESENTATION
    T value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
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

    /*
     * TODO: increment and decrement operator overloads
     * Increment and Decrement Operator Overloaders should make the iterator traverse
     * the tree in an in-order traversal.
    */
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
    iterator find(const T& key_value, TreeNode<T>* p) {}
    std::pair<iterator, bool> insert(const T& key_value, TreeNode<T>*& p){/*TODO*/}
    std::pair<iterator, bool> insert(TreeNode<T>*& key_node, TreeNode<T>*& p) {}
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
      // For in-order traversal, the begin point must be the smallest value,
      // which is the leftmost node in the tree
      if ( root_ == 0 ) return this->end();
      else {
        TreeNode<T>* smallest = root;
        while (smallest->left != 0) smallest = smallest->left;
        return iterator(smallest);
      }
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
    return insert(inset_node, p);
  } else {
    // it the item exists in the set, return pair of the iterator item and bool val of false
    return make_pair(to_find, false);
  }
}

template <class T>
typename iterator ds_set::find(const T& key_value, TreeNode<T>* p) {
  // Find function should traverse through the tree to see if there is a node
  // with the same value as key_value, and return the irerator pointing at the
  // Node. Otherwise, return null iterator;
  iterator itr = this->begin ();
  while ( itr != this->end(); ) {
    if ( *itr == key_value ) return itr;
    ++itr;
  }
  // return null iterator if item is not in the list
  return iterator (0);
}

template <class T>
std::pair<iterator, bool> ds_set::insert(TreeNode<T>*& key_node, TreeNode<T>*& p) {
  // TODO
  TreeNode<T>* parent_node = p;
  if ( root_ == 0 ) { // if there is not root_
    this->root_ = key_node;
    this->root_->parent = 0;
  }
  else { // if there is a root_

    // finding which parent node to add key_node to as a child
    bool node_found = false;
    while (!node_found) {
      if ( parent_node->value < key_value ) {
        if (parent_node->left != 0) parent_node = node->left;
        else parent_node_found = true;
      }
      else if ( parent_node->value > key_value ) {
        if (parent_node->right != 0) parent_node = parent_node->right;
        else node_found = true;
      }
    }

    // adding it -- lesser value on left, greater value on right
    if ( parent_node->value > key_value ) parent_node->left = key_node;
    else if ( parent_node->value < key_value ) parent_node->right = key_node;
    key_node->parent = parent_node;
  }
  // 3. Increment size value
  ++this->size_;
  return make_pair(iterator(key_node), true);

}

template <class T>
void ds_set::erase (const T& key_value, TreeNode<T>*& p) {
  /*
   * Erase Function: Erase the tree node, and, in order to evenly redistribute
   * the children of the erased node, insert the node back to the root_ of the
   * Tree to allow it to decide where it goes.
   * Do not want to re-insert ALL the children nodes, b/c there could be 1000+,
   * meaning, 1000+ nodes will need to be re-inserted for 1 erase, which is
   * inefficient, so just re-insert the 2 child nodes (left & right), and have
   * the trailing nodes just follow where it lands
   * The more balanced the tree is, the more efficient it is to use the tree.
  */

  // 1. Check if the value exists in the set
  typename iterator itr = find(key_value, p);
  if ( itr != iterator(0) ) {
    // if the result of find is not a null iterator
    // 1. Keep track of the left and right children
    TreeNode<T>* to_left = itr.ptr_->left;
    TreeNode<T>* to_right = itr.ptr_->right;

    // 2. Set pointers to this tree node to null
    if (itr.ptr_->parent != 0) {
      if ( itr.ptr_->parent->right == itr.ptr_ ) itr.ptr_->parent->right = 0;
      else if ( itr.ptr_->parent->left == itr.ptr_ ) itr.ptr_->parent->left = 0;
    }
    if ( to_left != 0 ) to_left->parent = 0;
    if ( to_right != 0 ) to_right->parent = 0;

    // 3. Delete the current tree node
    delete itr.ptr_;
    itr.ptr_ = 0;

    // 4. Redistribute the children of the deleted node
    insert (to_left, this->root_);
    insert (to_right, this->root_);

    // DONE
  }
}
#endif
