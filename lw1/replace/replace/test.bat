set PROGRAM="%~1"
set TESTDIR="%~2"
set SEARCH_STRING="testSearch"
set REPLACE_STRING="testReplace"

rem ѕри запуске без параметров ожидаетс€ ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo test 1 passed

rem ѕри запуске с правильными параметрами ожидаетс€ нулевой код возврата
%PROGRAM% "%TESTDIR%\input.txt" "%TEMP%\output.txt" dog cat
if ERRORLEVEL 1 goto err
echo test 2 passed

rem “ак же файл и готовый шаблон результата должны быть одинаковыми
fc.exe "%TEMP%\output.txt" "%TESTDIR%\dogForCatReplaceResult.txt" > nul
if ERRORLEVEL 1 goto err
echo test 3 passed

rem ѕри запуске с пустой строкой в качестве искомой ожидаетс€ нулевой код возврата
%PROGRAM% "%TESTDIR%\input.txt" "%TEMP%\output.txt" "" cat
if ERRORLEVEL 1 goto err
echo test 4 passed

rem “ак же файлы должны быть одинаковыми 
fc.exe "%TEMP%\output.txt" "%TESTDIR%\input.txt" > nul
if ERRORLEVEL 1 goto err
echo test 5 passed

rem ѕри запуске с пустой строкой в качестве замен€емой ожидаетс€ нулевой код возврата
%PROGRAM% "%TESTDIR%\input.txt" "%TEMP%\output.txt" cat ""
if ERRORLEVEL 1 goto err
echo test 6 passed

rem “ак же файл и готовый шаблон результата должны быть одинаковыми
fc.exe "%TEMP%\output.txt" "%TESTDIR%\catToEmptyString.txt" > nul
if ERRORLEVEL 1 goto err
echo test 7 passed

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1