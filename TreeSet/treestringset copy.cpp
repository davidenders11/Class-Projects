#include "treestringset.hpp"

using namespace std;

TreeStringSet::~TreeStringSet() {
    delete root_;  // Call node destructor helper function
}

size_t TreeStringSet::size() const {
    return size_;
}

void TreeStringSet::insert(const string& pushee) {
    if (!exists(pushee)) {
        insertHelper(root_, pushee);  // calls recursive helper function
    }
    ++size_;
}

bool TreeStringSet::exists(const string& test) const {
    return existsHelper(root_, test);  // calls recursive helper function
}

int TreeStringSet::height() const {
    return heightHelper(root_, -1);  // calls recursive helper function
}

double TreeStringSet::averageDepth() const {
    if (size_ == 0) {
        return 0.0;
    } else {
        // calls recursive helper function on non-empty tree
        return sumDepths(root_, -1)/size_;
    }
}

bool TreeStringSet::operator==(const TreeStringSet& rhs) const {
    return std::equal(this->begin(), this->end(), rhs.begin(), rhs.end());
}

bool TreeStringSet::operator!=(const TreeStringSet& rhs) const {
    return !(*this == rhs);
}

ostream& TreeStringSet::printToStream(ostream& outStream) const {
    // call recursive helper function
    return printToStreamHelper(root_, outStream);
}

std::ostream& operator<<(std::ostream& os, const TreeStringSet& tree) {
    tree.printToStream(os);
    return os;
}

ostream& TreeStringSet::showStatistics(ostream& outStream) const {
    outStream << size() << " nodes, height " << height()
    << ", average depth " << averageDepth() << endl;
    return outStream;
}

TreeStringSet::const_iterator TreeStringSet::begin() const {
    const_iterator iter;
    iter.push_to_minimum(root_);  // call recursive helper function
    return iter;
}

TreeStringSet::const_iterator TreeStringSet::end() const {
    const_iterator iter;
    return iter;  // end iterator is default iterator (empty stack)
}

void TreeStringSet::insertHelper(Node*& tree, string value) {
    // if tree not empty, recursively insert into appropriate subtree
    if (tree == nullptr) {
        tree = new Node{value};
    } else if (value < tree->value_) {
        insertHelper(tree->left_, value);
    } else {
        insertHelper(tree->right_, value);
    }
}

bool TreeStringSet::existsHelper(const Node* tree, string test) {
    if (tree == nullptr) {
        return false;  // test not in tree
    } else if (test == tree->value_) {
        return true;  // we found test!
    } else if (test < tree->value_) {
        return existsHelper(tree->left_, test);
    } else {
        return existsHelper(tree->right_, test);
    }
}

ostream& TreeStringSet::printToStreamHelper
(const Node* tree, ostream& outStream) {
    if (tree == nullptr) {
        outStream << "-";  // empty tree representation
    } else {
        // recursive representation of non-empty tree
        outStream << "(";
        printToStreamHelper(tree->left_, outStream);
        outStream << ", ";
        outStream << tree->value_;
        outStream << ", ";
        printToStreamHelper(tree->right_, outStream);
        outStream << ")";
    }
    return outStream;
}

double TreeStringSet::sumDepths(const Node* tree, double currDepth) {
    if (tree == nullptr) {
        return 0.0;
    } else {
        currDepth += 1.0;  // root node exists so add its depth to the sum
        // and recurse to its children
        return currDepth + sumDepths(tree->left_, currDepth)
        + sumDepths(tree->right_, currDepth);
    }
}

int TreeStringSet::heightHelper(Node* tree, int currHeight) {
    if (tree == nullptr) {
        return currHeight;  // reached a leaf
    } else {
        // not a leaf, pick the max height from either of node's children
        currHeight += 1;
        int heightLeft = heightHelper(tree->left_, currHeight);
        int heightRight = heightHelper(tree->right_, currHeight);
        if (heightLeft > heightRight) {
            return heightLeft;
        } else {
            return heightRight;
        }
    }
}

//////////////////////////
// Node functions
//////////////////////////

TreeStringSet::Node::~Node() {
    if (left_ != nullptr) {
        delete left_;
    }
    if (right_ != nullptr) {
        delete right_;
    }
}

TreeStringSet::Node::Node(string value)
                    : value_{value},
                      left_{nullptr},
                      right_{nullptr} {
}

//////////////////////////
// const_iterator functions
//////////////////////////

void TreeStringSet::ConstIterator::push_to_minimum(Node* root) {
    // keep pushing values starting at root until we've reached min elem
    if (root != nullptr) {
        stack_.push(root);
        push_to_minimum(root->left_);
    }
}

TreeStringSet::ConstIterator::reference
TreeStringSet::ConstIterator::operator*() const {
    Node* topNode = stack_.top();  // curr value is elem at top of stack
    return topNode->value_;
}

TreeStringSet::ConstIterator&
TreeStringSet::ConstIterator::operator++() {
    Node* oldTop = stack_.top();
    stack_.pop();  // remove top element
    // push all elems smaller than new top of stack onto stack
    push_to_minimum(oldTop->right_);
    return *this;
}

bool TreeStringSet::ConstIterator::operator==(const ConstIterator& rhs) const {
    return stack_ == rhs.stack_;
}

bool TreeStringSet::ConstIterator::operator!=(const ConstIterator& rhs) const {
    return !(*this == rhs);
}

TreeStringSet::ConstIterator::pointer
TreeStringSet::ConstIterator::operator->() const {
    return &(**this);
}
