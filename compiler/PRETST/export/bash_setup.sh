# UNIX bash PRE-BETA setup
# usage: . bash_setup.sh
export BETALIB=`pwd`
export PATH=${BETALIB}/bin:${PATH}
cd $BETALIB/examples
echo Working directory now $PWD
echo BETALIB and PATH set. 
echo Now start using pre-beta for compilation.
