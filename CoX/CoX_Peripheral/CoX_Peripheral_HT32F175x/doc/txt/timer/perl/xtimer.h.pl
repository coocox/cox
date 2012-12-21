###############################################################################
# xTIMER_Mode_Type
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
    [ "xTIMER Mode", "COX", "HT32F175x/275x"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_MODE_ONESHOT", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_MODE_PERIODIC", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_MODE_TOGGLE", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_MODE_CONTINUOUS", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_MODE_CAPTURE", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_MODE_PWM", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xTIMER_Mode_Type\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xTIMER_INT_Type
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
    [ "xTIMER Interrupt", "COX", "HT32F175x/275x"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_INT_MATCH", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_INT_CAP_EVENT", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_INT_CAP_MATCH", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_INT_OVERFLOW", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_INT_PWM", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xTIMER_INT_Type\n";
print $tb; 
###############################################################################
#
###############################################################################




###############################################################################
# xTIMER_Counter_Pase_Type
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
    [ "xTIMER Counter Pase Type", "COX", "HT32F175x/275x"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_COUNTER_RISING", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_COUNTER_FALLING", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xTIMER_Counter_Pase_Type\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xTIMER_Capture_Edge_Type
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
    [ "xTIMER Capture Edge", "COX", "HT32F175x/275x"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_CAP_RISING", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_CAP_FALLING", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_CAP_BOTH", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xTIMER_Capture_Edge_Type\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xTIMER_Capture_Mode_Type
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
    [ "xTIMER Capture Mode", "COX", "HT32F175x/275x"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_CAP_MODE_CAP", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_CAP_MODE_RST", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xTIMER_Capture_Mode_Type\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xTIMER_Count_Direction
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
    [ "xTIMER Count Direction", "COX", "HT32F175x/275x"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_COUNT_UP", "Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_COUNT_DOWN", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xTIMER_Count_Direction\n";
print $tb; 
###############################################################################
#
###############################################################################



###############################################################################
# xTIMER_Count_Channel
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
    [ "xTIMER Count Channel", "COX", "HT32F175x/275x"  ],
    [ "------------------------", "----------------","------------------------", ],
    [ "xTIMER_CHANNELn", "Mandatory", "xTIMER_CHANNEL0" ],
    [ "------------------------", "----------------","------------------------", ],
);  

# Print to console or file
print "\n#####xTIMER_Count_Channel\n";
print $tb; 
###############################################################################
#
###############################################################################




###############################################################################
# xTIMER_Exported_APIs
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "------------------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "----------------", align => center, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 3
    { title => "------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xTIMER API", "COX", "HT32F175x/275x"  ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerInitConfig", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerStart", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerStop", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerCounterEnable", "Mandatory", "N" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerCounterDisable", "Mandatory", "N" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerCaptureModeSet", "Mandatory", "N" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerPrescaleSet", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerPrescaleGet", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerLoadSet", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerLoadGet", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerValueGet", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerMatchSet", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerMatchGet", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerIntCallbackInit", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerIntEnable", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerIntDisable", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerIntStatus", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerIntClear", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerCounterDetectPhaseSelect", "Mandatory", "N" ],
    [ "------------------------------", "----------------","------------------", ],
    [ "xTimerCaptureEdgeSelect", "Mandatory", "Y" ],
    [ "------------------------------", "----------------","------------------", ],
);  

# Print to console or file
print "\n#####xTIMER_Exported_APIs\n";
print $tb; 
###############################################################################
#
###############################################################################