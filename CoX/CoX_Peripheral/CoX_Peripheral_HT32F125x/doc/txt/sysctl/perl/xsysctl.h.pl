###############################################################################
# xSysCtl_Peripheral_ID
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "--------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "--------------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "SysCtl Peripheral ID", "CoX", "HT32F125x"  ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_PERIPH_GPIOn", "Mandatory", "xSYSCTL_PERIPH_GPIOA" ],
    [ "", "","--------------------------", ],
    [ "", "", "xSYSCTL_PERIPH_GPIOB" ],
    [ "", "","--------------------------", ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_PERIPH_I2Cn", "Non-Mandatory", "xSYSCTL_PERIPH_I2C0" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_PERIPH_SPIn", "Mandatory", "xSYSCTL_PERIPH_SSI0" ],
    [ "", "","--------------------------", ],
    [ "", "", "xSYSCTL_PERIPH_SPI1" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_PERIPH_TIMERn", "Mandatory", "xSYSCTL_PERIPH_TIMER0" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_PERIPH_UARTn", "Mandatory", "xSYSCTL_PERIPH_UART0" ],
    [ "", "","--------------------------", ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_PERIPH_WDOG", "Mandatory", "Y" ],
    [ "--------------------------", "----------------","--------------------------", ],  

);  

# Print to console or file
print "\n#####xSysCtl_Peripheral_ID\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# xSysCtl_Clock_Set_Config
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "--------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "--------------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "SysCtl Clock Set Configs", "CoX", "HT32F125x"  ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_OSC_MAIN", "Mandatory", "Y" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_OSC_INT", "Mandatory", "Y" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_OSC_INTSL", "Non-Mandatory", "Y" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_XTAL_nMHZ", "Non-Mandatory", "xSYSCTL_XTAL_4MHZ" ],
    [ "", "","--------------------------", ],
    [ "", "", "..." ],
    [ "", "", "--------------------------", ],
    [ "", "", "xSYSCTL_XTAL_8MHZ" ],
    [ "", "", "--------------------------", ],
    [ "", "", "..." ],
    [ "", "", "--------------------------", ],
    [ "", "", "xSYSCTL_XTAL_12MHZ" ],
    [ "", "", "--------------------------", ],
    [ "", "", "..." ],
    [ "", "", "--------------------------", ],
    [ "", "", "xSYSCTL_XTAL_16MHZ" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_INT_nMHZ", "Non-Mandatory", "xSYSCTL_INT_8MHZ" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_INTSL_nKHZ/HZ", "Non-Mandatory", "xSYSCTL_INTSL_32KHZ" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_INT_OSC_DIS", "Non-Mandatory", "N" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_MAIN_OSC_DIS", "Non-Mandatory", "N" ],
    [ "--------------------------", "----------------","--------------------------", ],
    [ "xSYSCTL_PLL_PWRDN", "Non-Mandatory", "N" ],
    [ "--------------------------", "----------------","--------------------------", ],

);  

# Print to console or file
print "\n#####xSysCtl_Clock_Set_Config\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xSysCtl_Peripheral_Src_Clk
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "--------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "--------------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "Peripheral Source Clock Set", "CoX", "HT32F125x"  ],
    [ "---------------------------", "----------------","--------------------------", ],
    [ "Those are all Non-Mandatory\n parameter,the Mandatory\n is variable naming\nModuleName+n+SourceClock", "Non-Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "xSYSCTL_WDT0_EXTSL",    "Non-Mandatory", "Y" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "xSYSCTL_WDT_INTSL", "Non-Mandatory", "Y" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "......", "Non-Mandatory", "Y" ],
    [ "--------------------------", "----------------","--------------------------", ],

);  

