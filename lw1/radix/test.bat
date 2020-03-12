SET PROGRAM="%~1"
set TESTDIR="%~2"
@echo off

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo test 1 passed

rem При переводе из 16ой сс в 10ю числа F ожидается результат - 15
%PROGRAM% 16 10 F > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_f.txt" > nul
if ERRORLEVEL 1 goto err
echo test 2 passed

rem При переводе из 10ой сс в 16ю числа 15 ожидается результат - f
%PROGRAM% 10 16 15 > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_10_to_16_15.txt" > nul
if ERRORLEVEL 1 goto err
echo test 3 passed

rem При переводе из 16ой сс в 10ю числа 0 ожидается результат - 0
%PROGRAM% 16 10 0 > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_0.txt" > nul
if ERRORLEVEL 1 goto err
echo test 4 passed

rem При переводе из 16ой сс в 10ю числа -f ожидается результат - -15
%PROGRAM% 16 10 -f > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_-f.txt" > nul
if ERRORLEVEL 1 goto err
echo test 5 passed

rem При переводе из 16ой сс в 10ю числа 7FFFFFFF ожидается результат - 2147483647 (INT_MAX)
%PROGRAM% 16 10 7FFFFFFF > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_7FFFFFFF.txt" > nul
if ERRORLEVEL 1 goto err
echo test 6 passed

rem При переводе из 16ой сс в 10ю числа -80000000 ожидается результат - -2147483648 (INT_MIN)
%PROGRAM% 16 10 -80000000 > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_-80000000.txt" > nul
if ERRORLEVEL 1 goto err
echo test 7 passed

rem При переводе из 16ой сс в 10ю числа 80000000 ожидается ненулевой код возврата (переполнение INT_MAX)
%PROGRAM% 16 10 80000000
if NOT ERRORLEVEL 1 goto err
echo test 8 passed

rem При переводе из 16ой сс в 10ю числа -80000001 ожидается ненулевой код возврата (переполнение значение INT_MIN)
%PROGRAM% 16 10 -80000001
if NOT ERRORLEVEL 1 goto err
echo test 9 passed

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1