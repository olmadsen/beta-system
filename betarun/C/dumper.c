/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * dumper.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include <ctype.h>
#include "beta.h"

FILE *output;

/* Display the ItemName of the item */
char *DumpItemName(theItem)
     struct Item *theItem;
{ DescribeObject(theItem); }

static char theString[100];


char *DumpItemFragment( theItem)
     struct Item *theItem;
{ long index;
  char * str;

  index = (long) theItem->Proto->FormOff;
  str = (char *) ((long) theItem->Proto) + index;  

  return  str;
}

char *DumpValContents( theValRep) /* Needs checking ! */
     struct ValRep *theValRep;
{ long pos, i; char c;

  long empty;

  empty = 1;
  for(i= theValRep->LowBorder - 1; i < theValRep->HighBorder;i++)
    if( theValRep->Body[i]  != 0 ) empty = 0;
  if( empty == 1 ) return "<<EMPTY>>";

  if( theValRep->HighBorder - theValRep->LowBorder > 80) return "<<BIG>>";  

  pos = 0;
  for(i= theValRep->LowBorder - 1; i < theValRep->HighBorder;i++){
    c = (char) theValRep->Body[i];
    if( isprint( c ) ) theString[pos++] =  c;
  }
  theString[pos] = 0;
  return theString;
}

static DumpFormat( type, age, size, name, fragment)
     char type;
     long age,size;
     char *name,*fragment;
{
  fprintf( output,"%c\t%d\t%d", type, age, size);
  if( name != 0 ) fprintf( output,"\t%s\t%s\n", name, fragment);
  else fprintf( output,"\n");
}

static DumpObject( theObj)
     struct Object *theObj;
{
  if( theObj == 0 ) fprintf( output,"none");
  else{
    if( !isObject( theObj)){
      fprintf( output,"# object 0x%x is garbage!\n", theObj);
      return 0;
    }
    if( inIOA( theObj)){
      if( isSpecialProtoType( theObj->Proto )){
        switch( (long) theObj->Proto ){
	case (long) ComponentPTValue:
	  DumpFormat('C', theObj->GCAttr, 4*ObjectSize(theObj),
		     DumpItemName( ComponentItem( theObj) ),
		     DumpItemFragment( ComponentItem( theObj) ) );
	  break;
	case (long) StackObjectPTValue:
	  DumpFormat('S', theObj->GCAttr, 4*ObjectSize(theObj), 0, 0);
	  break;
        case (long) ByteRepPTValue:
	  DumpFormat('B', theObj->GCAttr, 4*ObjectSize(theObj), 
		     DumpValContents( theObj), "" );
	  break;
        case (long) WordRepPTValue:
	  DumpFormat('W', theObj->GCAttr, 4*ObjectSize(theObj), 
		     DumpValContents( theObj), "" );
	  break;
        case (long) DoubleRepPTValue:
	  DumpFormat('D', theObj->GCAttr, 4*ObjectSize(theObj), 
		     DumpValContents( theObj), "" );
	  break;
        case (long) ValRepPTValue:
	  DumpFormat('V', theObj->GCAttr, 4*ObjectSize(theObj), 
		     DumpValContents( theObj), "" );
	  break;
#ifdef STATIC_OBJECT_REPETITIONS
	case (long) StatItemRepPTValue:
	case (long) StatCompRepPTValue:
#endif /* STATIC_OBJECT_REPETITIONS */
	case (long) DynItemRepPTValue:
	case (long) DynCompRepPTValue:
	  fprintf(output, "DumpObject: ObjectRep\n"); return;
        case (long) RefRepPTValue:
	  DumpFormat('R', theObj->GCAttr, 4*ObjectSize(theObj), 0, 0);
	  break;
        default:
	  fprintf( output,"U\n");
	  break;
	}
      }else{			/* theObj is an item */
	DumpFormat('I', theObj->GCAttr, 4*ObjectSize(theObj),
		   DumpItemName( theObj ),
		   DumpItemFragment( theObj) );
      }
    }else fprintf( output,"<garbage>");
  }
}

void DumpIOA( fileName)
     char *fileName;
{
  ref(Object) theObj;
  ptr(long)   handled;

  if( (output = fopen(fileName, "w")) == NULL) output = stderr;

  handled = IOA;

  while( handled < IOATop){
    theObj  = (ref(Object)) handled;
    handled = (ptr(long)) (((long) handled) + 4*ObjectSize(theObj));
    DumpObject( theObj);
  }

  fclose(output);
}


#ifdef RTDEBUG

void DescribeObject(theObject)
     struct Object *theObject;
{
  ref(ProtoType) theProto = theObject->Proto;
  if (isSpecialProtoType(theProto)){
    switch ((long) theProto){
    case (long) ComponentPTValue:
      fprintf(output, "Component: ");
      DescribeObject((struct Object *)(cast(Component)theObject)->Body);
      return;
    case (long) StackObjectPTValue:
      fprintf(output, "StackObj");
      return;
    case (long) StructurePTValue:
      fprintf(output, 
	      "Struc: origin: 0x%x, proto: 0x%x", 
	      (int)((cast(Structure)theObject)->iOrigin),
	      (int)((cast(Structure)theObject)->iProto));
      return;
    case (long) DopartObjectPTValue:
      fprintf(output, 
	      "Dopart: origin: 0x%x", 
	      (int)((cast(DopartObject)theObject)->Origin));
      return;
#ifdef STATIC_OBJECT_REPETITIONS
    case (long) StatItemRepPTValue:
    case (long) StatCompRepPTValue:
#endif /* STATIC_OBJECT_REPETITIONS */
    case (long) DynItemRepPTValue:
    case (long) DynCompRepPTValue:
      fprintf(output, "ObjectRep\n"); return;
    case (long) RefRepPTValue:
      fprintf(output, "RefRep"); return;
    case (long) ValRepPTValue:
      fprintf(output, "IntegerRep"); return;
    case (long) ByteRepPTValue:
      fprintf(output, "CharRep: '");
      if ( (((cast(ValRep)theObject)->HighBorder)-((cast(ValRep)theObject)->LowBorder)+1) > 10 ){
	fprintf(output, "%s", (char *)(cast(ValRep)theObject)->Body);
	fprintf(output, "...'");
      } else {
	fprintf(output, "%s", (char *)(cast(ValRep)theObject)->Body);
	fprintf(output, "'");
      }
      return;
    case (long) WordRepPTValue:
      fprintf(output, "ShortRep");
      return;
    case (long) DoubleRepPTValue:
      fprintf(output, "RealRep");
      return;
    default:
      fprintf(output, "Unknown object type!");
      return;
    }
  } else {
    ref(GCEntry) stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
    ptr(short) dyn;
    
    while (*(short *) stat) stat++;	/* Step over static gc entries */ 
    dyn = ((short *) stat) + 1;		/* Step over the zero */
    while (*dyn++);			/* Step over dynamic gc entries */
    
#ifdef sparc
    if (DebugStack){
      extern char *getLabel (long addr);
      fprintf(output, "%s: \"%s\"", getLabel((long)theProto), (char *)dyn);
    } else {
      fprintf(output, "%s", (char *)dyn);
    }
#else
    fprintf(output, "%s", (char *)dyn);
#endif
  }
}

#endif /* RT_DEBUG */
