SET PROGRAM="%~1"
set TESTDIR="%~2"

REM no parameters
%PROGRAM% && goto err
echo test 1 passed

REM if output not exist, expeting errorlevel != 
%PROGRAM% MissingFile.txt && goto err
echo Test 2 passed

REM det != 0
%PROGRAM% %TESTDIR%\test1.txt > %TEMP%\output.txt || goto err
fc.exe %TEMP%\output.txt %TESTDIR%\test1_right_res.txt > nul || goto err
echo test 3 passed

REM det = 0
%PROGRAM% %TESTDIR%\test2.txt && goto err
echo Test 4 passed

REM empty file
 %PROGRAM% %TESTDIR%\input_empty_file.txt && goto err
 echo test 5 passed

 REM matrix with letters
%PROGRAM% %TESTDIR%\input_matrix_with_letters.txt && goto err
echo test 6 passed

REM I successfully tested the tests
echo All tests passed successfuly
exit 0

REM We will get here in case of an error
:err
echo Test failed
exit 1