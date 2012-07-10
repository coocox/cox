###############################################################################
# xWATCHDOG_Function_Type
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "------------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xWATCHDOG Function Type", "CoX", "STM32F1xx"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOG_INT_FUNCTION", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOG_RESET_FUNCTION", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOG_WAKEUP_FUNCTION", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOG_HOLD_IN_ICE", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xWATCHDOG_Function_Type\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xWATCHDOG_Clock_Config
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "------------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "Clock Configuration", "CoX", "STM32F1xx"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOG_S_EXTSL", "Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWDT_S_HCLK_DIV", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xWATCHDOG_Clock_Config\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xWATCHDOG_Time_Reload_Config
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "------------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "Time Reload Config", "CoX", "STM32F1xx"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "Time Reload Value", "Mandatory", xWDT_Reload_0],
    [ "", "","------------------------", ],
    [ "unsigned value", "", "..." ],
    [ "", "","------------------------", ],
    [ "", "", "xWDT_Reload_0xFFF" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xWATCHDOG_Time_Reload_Config\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xWATCHDOG_Exported_APIs
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "------------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xWATCHDOG API", "CoX", "STM32F1xx"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOGInit", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOGEnable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWDTimerIntCallbackInit", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOGDisable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOGRestart", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOGFunctionEnable", "Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xWATCHDOGFunctionDisable", "Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
    
);  

# Print to console or file
print "\n#####xWATCHDOG_Exported_APIs\n";
print $tb; 
###############################################################################
#
###############################################################################