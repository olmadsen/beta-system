
/* MACRO_CopyBlock copy from address src to address dst a block
 * of length = len bytes. (Used to be longs!!)
 */
#define MACRO_CopyBlock( src, dst, len) \
{ unsigned char *XXe=((unsigned char *) dst)+len,*XXs=((unsigned char *) src),*XXd=((unsigned char *) dst);\
  while(XXd < XXe) *XXd++ = *XXs++;\
}

#define MACRO_TraverseObject( obj, reffunc, objfunc )\
{\
}

#define MACRO_TraverseObjectFlat( obj, reffunc, objfunc )\
{\
}

/* MACRO_ScanRepetition traverse the rep, and for each element 
 * code is called, thisCell refers the element in question.
 */
#define MACRO_ScanRepetition( rep, code) \
{ long *thisCell=(long *)&rep->Body[0], *XXe=((long *) rep)->HighBorder;\
  while( thisCell < XXe){  code;  thisCell++; }\
}

/* MACRO_ScanBlock traverse the block, and for each element 
 * code is called, thisCell refers the element in question.
 */
#define MACRO_ScanBlock( block, code) \
{ long *thisCell=(long *)( (long) block + sizeof(struct Block)), *XXe=block->top;\
  while( thisCell < XXe){  code;  thisCell++; }\
}

#define MACRO_DistanceToEnclosing( obj, variable)\
{ struct Object *XXobj=(struct Object *)obj;\
  while(XXobj->GCAttr<0)\
    XXobj=(struct Object *) ((long)XXobj + XXobj->GCAttr*4);\
  variable=(long)obj - (long)XXobj;\
}
