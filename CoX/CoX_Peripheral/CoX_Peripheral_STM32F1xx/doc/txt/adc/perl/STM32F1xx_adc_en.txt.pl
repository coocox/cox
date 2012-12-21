
###############################################################################
# STM32F1xx_ADC_Function_Desc.STM32F1xx_ADC_Pin_Desc
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
print "\n#####STM32F1xx_ADC_Function_Desc.STM32F1xx_ADC_Pin_Desc\n";
print $tb; 
###############################################################################
#
###############################################################################


###############################################################################
# STM32F1xx_ADC_Function_Desc.STM32F1xx_ADC_Func_Convertion.STM32F1xx_ADC_Func_Channel
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


# Print to console or file
print "\n#####STM32F1xx_ADC_Function_Desc.STM32F1xx_ADC_Func_Convertion.STM32F1xx_ADC_Func_Channel\n";
print $tb; 
###############################################################################
#
###############################################################################