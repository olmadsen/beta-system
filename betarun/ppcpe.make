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
Sym¥PPC      = 
ObjDir¥PPC   =

PPCC         = MrC
PPCCOptions  = {Includes} {Sym¥PPC} -w 2 -D MAC -D PE
Pre	         = SCpre -c -D __powerc -D PE

Objects¥PPC  = ¶
		{ObjDir¥PPC}:C:data.pe ¶
		{ObjDir¥PPC}:C:argument.pe ¶
		{ObjDir¥PPC}:C:betaenv.pe ¶
		{ObjDir¥PPC}:C:cbfa.pe ¶
		{ObjDir¥PPC}:C:dot.pe ¶
		{ObjDir¥PPC}:C:exit.pe ¶
		{ObjDir¥PPC}:C:floats.pe ¶
		{ObjDir¥PPC}:C:group.pe ¶
		{ObjDir¥PPC}:C:initialize.pe ¶
		{ObjDir¥PPC}:C:lazyref_gc.pe ¶
		{ObjDir¥PPC}:C:outpattern.pe ¶
		{ObjDir¥PPC}:C:property.pe ¶
		{ObjDir¥PPC}:C:scanobjects.pe ¶
		{ObjDir¥PPC}:C:sighandler.pe ¶
		{ObjDir¥PPC}:C:wordsort.pe ¶
		{ObjDir¥PPC}:C:valhallaComm.pe ¶
		{ObjDir¥PPC}:C:valhallaSOCKETS.pe ¶
		{ObjDir¥PPC}:C:valhallaFindComp.pe ¶
		{ObjDir¥PPC}:GC:aoa.pe ¶
		{ObjDir¥PPC}:GC:aoatoioa.pe ¶
		{ObjDir¥PPC}:GC:block.pe ¶
		{ObjDir¥PPC}:GC:copyobject.pe ¶
		{ObjDir¥PPC}:GC:ioa.pe ¶
		{ObjDir¥PPC}:GC:lvra.pe ¶
		{ObjDir¥PPC}:GC:misc.pe ¶
		{ObjDir¥PPC}:GC:objectsize.pe ¶
		{ObjDir¥PPC}:GC:stack.pe ¶
		{ObjDir¥PPC}:NEWRUN:AllocateComponent.pe ¶
		{ObjDir¥PPC}:NEWRUN:AllocateDopartObject.pe ¶
		{ObjDir¥PPC}:NEWRUN:AllocateItem.pe ¶
		{ObjDir¥PPC}:NEWRUN:AllocateObjectRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:AllocateRefRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:AllocateStackObject.pe ¶
		{ObjDir¥PPC}:NEWRUN:AllocateValRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:Attach.pe ¶
		{ObjDir¥PPC}:NEWRUN:CallBack.pe ¶
		{ObjDir¥PPC}:NEWRUN:CheckReferenceAssignment.pe ¶
		{ObjDir¥PPC}:NEWRUN:CInterface.pe ¶
		{ObjDir¥PPC}:NEWRUN:CopyCtext.pe ¶
		{ObjDir¥PPC}:NEWRUN:CopyRefRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:CopySliceRefRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:CopySliceValRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:CopyText.pe ¶
		{ObjDir¥PPC}:NEWRUN:CopyValRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:ExitObjects.pe ¶
		{ObjDir¥PPC}:NEWRUN:ExtendRefRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:ExtendValRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:Main.pe ¶
		{ObjDir¥PPC}:NEWRUN:MakeTextObj.pe ¶
		{ObjDir¥PPC}:NEWRUN:Misc.pe ¶
		{ObjDir¥PPC}:NEWRUN:NewRefRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:NewValRep.pe ¶
		{ObjDir¥PPC}:NEWRUN:PerformGC.pe ¶
		{ObjDir¥PPC}:NEWRUN:Qua.pe ¶
		{ObjDir¥PPC}:NEWRUN:Structure.pe ¶
		{ObjDir¥PPC}:NEWRUN:Suspend.pe


ppcbetarun ÄÄ {¥MondoBuild¥} {Objects¥PPC}
	PPCLink ¶
		-o betarun.pe ¶
		{Sym¥PPC} ¶
		{Objects¥PPC} ¶
		-xm library

:C:data.pe Ä :C:data.gen {¥MondoBuild¥}
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
:C:data.pe Ä :C:declare.h 
:C:data.pe Ä :C:export.h 

.pe Ä .c {¥MondoBuild¥}
	{PPCC} {PPCCOptions} {depdir}{default}.c -o {Targ} 
