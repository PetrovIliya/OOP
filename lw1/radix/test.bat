SET PROGRAM="%~1"
set TESTDIR="%~2"
@echo off

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo test 1 passed

%PROGRAM% 16 10 f

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1