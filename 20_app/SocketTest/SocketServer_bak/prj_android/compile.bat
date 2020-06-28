pushd %~pd0

ndk-build  >  compileinfo.txt 

echo  ppp  >  compileinfo.txt 
popd