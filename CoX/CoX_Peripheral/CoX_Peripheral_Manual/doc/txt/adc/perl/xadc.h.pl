###############################################################################
# xADC_Ints
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
    { title => "--------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xADC Interrupt Source", "COX", "NUC1xx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "xADC_INT_COMP", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADC_INT_END_CONVERSION", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####xADC_Ints\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# xADC_Events
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "-------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "----------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xADC Event", "COX", "NUC1xx"  ],
    [ "-------------------------", "----------------","----------------", ],
    [ "xADC_EVENT_COMP\$x\$", "Non-Mandatory", "xADC_EVENT_COMP0\nxADC_EVENT_COMP1" ],
    [ "-------------------------", "----------------","----------------", ],
    [ "xADC_EVENT_END_CONVERSION", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------", ],    
);  

# Print to console or file
print "\n#####xADC_Events\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# xADC_Mode
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "---------------------------", align => left, },
    
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
    [ "xADC Mode", "COX", "NUC1xx"  ],
    [ "---------------------------", "----------------","--------", ],
    [ "xADC_MODE_SCAN_SINGLE_CYCLE", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xADC_MODE_SCAN_CONTINUOUS", "Non-Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####xADC_Mode\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xADC_Trigger_Source
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "---------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "--------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xADC Trigger Source", "COX", "NUC1xx"  ],
    [ "---------------------------", "----------------","--------------------", ],
    [ "xADC_TRIGGER_PROCESSOR", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------------------", ],
    [ "xADC_TRIGGER_EXT_\$ShortPin\$", "Non-Mandatory", "xADC_TRIGGER_EXT_PB8" ],
    [ "---------------------------", "----------------","--------------------", ],
);  

# Print to console or file
print "\n#####xADC_Trigger_Source\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# xADC_EXT_Trigger_Mode
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "-----------------------------", align => left, },
    
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
    [ "xADC Ext Trigger Mode", "COX", "NUC1xx"  ],
    [ "-----------------------------", "----------------","--------", ],
    [ "xADC_TRIGGER_EXT_LOW_LEVEL", "Non-Mandatory", "Y" ],
    [ "-----------------------------", "----------------","--------", ],
    [ "xADC_TRIGGER_EXT_HIGH_LEVEL", "Non-Mandatory", "Y" ],
    [ "-----------------------------", "----------------","--------", ],
    [ "xADC_TRIGGER_EXT_RISING_EDGE", "Non-Mandatory", "Y" ],
    [ "-----------------------------", "----------------","--------", ],
    [ "xADC_TRIGGER_EXT_FALLING_EDGE", "Non-Mandatory", "Y" ],
    [ "-----------------------------", "----------------","--------", ],
    [ "xADC_TRIGGER_EXT_BOTH_EDGE", "Non-Mandatory", "N" ],
    [ "-----------------------------", "----------------","--------", ],

);  

# Print to console or file
print "\n#####xADC_EXT_Trigger_Mode\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# xADC_Step_Config
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "----------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "-------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xADC Step Config", "COX", "NUC1xx"  ],
    [ "----------------", "----------------","-------------", ],
    [ 
        "xADC_CTL_CH\$x\$", 
        "Mandatory", 
        "xADC_CTL_CH0\nxADC_CTL_CH1\nxADC_CTL_CH2\nxADC_CTL_CH3\n". 
        "xADC_CTL_CH4\nxADC_CTL_CH5\nxADC_CTL_CH6\nxADC_CTL_CH7"
    ],
    [ "----------------", "----------------","-------------", ],
    [ "xADC_CTL_TS", "Non-Mandatory", "Y" ],
    [ "----------------", "----------------","-------------", ],
    [ "xADC_CTL_CMP\$x\$", "Non-Mandatory", "xADC_CTL_CMP0\nxADC_CTL_CMP1" ],
    [ "----------------", "----------------","-------------", ],
    [ "xADC_CTL_D", "Non-Mandatory", "Y" ],
    [ "----------------", "----------------","-------------", ],
    [ "xADC_CTL_END", "Non-Mandatory", "Y" ],
    [ "----------------", "----------------","-------------", ],
);  

# Print to console or file
print "\n#####xADC_Step_Config\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xADC_Exported_APIs
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
    { title => "--------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xADC API", "COX", "NUC1xx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCConfigure", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCStepConfigure", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCIntCallbackInit", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCIntEnable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCIntDisable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCDMAEnable", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCDMADisable", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCEnable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCDisable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCProcessorTrigger", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCDataGet", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCOverflow", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCOverflowClear", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCCompConditionConfig", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCCompRegionSet", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCCompEnable", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xADCCompDisable", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],

);  

# Print to console or file
print "\n#####xADC_Exported_APIs\n";
print $tb; 
###############################################################################
#
###############################################################################