set PROGRAM="%~1"
set DATA="test-data"
set COUNT=1

::put tests here

echo ALL PASSED
exit 0

:err
echo TEST %COUNT% FAILED
exit 1

:print_passed_message
echo TEST %COUNT% PASSED
set /a COUNT=COUNT+1
goto :eof

:assert_files_equals value desired_value
fc.exe %1 %2 > nul
if ERRORLEVEL 1 goto :err
goto :eof

:test_hint
%PROGRAM% -h > "%TEMP%\hint.txt"
if ERRORLEVEL 1 goto :err
call :assert_files_equals "%TEMP%\hint.txt" "%DATA%\usage-hint.txt"
call :print_passed_message
goto :eof

:test_run
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto :err
call :print_passed_message
goto :eof

:test_fail input  arg
%PROGRAM% "%DATA%\%1" %2 > nul
if NOT ERRORLEVEL 1 goto :err
call :print_passed_message
goto :eof

:test_success input output
%PROGRAM% "%DATA%\%1" > "%TEMP\%2"
if ERRORLEVEL 1 goto :err
call :assert_files_equals "%TEMP\%2" "%DATA%\%2"
call :print_passed_message
goto :eof