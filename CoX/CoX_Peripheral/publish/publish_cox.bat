echo off

echo --------------------------------------------
echo Publish CoX_Peripheral
echo --------------------------------------------

::----------------------------------------------
:: Configure the version & MCU platform

:publish_config_mcu
set /p _publish_cox=Please input the MCU platform that to publish(NUC1xx,NUC122,M051,Mini51 Template):

if "%_publish_cox%"=="" goto publish_config_mcu_error
if %_publish_cox%==NUC1xx goto publish_config_version
if %_publish_cox%==NUC122 goto publish_config_version
if %_publish_cox%==M051 goto publish_config_version
if %_publish_cox%==Mini51 goto publish_config_version
if %_publish_cox%==Template goto publish_config_version

:publish_config_mcu_error
echo Error: You select an error mcu platform, Try again.
goto publish_config_mcu

:publish_config_version
set /p _version=Please input the version(such as V2.0.1.0):

if "%_version%"=="" goto publish_config_version_error

goto publish_continue

:publish_config_version_error
echo Version number can not empty. Please try again.
goto publish_config_version

:publish_continue

set v_repo_root=..\..\..
set v_cox_peripheral=%v_repo_root%\CoX\CoX_Peripheral\CoX_Peripheral_%_publish_cox%
set v_publish_root=%v_repo_root%\CoX\CoX_Peripheral\publish
set v_iar2coide=%v_repo_root%\resource\tools\iar2coide\iar2coide.exe
set v_tools_root=%v_repo_root%\resource\tools
if %_publish_cox%==Template (
    set v_cox_peripheral_doc=%v_repo_root%\CoX\CoX_Peripheral\CoX_Peripheral_Manual\doc
    
) else (
    set v_cox_peripheral_doc=%v_cox_peripheral%\doc
)

echo --------------------------------------------
echo copy libcox
set _publish_dir=CoX_%_publish_cox%_%_version%
if exist %v_publish_root%\%_publish_dir% rd /s /q %v_publish_root%\%_publish_dir% >>nul 
md %v_publish_root%\%_publish_dir%\libcox >>nul 
echo %v_cox_peripheral%\libcox
copy %v_cox_peripheral%\libcox %v_publish_root%\%_publish_dir%\libcox >>nul
echo completed
echo copy startup
md %v_publish_root%\%_publish_dir%\startup
if %_publish_cox%==Template (
    copy %v_cox_peripheral%\startup %v_publish_root%\%_publish_dir%\startup >>nul
) else (
    copy %v_cox_peripheral%\startup\src %v_publish_root%\%_publish_dir%\startup >>nul
)
echo completed

echo gen example\project\template\coide
call %v_cox_peripheral%\all\gen_coide.bat

echo copy example\project\template
md %v_publish_root%\%_publish_dir%\example\project >>nul
xcopy /s /e %v_cox_peripheral%\all\project %v_publish_root%\%_publish_dir%\example\project >>nul
echo completed

:: Doxygen need to run in the configure file directory
cd %v_cox_peripheral_doc%\gen
call .\doxygen_doc_gen.bat
cd ..\..\..\publish

echo copy html doxygen generated
md %v_publish_root%\%_publish_dir%\doc >>nul
md %v_publish_root%\%_publish_dir%\doc\html >>nul
xcopy /s /e %v_cox_peripheral_doc%\en\html %v_publish_root%\%_publish_dir%\doc\html >>nul
echo completed

echo del .gitignore
::echo %v_publish_root%\%_publish_dir%
@for /r %v_publish_root%\%_publish_dir% %%a in (.) do (
    @if exist "%%a\.gitignore" del /q "%%a\.gitignore" >>nul
)
@echo completed

echo archive to .zip
%v_tools_root%\7za.exe a %_publish_dir%.zip %v_publish_root%\%_publish_dir% >>nul
echo completed

echo del %_publish_dir%
rd /s /q %v_publish_root%\%_publish_dir%
echo completed
echo --------------------------------------------
pause
