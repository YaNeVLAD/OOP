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

:test_run
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto :err
goto :eof

:test_fail source destination value
%PROGRAM% %1 %2 %3 > nul
if NOT ERRORLEVEL 1 goto :err
call :print_passed_message
goto :eof

:test_success output source destination value
%PROGRAM% %2 %3 %4 > "%TEMP\%1"
if ERRORLEVEL 1 goto :err
call :assert_files_equals "%TEMP\%1" "%DATA%\%1"
call :print_passed_message
goto :eof