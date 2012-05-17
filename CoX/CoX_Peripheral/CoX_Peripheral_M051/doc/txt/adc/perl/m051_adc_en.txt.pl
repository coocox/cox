
###############################################################################
# NUC1xx_ADC_Function_Desc.NUC1xx_ADC_Pin_Desc
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "-------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },  
    
    # Column 3
    { title => "-----------------------", align => left, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "Peripheral Pin Name", "GPIO Pin multiplex", "Pin Description",  ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "ADC0", "PA0", "ADC channel 0 input", ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "ADC1", "PA1", "ADC channel 0 input", ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "ADC2", "PA2", "ADC channel 0 input", ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "ADC3", "PA3", "ADC channel 0 input", ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "ADC4", "PA4", "ADC channel 0 input", ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "ADC5", "PA5", "ADC channel 0 input", ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "ADC6", "PA6", "ADC channel 0 input", ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "ADC7", "PA7", "ADC channel 0 input", ],
    [ "-------------------", "------------------", "-----------------------", ],
    [ "STADC", "PB8", "ADC external trigger \ninput", ],
    [ "-------------------", "------------------", "-----------------------", ], 
);  

# Print to console or file
print "\n#####NUC1xx_ADC_Function_Desc.NUC1xx_ADC_Pin_Desc\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# NUC1xx_ADC_Function_Desc.NUC1xx_ADC_Func_Convertion.NUC1xx_ADC_Func_Channel
###############################################################################
use Text::Table;
my $tb = Text::Table->new(
    # First separator column 
    { is_sep => 1, title => "//! +", body => "//! |", },
    
    # Column 1
    { title => "-------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },
    
    # Column 2
    { title => "------------------", align => left, },
    
    # Separator column
    { is_sep => 1, title => "+", body => "|", },  
    
    # Column 3
    { title => "------------------", align => left, },
    
    # End separator column
    { is_sep => 1, title => "+", body => "|", },
); 

    
# Fill Table Cotent
$tb->load(
    # Line 0(Column Name)
    [ "Diff paired channel", "Vplus channel", "Vminus channel",  ],
    [ "-------------------", "------------------", "------------------", ],
    [ "Pair 0", "ADC0(channel 0)", "ADC1(channel 1)", ],
    [ "-------------------", "------------------", "------------------", ],
    [ "Pair 1", "ADC2(channel 2)", "ADC3(channel 3)", ],
    [ "-------------------", "------------------", "------------------", ],
    [ "Pair 2", "ADC4(channel 4)", "ADC5(channel 5)", ],
    [ "-------------------", "------------------", "------------------", ],
    [ "Pair 3", "ADC6(channel 6)", "ADC7(channel 7)", ],
    [ "-------------------", "------------------", "------------------", ],
     
);  

# Print to console or file
print "\n#####NUC1xx_ADC_Function_Desc.NUC1xx_ADC_Func_Convertion.NUC1xx_ADC_Func_Channel\n";
print $tb; 
###############################################################################
#
###############################################################################