
echo off

echo --------------------------------------------
echo clean doxygen(en/html,en/rtf) 
del /q doxy.log >>nul
rd /s /q ..\en
echo completed.
echo --------------------------------------------

pause