
MAKEFILE     = ppcbetarun.make
¥MondoBuild¥ = ¶
       {MAKEFILE} ¶
		:NEWRUN:crun.h ¶
		:C:macro.h ¶
		:C:beta.h ¶
		:C:define.h ¶
		:C:constant.h ¶
		:C:heap.h ¶
		:C:object.h ¶
		:C:function.h ¶
		:C:valhallaComm.h ¶
		:C:valhallaFindComp.h ¶
		:C:valhallaSOCKETS.h
		
Includes     = -i :C:
Sym¥PPC      = -sym full 
ObjDir¥PPC   =

PPCC         = MrC
PPCCOptions  = {Includes} {Sym¥PPC} -w 2 -D MAC 
Pre	         = SCpre -c -D __powerc

Objects¥PPC  = ¶
		{ObjDir¥PPC}:C:data.o ¶
		{ObjDir¥PPC}:C:argument.o ¶
		{ObjDir¥PPC}:C:betaenv.o ¶
		{ObjDir¥PPC}:C:cbfa.o ¶
		{ObjDir¥PPC}:C:dot.o ¶
		{ObjDir¥PPC}:C:exit.o ¶
		{ObjDir¥PPC}:C:group.o ¶
		{ObjDir¥PPC}:C:initialize.o ¶
		{ObjDir¥PPC}:C:outpattern.o ¶
		{ObjDir¥PPC}:C:property.o ¶
		{ObjDir¥PPC}:C:wordsort.o ¶
		{ObjDir¥PPC}:C:valhallaComm.o ¶
		{ObjDir¥PPC}:C:valhallaSOCKETS.o ¶
		{ObjDir¥PPC}:C:valhallaFindComp.o ¶
		{ObjDir¥PPC}:GC:aoa.o ¶
		{ObjDir¥PPC}:GC:aoatoioa.o ¶
		{ObjDir¥PPC}:GC:block.o ¶
		{ObjDir¥PPC}:GC:copyobject.o ¶
		{ObjDir¥PPC}:GC:ioa.o ¶
		{ObjDir¥PPC}:GC:lvra.o ¶
		{ObjDir¥PPC}:GC:misc.o ¶
		{ObjDir¥PPC}:GC:objectsize.o ¶
		{ObjDir¥PPC}:GC:stack.o ¶
		{ObjDir¥PPC}:NEWRUN:AllocateComponent.o ¶
		{ObjDir¥PPC}:NEWRUN:AllocateDopartObject.o ¶
		{ObjDir¥PPC}:NEWRUN:AllocateItem.o ¶
		{ObjDir¥PPC}:NEWRUN:AllocateObjectRep.o ¶
		{ObjDir¥PPC}:NEWRUN:AllocateRefRep.o ¶
		{ObjDir¥PPC}:NEWRUN:AllocateStackObject.o ¶
		{ObjDir¥PPC}:NEWRUN:AllocateValRep.o ¶
		{ObjDir¥PPC}:NEWRUN:Attach.o ¶
		{ObjDir¥PPC}:NEWRUN:CallBack.o ¶
		{ObjDir¥PPC}:NEWRUN:CheckReferenceAssignment.o ¶
		{ObjDir¥PPC}:NEWRUN:CInterface.o ¶
		{ObjDir¥PPC}:NEWRUN:CopyCtext.o ¶
		{ObjDir¥PPC}:NEWRUN:CopyRefRep.o ¶
		{ObjDir¥PPC}:NEWRUN:CopySliceRefRep.o ¶
		{ObjDir¥PPC}:NEWRUN:CopySliceValRep.o ¶
		{ObjDir¥PPC}:NEWRUN:CopyText.o ¶
		{ObjDir¥PPC}:NEWRUN:CopyValRep.o ¶
		{ObjDir¥PPC}:NEWRUN:ExitObjects.o ¶
		{ObjDir¥PPC}:NEWRUN:ExtendRefRep.o ¶
		{ObjDir¥PPC}:NEWRUN:ExtendValRep.o ¶
		{ObjDir¥PPC}:NEWRUN:Main.o ¶
		{ObjDir¥PPC}:NEWRUN:MakeTextObj.o ¶
		{ObjDir¥PPC}:NEWRUN:Misc.o ¶
		{ObjDir¥PPC}:NEWRUN:NewRefRep.o ¶
		{ObjDir¥PPC}:NEWRUN:NewValRep.o ¶
		{ObjDir¥PPC}:NEWRUN:PerformGC.o ¶
		{ObjDir¥PPC}:NEWRUN:Qua.o ¶
		{ObjDir¥PPC}:NEWRUN:Structure.o ¶
		{ObjDir¥PPC}:NEWRUN:Suspend.o


ppcbetarun ÄÄ {¥MondoBuild¥} {Objects¥PPC}
	PPCLink ¶
		-o betarun.o ¶
		{Sym¥PPC} ¶
		{Objects¥PPC} ¶
		-xm library
	duplicate betarun.o betarunv.o

:C:data.o Ä :C:data.gen {¥MondoBuild¥}
	# generating :C:data.h
	catenate :C:export.h :C:data.gen > :C:tmpdata.c
	{Pre} {PPCCOptions} :C:tmpdata.c -o :C:data.h
	delete -y :C:tmpdata.c
	# done
	# generating :C:data.c
	echo '#include <stdio.h>' > :C:data.c
	echo '#include "heap.h"' >> :C:data.c
	echo '#include "define.h"' >> :C:data.c
	echo '#include "macro.h"' >> :C:data.c
	catenate :C:declare.h :C:data.c  :C:data.gen > :C:tmpdata.c
	{Pre} {PPCCOptions} :C:tmpdata.c -o :C:data.c
	delete -y :C:tmpdata.c
	# done
	{PPCC} {PPCCOptions} :C:data.c -o {Targ} 
:C:data.o Ä :C:declare.h 
:C:data.o Ä :C:export.h 

.o Ä .c {¥MondoBuild¥}
	{PPCC} {PPCCOptions} {depdir}{default}.c -o {Targ} 
