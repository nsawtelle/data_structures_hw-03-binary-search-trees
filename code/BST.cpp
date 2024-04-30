/* Note: refer to the header file (BST.h) for documentation of each method. */

#include "BST.h"

BST::BST() {
  root = new bst_node*;
  *root = NULL;
}

BST::~BST() {}

bst_node* BST::init_node(int data) {
  ///////Create a new bst_node on the heap
  bst_node* newNode = new bst_node;

  ///////Set the data of the new node to the given data
  newNode->data = data;

  ///////Set the left child of the new node to nullptr
  newNode->left = nullptr;

  //////Set the right child of the new node to nullptr
  newNode->right = nullptr;

  ///////Return a pointer to the new node
  return newNode; }

///////This function inserts the new_node into the binary search tree
///while maintaining the binary search tree property. It updates
///the root pointer if necessary.
void BST::insert(bst_node* new_node) {
    
  //////If the root pointer is null, set it to the new node
  if (*root == NULL) {
    *root = new_node;
  }
  else {
      
    //////Otherwise, traverse the tree to find the appropriate
    ///position for the new node
    bst_node* current = *root;
    while (true) {
        
      /////If the data of the new node is less than the current
      ///node's data, move to the left subtree
      if (new_node->data < current->data) {
          
        /////If the left child of the current node is null, insert
        ///the new node here
        if (current->left == NULL) {
          current->left = new_node;
          break;
        }
          
        ////Otherwise, move to the left child and continue traversing
        current = current->left;
      }
      else {
          
        ////If the data of the new node is greater than or equal to
        ///the current node's data, move to the right subtree
        if (current->right==NULL) {
            
          /////If the right child of the current node is null, insert
          ///the new node here
          current->right = new_node;
          break;
        }
          
        ////Otherwise, move to the right child and continue traversing
        current = current->right;
      }
    }
  }
}

/////This function creates a new node with the given data value
///and inserts it into the binary search tree using the insert method
void BST::insert_data(int data) {
    
  /////Create a new node with the given data value
  bst_node* newNode = init_node(data);

  ////////Insert the new node into the binary search tree
  insert(newNode);
}

//////This function removes a node from the BST whose data value
///matches the input data. It also updates the root pointer
///if needed.
void BST::remove(int data) {
    
/////Calls the removeNode function to remove the node with the
///specified data value from the subtree rooted at the current
///root pointer, and update the root pointer with the new root
///of the subtree after removal.
  *root = removeNode(*root, data);
}

/////////Recursive function to remove a node from the subtree rooted at 'node'
bst_node* BST::removeNode(bst_node* node, int data) {
  if (node == nullptr) {
    return nullptr;   //If tree/subtree empty, there is nothing to remove
  }

  ///////////If data < current node's data, go to the left of the tree
  if (data < node->data) {
    node->left = removeNode(node->left, data);
  }

  ///////////If data > current node's data, go to the right of the tree
  else if (data > node->data) {
    node->right = removeNode(node->right, data);
  }
  
  /////////If data matches current node's data, this will be the node of removal
  else {
    /////////Scenario: Node has no children or only one child
    if (node->left == nullptr) {
      bst_node* temp = node->right;
      delete node;
      return temp; //Returns the right child
    }
    else if (node->right == nullptr) {
      bst_node* temp = node->left;
      delete node;
      return temp; //Returns the left child
    }
      
    ///////////Scenario: If the node has two children
    ///////////Find the predecessor
    bst_node* temp = findMinNode(node->right);
    node->data = temp->data; //copies the data of the predecessor to this node
    node->right = removeNode(node->right, temp->data);
  }
  return node;
}

/////This function finds and returns the node with the minimum
///data value in the subtree rooted at the input node. If the
///subtree is empty (node is nullptr), it returns nullptr
bst_node* BST::findMinNode(bst_node* node) {
    
    ////If the subtree is empty, return nullptr
  if (node == nullptr) {
    return nullptr;
  } 
  /////Traverse down the left subtree ultil reaching the node with
  ///the minimum data value
  while (node->left != nullptr) {
    node = node->left;
  }
 //////Returns the node with the minimum data value
  return node;
}

/////This function checks if a given data value exists in the
///subtree rooted at the input node. It returns true if the data
///value is found, and false otherwise
bool BST::contains(bst_node* subt, int data) {
    
 /////If the subtree is empty, return false
  if (subt == nullptr) {
    return false;
  }
    
  /////If the data value matches the current node's data, return true
  if (subt->data == data) {
    return true;
  }
    
  ///////If the data value is less than the current node's data,
  ///recursively search the left subtree
  if (data < subt->data) {
    return contains(subt->left, data);
  }
    
  /////If the data value is greater than the current node's data,
  ///recursively search the right subtree
  else {
    return contains(subt->right, data);
  }
}

bst_node* BST::get_node(bst_node* subt, int data) {
  /////////Base case, if the subtree is empty,
  ///or node with the given data is found
  if (subt == nullptr || subt->data == data) {
    return subt;
  }
    
  ////////If the data is smaller than the current node's data,
  ///search the left subtree
  if (data < subt->data) {
    return get_node(subt->left, data);
  }
    
  ///////If the data is greater than the current node's data,
  ///search the right subtree
  else {
    return get_node(subt->right, data);
  }
}

int BST::size(bst_node* subt) {
  ///////Base case, if the subtree is empty
  if (subt == nullptr) {
    return 0;
  }
    
  ///////Recursively count the nodes in the left subtrees
  int left_size = size(subt->left);

  //////Recursively count the nodes in the right subtrees
  int right_size = size(subt->right);

  //////Return the total size of the subtree 
  ///(1 as the current node + the sizes of the left and right nodes)
  return 1 + left_size + right_size;
}

void BST::to_vector(bst_node* subt, vector<int>& vec) {
  ///////Base case, if the subtree is empty
  if (subt == nullptr) {
    return;
  }
    
  ///////Recursively traverse the left subtree
  to_vector(subt->left, vec);

  ///////Add the current node's data to the vector
  vec.push_back(subt->data);

  ///////Recursively traverse the right subtree
  to_vector(subt->right, vec);
}

bst_node* BST::get_root() {
  if (*root == nullptr)
    return nullptr;
  return *root;
}

void BST::set_root(bst_node** new_root) {
  root = new_root;
}
