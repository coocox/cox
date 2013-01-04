echo off
set v_repo_root_self=..\..\..\..
if defined v_repo_root set v_repo_root_self=%v_repo_root%
set v_gen_root=%v_repo_root_self%\CoX\Driver\Sensor_Matrix
set v_coide_empty_project=%v_repo_root_self%\CoX\resource\cox_coide_empty_project_nuc1xx
set v_cox_peripheral=%v_repo_root_self%\CoX\CoX_Peripheral\CoX_Peripheral_M051
set v_iar2coide=%v_repo_root_self%\resource\tools\iar2coide\iar2coide.exe


echo --------------------------------------------
echo update .\startup\src\startup_coide.c to cox_coide_empty_project
copy %v_cox_peripheral%\startup\src\startup_coide.c %v_coide_empty_project% >>nul
echo gen coide project root dir: %v_gen_root%
%v_iar2coide% -w "%v_gen_root%" -t %v_coide_empty_project%  >>nul
del /s /q %v_coide_empty_project%\startup_coide.c >>nul
echo completed.
echo --------------------------------------------

if not defined v_repo_root pause