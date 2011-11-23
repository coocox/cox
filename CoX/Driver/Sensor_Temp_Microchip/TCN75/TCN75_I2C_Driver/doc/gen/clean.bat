
echo off
set v_repo_root=..\..\..\..\..\..
set v_tools_root=%v_repo_root%\resource\makesection\tools

echo --------------------------------------------
echo clean doxygen(en/html,en/rtf) 
%v_tools_root%\rm.exe -f doxy.log >>nul
%v_tools_root%\rm.exe -f -r ../en/html ../en/rtf>>nul
echo completed.
echo --------------------------------------------

pause