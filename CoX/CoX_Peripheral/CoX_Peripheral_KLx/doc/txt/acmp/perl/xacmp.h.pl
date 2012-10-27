###############################################################################
# XCOMP_Exported_APIs
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
    [ "XCOMP API", "COX", "KLx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMPConfigure", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMPEnable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMPDisable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMPIntCallbackInit", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMPIntEnable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMPIntDisable", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],

);  

# Print to console or file
print "\n#####XCOMP_Exported_APIs\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# XCOMP_Analog_Src_Negative
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
    [ "XCOMP COMP- Source", "COX", "KLx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMP_ASRCN_PIN", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMP_ASRCN_REF", "Non-Mandatory", "N" ],
    [ "------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####XCOMP_Analog_Src_Negative\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# XCOMP_Analog_Src_Positive
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
    [ "XCOMP COMP+ Source", "COX", "KLx"  ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMP_ASRCP_PIN", "Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
    [ "XCOMP_ASRCP_REF", "Non-Mandatory", "Y" ],
    [ "------------------------", "----------------","--------", ],
);  

# Print to console or file
print "\n#####XCOMP_Analog_Src_Positive\n";
print $tb; 
###############################################################################
#
###############################################################################