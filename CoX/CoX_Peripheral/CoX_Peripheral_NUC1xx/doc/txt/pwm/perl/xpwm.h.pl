###############################################################################
# xPWM_Int_Type
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
    [ "xPWM Interrupt Source", "COX", "NUC1xx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWM_INT_PWM", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####xPWM_Int_Type\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xPWM_Event_Type
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
    [ "xPWM Event Source", "COX", "NUC1xx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWM_EVENT_PWM", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
	[ "xPWM_EVENT_CAP", "non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####xPWM_Event_Type\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xPWM_Freq_Config
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
    [ "xPWM Freq Config", "COX", "NUC1xx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWM_FREQ_CONFIG(a,b,c)", "Mandatory", "Y" ],
	[ "a is The Divider value", "", "" ],
	[ "b is The PreScale value", "", "" ],
	[ "c is PWM Counter value", "", "" ],
    [ "------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####xPWM_Freq_Config\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xPWM_Channel
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
    { title => "-------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xPWM Channel Number", "COX", "NUC1xx"  ],
    [ "------------------------", "----------------","-------------", ],
    [ "xPWM_CHANNEL$x\$", "Non-Mandatory", "xPWM_CHANNEL0" ],
    [ "", "","-------------", ],
	[ "", "", "xPWM_CHANNEL1" ],
	[ "", "","-------------", ],
	[ "", "", "xPWM_CHANNEL2" ],
	[ "", "","-------------", ],
	[ "", "", "xPWM_CHANNEL3" ],
	[ "", "","-------------", ],
	[ "", "", "xPWM_CHANNEL4" ],
	[ "", "","-------------", ],
	[ "", "", "xPWM_CHANNEL5" ],
	[ "", "","-------------", ],
	[ "", "", "xPWM_CHANNEL6" ],
	[ "", "", "-------------", ],
	[ "", "", "xPWM_CHANNEL7" ],
    [ "------------------------", "----------------","-------------", ],
);  

# Print to console or file
print "\n#####xPWM_Channel\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xPWM_Config
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
    [ "xPWM Config", "COX", "NUC1xx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWM_ONE_SHOT_MODE", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
	[ "xPWM_TOGGLE_MODE", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
	[ "xPWM_OUTPUT_INVERTER_EN", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
	[ "xPWM_OUTPUT_INVERTER_DIS", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
	[ "xPWM_DEAD_ZONE_EN", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
	[ "xPWM_DEAD_ZONE_DIS", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####xPWM_Config\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xPWM_Exported_APIs
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
    [ "xPWM API", "COX", "NUC1xx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMInitConfigure", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMFrequencySet", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMFrequencyConfig", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMFrequencyGet", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMOutputEnable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMOutputDisable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMStart", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMStop", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMDutySet", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMDutyGet", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMIntEnable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMIntDisable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMIntFlagGet", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMIntFlagClear", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "xPWMIntCallbackInit", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
 

);  

# Print to console or file
print "\n#####xPWM_Exported_APIs\n";
print $tb; 
###############################################################################
#
###############################################################################