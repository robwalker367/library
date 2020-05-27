#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

// golden ratio
double PHI = (1 + sqrt(5)) / 2;

struct Node {
  int key;
  int degree;
  bool mark;
  Node* p;
  Node* left;
  Node* right;
  Node* child;
};

// inserts x to left of p in linked list
void insertLL(Node* p, Node* x) {
  x->right = p;
  x->left = p->left;
  p->left->right = x;
  p->left = x;
};

// concatenates two linked lists
void concatLL(Node* x, Node* y) {
  Node* y_l = y->left;
  Node* x_r = x->right;

  x->right = y;
  y->left = x;

  x_r->left = y_l;
  y_l->right = x_r;
};

// removes given node from the linked list
void removeLL(Node* x) {
  Node* x_l = x->left;
  Node* x_r = x->right;
  x_l->right = x_r;
  x_r->left = x_l;
}

// maximum degree function, n is number of nodes in heap
int D(int n) {
  return ceil(log(n) / PHI);
}

class FibHeap {
  private:
    int n;      // number of nodes in heap
    Node* min;  // pointer to min node
  public:
    FibHeap() {
      n = 0;
      min = nullptr;
    }

    Node* insert(int key) {
      // init new node with given key
      Node* x = new Node { 
        key,      // key
        0,        // degree
        false,    // mark
        nullptr,  // parent
        nullptr,  // left
        nullptr,  // right
        nullptr,  // child
      };
      
      // add to root list 
      if (!min) {
        min = x;
        x->left = x;
        x->right = x;
      } else {
        insertLL(min, x);
        if (x->key < min->key) {
          min = x;
        }
      }

      // update node count
      n++;
      return min;
    };

    Node* findMin() {
      return min;
    }

    FibHeap unionWith(FibHeap Y) {
      // init new heap for union
      FibHeap H = FibHeap();
      H.min = min;

      // concatenate root lists, update min accordingly
      concatLL(min, Y.min);
      if (!min || (Y.min && Y.min->key < min->key)) {
        H.min = Y.min;
      }

      // update node count
      H.n = n + Y.n;

      return H;
    }

    Node* extractMin() {
      Node* z = min;
      
      // if heap is non-empty
      if (z) {
        // iterate through children of minimum, add each child root list
        Node* c = z->child;
        if (c) {
          Node* c_i = c->right;
          insertLL(z, c);
          c->p = nullptr;
          while (c_i != c) {
            Node* new_c_i = c_i->right;
            insertLL(z, c_i);
            c_i->p = nullptr;
            c_i = new_c_i;
          }
        }

        // remove min from root list
        removeLL(z);
        if (z == z->right) {
          min = nullptr;
        } else {
          min = z->right;

          // fix heap to improve time bounds of future operations
          consolidate();
        }

        // decrement node counter
        n--;
      }
      return z;
    };

    void consolidate() {
      // initialize A, A[i] stores a pointer to a node with i children
      int Dn = D(n) + 2;
      Node** A = new Node*[Dn];
      for (int i = 0; i < Dn; i++) {
        A[i] = nullptr;
      }

      // iterate over root list
      Node* w = nullptr;
      Node* w_i = min;
      while (w_i != w) {
        Node* x = w_i;
        int d = x->degree;
        bool entered = false;

        // while exists node of same degree, make one node the
        // child of the other, preserving the heap property
        while (A[d]) {
          entered = true;
          Node* y = A[d];
          if (x->key > y->key) {
            Node* t = x;
            x = y;
            y = t;
          }
          link(y, x);
          A[d] = nullptr;
          d++;
        }
        A[d] = x;
        w_i = x->right;
        w = entered ? x : w;
      }

      // create root list comprised of remaining nodes in A[i]
      min = nullptr;
      for (int i = 0; i < Dn; i++) {
        if (A[i]) {
          Node* a = A[i];
          if (!min) {
            a->left = a;
            a->right = a;
            a->p = nullptr;
            min = a;
          } else {
            insertLL(min, a);
            if (a->key < min->key) {
              min = a;
            }
          }
        }
      }
    };

    // makes node y a child of x, updating respective member data
    void link(Node* y, Node* x) {
      removeLL(y);
      if (x->child) {
        insertLL(x->child, y);
        y->p = x;
      } else {
        x->child = y;
        y->p = x;
        y->left = y;
        y->right = y;
      }
      x->degree++;
      y->mark = false;
    };

    void decreaseKey(Node* x, int k) {
      // catch invalid key
      if (k > x->key) {
        cout << "Invalid key: new key > current key" << endl;
        return;
      }
      x->key = k;
      Node* y = x->p;

      // changes heap to abide by heap property
      if (y && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
      }
      if (x->key < min->key) {
        min = x;
      }
    };

    // moves x from child of y to root list
    void cut(Node* x, Node* y) {
      y->child = (x->right == x) ? nullptr : x->right;
      removeLL(x);
      y->degree--;

      insertLL(min, x);
      x->p = nullptr;
      x->mark = false;
    };


    void cascadingCut(Node* y) {
      // store pointer to y's parent
      Node* z = y->p;

      // if y is not a root, continue
      if (z) {
        if (!y->mark) {
          // y's first child has just been cut, so set mark to true
          y->mark = true;
        } else {
          // recurse up tree, cutting, until we find a root or unmarked node
          cut(y, z);
          cascadingCut(z);
        }
      }
    };

    void deleteNode(Node* x) {
      // set key to minimum possible value, then extract
      decreaseKey(x, INT_MIN);
      extractMin();
    };
};


int main(void) {
  FibHeap H = FibHeap();
  return 0;
};