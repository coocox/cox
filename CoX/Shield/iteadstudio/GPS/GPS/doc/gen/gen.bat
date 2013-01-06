
echo off
set v_repo_root=..\..\..\..\..\..\..


echo --------------------------------------------
echo generate doxygen(en\html,en\rtf) 
doxygen .\cox_en.cfg >>nul

copy ..\images\*.png ..\en\html >>nul

copy ..\..\..\..\..\..\CoX_Peripheral\CoX_Peripheral_Manual\doc\images\* ..\en\html >>nul

copy ..\..\..\..\..\..\CoX_Peripheral\CoX_Peripheral_Manual\doc\css\* ..\en\html >>nul

@for /r ..\en\html %%a in (.) do (
    @if exist "%%a\.svn" rd /s /q "%%a\.svn"
)

echo completed.
echo --------------------------------------------

pause





