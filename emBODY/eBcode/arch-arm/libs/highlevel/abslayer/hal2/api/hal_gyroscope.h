/*
 * Copyright (C) 2012 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

// - include guard ----------------------------------------------------------------------------------------------------

#ifndef _HAL_GYROSCOPE_H_
#define _HAL_GYROSCOPE_H_

// - doxy begin -------------------------------------------------------------------------------------------------------

/** @file       hal_gyroscope.h
    @brief      This header file implements interface to a generic hal sensor angular rate module (gyroscope)
    @author     marco.accame@iit.it
    @date       10/24/2012
**/

/** @defgroup doxy_group_hal_gyroscope HAL GYROSCOPE

    The HAL veth5 is a high level module which manages a angular rate sensor
 
    @todo acemor-facenda: review documentation.
    
    @{        
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "hal_common.h"



// - public #define  --------------------------------------------------------------------------------------------------
// empty-section
  

// - declaration of public user-defined types ------------------------------------------------------------------------- 


/** @typedef    typedef enum hal_gyroscope_t 
    @brief      hal_gyroscope_t contains the possible sensors
 **/
typedef enum
{
    hal_gyroscope1     = 0
} hal_gyroscope_t;

enum { hal_gyroscopes_number = 1 };


/** @typedef    typedef int8_t hal_gyroscope_angularrate_t 
    @brief      expresses the angular rate in milli degrees per second.
 **/
typedef struct
{
    int32_t     xar;
    int32_t     yar;
    int32_t     zar;
} hal_gyroscope_angularrate_t;

typedef enum
{
    hal_gyroscope_range_250dps     = 0,
    hal_gyroscope_range_500dps     = 1,
    hal_gyroscope_range_2000dps    = 2   
} hal_gyroscope_range_t;


/** @typedef    typedef enum hal_gyroscope_cfg_t 
    @brief      hal_gyroscope_cfg_t contains the configuration for the sensor.
 **/
typedef struct
{
    hal_gyroscope_range_t   range;
} hal_gyroscope_cfg_t;

 
// - declaration of extern public variables, ... but better using use _get/_set instead -------------------------------

extern const hal_gyroscope_cfg_t hal_gyroscope_cfg_default; // = { .range = hal_gyroscope_range_250dps };


// - declaration of extern public functions ---------------------------------------------------------------------------


extern hal_bool_t hal_gyroscope_supported_is(hal_gyroscope_t id);


extern hal_result_t hal_gyroscope_deinit(hal_gyroscope_t id);

/** @fn			extern hal_result_t hal_gyroscope_init(hal_gyroscope_t id, const hal_gyroscope_cfg_t *cfg)
    @brief  	this function initializes a given gyro sensor 
    @param  	sensor	        the sensor
    @param  	cfg 	        pointer to configuration data
    @return 	hal_res_NOK_generic on error else hal_res_OK
    @warning    a given gyroscope can be initted only once. The second call of hal_gyroscope_init(id, cfg) will do nothing.
                The return value will be hal_res_OK if the parameter cfg is the same as one used the first time,
                otherwise it will be hal_res_NOK_generic to express the fact that the device is not initted as wanted.
  */
extern hal_result_t hal_gyroscope_init(hal_gyroscope_t id, const hal_gyroscope_cfg_t *cfg);




/** @fn			extern hal_result_t hal_gyroscope_read(hal_gyroscope_t id, hal_device_gyroscope_degree_t* degrees)
    @brief  	this function reads temperatures on a given sensor.
    @param  	sensor	        the sensor
    @param  	degrees 	    the read degrees
    @return 	hal_res_NOK_generic on error else hal_res_OK
  */
extern hal_result_t hal_gyroscope_read(hal_gyroscope_t id, hal_gyroscope_angularrate_t* angrate);

extern hal_result_t hal_gyroscope_readraw(hal_gyroscope_t id, int16_t *x, int16_t *y, int16_t *z);





/** @}            
    end of group doxy_group_hal_gyroscope  
 **/

#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------



