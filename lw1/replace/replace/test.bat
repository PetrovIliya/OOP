set PROGRAM="%~1"
set TESTDIR="%~2"
set SEARCH_STRING="testSearch"
set REPLACE_STRING="testReplace"



echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1