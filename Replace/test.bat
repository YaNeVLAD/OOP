set PROGRAM="%~1"
set DATA="test-data"
set COUNT=1

call :test_run

call :test_replace fox.txt fox-replace-dog-with-cat.txt dog cat

call :test_replace fox.txt fox-replace-bird-with-cat.txt bird cat

call :test_replace mama.txt mama-replace-ma-with-mama.txt ma mama

call :test_replace numbers.txt numbers-replace-1231234-with-rep.txt 1231234 rep

call :test_replace empty-search.txt empty-search-out.txt "" replace

call :test_replace abcdef.txt abcdef-replace-abc-with-empty.txt abc ""

call :test_replace empty.txt empty-out.txt search ""

call :test_replace_fail unexisting_file.txt out.txt ma mama

echo ALL PASSED
exit 0

:err
echo TEST %COUNT% FAILED
exit 1

:print_success_message
echo TEST %COUNT% PASSED
set /a COUNT=COUNT+1
goto :eof

:is_files_equal value desired_value
fc.exe %1 %2 > nul
if ERRORLEVEL 1 goto :err
goto :eof

:test_run
%PROGRAM% > nul
if ERRORLEVEL 1 goto :err
goto :eof

:test_replace_fail value search replace
%PROGRAM% "%DATA%\%1" "%TEMP\%1" %2 %3 > nul
if NOT ERRORLEVEL 1 goto :err
call :print_success_message
goto :eof

:test_replace input output search replace
%PROGRAM% "%DATA%\%1" "%TEMP\%1" %3 %4 > nul
if ERRORLEVEL 1 goto :err
call :is_files_equal "%TEMP\%1" "%DATA%\%2"
call :print_success_message
goto :eof