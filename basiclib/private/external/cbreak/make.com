!
!
$so:==write sys$output
$so "Compiling MY_GETCH.C"
$CC MY_GETCH.C
$so "Compiling MY_GETS.C"
$CC MY_GETS.C
$so "Compiling MYSTRINGS.C"
$CC MYSTRINGS.C
$so "Compiling VMS_GETKEY.C"
$CC VMS_GETKEY.C
$so "Compiling TEST.C"
$CC TEST.C
$so "Defining link libraries"
$DEFINE LNK$LIBRARY SYS$LIBRARY:VAXCRTL
$so "Linking the TEST program"
LINK/EXECUT=TEST.EXE  TEST.OBJ,MY_GETCH.OBJ,VMS_GETKEY.OBJ
$!
$so "Creating the library MOC.OLB"
$lib/create [.-]moc.olb
$lib [.-]moc.olb my_getch.obj,my_gets.obj,mystrings.obj,vms_getkey.obj
$so "Done"
!
