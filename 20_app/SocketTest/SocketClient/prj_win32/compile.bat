

call "%VS140COMNTOOLS%\vsvars32.bat"
rem echo build clean Unicode_Debug vs2010
rem @devenv skyshare.vcxproj /ReBuild "Unicode_Debug" /Out ..\..\..\..\10-common\version\CompileInfo\skyshare_u_d_2010.txt

echo build clean Unicode_Release vs2010
@devenv SocketClient.vcxproj /ReBuild "Unicode_Release" /Out ..\..\..\..\10-common\version\CompileInfo\skyshare_u_r_2010.txt