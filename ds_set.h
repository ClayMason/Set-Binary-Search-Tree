#ifndef ds_set_h_
#define ds_set_h_
#include <utility> // pair class
#include <iostream>

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
    bool is_leaf () { return left == 0 && right == 0; }
    bool is_left_child () {
      if (parent != 0) return parent->left == this;
      return false;
    }

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
    bool is_leaf () { return ptr_->is_leaf(); }
    bool is_left_child () {
      return ptr_->is_left_child();
    }
    tree_iterator<T>& find_next (const tree_iterator<T>& iter);
    tree_iterator<T>& find_prev (const tree_iterator<T>& iter);
  public:
    // CONSTRUCTORS
    tree_iterator() : ptr_(NULL) {}
    tree_iterator(TreeNode<T>* p) : ptr_(p) {}
    tree_iterator(const tree_iterator& old) : ptr_(old.ptr_) {}
    ~tree_iterator() {}

    // OPERATOR OVERLOADING
    tree_iterator& operator=(const tree_iterator& old) {ptr_=old.ptr_; return *this;}
    const T& operator*() const {return ptr_->value;}
    // iterators equal if ptr is same, not if value is same
    bool operator== (const tree_iterator& r) { return ptr_ == r.ptr_; }
    bool operator!= (const tree_iterator& r) { return ptr_ != r.ptr_; }

    /*
     * TODO: increment and decrement operator overloads
     * Increment and Decrement Operator Overloaders should make the iterator traverse
     * the tree in an in-order traversal.
    */
    tree_iterator<T>& operator++ (int) { // itr++
      return find_next (tree_iterator<T> (*this));
    }
    tree_iterator<T>& operator++ () { // ++iter
      return find_next (*this);
    }
    tree_iterator<T>& operator-- (int) { // itr--
      return find_prev (tree_iterator<T> (*this));
    }
    tree_iterator<T>& operator-- () { // --iter
      return find_prev (*this);
    }

    // make friend to access private ptr_
    friend class ds_set<T>;
};

template <class T>
tree_iterator<T>& tree_iterator<T>::find_next (const tree_iterator<T>& iter) {
  tree_iterator<T> itr(iter);
  // leaf nodes
  if ( itr.is_leaf() ) {
    if ( itr.is_left_child() ) itr.ptr_ = itr.ptr_->parent;
    else {
      // if right leaf
      TreeNode<T>* itr_parent = itr.ptr_->parent;
      TreeNode<T>* itr_child = itr.ptr_;
      while ( itr_child !=0 && itr_parent !=0 && !itr_child->is_left_child() ) {
        itr_child = itr_parent;
        itr_parent = itr_parent->parent;
      }

      // if itr_parent is null, then that is the end of the tree, otherwise, return the itr_parent ptr
      itr.ptr_ = itr_parent;
    }
  }

  // TODO: non-leaf nodes
  else {
    if ( ptr_->right != 0 ) {
      itr.ptr_ = itr.ptr_->right;
      if ( itr.ptr_ != 0 ) { while ( itr.ptr_->left != 0 ) itr.ptr_ = itr.ptr_->left; }
    } else itr.ptr_ = 0; // return null iterator
  }

  return itr;
}

template <class T>
tree_iterator<T>& tree_iterator<T>::find_prev (const tree_iterator<T>& iter) {
  // find the node previous to this one in the tree in a reverse in-order traversal
  tree_iterator<T> itr(iter);
  if (itr.is_leaf ()){
    if (itr.is_left_child()) {
      // left child
      TreeNode<T>* t_parent = itr.ptr_->parent;
      TreeNode<T>* t_child = itr.ptr_;
      while (t_child != 0 && t_parent != 0 && t_child->is_left_child()) {
        t_child = t_parent;
        t_parent = t_parent->parent;
      }

      itr.ptr_ = t_parent;
    } else {
      // right child
      itr.ptr_ = itr.ptr_->parent;
    }
  }

  else {
    // non-leaf
    itr.ptr_ = itr.ptr_->left;
    if ( itr.ptr_ != 0 ) { while (itr.ptr_->right != 0) itr.ptr_ = itr.ptr_->right; }
  }

  return itr;
}

//-----------------------------------------------------------------------------
// DS SET CLASS
template <class T>
class ds_set {
  public:
    typedef tree_iterator<T> iterator;
    // CONSTRUCTORS
    ds_set () : root_(NULL), size_(0) {}
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
      s.print_in_order(ostr, s.root_);
      return ostr;
    }
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
        TreeNode<T>* smallest = root_;
        while (smallest->left != 0) smallest = smallest->left;
        return iterator(smallest);
      }
    }
    iterator end () const { return iterator(0); }
  private:
    // REPRESENTATION
    TreeNode<T>* root_;
    int size_;
    TreeNode<T>& copy_tree(TreeNode<T>* old_tree);
    void copy_sibblings (TreeNode<T>* parent_, TreeNode<T>* l_child, TreeNode<T>* r_child);
    void destroy_tree(TreeNode<T>* p);
    iterator find(const T& key_value, TreeNode<T>* p);
    std::pair<iterator, bool> insert(const T& key_value, TreeNode<T>*& p);
    std::pair<iterator, bool> insert(TreeNode<T>*& key_node, TreeNode<T>*& p);
    void erase (T const& key_value, TreeNode<T>*&p);
    void print_in_order(std::ostream& ostr, const TreeNode<T>* p) const {
      if (p) {
        print_in_order(ostr, p->left);
        ostr << p->value << std::endl;
        print_in_order(ostr, p->right);
      }
    }
};

