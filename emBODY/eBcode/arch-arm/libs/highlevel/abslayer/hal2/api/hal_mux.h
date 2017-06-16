/*
 * Copyright (C) 2013 iCub Facility - Istituto Italiano di Tecnologia
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

#ifndef _HAL_MUX_H_
#define _HAL_MUX_H_

#ifdef __cplusplus
extern "C" {
#endif

// - doxy begin -------------------------------------------------------------------------------------------------------

/** @file       hal_mux.h
    @brief      This header file implements interface to a hal mux 
    @author     marco.accame@iit.it
    @date       02/07/2013
**/

/** @defgroup doxy_group_hal_mux HAL MUX

    The HAL MUX ....
 
    @todo acemor-facenda: review documentation.
    
    @{        
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "hal_common.h"
#include "hal_gpio.h"


// - public #define  --------------------------------------------------------------------------------------------------
// empty-section
  

// - declaration of public user-defined types ------------------------------------------------------------------------- 

/** @typedef    typedef enum hal_mux_t 
    @brief      hal_mux_t contains every possible mux identifier.
 **/ 
typedef enum  
{ 
    hal_mux1   = 0,
    hal_mux2   = 1,
    hal_mux3   = 2,         
    hal_mux4   = 3
} hal_mux_t;

enum { hal_muxes_number = 4 };


typedef enum
{
    hal_mux_selA    = 0,
    hal_mux_selB    = 1,
    hal_mux_selC    = 2,
    hal_mux_selNONE = 255
} hal_mux_sel_t;

enum { hal_mux_sels_number = 3 };



/** @typedef    typedef struct hal_mux_cfg_t;
    @brief      contains configuration data of mux.
 **/
typedef struct
{
    uint8_t     dummy;        /**< nothing  */
} hal_mux_cfg_t;

 
// - declaration of extern public variables, ... but better using use _get/_set instead -------------------------------

extern const hal_mux_cfg_t hal_mux_cfg_default;   // = { .dummy = 0 };


// - declaration of extern public functions ---------------------------------------------------------------------------

/** @fn			extern hal_result_t hal_mux_init(hal_mux_t id, const hal_mux_cfg_t *cfg)
    @brief  	This function initializes the mux. if called multiple times it initialise only the first time
    @param  	id 	            the mux id
    @param  	cfg 	        The configuration of the mux. 
    @return 	hal_res_NOK_generic in case the mux is not supported, else hal_res_OK
  */
extern hal_result_t hal_mux_init(hal_mux_t id, const hal_mux_cfg_t *cfg);


/** @fn			extern hal_result_t hal_mux_enable(hal_mux_t id, hal_mux_sel_t muxsel)
    @brief  	This function enables the mux id with a given selection.
    @param  	id              the mux id
    @param  	muxsel          the mux selection 
    @return 	hal_res_NOK_generic on error else hal_res_OK
  */
extern hal_result_t hal_mux_enable(hal_mux_t id, hal_mux_sel_t muxsel);


/** @fn			extern hal_result_t hal_mux_disable(hal_mux_t id)
    @brief  	This function disables the mux. no selection is active.
    @param  	id              the mux id
    @return 	hal_res_NOK_generic on error else hal_res_OK
  */
extern hal_result_t hal_mux_disable(hal_mux_t id);

/** @fn			 extern hal_result_t hal_mux_get_cs(hal_mux_t id, hal_gpio_t* cs)
    @brief  	This function store inside a variable the chip select gpio struct for the specified mux
    @param  	id              the mux id
		@param  	cs              pointer  to chip select gpio struct
    @return 	hal_res_NOK_generic on error else hal_res_OK
  */
extern hal_result_t hal_mux_get_cs(hal_mux_t id, hal_gpio_t* cs);

/** @fn			extern hal_result_t hal_mux_deinit(hal_mux_t id)
    @brief  	This function deinitializes the mux and all the associated resources.
    @param  	id 	            the mux id
    @return 	hal_res_NOK_generic in case of error, else hal_res_OK
  */
extern hal_result_t hal_mux_deinit(hal_mux_t id);

/** @}            
    end of group doxy_group_hal_mux  
 **/

#ifdef __cplusplus
}       // closing brace for extern "C"
#endif 

#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------



