set PROGRAM="%~1"
set DATA="test-data"
set COUNT=1

::put tests here

call :test_fail 10 1 42
call :test_fail 37 10 42
call :test_fail 10 10 400000000
call :test_fail 10 2 A
call :test_fail 16 10 !D
call :test_fail 10 10 2147483647
::call :test_success 16-10-FF.txt 16 10 FF

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

:test_fail source destination value 
%PROGRAM% %2 %3 %4 > "%TEMP\%1"
if NOT ERRORLEVEL 1 goto :err
call :print_success_message
goto :eof

:test_success output source destination value
%PROGRAM% %2 %3 %4 > "%TEMP\%1"
if ERRORLEVEL 1 goto :err
call :is_files_equal "%TEMP\%1" "%DATA%\%1"
call :print_success_message
goto :eof