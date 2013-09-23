echo off

set v_repo_root_self=..\..\..
if defined v_repo_root set v_repo_root_self=%v_repo_root%

set v_gen_root=%v_repo_root_self%\CoX\CoX_Peripheral\CoX_Peripheral_STM32F1xx
set v_cox_peripheral=%v_repo_root_self%\CoX\CoX_Peripheral\CoX_Peripheral_STM32F1xx
::echo %v_repo_root_self%
set v_iar2coide=%v_repo_root_self%\resource\tools\iar2coide\iar2coide.exe
::echo %v_iar2coide%

echo --------------------------------------------
echo generate coide project in publish\example
echo --------------------------------------------
echo clean project/coide/rvmdk/ewarm
@for /r %v_gen_root% %%a in (.) do (
    @if exist "%%a\coide_gen" rd /s /q "%%a\coide_gen"
    @if exist "%%a\Debug_Flash" rd /s /q "%%a\Debug_Flash"
    @if exist "%%a\Debug_Ram" rd /s /q "%%a\Debug_Ram"
    @if exist "%%a\ewarm\settings" rd /s /q "%%a\ewarm\settings"
    @if exist "%%a\Debug" rd /s /q "%%a\Debug"
    @if exist "%%a\Release" rd /s /q "%%a\Release"
    @if exist "%%a\*.dep" del /q "%%a\*.dep"
    @if exist "%%a\obj" rd /s /q "%%a\obj"
    @if exist "%%a\lst" rd /s /q "%%a\lst"
    @if exist "%%a\*.uvgui.*" del /q "%%a\*.uvgui.*"
    @if exist "%%a\*.uvopt" del /q "%%a\*.uvopt" 
    @if exist "%%a\*.bak" del /q "%%a\*.bak" 
    @if exist "%%a\*.o" del /q "%%a\*.o" 
    @if exist "%%a\*.d" del /q "%%a\*.d"
)
echo completed

echo update \startup\src\startup_coide.c to \resource\cox_coide_test_project
copy %v_cox_peripheral%\startup\src\startup_coide.c %v_cox_peripheral%\resource\cox_coide_test_project >>nul
echo completed

echo gen coide project: CoX\CoX_Peripheral\CoX_Peripheral_STM32F1xx\sysctl\test
%v_iar2coide% -w "%v_gen_root%" -t %v_cox_peripheral%\resource\cox_coide_test_project  >>nul
echo completed

echo --------------------------------------------

if not defined v_repo_root pause
