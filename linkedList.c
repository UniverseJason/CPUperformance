#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

/*
    This function will create a new node of the double linked list
@ param:
    int id: the process ID
    int pr: the priority of the process
    int numCPU: the number of CPU burst
    int numIO: the number of IO burst
    int *CPU: the CPU burst list
    int *IO: the IO burst list
*/
PCB_st *newPCBnode(int pid, int pr, int numCPU, int numIO, int *CPU, int *IO)
{
    PCB_st *pcb = (PCB_st*)malloc(sizeof(PCB_st));
    if(!pcb)
    {
        fprintf(stderr,"ERROR: newPCB node cannot allocate memory\n");
        return NULL;
    }

    // save the given data into corresponding fields of PCB
    pcb->ProcId = pid;
    pcb->ProcPR = pr;
    pcb->numCPUBurst = numCPU;
    pcb->numIOBurst = numIO;
    pcb->CPUBurst = CPU;
    pcb->IOBurst = IO;
    pcb->cpuIndex = 0;
    pcb->ioIndex = 0;
    
    pcb->ts_begin.tv_sec = 0;
    pcb->ts_begin.tv_nsec = 0;
    
    pcb->ts_end.tv_sec = 0;
    pcb->ts_end.tv_nsec = 0;

    pcb->next = NULL;
    pcb->prev = NULL;

    return pcb;
}

/*
    this functrion will create a new(empty) double linked list
*/
PCB_list *newPCBlist()
{
    PCB_list *list = (PCB_list*)malloc(sizeof(PCB_list));
    if(!list)
    {
        fprintf(stderr,"ERROR: newPCBlist cannot allocate memory\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

/*
    this function will free the double linked list
*/
void freeList(PCB_list *list)
{
    PCB_st *temp;
    
    while(list->head != NULL)
    {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }

    free(list);
}

/*
    this function will add a new node to the end of the double linked list
*/
void appendList(PCB_list *list, PCB_st *node)
{
    // if this is empty list
    if(list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = NULL;
        list->tail = node;
    }
}
/*
    this function will remove the head node of the double linked list
    and will return it to the caller.
*/
PCB_st *deleteList(PCB_list *list)
{
    PCB_st *temp;

    if(list->head == NULL)
    {
        return NULL;
    }
    else if (list->head == list->tail)
    {
        temp = list->head;
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        temp = list->head;
        list->head = list->head->next;
    }

    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

/*
    this functino will select the node with the highest priority
    or with the minimun CPU burst cycle
*/
PCB_st *deleteNode_SJT_or_PR(PCB_list *list, int algorithm)
{
    PCB_st *temp, *target;
    temp = list->head;
    target = list->head;

    if(list->head == NULL)
    {
        return NULL;
    }
    
    if(list->head == list->tail)
    {
        target = list->head;
        list->head = NULL;
        list->tail = NULL;
        return target;
    }

    // go through the linked list
    if(algorithm == SJF)
    {
        while(temp != NULL)
        {
            if(temp->CPUBurst[temp->cpuIndex] < target->CPUBurst[target->cpuIndex])
            {
                target = temp;
            }
            temp = temp->next;
        }
    }
    else if(algorithm == PR)
    {
        while(temp != NULL)
        {
            if(temp->ProcPR < target->ProcPR)
            {
                target = temp;
            }
            temp = temp->next;
        }
    }

    // if the target is the head
    if(target == list->head)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    // if the target is the tail
    else if(target == list->tail)
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    // if the target is in the middle
    else
    {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    target->next = NULL;
    target->prev = NULL;
    return target;
}

/*
    this function will check if the list is empty
*/
int isEmpty(PCB_list *list)
{
    if(list->head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
    this function will print all the node in the Linked list
*/
void printLL(PCB_list *list)
{
    if(isEmpty(list)) return;
    
    PCB_st *temp = list->head;
    while(temp != NULL)
    {
        printf("ID: %d, PR: %d, cpuidx: %d, IOidx: %d\n", temp->ProcId, temp->ProcPR, temp->cpuIndex, temp->ioIndex);
        temp = temp->next;
    }
    printf("\n");
}

/*
    this function will get elapsed time in ms
*/
double getElapsed(struct timespec begin, struct timespec end)
{
    double elapsed;
    elapsed = end.tv_sec - begin.tv_sec;
    elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    return elapsed * 1000;
}