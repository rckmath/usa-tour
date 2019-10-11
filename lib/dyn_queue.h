// Fila dinamica

#ifndef dyn_queue_h
#define dyn_queue_h

#include <iostream>

class Queue {
    struct node {
        queue_element data;
        struct node *next;
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
     * Insere no final da fila
     */
    void insert(queue_element x) {
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
    queue_element eliminate() {
        temp = new node();
        temp = front;
        queue_element data = front->data;  // Recebe a info que estarei retirando da fila

        if (front != NULL) {
            front = front->next;
            delete temp;  // Limpa na memoria
            return data;
        }
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
};

#endif