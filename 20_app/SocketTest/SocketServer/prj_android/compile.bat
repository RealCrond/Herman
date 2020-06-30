pushd %~pd0


call :compile_r > compileinfo.txt 2>&1

:compile_r
echo ============clean_temp start===========
call :clean_temp
echo ============clean_temp end=============
echo ============compile start=============
call %ANDROID_NDK_HOME_R16%\ndk-build 
echo ============compile end=============
goto :eof

:clean_temp
 if exist libs (rd /s /q libs)
 if exist obj  (rd /s /q obj)
goto :eof

popd


