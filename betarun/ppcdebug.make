
MAKEFILE     = ppcdebug.make
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
PPCCOptions  = {Includes} {Sym¥PPC} -D RTDEBUG -w 2 -traceback -D MAC 
Pre	         = SCpre -c -D __powerc

Objects¥PPC  = ¶
		{ObjDir¥PPC}:C:data.debug ¶
		{ObjDir¥PPC}:C:argument.debug ¶
		{ObjDir¥PPC}:C:betaenv.debug ¶
		{ObjDir¥PPC}:C:cbfa.debug ¶
		{ObjDir¥PPC}:C:dot.debug ¶
		{ObjDir¥PPC}:C:exit.debug ¶
		{ObjDir¥PPC}:C:group.debug ¶
		{ObjDir¥PPC}:C:initialize.debug ¶
		{ObjDir¥PPC}:C:outpattern.debug ¶
		{ObjDir¥PPC}:C:property.debug ¶
		{ObjDir¥PPC}:C:sighandler.debug ¶
		{ObjDir¥PPC}:C:wordsort.debug ¶
		{ObjDir¥PPC}:C:valhallaComm.debug ¶
		{ObjDir¥PPC}:C:valhallaSOCKETS.debug ¶
		{ObjDir¥PPC}:C:valhallaFindComp.debug ¶
		{ObjDir¥PPC}:GC:aoa.debug ¶
		{ObjDir¥PPC}:GC:aoatoioa.debug ¶
		{ObjDir¥PPC}:GC:block.debug ¶
		{ObjDir¥PPC}:GC:copyobject.debug ¶
		{ObjDir¥PPC}:GC:ioa.debug ¶
		{ObjDir¥PPC}:GC:lvra.debug ¶
		{ObjDir¥PPC}:GC:misc.debug ¶
		{ObjDir¥PPC}:GC:objectsize.debug ¶
		{ObjDir¥PPC}:GC:stack.debug ¶
		{ObjDir¥PPC}:NEWRUN:AllocateComponent.debug ¶
		{ObjDir¥PPC}:NEWRUN:AllocateDopartObject.debug ¶
		{ObjDir¥PPC}:NEWRUN:AllocateItem.debug ¶
		{ObjDir¥PPC}:NEWRUN:AllocateObjectRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:AllocateRefRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:AllocateStackObject.debug ¶
		{ObjDir¥PPC}:NEWRUN:AllocateValRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:Attach.debug ¶
		{ObjDir¥PPC}:NEWRUN:CallBack.debug ¶
		{ObjDir¥PPC}:NEWRUN:CheckReferenceAssignment.debug ¶
		{ObjDir¥PPC}:NEWRUN:CInterface.debug ¶
		{ObjDir¥PPC}:NEWRUN:CopyCtext.debug ¶
		{ObjDir¥PPC}:NEWRUN:CopyRefRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:CopySliceRefRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:CopySliceValRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:CopyText.debug ¶
		{ObjDir¥PPC}:NEWRUN:CopyValRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:ExitObjects.debug ¶
		{ObjDir¥PPC}:NEWRUN:ExtendRefRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:ExtendValRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:Main.debug ¶
		{ObjDir¥PPC}:NEWRUN:MakeTextObj.debug ¶
		{ObjDir¥PPC}:NEWRUN:Misc.debug ¶
		{ObjDir¥PPC}:NEWRUN:NewRefRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:NewValRep.debug ¶
		{ObjDir¥PPC}:NEWRUN:PerformGC.debug ¶
		{ObjDir¥PPC}:NEWRUN:Qua.debug ¶
		{ObjDir¥PPC}:NEWRUN:Structure.debug ¶
		{ObjDir¥PPC}:NEWRUN:Suspend.debug


ppcdebug ÄÄ {¥MondoBuild¥} {Objects¥PPC}
	PPCLink ¶
		-o betarun.debug ¶
		{Sym¥PPC} ¶
		{Objects¥PPC} ¶
		-xm library

:C:data.debug Ä :C:data.gen {¥MondoBuild¥}
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
:C:data.debug Ä :C:declare.h 
:C:data.debug Ä :C:export.h 

.debug Ä .c {¥MondoBuild¥}
	{PPCC} {PPCCOptions} {depdir}{default}.c -o {Targ} 
