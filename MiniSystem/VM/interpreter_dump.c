/*****************************************************
 * qBeta interpreter: files for dumping bytecode image
 *****************************************************/
void dumpStringTable(FILE *trace) {
  int inx, StringsSize,i;
  inx = getStringTableIndex();
  StringsSize = getInt4(inx);
  i = 4;  
  i = inx + 4;
  fprintf(trace,"first; %s  :: ",stringTable + 4);
  for (i=4; i< StringsSize; i++) {
    int ch = descs[inx + i];
    if (ch == 0) { fprintf(trace," ");} else {fprintf(trace,"%c",ch);}
  }
  fprintf(trace,"\n");
};

void dumpLiterals(FILE *trace,ObjDesc desc){
  int start = desc_getInt4(desc,literal_index);
  int end = desc_getInt4(desc,GCinfo_index);
  int i,v;

  fprintf(trace,"Literals: \n");
  /* This function is incomplete
   * The size of a literal (e.g. String) is written before the elements 
   * Of the literal. This is not handled below.
   * In addition, i should increment with 2 in each iteration
   */
  for (i = start; i < end; i++) {
    v = desc_getInt2(desc,start + (i - start) * 2);
    fprintf(trace, "%c %i ",v,v);
  };
  fprintf(trace,"\n");
};

void dumpString(FILE *trace, int inx) { //fprintf(trace,"dumpString %i\n",inx);
  int i,length = stringTable[4 + inx] + stringTable[4 + inx + 1];
  //fprintf(trace," %i:",length);
  for (i=0; i<length; i++) fprintf(trace,"%c",stringTable[4 + inx + 2 + i]);
}

void dumpGCinfo(FILE *trace,ObjDesc desc){
  fprintf(trace,"GCinfo: ");
  int start = desc_getInt4(desc,GCinfo_index);
  int end = desc_getInt4(desc,BC_index);
  int i,v; 
  fprintf(trace,"start:%i end:%i ::",start,end);
  for (i = start; i < end; i = i + 2) {
    v = desc_getInt2(desc,start + (i - start));
    fprintf(trace,"%i ",v);
  }
  fprintf(trace,"\n");
}

