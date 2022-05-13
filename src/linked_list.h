#pragma once

#include <glm/vec2.hpp>
#include <type_traits>

template <typename T>
struct Node {
    T data;
    Node * next = nullptr;
    Node * prev = nullptr;

    Node(T data) : data(data) {}

    Node<T>* append(T newdata) {
        Node * node_end = this; // Last node
        while (node_end->next != nullptr)
            node_end = node_end->next;

        Node * node_next = new Node(newdata);
        node_end->next = node_next;
        node_next->prev = node_end;
        return node_end->next;
    }

    void remove(int offset) {
        if (offset >= 0) {
            remove_forward(offset);
            return;
        }
        if (offset < 0) {
            remove_backward(-offset); // Make positive
            return;
        }
    }

    /**
     * Write elements to an array excluding the calling
     * node.
     *
     * @param dest Where to write
     * @returns Bytes written
     */
    int write2array(T* dest) {
        int i = 0;     // Elements passed
        Node<T> *node = this;
        while ( (node = node->next) ) {
            memcpy(dest + i, &(node->data), sizeof(T));
            i++;
        }
        return i * sizeof(T);
    }
private:
    /// Removes the element seeking forward
    /// Assumes that index > 0
    /// @param index Index of a node to delete
    void remove_forward(int offset) {
        Node *node = this;
        for (int i = 0; i < offset; i++)
            node = node->next;

        Node * prev, * next;
        next = node->next;
        prev = node->prev;

        // Rewire the pointer of the previous and next elements
        prev->next = next;
        if (next) next->prev = prev; // If we're removing the last element in a list, `next` will be null

        delete node;
    }
    void remove_backward(int offset) {
        Node *node = this;
        for (int i = 0; i < offset; i++)
            node = node->prev;

        Node * prev, * next;
        next = node->next;
        prev = node->prev;


        // Rewire the pointer of the previous and next elements
        prev->next = next;
        next->prev = prev;

        delete node;
    }
};
