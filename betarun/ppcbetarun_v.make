MAKEFILE     = ppcbetarun_v.make
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
PPCCOptions  = {Includes} {Sym¥PPC} -w 2 -D MAC -D RTVALHALLA -shared_lib_export on
Pre	         = SCpre -c -D __powerc

Objects¥PPC  = ¶
		{ObjDir¥PPC}:C:data.v ¶
		{ObjDir¥PPC}:C:argument.v ¶
		{ObjDir¥PPC}:C:betaenv.v ¶
		{ObjDir¥PPC}:C:cbfa.v ¶
		{ObjDir¥PPC}:C:dot.v ¶
		{ObjDir¥PPC}:C:exit.v ¶
		{ObjDir¥PPC}:C:floats.v ¶
		{ObjDir¥PPC}:C:group.v ¶
		{ObjDir¥PPC}:C:initialize.v ¶
		{ObjDir¥PPC}:C:lazyref_gc.v ¶
		{ObjDir¥PPC}:C:outpattern.v ¶
		{ObjDir¥PPC}:C:property.v ¶
		{ObjDir¥PPC}:C:sighandler.v ¶
		{ObjDir¥PPC}:C:scanobjects.v ¶
		{ObjDir¥PPC}:C:wordsort.v ¶
		{ObjDir¥PPC}:C:valhallaComm.v ¶
		{ObjDir¥PPC}:C:valhallaSOCKETS.v ¶
		{ObjDir¥PPC}:C:valhallaFindComp.v ¶
		{ObjDir¥PPC}:C:heapview.v ¶
		{ObjDir¥PPC}:C:macsockets.v ¶
		{ObjDir¥PPC}:GC:aoa.v ¶
		{ObjDir¥PPC}:GC:aoatoioa.v ¶
		{ObjDir¥PPC}:GC:block.v ¶
		{ObjDir¥PPC}:GC:copyobject.v ¶
		{ObjDir¥PPC}:GC:ioa.v ¶
		{ObjDir¥PPC}:GC:lvra.v ¶
		{ObjDir¥PPC}:GC:misc.v ¶
		{ObjDir¥PPC}:GC:objectsize.v ¶
		{ObjDir¥PPC}:GC:stack.v ¶
		{ObjDir¥PPC}:NEWRUN:AllocateComponent.v ¶
		{ObjDir¥PPC}:NEWRUN:AllocateDopartObject.v ¶
		{ObjDir¥PPC}:NEWRUN:AllocateItem.v ¶
		{ObjDir¥PPC}:NEWRUN:AllocateObjectRep.v ¶
		{ObjDir¥PPC}:NEWRUN:AllocateRefRep.v ¶
		{ObjDir¥PPC}:NEWRUN:AllocateStackObject.v ¶
		{ObjDir¥PPC}:NEWRUN:AllocateValRep.v ¶
		{ObjDir¥PPC}:NEWRUN:Attach.v ¶
		{ObjDir¥PPC}:NEWRUN:CallBack.v ¶
		{ObjDir¥PPC}:NEWRUN:CheckReferenceAssignment.v ¶
		{ObjDir¥PPC}:NEWRUN:CInterface.v ¶
		{ObjDir¥PPC}:NEWRUN:CopyCtext.v ¶
		{ObjDir¥PPC}:NEWRUN:CopyRefRep.v ¶
		{ObjDir¥PPC}:NEWRUN:CopySliceRefRep.v ¶
		{ObjDir¥PPC}:NEWRUN:CopySliceValRep.v ¶
		{ObjDir¥PPC}:NEWRUN:CopyText.v ¶
		{ObjDir¥PPC}:NEWRUN:CopyValRep.v ¶
		{ObjDir¥PPC}:NEWRUN:ExitObjects.v ¶
		{ObjDir¥PPC}:NEWRUN:ExtendRefRep.v ¶
		{ObjDir¥PPC}:NEWRUN:ExtendValRep.v ¶
		{ObjDir¥PPC}:NEWRUN:Main.v ¶
		{ObjDir¥PPC}:NEWRUN:MakeTextObj.v ¶
		{ObjDir¥PPC}:NEWRUN:Misc.v ¶
		{ObjDir¥PPC}:NEWRUN:NewRefRep.v ¶
		{ObjDir¥PPC}:NEWRUN:NewValRep.v ¶
		{ObjDir¥PPC}:NEWRUN:PerformGC.v ¶
		{ObjDir¥PPC}:NEWRUN:Qua.v ¶
		{ObjDir¥PPC}:NEWRUN:Structure.v ¶
		{ObjDir¥PPC}:NEWRUN:Suspend.v


ppcbetarun_v ÄÄ {¥MondoBuild¥} {Objects¥PPC}
	PPCLink ¶
		-o betarun_v.obj ¶
		{Sym¥PPC} ¶
		{Objects¥PPC} ¶
		-xm library
	Catenate {ObjDir¥PPC}:Å:Å.x > betarun_v.x

:C:data.v Ä :C:data.gen {¥MondoBuild¥}
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
:C:data.v Ä :C:declare.h 
:C:data.v Ä :C:export.h 

.v Ä .c {¥MondoBuild¥}
	{PPCC} {PPCCOptions} {depdir}{default}.c -o {Targ} 
