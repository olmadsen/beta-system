# Cygwin bash BETA.Net/BETA.Java setup
# usage: . bash_setup.sh
export JAVAHOME="C:/Program Files/Java"
CYG_JAVAHOME=`echo $JAVAHOME | sed -e 's%^\([a-z]\):%/cygdrive/\1%i'`
export JNIDIR="win32"
export DYNEXTENSION="dll"
echo JAVA specific variables set: JAVAHOME, JNIDIR, DYNEXTENSION. 
echo JAVAHOME=$JAVAHOME assumed - fix script if this is not correct.
CYG_BETALIB=`pwd`
export BETALIB=`pwd | sed -e 's%/cygdrive/\(.\)/%\1:/%i'`
export PATH=${CYG_BETALIB}/bin:${CYG_JAVAHOME}/bin:${PATH}
cd $BETALIB/examples
echo BETALIB and PATH set. 
echo Now start using jbeta/nbeta for compilation.
