echo Recompiling all tests...

call beta testcursor.bet

call beta testscrollingcursor.bet

call beta testpatternparser.bet

rem call beta testpositionedupdate.bet

call beta testsensitivity

call beta testsimplestatementset

call beta teststatementset

call beta testtransact

testall.bat %1 %2 %3
