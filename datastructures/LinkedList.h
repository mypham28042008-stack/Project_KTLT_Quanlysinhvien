#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <cstddef>
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    // Disable copy constructor and assignment operator to avoid double-free bugs
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void insertAtHead(const T& val) {
        Node<T>* newNode = new Node<T>(val, head);
        head = newNode;
        if (tail == nullptr) {
            tail = head;
        }
        size++;
    }

    void insertAtTail(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    bool remove(const T& val) {
        if (head == nullptr) return false;

        // If the head matches the value
        if (head->data == val) {
            Node<T>* temp = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
            size--;
            return true;
        }

        Node<T>* current = head;
        while (current->next != nullptr) {
            if (current->next->data == val) {
                Node<T>* temp = current->next;
                current->next = temp->next;
                if (temp == tail) {
                    tail = current;
                }
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }

        return false;
    }

    Node<T>* getHead() const {
        return head;
    }

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

#endif // LINKEDLIST_H
