rem
rem Script to automate packing of BETA systems using InstallShield
rem
rem See the Mjolner Internal WWW pages for further information on how
rem to use this script
rem

set packdir=%_cwd%

echo ---------- Making datafiles directory

mkdir datafiles

for %%f in (*.cmd) do (echo ---------- Running %%f ^ call %%f ^ cdd %packdir% ^ echo ---------- Moving %betalib%\%@format[.8,%@NAME[%%f]].z to datafiles\%@format[.8,%@NAME[%%f]].z ^ mv %betalib%\%@format[.8,%@NAME[%%f]].z datafiles\%@format[.8,%@NAME[%%f]].z)

echo ---------- Copying %betalib%\bin\admin\setup.rul.template to %packdir%\setup.rul.template

cp %betalib%\bin\admin\setup.rul.template %packdir%\setup.rul.template

cd datafiles

echo ---------- Running autogenerate *.z

call perl %betalib%\bin\admin\autogenerate-installshield *.z

echo ---------- Making ZIP file beta_%sdk%.zip from disk*

call zip -r beta_%sdk% disk*

cdd %packdir%