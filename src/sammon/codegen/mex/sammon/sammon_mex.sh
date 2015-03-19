MATLAB="/enacit1/opt/matlab/R2013a"
Arch=glnxa64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/home/jornod/.matlab/R2013a"
OPTSFILE_NAME="./mexopts.sh"
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for sammon" > sammon_mex.mki
echo "CC=$CC" >> sammon_mex.mki
echo "CFLAGS=$CFLAGS" >> sammon_mex.mki
echo "CLIBS=$CLIBS" >> sammon_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> sammon_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> sammon_mex.mki
echo "CXX=$CXX" >> sammon_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> sammon_mex.mki
echo "CXXLIBS=$CXXLIBS" >> sammon_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> sammon_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> sammon_mex.mki
echo "LD=$LD" >> sammon_mex.mki
echo "LDFLAGS=$LDFLAGS" >> sammon_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> sammon_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> sammon_mex.mki
echo "Arch=$Arch" >> sammon_mex.mki
echo OMPFLAGS= >> sammon_mex.mki
echo OMPLINKFLAGS= >> sammon_mex.mki
echo "EMC_COMPILER=" >> sammon_mex.mki
echo "EMC_CONFIG=optim" >> sammon_mex.mki
"/enacit1/opt/matlab/R2013a/bin/glnxa64/gmake" -B -f sammon_mex.mk
