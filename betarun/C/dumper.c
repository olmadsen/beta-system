/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-93 Mjolner Informatics Aps.
 * dumper.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include <ctype.h>
#include "beta.h"

FILE *output;

char *DescribeObject(theObject)
  struct Object *theObject;
{
  ref(ProtoType) theProto = theObject->Proto;
  if (isSpecialProtoType(theProto)){
    char buffer[100];
    switch ((long) theProto){
    case (long) ComponentPTValue:
      strcpy(buffer, "Component: ");
      strncat(buffer, DescribeObject((cast(Component)theObject)->Body), 88);
      return buffer;
    case (long) StackObjectPTValue:
      return "StackObj";
    case (long) StructurePTValue:
      sprintf(buffer, 
	     "Struc: origin: 0x%x, proto: 0x%x", 
	     (cast(Structure)theObject)->iOrigin,
	     (cast(Structure)theObject)->iProto);
      return buffer;
    case (long) RefRepPTValue:
      return "RefRep";	
    case (long) ValRepPTValue:
      return "IntegerRep";
    case (long) ByteRepPTValue:
      strcpy(buffer, "CharRep: '");
      if ( (((cast(ValRep)theObject)->HighBorder)-((cast(ValRep)theObject)->LowBorder)+1) > 10 ){
	strncat(buffer, (cast(ValRep)theObject)->Body, 10);
	strcat(buffer, "...'");
      } else {
	strcat(buffer, (cast(ValRep)theObject)->Body);
	strcat(buffer, "'");
      }
      return buffer;
    case (long) WordRepPTValue:
      return "ShortRep";
    case (long) DoubleRepPTValue:
      return "RealRep";
    }
  } else {
    ref(GCEntry) stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
    ptr(short) dyn;
  
    while (*(short *) stat) stat++;	/* Step over static gc entries */ 
    dyn = ((short *) stat) + 1;		/* Step over the zero */
    while (*dyn++);			/* Step over dynamic gc entries */
    
    return (ptr(char)) dyn;
  }
}

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
        case (long) RefRepPTValue:
	    DumpFormat('R', theObj->GCAttr, 4*ObjectSize(theObj), 0, 0);
	    break;
        default:
	  fprintf( output,"U\n");
	  break;
	}
      }else{ /* theObj is an item */
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
