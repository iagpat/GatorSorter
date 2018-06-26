//Simple Singly-Linked List (SSLL)
// - A basic implementation: whenever an item is added to the list, a new node is allocated to hold it; whenever an item is removed, the node that held it is deallocated.
//
// by Iago Patiño López
// with content from https://www.cise.ufl.edu/~dts/ as well as "Algorithms in C++ by Robert Segewick"

#ifndef SSLL_H
#define SSLL_H

#include <stdexcept>
#include <iostream>
#include <iterator>
#include "List.h"

namespace cop3530 {

    template <typename E>
    class SSLL : public List<E> { //We need to create the list class
    public:

        template <typename T>
        class SSLL_Iter {
        public:
            // type aliases required for C++ iterator compatibility
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            // type aliases for prettier code
            using self_type = SSLL_Iter;
            using self_reference = SSLL_Iter&;

        private:
            node<T>* here; //This is the pointer the the list member the iterator is pointing at

        public:

            explicit SSLL_Iter(node<T>* start = nullptr) : here(start) { //This is the explicit constructor for the iterator class. It does not allow implicit conversions or copy-initialization.
            }

            SSLL_Iter(const SSLL_Iter& src) : here(src.here) { //This is the regular constructor for the iterator class
            }

            reference operator*() const {
                return here->datum; //temporary line
            }

            pointer operator->() const {
                return &(here->datum);
            }

            self_reference operator=(SSLL_Iter<T> const& src) {
                here = SSLL_Iter(src).here;
                return *this; //temporary line
            }

            self_reference operator++() { //Returns the modified iterator
                here = here->next;
                return *this;
            } // preincrement

            self_type operator++(int) {
                SSLL_Iter temp(*this);
                here = here->next;
                return temp;
            } // postincrement

            bool operator==(SSLL_Iter<T> const& rhs) const {
                if (here == rhs.here)
                    return true;
                else
                    return false;
            }

            bool operator!=(SSLL_Iter<T> const& rhs) const {
                if (here != rhs.here)
                    return true;
                else
                    return false;
            }

        }; // end SSLL_Iter        

        using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = E;
        using iterator = SSLL_Iter<E>; //When we use the word iterator, we mean the iterator class
        using const_iterator = SSLL_Iter<E const>;

        //operations
        SSLL(); //This is the constructor method of the singly linked list
        SSLL(const SSLL& other); //copy constructor
        SSLL(SSLL&& other); //move constructor
        ~SSLL(); //This is the destructor method of the singly linked list

        iterator begin() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return SSLL_Iter<E>(head);
        }

