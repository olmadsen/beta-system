

IF %1 gt "" goto ok
echo USAGE: testall datasourcename [username] [password]
echo (Supply at least a data source name!)
cancel

:ok
echo testcursor
testcursor %1

echo testpatternparser
testpatternparser

rem echo testpositionedupdate
rem testpositionedupdate

echo testsensitivity %1
testsensitivity %1

echo testsimplestatementset %1
testsimplestatementset %1

echo teststatementset %1
teststatementset %1

echo testtransact %1 %2
testtransact %1 %2


