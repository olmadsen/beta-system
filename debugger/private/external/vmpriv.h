
/***
*  Memory protection API for MacOS 8.x
*
*  (c)1998 Emagic Soft- und Hardware GmbH, Markus Fritze
***/

// Warning: this functions needed to get page aligned parameters!
// use Gestalt(gestaltLogicalPageSize) for getting the page size and
// (~gestaltLogicalPageSize-1) as a mask.

#include <ConditionalMacros.h>
#include <Traps.h>


const UniversalProcPtr  MemoryDispatch = (struct RoutineDescriptor *) 0x570;

const ProcInfoType      uppMemoryDispatchProcInfo = kRegisterBased 
                              | RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
                              | REGISTER_ROUTINE_PARAMETER(1,
kRegisterD0, SIZE_CODE(sizeof(long)))
                              | REGISTER_ROUTINE_PARAMETER(2,
kRegisterD1, SIZE_CODE(sizeof(long)))
                              | REGISTER_ROUTINE_PARAMETER(3,
kRegisterA0, SIZE_CODE(sizeof(void*)))
                              | REGISTER_ROUTINE_PARAMETER(4,
kRegisterA1, SIZE_CODE(sizeof(long)));

pascal OSErr  VMWriteProtectMemory(void *address, unsigned long count) {
return CallOSTrapUniversalProc(MemoryDispatch,
uppMemoryDispatchProcInfo, 6, _MemoryDispatch, address, count);
}

pascal OSErr  VMUnWriteProtectMemory(void *address, unsigned long count) {
return CallOSTrapUniversalProc(MemoryDispatch,
uppMemoryDispatchProcInfo, 7, _MemoryDispatch, address, count);
}

