

echo off
set v_repo_root_self=..\..\..\..\..

set v_doxygen_cfg=.\cox_en.cfg

echo --------------------------------------------
echo generate doxygen(en/html,en/rtf) 
doxygen %v_doxygen_cfg% >>nul
copy ..\images\* ..\en\html >>nul
copy ..\..\..\..\..\resource\doxygen\css\* ..\en\html >>nul
echo completed.
echo --------------------------------------------

if not defined v_repo_root pause