void dumpCode(FILE *trace, ObjDesc desc){
  ObjDesc bc;
  int opCode,arg1,arg2,arg3,bcTop,glsc;

  bc = getByteCode(desc);
  bcTop = getBCtop(desc);
  glsc = 0;

  while(glsc < bcTop) {
    if ((glsc + 1) == desc_getInt2(desc,procE_index)) fprintf(trace,"procE:\n");
    if ((glsc + 1) == alloE(desc)) fprintf(trace,"storeArgsE:\n");
    if ((glsc + 1) == desc_getInt2(desc,enterE_index)) fprintf(trace,"allocE:\n");
    if ((glsc + 1) == desc_getInt2(desc,doE_index)) fprintf(trace,"doE:\n");
    if ((glsc + 1) == desc_getInt2(desc,exitE_index))fprintf(trace,"exitE:\n");

    fprintf(trace,"%i:\t",glsc + 1); // we add 1 to show same glsc as in
                                     // the dump from objectImage
    opCode = bc[glsc]; glsc = glsc + 1; 
    switch (opCode)
      {
      case pushthis:
	fprintf(trace,"pushthis ");
	break;
      case pushValId:
	fprintf(trace,"pushValId ");
	break;
      case pushC: 
	arg1 = op1(bc,&glsc);
	fprintf(trace,"pushC %i", arg1);
	break;
      case push:
	fprintf(trace,"push %i",op1(bc,&glsc));
	break;
      case rpush:
	fprintf(trace,"rpush %i",op1(bc,&glsc));
	break;
      case pushg:
	fprintf(trace,"pushg %i",op1(bc,&glsc));
	break;
      case vpushg:
	fprintf(trace,"vpushg %i",op1(bc,&glsc));
	break;
      case vstoreg:
	fprintf(trace,"vstoreg %i",op1(bc,&glsc));
	break; 
      case ovpushg:
	fprintf(trace,"ovpushg %i",op1(bc,&glsc));
	break;
      case ovstoreg:
	fprintf(trace,"ovstoreg %i",op1(bc,&glsc));
	break; 
      case rpushg:
	fprintf(trace,"rpushg %i ", op1(bc,&glsc));
	break;
      case xrpush:
	fprintf(trace,"xrpush %i",op1(bc,&glsc));
	break;
      case xpushg:
	fprintf(trace,"xpushg %i %i",op1(bc,&glsc),op1(bc,&glsc));
	break;
      case xrpushg:
	fprintf(trace,"xrpushg");
	break;
      case vassign:
	arg1 = op1(bc,&glsc);
	arg2 = op1(bc,&glsc);
	arg3 = op1(bc,&glsc);
	fprintf(trace,"vassign %i %i %i",arg1,arg2,arg3);
	break;
      case store:
	fprintf(trace,"store %i",op1(bc,&glsc));
     	break;
      case rstore:
	fprintf(trace,"rstore %i ",op1(bc,&glsc));
	break;
      case storeg:
	fprintf(trace,"storeg %i ",op1(bc,&glsc));
	break;
      case rstoreg:   
	fprintf(trace,"rstoreg %i ",op1(bc,&glsc));
	break; 
      case xstore:
	fprintf(trace,"xstore %i ",op1(bc,&glsc));
	break;
      case xrstore:
	fprintf(trace,"xrstore %i ",op1(bc,&glsc));
	break;
      case xstoreg:
	fprintf(trace,"xstoreg %i %i",op1(bc,&glsc),op1(bc,&glsc));
	break;
      case xrstoreg:
	fprintf(trace,"xrstoreg");
	break;
      case fstoreg:
	fprintf(trace,"fstoreg %i ",op1(bc,&glsc));
	break;
      case pushFloatConst:
	arg1 = op4(bc,&glsc); // should read the flaot const
	arg2 = op4(bc,&glsc);
	
	fprintf(trace,"pushFloatConst %x %x",arg1,arg2);
	break;
	
      case _double:
	fprintf(trace,"double");
	break;
      case rdouble:
	fprintf(trace,"rdouble");
	break;
      case swap:
	fprintf(trace,"swap %i",op1(bc,&glsc));
	break;
      case _rswap:
	fprintf(trace,"rswap %i",op1(bc,&glsc));
	break;
      case rshiftup:
	fprintf(trace,"rshiftup %i",op1(bc,&glsc));
	break;	
      case rshiftdown:
	fprintf(trace,"rshiftdown %i",op1(bc,&glsc));
	break;
      case rtn:
	fprintf(trace,"rtn %c ",op1(bc,&glsc));
	break;
      case mvStack:
	fprintf(trace,"mvStack");
	break;
      case setThisStack:
	fprintf(trace,"setThisStack");
	break;
      case rpopThisObj:
	fprintf(trace,"rpopThisObj");
	break;
      case toSuper:
	fprintf(trace,"toSuper %i",op2(bc,&glsc));
        break;
      case call:
	arg1 = (char) op1(bc,&glsc);
	fprintf(trace,"call %c ",arg1);
	break;
      case susp:
	fprintf(trace,"susp");
	break;
      case alloc:
	arg1 = op2(bc,&glsc);
	arg2 = op1(bc,&glsc);
	fprintf(trace,"alloc %i %i",arg1,arg2);
	break;
      case tstOriginNone:
	fprintf(trace,"tstOriginNone");
	break;
      case fmult:
	fprintf(trace,"fmult");
	break; 
      case fexp:
	fprintf(trace,"fexp");
	break;
      case invoke:
	arg1 = op2(bc,&glsc);
	arg2 = op2(bc,&glsc);
	arg3 = op1(bc,&glsc);
	fprintf(trace,"invoke %i %i %i",arg1,arg2,arg3);
	break;
      case invokeVal:
	arg1 = op2(bc,&glsc);
	arg2 = op2(bc,&glsc);
	arg3 = op1(bc,&glsc);
	fprintf(trace,"invokeVal %i %i %i",arg1,arg2,arg3);
	break;
      case boxedInvokeVal:
	arg1 = op2(bc,&glsc);
	arg2 = op2(bc,&glsc);
	fprintf(trace,"boxedInvokeVal %i %i",arg1,arg2);
	break;
      case mkValueProxy:
	arg1 = op2(bc,&glsc);
	arg2 = op2(bc,&glsc);
	arg3 = op1(bc,&glsc);
	int arg4  = op1(bc,&glsc);
	fprintf(trace,"mkValueProxy %i %i %i %i",arg1,arg2,arg3,arg4);
	break;
      case invokeExternal:
	arg1 = op1(bc,&glsc);
	fprintf(trace,"invokeExternal %i",arg1);
	break;
      case doExit:
	fprintf(trace,"doExit");
	break;
      case rtnExit:
	fprintf(trace,"rtnExit");
	break;
      case prim:
	arg1 = op1(bc,&glsc);
	fprintf(trace,"prim %i ",arg1);
	switch (arg1){
	case 10: // attach 
	  fprintf(trace,"%c",op1(bc,&glsc));
	}
	break;
      case jmp:	
	fprintf(trace,"jmp %i",op2(bc,&glsc));
	break;
      case jmpFalse:
	fprintf(trace,"jmpFalse %i",op2(bc,&glsc));
	break;
      case jmpGT:
	fprintf(trace,"jmpGT %i",op2(bc,&glsc));
	break;
      case pushNone:
	fprintf(trace,"pushNone");
	break;
      case rtnEvent:
	fprintf(trace,"rtnEvent %i ",op1(bc,&glsc));
	break;
      case rtnEventQ:
	fprintf(trace,"rtnEventQ %i ",op1(bc,&glsc));
	break;
      case doEventQ:
	fprintf(trace,"doEventQ ");
	break;
      case saveBETAworld:
	fprintf(trace,"saveBETAworld %i",op2(bc,&glsc));
	break;
      case saveStringOrigin:
	fprintf(trace,"saveStringOrigin ");
	break;
      case doSuper:
	fprintf(trace,"doSuper %i",op2(bc,&glsc));
	break;
      case innerx:
	fprintf(trace,"innerx %i",op1(bc,&glsc));
	break;
      case innerP:
	fprintf(trace,"innerP %i",op1(bc,&glsc));
	break;
      case innera:
	fprintf(trace,"innera %i",op1(bc,&glsc));
	break;
      case rtnInner:
	fprintf(trace,"returnInner");
	break;
      case innerExit:
	fprintf(trace,"innerExit %i",op1(bc,&glsc));
	break;
      case invokev:
	arg1 = op1(bc,&glsc);
	arg2 = op1(bc,&glsc);
	arg3 = op1(bc,&glsc);
	fprintf(trace,"invokev %i %i %i",arg1,arg2,arg3);
	break;
      case sendx: 
	fprintf(trace,"send %i",op1(bc,&glsc)); 
	break;
      case newVrep:
	fprintf(trace,"newVrep");
	break;
      case jmpTrue:
	fprintf(trace,"jmpTrue %i",op2(bc,&glsc));
	break;
      case pushText:
	fprintf(trace,"pushText %i",op1(bc,&glsc));
	break;
      case exeAlloc:
	fprintf(trace,"exeAlloc %i",op2(bc,&glsc));
	break;
      case rtnc:   
	fprintf(trace,"rtnC");
	break;
      case rtnV:
	fprintf(trace,"rtnV");
	break;
      case rpop:
	fprintf(trace,"rpop");
	break;
      case vpop:
	fprintf(trace,"vpop");
	break;
      case eq:
	fprintf(trace,"eq");
	break;
      case lt:
	fprintf(trace,"lt");
	break;
      case le:
	fprintf(trace,"le");
	break;
      case gt:
	fprintf(trace,"gt");
	break;
      case ge:
	fprintf(trace,"ge");
	break;
      case ne:
	fprintf(trace,"ne");
	break;
      case req:
	fprintf(trace,"req");
	break;
      case rne:
	fprintf(trace,"rne");
	break;
      case seq:
	fprintf(trace,"seq");
	break;
      case sne:
	fprintf(trace,"sne");
	break;
      case plus: 
	fprintf(trace,"plus");
	break;
      case minus:
	fprintf(trace,"minus");
	break;
      case orr: 
	fprintf(trace,"orr");
	break;
      case xorr:
	fprintf(trace,"xorr");
	break;
      case nott:
	fprintf(trace,"nott");
	break;
      case mult:
	fprintf(trace,"mult");
	break;
      case rdiv:
	fprintf(trace,"rdiv");
	break;
      case idiv:
	fprintf(trace,"idiv");	
	break;
      case modd:
	fprintf(trace,"modd");
	break;
      case andd:
	fprintf(trace,"andd");
	break;
      case uminus:
	fprintf(trace,"ne");
	break;
      case pushc2:
	fprintf(trace,"pushc2 %i",op2(bc,&glsc));
	break;
      case allocIndexed:
	arg1 = op2(bc,&glsc);
	arg2 = op1(bc,&glsc);
	arg3 = op1(bc,&glsc);
	fprintf(trace,"allocIndexed %i %i %i",arg1,arg2,arg3);
	break;
      case mkStrucRef: 
	fprintf(trace,"mkStrucRef");
	break;
      case mkObjStrucRef: 
	fprintf(trace,"mkObjStrucRef");
	break;
      case mkVirtualStrucRef:
	fprintf(trace,"mkVirtualStrucRef");
	break;
      case _allocFromStrucRefObj:
	fprintf(trace,"allocFromStrucRefObj");
	break;
      case _break:
	fprintf(trace,"break %i %i %i",op1(bc,&glsc),op2(bc,&glsc),op2(bc,&glsc));
	break;
      case stop: 
	fprintf(trace,"stop ");
	break;
      case allocEventQ:
	fprintf(trace,"allocEventQ %i",op1(bc,&glsc));
        break;
      case addOff:
	fprintf(trace,"addOff %i",op2(bc,&glsc));
	break;
      case saveAndSetThis:
	fprintf(trace,"saveAndSetThis");
	break;
      case restoreThis:
	fprintf(trace,"restoreThis");
	break;
      case pushValue:
	fprintf(trace,"pushValue %i %i",op2(bc,&glsc),op1(bc,&glsc));
	break;
      case mkVindexed:
	fprintf(trace,"mkVindexed %i",op2(bc,&glsc));
	break;
      case mkRindexed:
	fprintf(trace,"mkRindexed %i",op2(bc,&glsc));
	break;
      case fpushg:
	fprintf(trace,"fpushg %i",op1(bc,&glsc));
	break;
      default:
	fprintf(trace,"Op: %i ",bc[glsc - 1]);
	break;
      }
    fprintf(trace,"\n");
  };
  fprintf(trace,"\n");
}

