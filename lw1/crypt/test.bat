SET PROGRAM="%~1"
set TESTDIR="%~2"

%PROGRAM%
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed!

rem запуск с указанием некорректного режима должен привести к ненулевому коду возврата
%PROGRAM% someMode in.txt out.txt 10
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed!

rem запуск с указанием некорректных входных файлов должен привести к ненулевому коду возврата
%PROGRAM% crypt unexisting.txt out.txt 12
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed!

rem запуск с указанием некорректного ключа должен привести к ненулевому коду возврата
%PROGRAM% crypt test-data\inputs\input1.txt %TEMP%\output.txt -2
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed!

%PROGRAM% decrypt test-data\inputs\input1.txt %TEMP_FILE_DECRYPT% 512
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed!

%PROGRAM% crypt test-data\inputs\input1.txt %TEMP_FILE_CRYPT% a
if NOT ERRORLEVEL 1 goto err
echo Test 6 passed!

rem запуск программы сначала в режиме шифрования, затем в режиме дешифрования - в результате должен получиться исходный файл
%PROGRAM% crypt %TESTDIR%\input1.txt %TEMPT%\output.txt 12
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt %TEMPT%\output.txt %TEMPT%\output_decript.txt 12
if ERRORLEVEL 1 goto err
fc %TEMPT%\output_decript.txt %TESTDIR%\input1.txt > nul
if ERRORLEVEL 1 goto err
echo Test 7 passed!

rem запуск программы в режиме шифрования и проверка разности исходного файла и выходного
%PROGRAM% crypt %TESTDIR%\input1.txt %TEMPT%\output.txt 12
if ERRORLEVEL 1 goto err
fc %TEMPT%\output.txt %TESTDIR%\input1.txt > nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed!

REM I successfully tested the tests
echo All tests passed successfuly
exit 0

REM We will get here in case of an error
:err
echo Test failed
exit 1