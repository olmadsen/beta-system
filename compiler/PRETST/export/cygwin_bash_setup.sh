# Cygwin bash PRE-BETA setup
# usage: . cygwin_bash_setup.sh
CYG_BETALIB=`pwd`
export BETALIB=`pwd | sed -e 's%/cygdrive/\(.\)/%\1:/%i'`
export PATH=${CYG_BETALIB}/bin:${CYG_JAVAHOME}/bin:${PATH}
cd $BETALIB/examples
echo Working directory now $PWD
echo BETALIB and PATH set. 
echo Now start using pbeta for compilation.
