/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author:  Valentina Gaggero
 * email:   valentina.gaggero@iit.it
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
#ifndef _EOTHEMEASURESCONVERTER_H_
#define _EOTHEMEASURESCONVERTER_H_

// - doxy begin -------------------------------------------------------------------------------------------------------

/** @file       EOtheMeasuresConverter.h
    @brief      This file provides interface to converter obj.
                this obj convertes position, veleocity, acceleration, torque, stiffness, etc. 
                expressed in encoder/sensor ticks in "icub measure unit". see file "EoMeasures.h"
    @author     valentina.gaggero@iit.it
    @date       08/24/2012
**/


/** @defgroup   eo_app_measuresConverter Object EOtheMeasuresConverter
    NOTE: corrent doesn't need conversions because icub-can-proto and embobj-proto use the same mesurament unit  
    @{        
 **/


// - external dependencies --------------------------------------------------------------------------------------------
#include "eOcommon.h"
#include "EoMotionControl.h"
#include "EoUtilities.h"
#include "EoMeasures.h"
#include "iCubCanProto_types.h"

// - public #define  --------------------------------------------------------------------------------------------------
// empty-section
 
// - declaration of public user-defined types ------------------------------------------------------------------------- 

typedef struct EOtheMeasuresConverter_hid  EOtheMeasuresConverter;


typedef struct
{
    uint8_t dummy;
    uint8_t jointVelocityShift;
    uint8_t jointVelocityEstimationShift;
    uint8_t jointAccEstimationShift;
//     uint8_t     jointvelocityShift;                      read from DB
//     uint8_t     jointVelocityEstimationShift;            read from DB
//     uint8_t     jointAccelerationEstimationShift;        actually not used
//     uint8_t     motorVelocityEstimationShift;            actually not used
//     uint8_t     motorAccelerationEstimationShift;        actually not used
} eOmeasconv_cfg_t;


// typedef eOutil_emulfloat32_t eOmeasconv_encConversionFactor_t;  /**< expressed in encoder_ticks/idegree  */
// typedef eOutil_emulfloat32_t eOmeasconv_encConversionOffset_t;  /**< express in idg  */

typedef float eOmeasconv_encConversionFactor_t;  /**< expressed in encoder_ticks/idegree  */
typedef float eOmeasconv_encConversionOffset_t;  /**< express in idg  */

// - declaration of extern public variables, ...deprecated: better using use _get/_set instead ------------------------
// empty-section

// - declaration of extern public functions ---------------------------------------------------------------------------
/** @fn         extern EOtheMeasuresConverter* eo_appEncReader_New(eOmeasconv_cfg_t *cfg)
    @brief      Create a measures converter.
    @param      cfg        configuration for the obj. (currently is not used)
    @return     NULL in case of errors or pointer to EOtheMeasuresConverter on successfully 
 **/
extern EOtheMeasuresConverter* eo_measconv_Initialise(eOmeasconv_cfg_t *cfg);

extern EOtheMeasuresConverter* eo_measconv_GetHandle(void);

/** @fn         extern eOresult_t eo_measconv_SetJntEncoderPropRatio(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeasconv_encConversionFactor_t propRatio)
    @brief      Set EncoderPropRatio of joint with @e jId
    @param      p               referece to converter
    @param      jId             identifier of joint
    @param      propRatio       proportional ration of joint jId
    @return     - eores_NOK_nullpointer if p is NULL
                - eores_NOK_nodata if joint identified by @e jId is not managed by the given ems
                - eores_OK on success
 **/
extern eOresult_t eo_measconv_SetJntEncoderConversionFactor(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeasconv_encConversionFactor_t convfactor);


/** @fn         extern eOresult_t eo_measconv_SetJntEncoderZero(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeasconv_encConversionOffset_t zero)
    @brief      Set EncoderZero of encoder of joint with @e jId
    @param      p               referece to converter
    @param      jId             identifier of joint
    @param      convoffset      conversion offset expressed in icub degree
    @return     - eores_NOK_nullpointer if p is NULL
                - eores_NOK_nodata if joint identified by @e jId is not managed by the given ems
                - eores_OK on success
 **/
extern eOresult_t eo_measconv_SetJntEncoderConversionOffset(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeasconv_encConversionOffset_t convoffset);

