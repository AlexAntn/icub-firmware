/*
 * Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
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

#ifndef _HAL_QUAD_ENC_HID_H_
#define _HAL_QUAD_ENC_HID_H_


/* @file       hal_quan_enc_hid.h
    @brief      This header file implements hidden interface to a quadrature encoder
    @author     marco.accame@iit.it
    @date       25 jan 2016
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "hal_common.h"


// - declaration of extern public interface ---------------------------------------------------------------------------
 
#include "hal_quad_enc.h"



// - #define used with hidden struct ----------------------------------------------------------------------------------
// empty-section


// - definition of the hidden struct implementing the object ----------------------------------------------------------


typedef struct
{
    uint32_t        supportedmask;
} hal_quad_enc_boardconfig_t;


// - declaration of extern hidden variables ---------------------------------------------------------------------------

extern const hal_quad_enc_boardconfig_t hal_quad_enc__theboardconfig;

// - declaration of extern hidden functions ---------------------------------------------------------------------------



#endif  // include guard

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------




