// Fila dinamica

#ifndef dyn_queue_h
#define dyn_queue_h

#include <iostream>

class Queue {
    struct node {
        element data;
        struct node* next;
    } * front, *rear, *temp;
    typedef struct node node;

public:
    /**
     * Construtor, inicializa a fila nula
     */
    Queue() {
        front = NULL;
        rear = NULL;
    }

    /**
     * Verifica se fila esta vazia, retorna 1 caso estiver
     */
    int is_empty() {
        if (front == NULL) {
            return 1;
        }
        return 0;
    }

    /**
     * Insere no final da fila
     */
    void insert(element x) {
        temp = new node();
        temp->data = x;

        if (front == NULL) {
            front = temp;
            rear = temp;
        } else {
            temp->next = NULL;
            rear->next = temp;
            rear = temp;
        }
    }

    /**
     *  Elimina o elemento da primeira posicao da fila e retorna ele
     */
    element eliminate() {
        temp = front;
        element data = front->data;  // Recebe a info que estarei retirando da fila

        if (front != NULL) {
            front = (front)->next;
            delete temp;
            return data;
        }
    }
};

#endif