        iterator end() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return SSLL_Iter<E>(tail->next);
        }

        const_iterator begin() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return SSLL_Iter<E>(head);
        }

        const_iterator end() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return SSLL_Iter<E>(tail->next);
        }
        SSLL & operator=(const SSLL & other);
        SSLL & operator=(SSLL&& other);
        void insert(E element, int); //Adds the specific element to the list at the specified position, shifting the element originally at that and those in subsequent positions one position to the "right"
        void push_back(E element); //Appends the specified element to the list
        void push_front(E element); //Prepends the specified element to the list
        E replace(E element, int); //Replaces the existing element at the specified position with the specified element and returns the original element
        E remove(int); //Removes and returns the element at the specified position, shifting the subsequent elements one position to the "left"
        E pop_back(void); //Removes and returns the element at the list's tail
        E pop_front(void); //Removes and returns the element at the list's head
        E item_at(int); //Returns (without removing from the list) the element at the specified position
        E peek_back(void); //Returns the elements at the list's tail
        E peek_front(void); //Returns the elements at the list's head
        bool is_empty(void); //Returns true IFF the list contains no elements
        bool is_full(void); //There isn't a is_full method because a SSLL cannot be full
        size_t length(void); //Returns the number of elements in the list as a size_t
        void clear(void); //removes all elements from the list
        bool contains(E element, bool (*equals_function)(const E&, const E&)); //returns true IFF at least one of the elements of the list matches the specified element
        void print(std::ostream& o); //If the list is empty, inserts "<empty list>" into the ostream; otherwise, inserts, enclosed in square brackets, the list's elements, separated by commas, in sequential order 

        E * const contents(); //Allocates, initializes, and returns an array containing a copy of the list's elements in sequential order

    private:
        //variables
        node<E> *head;
        node<E> *tail;
    }; //End of SSLL class

    //============================================================================================================================================================
    //========================  Beginning of SSLL methods  ========================//

    //==============================================================================
    // ------- constructor  

    template <typename E>
    SSLL<E>::SSLL() {
        head = nullptr;
        tail = nullptr;
    }

    // ------- copy constructor 

    template <typename E>
    SSLL<E>::SSLL(const SSLL& other) {
        //First copy the head
        head = new node<E>;
        head->datum = other.head->datum;

        //Traversal pointers
        node<E> *new_nodes = head;
        node<E> *old_nodes = other.head;

        //Deep copy
        while (old_nodes->next) { //While we have not finished traversing the "old" chain
            new_nodes->next = new node<E>;
            new_nodes = new_nodes->next;
            old_nodes = old_nodes->next;
            new_nodes->datum = old_nodes->datum;
        }

        //Last, copy the tail
        tail = new_nodes;
        tail->next = nullptr;

    }

    // ------- copy-assignment operator 

    template <typename E>
    SSLL<E> &
    SSLL<E>::operator=(const SSLL & other) {
        //First copy the head
        head = new node<E>;
        head->datum = other.head->datum;

        //Traversal pointers
        node<E> *new_nodes = head;
        node<E> *old_nodes = other.head;

        //Deep copy
        while (old_nodes->next) { //While we have not finished traversing the "old" chain
            new_nodes->next = new node<E>;
            new_nodes = new_nodes->next;
            old_nodes = old_nodes->next;
            new_nodes->datum = old_nodes->datum;
        }

        //Last, copy the tail
        tail = new_nodes;
        tail->next = nullptr;

        return *this;

    }

    // ------  move constructor

    template <typename E>
    SSLL<E>::SSLL(SSLL&& other) {
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }

    // ------- move assignment operator 

    template <typename E>
    SSLL<E> &
    SSLL<E>::operator=(SSLL&& other) {
        if (this != &other) {
            this->clear();
            head = other.head;
            tail = other.tail;
            other.head = nullptr;
            other.tail = nullptr;
        }
        return *this;
    }
    // ------  destructor 

    template <typename E>
    SSLL<E>::~SSLL() {
        clear();
    }

    //==============================================================================
    // operations

    //==============================================================================
    // --------- insert()

    template <typename E>
    void
    SSLL<E>::insert(E element, int position) {
        if (position > length() || position < 0)
            throw std::runtime_error("Sorry but that position is outside the current list boundaries");
        else if (position == 0)
            push_front(element);
        else if (position == length())
            push_back(element);
        else {
            node<E> *pre;
            node<E> *cur = head;
            for (int i = 0; i < position; i++) { //iterate though the list until the right position is found
                pre = cur;
                cur = cur->next;
            }
            node<E> *t = new node<E>; //create node to be inserted
            t->datum = element; //assign the new node's datum
            pre->next = t; //link node position-1 to new node	
            t->next = cur; //link new node to position+1 
        }
    }

    //==============================================================================
    //-------- contents()
    
    template <typename E>
    E * const
    SSLL<E>::contents() {
        size_t const len = length(); //Get the length of the list so that we can now what size array is needed
        E * const contents = new E[len]; //Initialize the array of contents
        node<E> *current = head;
        for (int i = 0; i < len; i++) { //This for loop fills our array with all the datums in order
            contents[i] = current->datum;
            current = current->next;
        }
        return contents;
    }


    //==============================================================================
    // --------- push_back()

    template <typename E>
    void
    SSLL<E>::push_back(E element) {

        node<E> *t = new node<E>; //Create new node to be inserted at the back
        t->datum = element; //Assign datum to new node
        t->next = nullptr; //The new node is the new tail and therefor must point to null

        if (head == nullptr) { //If we have an empty list, the new node will be both the tail and the head

            head = t;
            tail = t;
        } else { //If we don't have an empty list

            tail->next = t; //The previous tail must point to the new tail

            tail = t; //t becomes the new tail
        }
    }

    //==============================================================================
    // --------- push_front()

    template <typename E>
    void
    SSLL<E>::push_front(E element) {
        node<E> *t = new node<E>; //Create new node to be inserted at the front
        t->datum = element; //Assign the right datum to the new node
        t->next = head; //Link the new node to the previous head
        if (is_empty()) tail = t;
        head = t; //Declare the new node as the new head

    }

    //==============================================================================
    // --------- replace() 

    template <typename E>
    E
    SSLL<E>::replace(E element, int position) {
        if (position > length() - 1 || position < 0) throw std::runtime_error("Sorry but that position is outside the current list boundaries");
        node<E> *current = head;
        for (int i = 0; i < position; i++)
            current = current->next;
        E replaced_datum = current->datum;
        current->datum = element;
        return replaced_datum;
    }

    //==============================================================================
    // --------- remove() 

    template <typename E>
    E
    SSLL<E>::remove(int position) {
        if (position > length() - 1 || position < 0) throw std::runtime_error("Sorry but that position is outside the current list boundaries");
        if (position == 0) return pop_front();
        node<E> *previous;
        node<E> *current = head;
        for (int i = 0; i < position; i++) { //Iterate through the list until the position if found
            previous = current;
            current = current->next;
        }
        previous->next = current->next; //Link the node at position-1 to that at position+1
        E deleted_datum = current->datum;
        delete current;
        return deleted_datum;


    }

    //==============================================================================
    // --------- pop_back()

    template <typename E>
    E
    SSLL<E>::pop_back() {
        if (is_empty()) throw std::runtime_error("Sorry, cannot pop an empty list");
        if (head == tail) { //If we have only one element
            E deleted = head->datum;
            delete head;
            head = nullptr;
            tail = nullptr;
            return deleted;
        }
        node<E> *current = head;
        node<E> *previous;
        while (current->next != nullptr) { //Iterate to to the end of the list
            previous = current;
            current = current->next;
        }
        tail = previous; //Turn the node before the old tail into the new tail
        previous->next = nullptr; //Turn the node before the old tail into the new tail
        E deleted_datum = current->datum; //Save the old tail's datum so that it can be returned
        delete current;
        return deleted_datum;
    }

    //==============================================================================
    // --------- pop_front() 

    template <typename E>
    E
    SSLL<E>::pop_front() {
        if (is_empty()) throw std::runtime_error("Sorry, cannot pop an empty list");
        node<E> *t = head;
        head = head->next; //Make the second element the new head
        E deleted_datum = t->datum; //Save the old head's data so that it can be returned
        delete t; //Delete the old head
        return deleted_datum;
    }

    //==============================================================================
    // --------- item_at() 

    template <typename E>
    E
    SSLL<E>::item_at(int position) {
        if (position > length() - 1 || position < 0)
            throw std::runtime_error("Sorry but that position is outside the current list boundaries");
        node<E> *current = head;
        for (int i = 0; i < position; i++) //Iterate though the list until we reach the desired position
            current = current->next;
        return current->datum; //Return the datum at that position    
    }

    //==============================================================================
    // --------- peek_back()

    template <typename E>
    E
    SSLL<E>::peek_back() {
        if (length() < 1) throw std::runtime_error("Sorry, the list is empty");
        return tail->datum; //Return the tail's datum
    }

    //==============================================================================
    // --------- peek_front() 

    template <typename E>
    E
    SSLL<E>::peek_front() {
        if (length() < 1) throw std::runtime_error("Sorry, the list is empty");
        return head->datum; //Return the head's datum
    }

    //==============================================================================
    // --------- is_empty() 

    template <typename E>
    bool
    SSLL<E>::is_empty() {
        if (head == nullptr) return true; //If we don't have a head we don't have anything in the list   
        return false;
    }

    //==============================================================================
    // --------- is_full()

    template <typename E>
    bool
    SSLL<E>::is_full(void) {
        return false; //This list can have an infinite amount of nodes and therefore it always returns false 
    }

    //==============================================================================
    // --------- length()

    template <typename E>
    size_t
    SSLL<E>::length() {
        node<E> *current = head;
        size_t count = 0;
        if (head == nullptr) return count; //If the list is empty the count is zero
        while (current->next != nullptr) { //If the list is not empty we will count the nodes
            count++;
            current = current->next;
        }
        return ++count;
    }

    //==============================================================================
    // --------- clear() 

    template <typename E>
    void
    SSLL<E>::clear() {
        if (head == nullptr){
            return;
        }
        node<E> *current = head;
        node<E> *previous;
        while (current->next != nullptr) { //This deletes every element of the list except for the tail
            previous = current;
            current = current->next;
            delete previous;
        }
        delete current; //This deletes the tail
        head = nullptr;
        tail = nullptr;

    }

    //==============================================================================
    // --------- contains() 

    template <typename E>
    bool
    SSLL<E>::contains(E element, bool (*equals_function)(const E&, const E&)) {
        node<E> *current = head;
        while (current != nullptr) {//This checks whether the object we are looking for is anywhere else in the list
            if (equals_function(current->datum, element)) return true;
            current = current->next;
        }
        return false;
    }

    //==============================================================================
    // --------- print() 

    template <typename E>
    void
    SSLL<E>::print(std::ostream& o) {
        if (is_empty()) {
            o << "<empty list>" << std::endl;
            return;
        }
        node<E> *t = head;
        o << "[";
        while (t->next != nullptr) {
            o << t->datum << ",";
            t = t->next;
        }
        o << t->datum << "]";
    }
}
#endif /* SSLL_H */



