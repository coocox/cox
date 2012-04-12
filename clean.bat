@echo off

echo -----------------------------------
echo clean project/coide_gen/rvmdk/ewarm
@for /r . %%a in (.) do (
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
    @if exist "%%a\*.bak" del /q "%%a\*.bak" 
    @if exist "%%a\*.o" del /q "%%a\*.o" 
    @if exist "%%a\*.d" del /q "%%a\*.d"
)
@echo completed
echo -----------------------------------


echo -----------------------------------
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_NUC1xx\all\project\template\coide
echo clean %clean_target%(genernate)
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------


echo -----------------------------------
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_NUC122\all\project\template\coide
echo clean %clean_target%(genernate)
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------

echo -----------------------------------
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_M051\all\project\template\coide
echo clean %clean_target%(genernate)
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------

echo -----------------------------------
echo clean CoX.Peripheral.NUC1xx.doxygen(html/rtf)
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_NUC1xx\doc\gen\doxy.log
if exist %clean_target% del /q %clean_target% >>nul 
set clean_target="CoX\CoX_Peripheral\CoX_Peripheral_NUC1xx\doc\en"
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------

echo -----------------------------------
echo clean CoX.Peripheral.NUC122.doxygen(html/rtf)
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_NUC122\doc\gen\doxy.log
if exist %clean_target% del /q %clean_target% >>nul 
set clean_target="CoX\CoX_Peripheral\CoX_Peripheral_NUC122\doc\en"
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------

echo -----------------------------------
echo clean CoX.Peripheral.M051.doxygen(html/rtf)
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_M051\doc\gen\doxy.log
if exist %clean_target% del /q %clean_target% >>nul 
set clean_target="CoX\CoX_Peripheral\CoX_Peripheral_M051\doc\en"
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------


echo -----------------------------------
echo clean CoX.Peripheral.HT32F125x.doxygen(html/rtf)
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_HT32F125x\doc\gen\doxy.log
if exist %clean_target% del /q %clean_target% >>nul 
set clean_target="CoX\CoX_Peripheral\CoX_Peripheral_HT32F125x\doc\en"
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------
echo -----------------------------------
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_Template\all\project\template\coide
echo clean %clean_target%(genernate)
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------


echo -----------------------------------
echo clean CoX.Peripheral.Manual.doxygen(html/rtf)
set clean_target=CoX\CoX_Peripheral\CoX_Peripheral_Manual\doc\gen\doxy.log
if exist %clean_target% del /q %clean_target% >>nul 
set clean_target="CoX\CoX_Peripheral\CoX_Peripheral_Manual\doc\en"
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------


echo -----------------------------------
echo clean CoX.Peripheral.publish(*.zip)
set clean_target=CoX\CoX_Peripheral\publish\*.zip
if exist %clean_target% del /q %clean_target% >>nul 
echo completed
echo -----------------------------------


echo -----------------------------------
echo clean CoX.Driver.LCD.Character.HD44780.doxygen(html/rtf)
set clean_target=CoX\Driver\LCD_Character\HD44780\Character_LCD_HD44780_Driver\doc\gen\doxy.log
if exist %clean_target% del /q %clean_target% >>nul 
set clean_target="CoX\Driver\LCD_Character\HD44780\Character_LCD_HD44780_Driver\doc\en"
if exist %clean_target% rd /s /q %clean_target% >>nul
echo completed
echo -----------------------------------

pause