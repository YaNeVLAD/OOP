set PROGRAM="%~1"
set DATA="test-data"
set COUNT=1

::put tests here

call :test_run

::call :test_run_enctypted_program simple.txt out.txt 128

call :test_success simple.txt out.txt 255
call :test_success empty.txt out.txt 0
call :test_success multi-lines.txt out.txt 128
call :test_success empty-lines.txt out.txt 77

call :test_fail crypt simple.txt out.txt 1000
call :test_fail decrypt simple.txt out.txt -7

call :test_fail crypt simple.txt out.txt 256
call :test_fail decrypt simple.txt out.txt -1

call :test_fail crypt empty.txt out.txt ABOBA

call :test_fail unexisting_mode simple.txt out.txt 1
call :test_fail decrypt unexisting_file.txt out.txt 1

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
call :print_passed_message
goto :eof

:test_fail mod input output key arg
%PROGRAM% %1 "%DATA%\%2" "%TEMP%\%3" %4 %5 > nul
if NOT ERRORLEVEL 1 goto :err
call :print_passed_message
goto :eof

:test_success input output key
%PROGRAM% crypt "%DATA%\%1" "%TEMP%\%2" %3 > nul
if ERRORLEVEL 1 goto :err
%PROGRAM% decrypt "%TEMP%\%2" "%TEMP%\%1" %3 > nul
call :assert_files_equals "%DATA%\%1" "%TEMP%\%1"
call :print_passed_message
goto :eof

:test_run_enctypted_program input output key
%PROGRAM% crypt "%DATA%\crypt.exe" "%TEMP%\encrypted.bin" %3 > nul
if ERRORLEVEL 1 goto :err
%PROGRAM% decrypt "%TEMP%\encrypted.bin" "%TEMP%\crypt2.exe" %3 > nul
if ERRORLEVEL 1 goto :err
"%TEMP%\crypt2.exe" encrypt "%DATA%\%1" "%TEMP%\%2" %3 > nul
if ERRORLEVEL 1 goto :err
"%TEMP%\crypt2.exe" decrypt "%TEMP%\%2" "%TEMP%\%1" %3 > nul
call :assert_files_equals "%DATA%\%1" "%TEMP%\%1"
call :print_passed_message
goto :eof