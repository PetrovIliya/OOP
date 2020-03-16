SET PROGRAM="%~1"
set TESTDIR="%~2"

REM det != 0
%PROGRAM% %TESTDIR%\test1.txt > %TEMP%\output.txt || goto err
fc.exe %TEMP%\output.txt %TESTDIR%\test1_right_res.txt > nul || goto err
echo test 1 passed

REM I successfully tested the tests
echo All tests passed successfuly
exit 0

REM We will get here in case of an error
:err
echo Test failed
exit 1