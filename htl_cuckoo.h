#ifndef _HTL_CUCKOO_H_
#define _HTL_CUCKOO_H_ 1

/* onafgewerkt: cuckoo hashtable met ingebouwde link-list voor iteratie */

#include <stdint.h>

#define htl_cuckoo_code(hash_t,entry_t,gethash1,gethash2,eq,defined,init,unset) \
  typedef struct { \
    entry_t val; \
    int32_t prev,next; \
  } hash_t ## _unit_t; \
  typedef struct { \
    int size; \
    int used; \
    hash_t##_unit_t *data; \
  } hash_t;\
  void static inline hash_t ## _init(hash_t *ht) { \
    ht->size=0; \
    ht->used=0; \
    ht->data=NULL; \
  } \
  int static inline hash_t ## _count(hash_t *ht) { \
    return (ht->used); \
  } \
  entry_t static inline *hash_t ## _find(hash_t *ht, entry_t *entry) { \
    if (ht->size) { \
      uint32_t h1=gethash1((entry)),h2=gethash2((entry)); \
      h1 = (h1 >> (32-ht->size)); \
      h2 = (h2 >> (32-ht->size)) | (1 << ht->size); \
      if (defined(&(ht->data[h1].val)) && eq((entry),&(ht->data[h1].val))) return (&(ht->data[h1].val)); \
      if (defined(&(ht->data[h2].val)) && eq((entry),&(ht->data[h2].val))) return (&(ht->data[h2].val)); \
    } \
    return NULL; \
  } \
  hash_t##_unit_t static inline *hash_t ## _findx(hash_t *ht, entry_t *entry) { \
    return (hash_t##_unit_t*)hash_t##_find(ht,entry); \
  } \
  int static inline hash_t ## _have(hash_t *ht, entry_t *entry) { \
    return ((hash_t ## _find(ht,entry)) != NULL); \
  } \
  int static inline hash_t ## _size(hash_t *ht) { \
    return (ht->size); \
  } \
  int static inline hash_t ## _mem(hash_t *ht) { \
    return (ht->size > 0); \
  } \
  void static inline hash_t ## _double(hash_t *ht) { \
    hash_t##_unit_t *nw=malloc(sizeof(hash_t##_unit_t)*(1+(4 << (ht->size))))+1; \
    for (int i=0; i<(4 << ht->size); i++) { \
      init(&(nw[i].val)); \
    } \
    int32_t i=-1; \
    int32_t pr=-1; \
    if (ht->size) while (ht->data[i].next != -1) { \
      i=ht->data[i].next; \
      uint32_t h=(i < (1 << ht->size)) ? gethash1(&(ht->data[i].val)) : gethash2(&(ht->data[i].val)); \
      h = (h >> (31-ht->size)); \
      nw[h].val=ht->data[i].val; \
      nw[h].prev=pr; \
      nw[pr].next=h; \
      pr=h; \
    } \
    nw[i].next=-1; \
    nw[-1].prev=i; \
    ht->size++; \
    if (ht->data==NULL) { \
      /*fprintf(stderr,"[alloc " #hash_t " hashtable %p]\n",ht);*/ \
    } else { \
      free(ht->data); \
    } \
    ht->data=nw; \
  } \
  void static inline hash_t ## _set(hash_t *ht, entry_t *entry) { \
    hash_t##_unit_t *r=hash_t ## _findx(ht,entry); \
    entry_t bak; \
    if (r) { \
      (r)->val=(*entry); \
      return; \
    } \
    /*fprintf(stderr,"[adding element to %i-element " #hash_t " hash %p (size %i)]\n",ht->used,ht,ht->size);*/ \
    ht->used++; \
    if (ht->used>(5*(1<< (ht->size)))/6) { \
      hash_t ## _double(ht); \
    } \
    int32_t nxt=ht->data[-1].next; \
    int32_t prv=-1; \
    while (1) { \
      int maxiter=(23*ht->size+11)/2; \
      while (maxiter--) { \
        uint32_t h1=gethash1((entry)); \
        h1 = (h1 >> (32-ht->size)); \
	int32_t oprv1=ht->data[h1].prev; \
	int32_t onxt1=ht->data[h1].next; \
	ht->data[h1].next=nxt; \
	ht->data[nxt].prev=h1; \
	ht->data[h1].prev=prv; \
	ht->data[prv].next=h1; \
        if (!(defined(&(ht->data[h1].val)))) { \
	  ht->data[h1].val=(*entry); \
	  return; \
	} else { \
          bak=ht->data[h1].val; \
	  nxt=onxt1; \
	  prv=oprv1; \
	  ht->data[h1].val=(*entry); \
	} \
        uint32_t h2=gethash2(&bak); \
        h2 = (h2 >> (32-ht->size)) | (1 << ht->size); \
	int32_t oprv2=ht->data[h1].prev; \
	int32_t onxt2=ht->data[h1].next; \
	ht->data[h2].next=nxt; \
	ht->data[nxt].prev=h2; \
	ht->data[h2].prev=prv; \
	ht->data[prv].next=h2; \
        if (!(defined(&(ht->data[h2].val)))) { \
	  ht->data[h2].val=bak; \
	  return; \
	} else { \
          (*entry)=ht->data[h2].val; \
	  nxt=onxt1; \
	  prv=oprv2; \
	  ht->data[h2].val=bak; \
	} \
      } \
      int32_t nxth=(nxt==-1) ? -1 : ((nxt < (1 << ht->size)) ? gethash1(&(ht->data[nxt].val)) : gethash2(&(ht->data[nxt].val))); \
      int32_t prvh=(prv==-1) ? -1 : ((prv < (1 << ht->size)) ? gethash1(&(ht->data[prv].val)) : gethash2(&(ht->data[prv].val))); \
      hash_t ## _double(ht); \
      nxt=nxth >> (32-ht->size); \
      prv=prvh >> (32-ht->size); \
    } \
  } \
  void static inline hash_t ## _unset(hash_t *ht, entry_t *entry) { \
    entry_t *r=hash_t ## _find(ht,entry); \
    if (r) { \
      /*fprintf(stderr,"[unsetting element in %i-element " #hash_t " hash %p (size %i)]\n",ht->used,ht,ht->size);*/ \
      ht->used--; \
      unset(r); \
    } else {\
      /*fprintf(stderr,"[not unsetting element in %i-element " #hash_t " hash %p (size %i)]\n",ht->used,ht,ht->size);*/ \
    } \
  } \
  void static inline hash_t ## _free(hash_t *ht) { \
    if (ht->data) { \
      /*fprintf(stderr,"[removing %i-element " #hash_t " hash %p (size %i)]\n",ht->used,ht,ht->size);*/ \
      for (int j=0; j<(2<<ht->size); j++) { \
        if (defined(&(ht->data[j].val))) { \
          unset(&(ht->data[j].val)); \
        } \
      } \
      ht->size=0; \
      ht->used=0; \
      free(ht->data); \
      ht->data=NULL; \
    } \
  } \
  void static inline hash_t ## _freecopy(hash_t *ht) { \
    if (ht->data) { \
      /*fprintf(stderr,"[removing %i-element " #hash_t " hash %p (size %i)]\n",ht->used,ht,ht->size);*/ \
      ht->size=0; \
      ht->used=0; \
      free(ht->data); \
      ht->data=NULL; \
    } \
  } \
  void static inline hash_t ## _copy(hash_t *from, hash_t *to) { \
    to->size=from->size; \
    to->used=from->used; \
    if (from->data) { \
      to->data=malloc(sizeof(entry_t)*(2<<(from->size))); \
      memcpy(to->data,from->data,sizeof(entry_t)*(2<<(from->size))); \
    } else { \
      to->data=NULL; \
    } \
  } \
  entry_t static inline * hash_t ## _first(hash_t *ht) { \
    if (ht->data) { \
      int32_t pos=ht->data[-1].next; \
      if (pos>=0) return &(ht->data[pos].val); \
    } \
    return NULL; \
  } \
  entry_t static inline * hash_t ## _next(hash_t *ht, entry_t *entry) { \
    if (ht->data) { \
      int32_t pos=((hash_t##_unit_t*)entry)->next; \
      if (pos>=0) return &(ht->data[pos].val); \
    } \
    return NULL; \
  } \
  void static hash_t ## _addall(hash_t *to, hash_t *from) { \
    entry_t *ent=hash_t##_first(from); \
    while (ent) { \
      entry_t ent2=(*ent); \
      hash_t##_set(to,(&ent2)); \
      ent=hash_t##_next(from,ent); \
    } \
  } \

#endif
