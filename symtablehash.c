/*------------------------------------------------------------*/
/* symtablehash.c */
/* Author: Misrach Ewunetie */
/*------------------------------------------------------------*/
#include "symtable.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
/*----------------------------------------------------------*/

/* Return a hash code for pcKey that is between 0 and uBucketCount-1,
        inclusive. */

/* what is the purpose of a hashcode/this part of the code? */
static size_t SymTable_hash(const char *pcKey, size_t uBucketCount) {
        const size_t HASH_MULTIPLIER = 65599;
        size_t u;
        size_t uHash = 0;

        assert(pcKey != NULL);

        for (u = 0; pcKey[u] != '\0'; u++)
        uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];
        
        return uHash % uBucketCount;
}

SymTable_T SymTable_new(void) {
        
}

void SymTable_free(SymTable_T oSymTable) {
    assert(oSymTable != NULL);
}

size_t SymTable_getLength(SymTable_T oSymTable) {
    assert(oSymTable != NULL);
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
    assert(oSymTable != NULL);
    assert(*pcKey != NULL);
    /* check validity of statement */
    assert(pvValue != NULL);
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue) {
    assert(oSymTable != NULL);
    assert(*pcKey != NULL);
    /* check validity of statement */
    assert(pvValue != NULL);
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
    assert(oSymTable != NULL);
    assert(*pcKey != NULL);
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
    assert(oSymTable != NULL);
    assert(*pcKey != NULL);
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
    assert(oSymTable != NULL);
    assert(*pcKey != NULL);
}

void SymTable_map(SymTable_T oSymTable,
void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
const void *pvExtra) {
    assert(oSymTable != NULL);
    /* what's going on here */
    assert(pvValue != NULL);
    assert(pvExtra != NULL);
}