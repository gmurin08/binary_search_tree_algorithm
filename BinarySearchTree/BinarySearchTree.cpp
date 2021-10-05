//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Gino Murin
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    //Points to current node's left child
    Node* left;
    //points to current node's right child
    Node* right;

    //Default constructor
    Node() {
        //initializes nodes left and right children to nullptr
        left = nullptr;
        right = nullptr;
    }

    //Overload constructor with bid object
    Node(Bid aBid) : Node() {
        this->bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    void postOrder(Node* node);
    void preOrder(Node* node);
    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);

    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void DestroyTree(Node* tree);
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    delete root;
}



/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    this->preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // Implements inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(bid);
    } 
    // else
    else {
        // add Node root and bid
        this->addNode(root, bid);
    }
   
      
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // remove node root bidID
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // Searches the tree for a bid
    // set current node equal to root
    Node* current = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (current != nullptr) {
        // if match found, return current bid
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;
        }

        // if bid is smaller than current node then traverse left
        if (bidId.compare(current->bid.bidId) < 0) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }

    //Initialize and return empty bid when while loop breaks
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // Inserts a bid into the tree
    // if node is larger then add to left
    if (node->bid.bidId.compare(bid.bidId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(bid);
        }
        else {
            // else recurse down the left node
            this->addNode(node->left, bid);
        }
    }
    // else 
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(bid);
        }
        //else
        else {
            // recurse down the left node
            this->addNode(node->right, bid);
        }
    }    
            
}
void BinarySearchTree::inOrder(Node* node) {
    // Inorder Traversal
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder to left
        inOrder(node->left);
        //output bidID, title, amount, fund
        cout << node->bid.bidId << ": " << node->bid.title << " | "
            << " | " << node->bid.amount << " | " << node->bid.fund << endl;
        //InOder to right
        inOrder(node->right);
      }
      
      
      
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    //if the node is null then return 
    if (node == nullptr) {
        return node;
    }
    //if the bid is smaller than the current node bid
    if (bidId.compare(node->bid.bidId) < 0) {
        //recurse down left side of tree
        node->left = removeNode(node->left, bidId);
    }
    //else if bid is larger then current node bid
    else if(bidId.compare(node->bid.bidId) > 0){
        //recurse down right side of tree
        node->right = removeNode(node->right, bidId);
    }
    //else
    else {
        //if node has no children (leaf)
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        //if node has one left child
        else if (node->left != nullptr && node->right == nullptr) {
            //create a temp node 
            Node* temp = node;
            //assign left child to node
            node = node->left;
            delete temp;
        }
        //if node has one right child
        else if (node->right != nullptr && node->left == nullptr) {
            //create a temp node 
            Node* temp = node;
            //assign right child to node
            node = node->right;
            delete temp;
        }
        //else node has two children
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->bid = temp->bid;
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
    return node;
}

void BinarySearchTree::postOrder(Node* node) {
    // postorder traversal
    //if node is not equal to null ptr
    if (node != nullptr) {
      //postOrder left
      postOrder(node->left);
      //postOrder right
      postOrder(node->right);
      //output bidID, title, amount, fund
      cout << node->bid.bidId << ": " << node->bid.title << " | "
          << " | " << node->bid.amount << " | " << node->bid.fund << endl;
     }
      

}

void BinarySearchTree::preOrder(Node* node) {
    // preorder traversal
    //if node is not equal to null ptr
    if (node != nullptr) {
      //output bidID, title, amount, fund
      cout << node->bid.bidId << ": " << node->bid.title << " | "
            << " | " << node->bid.amount << " | " << node->bid.fund << endl;
      //postOrder left
      postOrder(node->left);
      //postOrder right 
      postOrder(node->right);
     }
           
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    /* readand display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }*/

    //initialize count for number of bids
    int count = 0;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;
            //increment count
            count++;
            // push this bid to the end
            bst->Insert(bid);
        }
        //output number of bids read
        cout << count << " bids read" << endl;

    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98104";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98104";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst {};

    Bid bid;

    int travversalChoice = 0;
    int choice = 0;

    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            //UPDATE: added functionality to choose multiple traversal styles
            cout << "1. Inorder Traversal" << endl;
            cout << "2. Postorder Traversal" << endl;
            cout << "3. Preorder Traversal" << endl;
            cout << "Enter choice: ";
            cin >> travversalChoice;
            switch (travversalChoice) {

            case 1:
                bst->InOrder();
                break;

            case 2:
                bst->PostOrder();
                break;

            case 3: 
                bst->PreOrder();
                break;
            }
            
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
