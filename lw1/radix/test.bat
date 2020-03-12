SET PROGRAM="%~1"
set TESTDIR="%~2"
@echo off

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo test 1 passed

rem ��� �������� �� 16�� �� � 10� ����� F ��������� ��������� - 15
%PROGRAM% 16 10 F > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_f.txt" > nul
if ERRORLEVEL 1 goto err
echo test 2 passed

rem ��� �������� �� 10�� �� � 16� ����� 15 ��������� ��������� - f
%PROGRAM% 10 16 15 > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_10_to_16_15.txt" > nul
if ERRORLEVEL 1 goto err
echo test 3 passed

rem ��� �������� �� 16�� �� � 10� ����� 0 ��������� ��������� - 0
%PROGRAM% 16 10 0 > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_0.txt" > nul
if ERRORLEVEL 1 goto err
echo test 4 passed

rem ��� �������� �� 16�� �� � 10� ����� -f ��������� ��������� - -15
%PROGRAM% 16 10 -f > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_-f.txt" > nul
if ERRORLEVEL 1 goto err
echo test 5 passed

rem ��� �������� �� 16�� �� � 10� ����� 7FFFFFFF ��������� ��������� - 2147483647 (INT_MAX)
%PROGRAM% 16 10 7FFFFFFF > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_7FFFFFFF.txt" > nul
if ERRORLEVEL 1 goto err
echo test 6 passed

rem ��� �������� �� 16�� �� � 10� ����� -80000000 ��������� ��������� - -2147483648 (INT_MIN)
%PROGRAM% 16 10 -80000000 > "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" "%TESTDIR%\from_16_to_10_-80000000.txt" > nul
if ERRORLEVEL 1 goto err
echo test 7 passed

rem ��� �������� �� 16�� �� � 10� ����� 80000000 ��������� ��������� ��� �������� (������������ INT_MAX)
%PROGRAM% 16 10 80000000
if NOT ERRORLEVEL 1 goto err
echo test 8 passed

rem ��� �������� �� 16�� �� � 10� ����� -80000001 ��������� ��������� ��� �������� (������������ �������� INT_MIN)
%PROGRAM% 16 10 -80000001
if NOT ERRORLEVEL 1 goto err
echo test 9 passed

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1