/** @fn         extern eOresult_t eo_measconv_position_E2I(EOtheMeasuresConverter *p)
    @brief      convert position measure from encoder ticks to icub degree (idg)
    @param      p        referece to converter
    @param      jId      joint identifier
    @return     - eores_NOK_nullpointer if p is NULL
                - eores_NOK_nodata if joint identified by @e jId is not managed by the given ems
                - eores_OK on success
 **/
extern eOmeas_position_t eo_measconv_jntPosition_E2I(EOtheMeasuresConverter *p, eOmc_jointId_t jId, icubCanProto_position_t e_pos);



/** @fn         extern eOresult_t eo_measconv_position_E2I(EOtheMeasuresConverter *p)
    @brief      convert position measure from icub degree (idg) to encoder ticks 
    @param      p        referece to converter
    @param      jId      joint identifier
    @return     - eores_NOK_nullpointer if p is NULL
                - eores_NOK_nodata if joint identified by @e jId is not managed by the given ems
                - eores_OK on success
 **/
extern icubCanProto_position_t eo_measconv_jntPosition_I2E(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_position_t i_pos);


/** @fn         extern eOresult_t eo_measconv_position_E2I(EOtheMeasuresConverter *p)
    @brief      convert velocity measure from encoder ticks to icub degree (idg) using absolute value of encoderfactor
    @param      p        referece to converter
    @param      jId      joint identifier
    @return     - eores_NOK_nullpointer if p is NULL
                - eores_NOK_nodata if joint identified by @e jId is not managed by the given ems
                - eores_OK on success
 **/
extern eOmeas_velocity_t eo_measconv_jntVelocity_E2I_abs(EOtheMeasuresConverter *p, eOmc_jointId_t jId, icubCanProto_velocity_t e_vel);

extern icubCanProto_velocity_t eo_measconv_jntVelocity_I2E_abs(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_velocity_t i_vel);


extern eOmeas_velocity_t eo_measconv_jntVelocity_E2I(EOtheMeasuresConverter *p, eOmc_jointId_t jId, icubCanProto_velocity_t e_vel);

extern icubCanProto_velocity_t eo_measconv_jntVelocity_I2E(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_velocity_t i_vel);
// /* this function is used only to convert the reference velocity(ref_vel) of position set point for a joint managed by mc4 board.
//    Mc4 board uses ref_vel expressed in (encoder ticks/second)/10.
//    diveded by 10 because in this way in 16 bits is possible rappresents + or - 5 round angles. 
//    see file trajectory.c of firmware */
// extern icubCanProto_velocity_t eo_measconv_jntVelocity_I2E_forSetVelRefMC4(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_velocity_t i_vel);


extern eOmeas_acceleration_t eo_measconv_jntAcceleration_E2I(EOtheMeasuresConverter *p, eOmc_jointId_t jId, icubCanProto_acceleration_t e_acc);
extern icubCanProto_acceleration_t eo_measconv_jntAcceleration_I2E(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_acceleration_t i_acc);
extern eOmeas_acceleration_t eo_measconv_jntAcceleration_E2I_abs(EOtheMeasuresConverter *p, eOmc_jointId_t jId, icubCanProto_acceleration_t e_acc);
extern icubCanProto_acceleration_t eo_measconv_jntAcceleration_I2E_abs(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_acceleration_t i_acc);


extern icubCanProto_stiffness_t eo_measconv_impedenceStiffness_I2S(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_stiffness_t i_stiff);
extern eOmeas_stiffness_t eo_measconv_impedenceStiffness_S2I(EOtheMeasuresConverter *p, eOmc_jointId_t jId, icubCanProto_stiffness_t s_stiff);

extern icubCanProto_damping_t eo_measconv_impedenceDamping_I2S(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_damping_t i_damping);
extern eOmeas_damping_t eo_measconv_impedenceDamping_S2I(EOtheMeasuresConverter *p, eOmc_jointId_t jId, icubCanProto_damping_t s_damping);

extern icubCanProto_torque_t eo_measconv_torque_I2S(EOtheMeasuresConverter *p, eOmc_jointId_t jId, eOmeas_torque_t i_torque);
extern eOmeas_torque_t eo_measconv_torque_S2I(EOtheMeasuresConverter *p, eOmc_jointId_t jId, icubCanProto_torque_t s_torque);

/** @}            
    end of group eo_app_measuresConverter
 **/

#endif  // include-guard

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------


