set PROGRAM="%~1"
set DATA="test-data"
set COUNT=1

::put tests here

call :test_run

call :test_hint

call :test_success invertable.txt invertable-out.txt
call :test_success invertable-real.txt invertable-real-out.txt

call :test_fail invalid-NaN.txt
call :test_fail invalid-wrong-cols.txt
call :test_fail invalid-wrong-rows.txt
call :test_fail invalid-non-invertable.txt
call :test_fail invalid-unexisting-file.txt
call :test_fail invertable.txt wrong-arg
call :test_fail invalid-overflow.txt

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