template <class T>
std::pair<typename ds_set<T>::iterator, bool> ds_set<T>::insert(const T& key_value, TreeNode<T>*& p) {
  /*
  * Insert Function:
    - Check if the value exists.
        - If so, return a pair with an iterator pointing to the value, and bool value of  false
        - Otherwise, insert the element into the set and return the iterator pointing to it, and a bool value of true
  */
  iterator to_find = find(key_value, p);

  #if DEBUG
  std::cout << "Insert Function:\tTo Find: " << key_value << " - exits? => ";
  if ( to_find != iterator(0) ) std::cout << "yes" << std::endl;
  else std::cout << "no" << std::endl;
  #endif

  if ( to_find == iterator(0) ) { // i'm actually stupid...
    // if the item does not exist in the set
    // 1. Create a new tree node for key_value
    TreeNode<T>* insert_node = new TreeNode<T>(key_value);

    #if DEBUG
    std::cout << "Entering Second Insert" << std::endl;
    #endif

    return insert(insert_node, p);
  } else {
    // it the item exists in the set, return pair of the iterator item and bool val of false
    #if DEBUG
    std::cout << "Returning false pair" << std::endl;
    #endif

    return std::make_pair(to_find, false);
  }
}

template <class T>
typename ds_set<T>::iterator ds_set<T>::find(const T& key_value, TreeNode<T>* p) {
  // Find function should traverse through the tree to see if there is a node
  // with the same value as key_value, and return the irerator pointing at the
  // Node. Otherwise, return null iterator;
  iterator itr = this->begin ();
  while ( itr != this->end() ) {
    if ( *itr == key_value ) return itr;
    ++itr;
  }
  // return null iterator if item is not in the list
  return iterator (0);
}

template <class T>
std::pair<typename ds_set<T>::iterator, bool> ds_set<T>::insert(TreeNode<T>*& key_node, TreeNode<T>*& p) {
  // TODO
  TreeNode<T>* parent_node = p;
  if ( root_ == 0 ) { // if there is not root_
    this->root_ = key_node;
    this->root_->parent = 0;

    #if DEBUG
    std::cout << "Insert: setting root_ node" << std::endl;
    #endif
    assert(root_ != 0);
  }
  else { // if there is a root_

    #if DEBUG
    std::cout << "Insert: setting non-root_ node" << std::endl;
    #endif
    assert(root_ != 0);

    // finding which parent node to add key_node to as a child
    bool node_found = false;
    while (!node_found) {
      if ( parent_node->value < key_node->value ) {
        if (parent_node->left != 0) parent_node = parent_node->left;
        else node_found = true;
      }
      else if ( parent_node->value > key_node->value ) {
        if (parent_node->right != 0) parent_node = parent_node->right;
        else node_found = true;
      }
    }

    // adding it -- lesser value on left, greater value on right
    if ( parent_node->value > key_node->value ) parent_node->left = key_node;
    else if ( parent_node->value < key_node->value ) parent_node->right = key_node;
    key_node->parent = parent_node;
  }
  // 3. Increment size value
  ++this->size_;
  std::cout << "Item added" << std::endl;
  return std::make_pair(iterator(key_node), true);

}

template <class T>
void ds_set<T>::erase (const T& key_value, TreeNode<T>*& p) {
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
  typename ds_set<T>::iterator itr = find(key_value, p);
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

template <class T>
void ds_set<T>::destroy_tree(TreeNode<T>* p) {
  // recursive destroy_tree
  if ( p->parent != 0 ) {
    // check which node it is -- left or right
    if ( p->parent->left == p ) p->parent->left = 0;
    else if ( p->parent->right == p ) p->parent->right = 0;
  }

  if ( p->right != 0 ) destroy_tree (p->right);
  if ( p->left != 0 ) destroy_tree (p->left);

  delete p;
  p = 0;
}

template <class T>
TreeNode<T>& ds_set<T>::copy_tree(TreeNode<T>* old_tree) {
  // copy the tree_nodes and key_values into this tree
  // -- recursive

  // 1. Create new Node
  TreeNode<T>* node_copy = new TreeNode<T>(*old_tree);
  // check if old_tree is the root
  if ( old_tree->parent == 0 ) this->root_ = node_copy;
  copy_sibblings(node_copy, old_tree->left, old_tree->right);
  return this->root_;

}

template <class T>
void ds_set<T>::copy_sibblings (TreeNode<T>* parent_, TreeNode<T>* l_child, TreeNode<T>* r_child) {
  // recursive base case -- if both children are null, recursion will end
  if ( l_child != 0 || r_child != 0 ) {
    // make copy of the children -- parent already exists
    if (l_child != 0) {
      TreeNode<T>* left_copy = new TreeNode<T>(*l_child);
      // link parent and child nodes
      parent_->left = left_copy;
      left_copy->parent = parent_;

      // pass the children of the left child, and our left copy to copy those sibblings to the left
      copy_sibblings(left_copy, l_child->left, l_child->right);
    }
    if (l_child != 0) {
      TreeNode<T>* right_copy = new TreeNode<T>(*r_child);
      // link parent and child nodes
      parent_->right = right_copy;
      right_copy->parent = parent_;

      copy_sibblings(right_copy, r_child->left, r_child->right);
    }

    // call the recursion on the children
  }
}

#endif
