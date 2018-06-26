//List
// -defines de ADT List
//
// by Iago Patiño López
// with content from https://www.cise.ufl.edu/~dts/ as well as "Algorithms in C++ by Robert Segewick"


#ifndef LIST_H
#define LIST_H
namespace cop3530 {
    //==============================================================================
    // node

    template <typename E>
    struct node {
        E datum;
        node* next;
    };

    template <typename E>
    class List {
    public:
        virtual void insert(E element, int) = 0; //Adds the specific element to the list at the specified position, shifting the element originally at that and those in subsequent positions one position to the "right"
        virtual void push_back(E element) = 0; //Appends the specified element to the list
        virtual void push_front(E element) = 0; //Prepends the specified element to the list
        virtual E replace(E element, int) = 0; //Replaces the existing element at the specified position with the specified element and returns the original element
        virtual E remove(int) = 0; //Removes and returns the element at the specified position, shifting the subsequent elements one position to the "left"
        virtual E pop_back(void) = 0; //Removes and returns the element at the list's tail
        virtual E pop_front(void) = 0; //Removes and returns the element at the list's head
        virtual E item_at(int) = 0; //Returns (without removing from the list) the element at the specified position
        virtual E peek_back(void) = 0; //Returns the elements at the list's tail
        virtual E peek_front(void) = 0; //Returns the elements at the list's head
        virtual bool is_empty(void) = 0; //Returns true IFF the list contains no elements
        virtual bool is_full(void) = 0; //Returns true IFF no more elements can be added to the list
        virtual size_t length(void) = 0; //Returns the number of elements in the list as a size_t
        virtual void clear(void) = 0; //removes all elements from the list
        virtual bool contains(E element, bool (*equals_function)(const E&, const E&)) = 0; //returns true IFF at least one of the elements of the list matches the specified element
        virtual void print(std::ostream& o) = 0; //If the list is empty, inserts "<empty list>" into the ostream; otherwise, inserts, enclosed in square brackets, the list's elements, separated by commas, in sequential order
        virtual E * const contents() = 0; //Allocates, initializes, and returns an array containing a copy of the list's elements in sequential order

        virtual ~List() {
        }; //Destructor method
    };
}

#endif /* LIST_H */

