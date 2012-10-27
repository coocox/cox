###############################################################################
# xDMA_Channel_IDs
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
    [ "xDMA Channel IDs", "COX", "KLx"  ],
    [ "-------------------------", "----------------","----------------", ],
    [ "xDMA_CHANNEL_\$x\$", "Non-Mandatory", "xDMA_CHANNEL_0\n......\nxDMA_CHANNEL_3" ],
    [ "-------------------------", "----------------","----------------", ],
    [ "xDMA_CHANNEL_COUNT", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------", ],   
    [ "xDMA_CHANNEL_NOT_EXIST", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------", ], 	
);  

# Print to console or file
print "\n#####xDMA_Channel_IDs\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xDMA_Ints
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
    [ "xDMA interrupt source", "COX", "KLx"  ],
    [ "-------------------------", "----------------","----------------", ],
    [ "xDMA_INT_TC", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------", ],   
    [ "xDMA_INT_ERROR", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------", ], 	
);  

# Print to console or file
print "\n#####xDMA_Ints\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# xDMA_Event_Flags
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
    [ "xDMA event flag", "COX", "KLx"  ],
    [ "-------------------------", "----------------","----------------", ],
    [ "xDMA_EVENT_TC", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------", ],   
    [ "xDMA_EVENT_ERROR", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------", ], 	
);  

# Print to console or file
print "\n#####xDMA_Event_Flags\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xDMA_Channel_Attr
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
    [ "xDMA channel Attr", "COX", "KLx"  ],
    [ "-------------------------", "----------------","----------------", ],
    [ "xDMA_ATTR_PRIORITY_NORMAL", "Non-Mandatory", "N" ],
    [ "-------------------------", "----------------","----------------", ],   
    [ "xDMA_ATTR_PRIORITY_HIGH", "Non-Mandatory", "N" ],
    [ "-------------------------", "----------------","----------------", ], 	
	[ "xDMA_ATTR_PRIORITY_MASK", "Non-Mandatory", "N" ],
    [ "-------------------------", "----------------","----------------", ],
);  

# Print to console or file
print "\n#####xDMA_Channel_Attr\n";
print $tb; 
###############################################################################
#
###############################################################################

###############################################################################
# xDMA_Channel_Control_Config
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
    { title => "-----------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xDMA Control Config", "COX", "KLx"  ],
    [ "-------------------------", "----------------","-----------------", ],
    [ "xDMA_DST_INC_\$x\$", "Non-Mandatory", "xDMA_DST_INC_8\nxDMA_DST_INC_16\nxDMA_DST_INC_32\nxDMA_DST_INC_NONE" ],
    [ "-------------------------", "----------------","-----------------", ],   
    [ "xDMA_SRC_INC_\$x\$", "Non-Mandatory", "xDMA_SRC_INC_8\nxDMA_SRC_INC_16\nxDMA_SRC_INC_32\nxDMA_SRC_INC_NONE" ],
    [ "-------------------------", "----------------","-----------------", ], 	
	[ "xDMA_DST_SIZE_\$x\$", "Non-Mandatory", "xDMA_DST_SIZE_8\nxDMA_DST_SIZE_16\nxDMA_DST_SIZE_32" ],
    [ "-------------------------", "----------------","-----------------", ],
	[ "xDMA_SRC_SIZE_\$x\$", "Non-Mandatory", "xDMA_SRC_SIZE_8\nxDMA_SRC_SIZE_16\nxDMA_SRC_SIZE_32" ],
    [ "-------------------------", "----------------","-----------------", ],
	[ "xDMA_ARB_\$x\$", "Non-Mandatory", "N" ],
    [ "-------------------------", "----------------","-----------------", ],
	[ "xDMA_MODE_BASIC", "Non-Mandatory", "N" ],
    [ "-------------------------", "----------------","-----------------", ],
	[ "xDMA_MODE_AUTO", "Non-Mandatory", "N" ],
    [ "-------------------------", "----------------","-----------------", ],
);  

# Print to console or file
print "\n#####xDMA_Channel_Control_Config\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# xDMA_Request_Connections
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
    { title => "----------------------", align => center, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "xDMA Request Connections", "COX", "KLx"  ],
    [ "-------------------------", "----------------","----------------------", ],
    [ "xDMA_REQUEST_NOT_EXIST", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------------", ],
    [ "xDMA_REQUEST_MEM", "Mandatory", "Y" ],
    [ "-------------------------", "----------------","----------------------", ],   
    [ "xDMA_REQUEST_UART\$x\$_RX", "Non-Mandatory",       "xDMA_REQUEST_UART0_RX\nxDMA_REQUEST_UART1_RX" ],
    [ "-------------------------", "----------------","----------------------", ], 	
	[ "xDMA_REQUEST_SPI\$x\$_TX", "Non-Mandatory", "xDMA_REQUEST_SPI0_TX\nxDMA_REQUEST_SPI1_TX\nxDMA_REQUEST_SPI2_TX\nxDMA_REQUEST_SPI3_TX" ],
    [ "-------------------------", "----------------","----------------------", ], 
	[ "xDMA_REQUEST_IIS\$x\$_TX", "Non-Mandatory", "N" ],
    [ "-------------------------", "----------------","----------------------", ],
	[ "xDMA_REQUEST_IIS\$x\$_RX", "Non-Mandatory", "N" ],
    [ "-------------------------", "----------------","----------------------", ],
	[ "xDMA_REQUEST_SPI\$x\$_RX", "Non-Mandatory", "xDMA_REQUEST_SPI0_RX\nxDMA_REQUEST_SPI1_RX\nxDMA_REQUEST_SPI2_RX\nxDMA_REQUEST_SPI3_RX" ],
    [ "-------------------------", "----------------","----------------------", ],
	[ "xDMA_REQUEST_UART\$x\$_RX", "Non-Mandatory", "xDMA_REQUEST_UART0_TX\nxDMA_REQUEST_UART1_TX" ],
    [ "-------------------------", "----------------","----------------------", ], 
);  

# Print to console or file
print "\n#####xDMA_Request_Connections\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# xDMA_Exported_APIs
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
    [ "xDMA API", "COX", "KLx"  ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAEnable", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMADisable", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelDynamicAssign", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelAssignmentGet", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelDeAssign", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelAttributeSet", "Non-Mandatory", "N" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelAttributeGet", "Non-Mandatory", "N" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelControlSet", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelTransferSet", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelIntCallbackInit", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelIntCallbackGet", "Non-Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelIntEnable", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAChannelIntDisable", "Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAIntEnable", "Non-Mandatory", "Y" ],
    [ "---------------------------", "----------------","--------", ],
    [ "xDMAIntDisable", "Non-Mandatory", "Y" ],
	[ "---------------------------", "----------------","--------", ],

);  

# Print to console or file
print "\n#####xDMA_Exported_APIs\n";
print $tb; 
###############################################################################
#
###############################################################################