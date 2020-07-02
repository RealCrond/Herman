

rem call "%VS100COMNTOOLS%\vsvars32.bat"
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\VCVARS32.BAT"
rem echo build clean Debug vs2017
rem @devenv SocketClient.vcxproj /ReBuild "Debug" /Out ..\..\..\..\10_common\version\CompileInfo\SocketClient_2017.txt

echo build clean Release vs2017
@devenv SocketClient.vcxproj /ReBuild "Release" /Out ..\..\..\..\10_common\version\CompileInfo\SocketClient_2017.txt