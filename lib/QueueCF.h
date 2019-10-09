//
//  QueueCF.h
//  Queue
//
//  Created by Angela Engelbrecht on 01/05/19.
//  Copyright © 2019 Angela Engelbrecht. All rights reserved.
//

#ifndef QueueCF_h
#define QueueCF_h

#include  <stdlib.h>

using namespace std;

#define MAXELEMENTS 100

struct Queue{
    int first,last;
    queue_element local[MAXELEMENTS];
};
// Prototipos

void initQueue          (Queue&);
void insert             (Queue& ,queue_element);
int isEmptyQ            (Queue);
queue_element eliminate (Queue&);
queue_element consult   (Queue);



void initQueue (Queue& Q)
{
    Q.first = 0;
    Q.last =-1;
}

int  isEmptyQ (Queue Q)
{
    if(Q.first  > Q.last) return 1;
    else return 0;
}

void insert (Queue& Q, queue_element V)
{
    if( Q.last == MAXELEMENTS ) exit(1);
    Q.last++;
    Q.local[Q.last] = V;
}

queue_element eliminate (Queue& Q)
{
    if( isEmptyQ(Q)) exit(1);
    return (Q.local [Q.first++ ]);
}
queue_element consult (Queue Q)
{
    if( isEmptyQ(Q))  exit(1);
    return (Q.local[Q.first]);
}

int compr(Queue& Q){
    return Q.last-Q.first+1;
}


#endif /* QueueCF_h */
