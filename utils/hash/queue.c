#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct node {
    struct node* next;
    void* input;
} queueNode;

typedef struct queue {
    queueNode* front;
    queueNode* back;
} queue_t;

queue_t* qopen(void) {
    queue_t* queuePointer = (queue_t*)malloc(sizeof(queue_t));

    if (!queuePointer) {
        return NULL;
    }
    queuePointer->front = NULL;
    queuePointer->back = NULL;
    return queuePointer;
}

void qclose(queue_t *qp) {
    if (!qp) 
        return;
    queueNode* currentNode;
    while (qp->front) {
        currentNode = qp->front;
        qp->front = qp->front->next;
        free(currentNode);
    }  
    free(qp);
}

int32_t qput(queue_t *qp, void *elementp) {
    if (!qp || !elementp)
        return 1;
    queueNode* addedNode = (queueNode*)malloc(sizeof(queueNode));
    if (!addedNode) {
        return 1;
    }
    addedNode->input = elementp;
    addedNode->next = NULL;

    if (qp->back) {
        qp->back->next = addedNode;
    } else {
        qp->front = addedNode;
    }
    qp->back = addedNode;
    return 0;
}

void* qget(queue_t *qp) {
    if (!qp || !qp->front) 
        return NULL;
    queueNode* currentNode = qp->front;
    void* input = currentNode->input;
    qp->front = qp->front->next;

    if (!qp->front) {
        qp->back = NULL;
    }
    free(currentNode);
    return input;
}

void qapply(queue_t *qp, void (*fn)(void* elementp)) {
    if (!qp || !fn) 
        return;
    queueNode* currentNode = qp->front;
    while (currentNode) {
        fn(currentNode->input);
        currentNode = currentNode->next;
    }
}

void* qsearch(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp) {
    if (!qp || !searchfn) 
        return NULL;

    queueNode* currentNode = qp->front;

    while (currentNode) {
        if (searchfn(currentNode->input, skeyp)) {
            return currentNode->input;
        }
        currentNode = currentNode->next;
    }

    return NULL;
}

void* qremove(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp) {
    if (!qp || !searchfn) 
        return NULL;
    queueNode* currentNode = qp->front;
    queueNode* previousNode = NULL;

    while (currentNode) {
        if (searchfn(currentNode->input, skeyp)) {
            if (previousNode) {
                previousNode->next = currentNode->next;
            } else {
                qp->front = currentNode->next;
            }
            if (currentNode == qp->back) {
                qp->back = previousNode;
            }
            void* input = currentNode->input;
            free(currentNode);
            return input;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    return NULL;
}

void qconcat(queue_t *q1p, queue_t *q2p) {
    if (!q1p || !q2p) 
        return;

    if (!q1p->back) {
        q1p->front = q2p->front;
        q1p->back = q2p->back;
    } else {
        q1p->back->next = q2p->front;
        if (q2p->back) {
            q1p->back = q2p->back;
        }
    }
    q2p->front = NULL;
    q2p->back = NULL;
    free(q2p);
}
