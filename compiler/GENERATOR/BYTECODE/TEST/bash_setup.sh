# Cygwin bash BETA.Net/BETA.Java setup
# usage: . bash_setup.sh
export BETALIB=`pwd`
CYG_BETALIB=`pwd | sed -e 's%^\([a-z]\):%/cygdrive/\1%i'`
export PATH=${CYG_BETALIB}/bin:${PATH}
cd $BETALIB/examples
echo BETALIB and PATH set. 
echo Now issue a 'make clean' and then use jbeta/nbeta for compilation.