# Print to console or file
print "\n#####xSysCtl_Peripheral_Src_Clk\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xSysCtl_Peripheral_Short
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "--------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "--------------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "Peripheral Short name", "CoX", "HT32F125x"  ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "UARTn", "Non-Mandatory", "UART0" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "WDTn", "Non-Mandatory", "WDT0" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "TIMERn", "Non-Mandatory", "TIMER0" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "I2Cn", "Non-Mandatory", "N" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "SPIn", "Non-Mandatory", "N" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "RTC", "Non-Mandatory", "N" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "GPIO", "Non-Mandatory", "N" ],
    [ "--------------------------", "----------------","--------------------------", ],
	[ "", "","", ],
	[ "Peripheral Clock source", "CoX", "HT32F125x"  ],
	[ "---------------------------", "----------------","--------------------------", ],
    [ "INT", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "HCLK", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "HCLK_n", "Non-Mandatory", "HCLK_2" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "EXTSL", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "INTSL", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "MAIN", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "PLL", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "PLL_n", "Non-Mandatory", "PLL_2" ],
    [ "---------------------------", "----------------","--------------------------", ],
	[ "EXTTRG", "Non-Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------------", ],

);  

# Print to console or file
print "\n#####xSysCtl_Peripheral_Short\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xSysCtl_Exported_APIs
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "--------------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "--------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xSysCtl API", "CoX", "HT32F125x"  ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlPeripheralReset", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlPeripheralEnable", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlPeripheralDisable", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlPeripheralReset2", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlPeripheralEnable2", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlPeripheralDisable2", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlClockSet", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlClockGet", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlDelay", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlReset", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
    [ "xSysCtlSleep", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
	[ "xSysCtlPeripheralClockSourceSet", "Mandatory", "Y" ],
    [ "--------------------------------", "----------------","--------", ],
	[ "xSysCtlPeripheralClockSourceSet2", "Mandatory", "N" ],
    [ "--------------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####xSysCtl_Exported_APIs\n";
print $tb; 
###############################################################################
#
###############################################################################




###############################################################################
# xSysCtlPeripheralClockSourceSet2.pl
###############################################################################

use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    {
        is_sep => 1,
        title => "//! +",
        body => "//! |",
    },
    
    # Column 1 "Item"
    {
        title => "--------------------",
        align => center,
    },
    
    # Separator column
    {
        is_sep => 1,
        title => "+",
        body => "|",
    },
    
    # Column 2 "Name"
    {
        title => "------------------------",
        align => left,
    },

    # Separator column
    {
        is_sep => 1,
        title => "+",
        body => "|",
    },
    
    # Column 2 "Brief"
    {
        title => "------------------------------",
        align => left,
    },
    
    # End separator column
    {
        is_sep => 1,
        title => "+",
        body => "|",
    },
); 

# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [
        "manufacturer",
        "ePeripheral",
        "eSrc"
    ],
    
    # Separtor Line(MAX Length)
    ["--------------------", "------------------------", "------------------------------"],
    
    # Line1 (Data)
    [
    "CoX Common & \n Mandatory", 
    "This parameter is a\n".
    "mandatory.Mandatory\n".
	"is the format of\n".
    "Variable naming.So it \n".
	"should be: \n".
	"TIMERn or UARTn\n".
	"n indicate the pin\n".
	"number such as \n".
	"0 1 2 3 ....", 
    "This parameter is a\n".
    "mandatory. So it \n".
	"should be: INT \n".
    "HCLK  HCLK_n EXTSL \n".
	"INTSL  MAIN  PLL\n".
	"PLL_n  EXTTRG\n".
	"n indicate the pin \n".
	"number such as \n".
	"0 1 2 3 ....", 
    ],
    
    # Separtor Line(MAX Length)
    ["--------------------", "------------------------", "------------------------------"],  
    # Line4
    [
        "HT32F125x",
"   TIMER0
    UART0
    WDT0
",
"INT HCLK EXTSL MAIN
INT HCLK EXTSL MAIN
INT HCLK PLL MAIN
INT EXTTRG HCLK EXTSL MAIN
INT EXTTRG HCLK EXTSL MAIN
INT EXTTRG HCLK EXTSL MAIN
INT EXTTRG HCLK EXTSL MAIN
INT PLL MAIN
INT PLL MAIN
INTSL HCLK_2 EXTSL
"
    ], 	
    # Separtor Line(MAX Length)
    ["--------------------", "------------------------", "------------------------------"],
);  

# Print to console or file
print $tb; 