void dumpDesc(FILE *trace, int xdescNo) {
  ObjDesc desc;  
  if ((int)(desc = getDesc(xdescNo)) > 0 ) {
    //fprintf(trace,"desc: %i ",desc);
    fprintf(trace,"\nClass ");
    //int i;
    //for (i=0; i <10; i++) fprintf(trace,"%i ",desc[i]);
    //fprintf(trace,"\n");
    //dumpString(getInt2(desc + 0 ));
    //    dumpString(desc[0] * 256 + desc[1]);
    //dumpString(desc_getInt2(desc,0));
    int oS = objSize(desc);
    int iI = isIndexed(desc);
    fprintf(trace,"%s",getString(desc_getInt2(desc,0)));
    fprintf(trace," descInx:%i objSize:%i isIndexed:%i originOff:%i "
	    ,descNo(desc),oS,iI,desc_getInt2(desc,originOff_index));
    fprintf(trace,"isValObj:%i\n",getIsValObj(xdescNo));
    /* the tests for VS and RS are no longer needed since all fields
     * are pæaced in the dynamixe array fields
     */
    if (oS >= 64) {
      fprintf(trace,"\n\n");
      fclose(trace);
      runTimeError("objSize too big");
    }

    dumpLiterals(trace,desc);
    dumpGCinfo(trace,desc);
    dumpCode(trace,desc);
  }
}

void dumpDescriptors(FILE *trace) {
  int descNo,noOfDescs = getInt4(noOfObjDesc_index);
  fprintf(trace,"Descriptors %i \n",noOfDescs);
  for (descNo=1; descNo <= noOfDescs; descNo++) dumpDesc(trace,descNo);
}

void dump_image(FILE * trace) {
  fprintf(trace,"%c%c%c%c%c%c%c%c\n"
	  ,descs[0],descs[1],descs[2],descs[3],descs[4],descs[5],descs[6],descs[7]);
  fprintf(trace,"StringTableIndex: %i\n",getStringTableIndex());
  dumpStringTable(trace);
  dumpDescriptors(trace);
}
