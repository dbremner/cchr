#ifndef _HT_CUCKOO_H_
#define _HT_CUCKOO_H_ 1

#include <stdint.h>

#define ht_cuckoo_code(hash_t,key_t,val_t,gethash1,gethash2,eq) \
  typedef struct { \
    int used; \
    key_t key; \
    val_t val; \
  } hash_t ## _entry_t; \
  typedef struct { \
    int size; \
    int used; \
    hash_t ## _entry_t *data; \
  } hash_t;\
  void static inline hash_t ## _init(hash_t *ht) { \
    ht->size=3; \
    ht->used=0; \
    ht->data=malloc(sizeof(hash_t ## _entry_t)*(1<<(ht->size+1))); \
    for (int j=0; j<(1<<(ht->size+1)); j++) { ht->data[j].used=0; } \
  } \
  hash_t ## _entry_t static inline *hash_t ## _find(hash_t *ht, key_t key) { \
    uint32_t h1=gethash1((key)),h2=gethash2((key)); \
    h1 = (h1 >> (32-ht->size)); \
    h2 = (h2 >> (32-ht->size)) | (1 << ht->size); \
    if (eq((key),ht->data[h1].key)) return (&(ht->data[h1])); \
    if (eq((key),ht->data[h2].key)) return (&(ht->data[h2])); \
    return NULL; \
  } \
  int static inline hash_t ## _have(hash_t *ht, key_t key) { \
    return ((hash_t ## _find(ht,key)) != NULL); \
  } \
  val_t static inline *hash_t ## _get(hash_t *ht, key_t key) { \
    hash_t ## _entry_t *r=hash_t ## _find(ht,key); \
    if (r==NULL) return NULL; \
    return (&(r->val)); \
  } \
  void static inline hash_t ## _set(hash_t *ht, key_t key, val_t val) { \
    hash_t ## _entry_t *r=hash_t ## _find(ht,key); \
    if (r) { \
      r->val=val; \
      return; \
    } \
    ht->used++; \
    while (1) { \
      uint32_t h1=gethash1((key)); \
      h1 = (h1 >> (32-ht->size)); \
      key_t key2=(ht->data[h1].key); \
      val_t val2=(ht->data[h1].val); \
      ht->data[h1].key = key; \
      ht->data[h1].val = val; \
      if (!ht->data[h1].used) { \
        ht->data[h1].used=1; \
	return; \
      } \
      uint32_t h2=gethash2((key2)); \
      h2 = (h2 >> (32-ht->size)) | (1 << ht->size); \
      key_t key3=(ht->data[h2].key); \
      val_t val3=(ht->data[h2].val); \
      ht->data[h2].key = key2; \
      ht->data[h2].val = val2; \
      if (!ht->data[h2].used) { \
        ht->data[h2].used=1; \
	return; \
      } \
      key=key3; \
      val=val3; \
    } \
  } \
  void static inline hash_t ## _unset(hash_t *ht, key_t key) { \
    hash_t ## _entry_t *r=hash_t ## _find(ht,key); \
    if (r) { \
      ht->used--; \
      r->used=0; \
    } \
  } \
  void static inline hash_t ## _double(hash_t *ht) { \
    hash_t ## _entry_t *nw=malloc(sizeof(hash_t ## _entry_t)*(4 << (ht->size))); \
    for (int i=0; i<(2 << ht->size); i++) { \
      if (ht->data[i].used) { \
        uint32_t h=(i < (1 << ht->size)) ? gethash1((ht->data[i].key)) : gethash2((ht->data[i].key)); \
        h = (h >> (31-ht->size)) & 1; \
        nw[i<<1 | h]=ht->data[i]; \
        nw[i<<1 | (h^1)].used=0; \
      } else { \
        nw[i<<1].used=0; \
	nw[i<<1 | 1].used=0; \
      } \
    } \
    ht->size++; \
    free(ht->data); \
    ht->data=nw; \
  }

#endif
