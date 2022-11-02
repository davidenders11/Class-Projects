/**
 * treestringset.hpp
 * A binary search tree of std::string values.
 */

#ifndef TREE_STRING_SET_HPP
#define TREE_STRING_SET_HPP

#include <string>
#include <ostream>
#include <stack>
using namespace std;

/**
 * TreeStringSet
 *
 * A binary search tree of many Node objects which hold \c strings.
 *
 * Class allocates memory dynamically; thus can't use C++'s
 *          defaults for copy constructor, assignment operator and
 *          destructor.
 */

class TreeStringSet {
 private:
     // forward declaration
    class ConstIterator;
 public:
    using const_iterator = ConstIterator;
    /**
      * \brief Construct a default TreeStringSet
    */
    TreeStringSet() = default;

    /**
     * \brief Copy constructing a TreeStringSet disabled
    */
    TreeStringSet(const TreeStringSet& orig) = delete;

    /**
     * \brief Using assigment operator to copy a TreeStringSet
     *        to overwrite an existing TreeStringSet is disabled
    */
    TreeStringSet& operator=(const TreeStringSet& rhs) = delete;

    /**
     * \brief Destruct a TreeStringSet
    */
    ~TreeStringSet();

    /**
     * \brief O(1) function that returns number of values in TreeStringSet
     * \returns size_t number of values in TreeStringSet
    */
    size_t size() const;

    /**
     * \brief O(height) function that inserts a string into the BST
     * \param pushee string to be inserted into the TreeStringSet
    */
    void insert(const string& pushee);

    /**
     * \brief O(height) function that returns whether or not the given
     *        string is already included in the TreeStringSet
     * \param pushee string to look for in the TreeStringSet
     * \returns bool whether or not pushee is already in TreeStringSet
    */
    bool exists(const string& test) const;

    /**
     * \brief O(1) function that returns the height of the TreeStringSet
     * \returns int height of TreeStringSet
    */
    int height() const;

    /**
     * \brief function that returns the average depth of the TreeStringSet
     * \returns double average depth of TreeStringSet
    */
    double averageDepth() const;

    /**
     * \brief O(n) func. specfifies how == operator works for TreeStringSets
     * \param rhs TreeStringSet being compared to this TreeStringSet
     * \returns True if TreeStringSets equivalent, else False
     *          Two trees are equal if they contain the same values,
     *          regardless of tree shape
    */
    bool operator==(const TreeStringSet& rhs) const;

    /**
     * \brief O(n) func. specifies how != operator works for TreeStringSets
     * \param rhs TreeStringSet being compared to this TreeStringSet
     * \returns True if TreeStringSets not equivalent, else False
    */ 
    bool operator!=(const TreeStringSet& rhs) const;

    /**
     * \brief Prints the TreeString to outStream
     * \param outStream An ostream object that allows us to 
     *                  send strings to stream
    */
    ostream& printToStream(ostream& outStream) const;

    /**
     * \brief Prints statistics of the TreeStringSet to outStream
     * \param outStream An ostream object that allows us to 
     *                  send strings to stream
    */
    ostream& showStatistics(ostream& outStream) const;

     /**
     * \brief Creates and returns a const iterator positioned at the 
     *        first (least) node of the tree
     * \returns An iterator positioned at the first item
     */
    const_iterator begin() const;

    /**
     * \brief Creates and returns a const iterator positioned "just past" 
     *        the last (greatest) node of the tree
     * \returns An iterator positioned "just past" the last item
     * \warning The returned iterator can only be used for comparison,
     *          reassignment, or destruction
     */
    const_iterator end() const;

 private:
   /**
     * Node
     *
     * The list is stored as a linked list of Nodes
     *        The class is private so only TreeStringSet knows about it.
     *        A constructor is provided for convenience.
     *
     * The Copy Constructor and Assignment operator are disabled.
     */
    struct Node {
        // Public data members
        string value_;
        Node* left_;
        Node* right_;

        /**
         * \brief Constructs a Node with a particular value and next Node
         * \param value   The value for the new Node
         */
        Node(string value);
        ~Node();
    };

    Node* root_ = nullptr;
    size_t size_ = 0;

    /**
      * \brief Helper function for TreeStringSet insert function
      * \param tree   The root of the tree, a reference to a Node*
      * \param value  The value to be stored in new Node being inserted
      */
    static void insertHelper(Node*& tree, string value);

    /**
      * \brief Helper function for TreeStringSet exists function
      * \param tree   The root of the tree, a const Node*
      * \param test   The value being checked if it is in tree
      * \returns True if test in tree, else False
      */
    static bool existsHelper(const Node* tree, string test);

    /**
      * \brief Helper function for TreeStringSet printToStream function
      * \param tree   The root of the tree, a const Node*
      * \param outStream   The ostream reference to which to print tree
      * \returns Reference to the ostream
      */
    static ostream& printToStreamHelper(const Node* tree, ostream& outStream);

    /**
      * \brief Helper function for TreeStringSet averageDepth() function
      * \param tree   The root of the tree, a Node*
      * \param currDepth  Recursive value keeping track of how deep in tree we are
      * \returns double sum of depth of each node in tree
      */
    static double sumDepths(const Node* tree, double currDepth);

    /**
      * \brief Helper function for TreeStringSet height() function
      * \param tree   The root of the tree, a reference to a Node*
      * \param currHeight  Recursive value keeping track of current height
      * \returns int height of the tree
      */
    static int heightHelper(Node* tree, int currHeight);

    class ConstIterator {
        friend class TreeStringSet;

     public:
        using value_type = std::string;
        using reference = const value_type&;
        using pointer = const value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        /**
         * \brief Constructs an invalid iterator
         * \warning A default-constructed iterator can only be reassigned, or
         * destroyed
         */
        ConstIterator() = default;
        ConstIterator(const ConstIterator& orig) = default;
        ConstIterator& operator=(const ConstIterator& rhs) = default;
        ~ConstIterator() = default;

        /**
         * \brief Returns a reference to the item at the current position
         * \returns A reference to the item at the current position
         * \warning Dereferencing the iterator returned by end has undefined
         * behavior
         */
        reference operator*() const;
        /**
         * \brief Advances the iterator to the next position
         * \returns A reference to the iterator
         * \warning Advancing the iterator returned by end has undefined
         * behavior
         */
        ConstIterator& operator++();
        /**
         * \brief Compares the positions of two iterators
         * \returns True if the two iterators have the same position, false
         * otherwise \warning Comparing iterators from different TreeStringSets has
         * undefined behavior
         */
        bool operator==(const ConstIterator& rhs) const;
        /**
         * \brief Compares the positions of two iterators
         * \returns False if the two iterators have the same position, true
         * otherwise \warning Comparing iterators from different TreeStringSets has
         * undefined behavior
         */
        bool operator!=(const ConstIterator& rhs) const;
        /**
         * \brief Allows use of arrow notation (->)
         * \returns pointer to the string stored in the desired node
         */
        pointer operator->() const;

     private:
        /**
         * \brief Adds nodes along minimum path to the stack
         * \param tree The tree whose nodes should be pushed to the stack
         */
        void push_to_minimum(Node* root);

        std::stack<Node*> stack_;
    };
};

/**
* \brief Defines what the streaming operator does to a TreeStringSet
* \returns A reference to an ostream object
*/
std::ostream& operator<<(std::ostream& os, const TreeStringSet& tree);

#endif
