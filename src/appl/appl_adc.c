/*******************************************************************************
 *    Description:   See header file
 *
 ******************************************************************************/


/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/

#include "appl_adc.h"
#include "appl_adc_channels.h"
#include "bsp_adc.h"

#include "xc.h"

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE FUNCTION PROTOTYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/

static T_ADCHandler _adc_handlers[ APPL_ADC_CH_CNT ];


/*******************************************************************************
 *    PUBLIC DATA
 ******************************************************************************/

/*******************************************************************************
 *    EXTERNAL DATA
 ******************************************************************************/

/*******************************************************************************
 *    EXTERNAL FUNCTION PROTOTYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *    PROTECTED FUNCTIONS
 ******************************************************************************/

/**
 * For usage in tests only!
 */
T_ADCHandler *_appl_adc__adc_handler__get(enum E_ApplAdcChannel channel)
{
    return &_adc_handlers[channel];
}



/*******************************************************************************
 *    PUBLIC FUNCTIONS
 ******************************************************************************/

void appl_adc__init(void)
{
    enum E_ApplAdcChannel channel;

    //-- init all ADC channels
    for (channel = 0; channel < APPL_ADC_CH_CNT; channel++){
        T_ADCHandler_CtorParams params = {};

        //-- here, we initialize all channels with the same params,
        //   but in real life different ADC channels may, of course,
        //   have different parameters.
        params.max_counts = 0x3ff;
        params.bsp_max_voltage = 10/*V*/ * ADC_HANDLER__SCALE_FACTOR__U;
        params.nominal_add_volts = 0/*V*/;

        //-- construct the ADC handler, saving the result to _ctor_result
        adc_handler__ctor(&_adc_handlers[ channel ], &params);
    }
}

T_ADCHandler_Voltage appl_adc__voltage__get(enum E_ApplAdcChannel channel_num)
{
    T_ADCHandler_Voltage ret = 0;

    if (channel_num < APPL_ADC_CH_CNT){
        ret = adc_handler__voltage__get_by_counts_value(
                &_adc_handlers[ channel_num ],
                bsp_adc__value__get(channel_num)
                );
    } else {
        //-- illegal channel_num given: should never be here
        __builtin_software_breakpoint();
    }

    return ret;
}



/*******************************************************************************
 *    end of file
 ******************************************************************************/



