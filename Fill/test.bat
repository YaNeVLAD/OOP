set PROGRAM="%~1"
set DATA="test-data"
set COUNT=1

::put tests here

call :test_run

call :test_hint

call :test_success start-only.txt start-only-out.txt
call :test_success empty.txt empty-out.txt
call :test_success one-start.txt one-start-out.txt
call :test_success two-starts.txt two-starts-out.txt
call :test_success two-fill-areas.txt two-fill-areas-out.txt
call :test_success 101-chars-wall.txt 101-chars-wall-out.txt

call :test_wrong_flag
call :test_fail empty.txt some_arg
call :test_fail unexisting-file.txt
call :test_fail invalid-char.txt

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

:test_wrong_flag
%PROGRAM% flag > nul
if NOT ERRORLEVEL 1 goto :err
call :print_passed_message
goto :eof

:test_run
%PROGRAM% > nul
if ERRORLEVEL 1 goto :err
call :print_passed_message
goto :eof

:test_fail input arg
%PROGRAM% "%DATA%\%1" "%TEMP%\%1" %2 > nul
if NOT ERRORLEVEL 1 goto :err
call :print_passed_message
goto :eof

:test_success input output
%PROGRAM% "%DATA%\%1" "%TEMP%\%1" > nul
if ERRORLEVEL 1 goto :err
call :assert_files_equals "%TEMP%\%1" "%DATA%\%2"
call :print_passed_message
goto :eof