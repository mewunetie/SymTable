/*------------------------------------------------------------*/
/* strp.c */
/* Author: Misrach Ewunetie */
/*------------------------------------------------------------*/
#include "symtable.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
/*----------------------------------------------------------*/

struct SymTableNode
{
   /* The key and value */
   const char *key;
   void *value;


   /* The address of the next StackNode. */
   struct SymTableNode *psNextNode;

   /* do I need a new structs for Key and Value? */
};

struct SymTable
{
    size_t valueCount;
    struct SymTableNode *psFirstNode;
};
   
SymTable_T SymTable_new(void) { 
    SymTable_T oSymTable;

   oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
   if (oSymTable == NULL)
      return NULL;

   oSymTable->psFirstNode = NULL;
   return oSymTable;
}

size_t SymTable_getLength(SymTable_T oSymTable) {
    assert(oSymTable != NULL);
    return oSymTable->valueCount;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) 
{
    struct SymTableNode *psNewNode;
    const char *pvKey;

    assert(oSymTable != NULL);

    /* is this correct? */
    if (SymTable_contains(oSymTable, pvKey))
        return 0;


    pvKey = (const char *)malloc(sizeof(const char));
    strcpy(pvKey, pcKey);
    
    
    psNewNode = (struct SymTableNode*)malloc(sizeof(struct SymTableNode));
    
    if (psNewNode == NULL)
      return 0;
      
    psNewNode->key = pvKey;
    psNewNode->value = pvValue;
    /* insert new node at the beginning of the Linked List */
    psNewNode->psNextNode = oSymTable->psFirstNode;
    oSymTable->psFirstNode = psNewNode;
    oSymTable->valueCount++;

   return 1;
}

/* does this occur through traversing through the entire linkedlist? */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
    return SymTable_get(oSymTable, pcKey) != NULL;
}

static struct SymTableNode *SymTable_findNode(SymTable_T oSymTable, const char *pcKey) {
    struct SymTableNode *psCurrentNode;
    struct SymTableNode *psNextNode;
    
    assert(oSymTable != NULL);
    assert(*pcKey != NULL);
    
    for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
    {
        if (strcmp(psCurrentNode->key, pcKey) == 0) {
            return psCurrentNode;
        }
    }
    
    return NULL;
}

/* be careful of unclear behavior of dereferencing NULL */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
    struct SymTableNode *node;
    node = SymTable_findNode(oSymTable, pcKey);

    if (node == NULL)
        return NULL;

    return node->value;
}

/* get value stored in the binding that contains pcKey, replace it with pvValue, and then return the original value */
void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue) {
    struct SymTableNode *node;
    const void *originalVal;

    node = SymTable_findNode(oSymTable, pcKey);

    if (node != NULL) {
        originalVal = node->value;
        node->value = pvValue;
        return originalVal;
    }

    return NULL;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
    struct SymTableNode *psCurrentNode;
    struct SymTableNode *psPrevioiusNode;
    const void *pvValue;
    
    assert(oSymTable != NULL);
    assert(*pcKey != NULL);

    if (strcmp(oSymTable->psFirstNode->key) == 0) {
        pvValue = oSymTable->psFirstNode->value;
        oSymTable->psFirstNode = oSymTable->psFirstNode->psNextNode;
    }

    for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
    {
        if (strcmp(psCurrentNode->key, pcKey) == 0) {
            psPrevioiusNode->psNextNode = psCurrentNode->psNextNode;
            pvValue = psCurrentNode->value;
            oSymTable->valueCount;
            return pvValue;
        }
        psPrevioiusNode = psCurrentNode;
    }
    
    return NULL;

}


void SymTable_free(SymTable_T oSymTable) {
    struct SymTableNode *psCurrentNode;
    struct SymTableNode *psNextNode;
    
    assert(oSymTable != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psNextNode)
   {
      psNextNode = psCurrentNode->psNextNode;
      free(psCurrentNode);
   }

   free(oSymTable);
}

void SymTable_map(SymTable_T oSymTable,
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
    const void *pvExtra)
{
   struct SymTableNode *psCurrentNode;

   assert(oSymTable != NULL);
   assert(pfApply != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
      (*pfApply)(psCurrentNode->key, psCurrentNode->value, pvExtra);
}
