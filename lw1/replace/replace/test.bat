set PROGRAM="%~1"
set TESTDIR="%~2"
set SEARCH_STRING="testSearch"
set REPLACE_STRING="testReplace"

rem ��������� ����������� ������� ����� (�������� ��� �� ��������� ����� �������� ������������)
%PROGRAM% "%TESTDIR%\empty.txt" %TEMP%\empty.txt %SEARCH_STRING% %REPLACE_STRING%
if ERRORLEVEL 1 goto err
echo test 1 passed

fc.exe %TEMP%\empty.txt "%TESTDIR%\empty.txt"
if ERRORLEVEL 1 goto err
echo test 2 passed

rem ��������� ����������� ����� �� ����� ������
%PROGRAM% "%TESTDIR%\oneLine.txt" %TEMP%\oneLine.txt %SEARCH_STRING% %REPLACE_STRING%
if ERRORLEVEL 1 goto err
echo test 3 passed

fc.exe %TEMP%\oneLine.txt "%TESTDIR%\oneLine.txt"
if ERRORLEVEL 1 goto err
echo test 4 passed

rem ��������� ����������� ����� �� ���������� �����
%PROGRAM% "%TESTDIR%\multiline.txt" %TEMP%\multiline.txt %SEARCH_STRING% %REPLACE_STRING%
if ERRORLEVEL 1 goto err
echo test 5 passed

fc.exe %TEMP%\multiline.txt "%TESTDIR%\multiline.txt"
if ERRORLEVEL 1 goto err
echo test 6 passed

rem ������� ��������� ��� ������ ��� ����������� ��������������� �����
%PROGRAM% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
echo test 7 passed

rem fc.exe "%TEMP%\output.txt" expected-output-when-input-file-is-missing.txt
rem if ERRORLEVEL 1 goto err
rem echo test 8 passed

rem ������� ��������� ��� ������ ��� ������������� ������ � �������� ���� (� ����������� ���� ���������)
%PROGRAM% multiline.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
echo test 9 passed

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1