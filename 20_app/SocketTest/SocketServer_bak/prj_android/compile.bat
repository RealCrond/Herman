pushd %~pd0


call :compile_r > compileinfo.txt 2>&1

:compile_r
echo ============compile start=============
call %ANDROID_NDK_HOME_R16%\ndk-build 
echo ============compile end=============


popd


