echo off
set v_repo_root=..\..
set v_gen_root=.\cmsis_lib
::echo %v_repo_root%
set v_iar2coide=%v_repo_root%\resource\tools\iar2coide\iar2coide.exe
::echo %v_iar2coide%

echo --------------------------------------------
echo %v_gen_root%
%v_iar2coide% -w "%v_gen_root%" -t .\resource\holtek_coide_empty_project -d "..\coide" >>nul
echo completed.
echo --------------------------------------------

pause