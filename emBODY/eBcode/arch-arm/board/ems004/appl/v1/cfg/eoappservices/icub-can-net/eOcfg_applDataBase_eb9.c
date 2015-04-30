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

/* @file       eOcfg_applDataBase_eb9.c
    @brief      This file keeps ems EB9(right lower leg) can network configuration
    @author     valentina.gaggero@iit.it
    @date       08/23/2012
**/
// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------
#include "string.h"
#include "EoCommon.h"
#include "EOconstvector_hid.h" 

//#include "emBODYrobot.h"

// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------
#include "EoappTheDataBase.h"



// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------




// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables, but better using _get(), _set() 
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------

//board 
#define FOC_ADDRCAN_1_BID       0
#define FOC_ADDRCAN_2_BID       1

#if     ( defined(ICUB_DARMSTADT01) || (emBODYrobot_ROBOT_NAME == iCubDarmstadt01) )
    #define STRAIN_ADDRCAN_1_BID   2
#endif


static const eOappTheDB_canboardinfo_t s_cfg_appDB_boards[] = 
{
    { // 0 == FOC_ADDRCAN_1_BID 
        .port           = eOcanport1,
        .addr           = 2,
        .type           = eobrd_cantype_1foc,
        .canprotversion = {.major = 1, .minor = 2}
    },
    { // 1 == FOC_ADDRCAN_2_BID 
        .port           = eOcanport1,
        .addr           = 1,
        .type           = eobrd_cantype_1foc,
        .canprotversion = {.major = 1, .minor = 2}
    }
#if     ( defined(ICUB_DARMSTADT01) || (emBODYrobot_ROBOT_NAME == iCubDarmstadt01) )       
    ,{// 2 == STRAIN_ADDRCAN_1_BID
        .port           = eOcanport2,
        .addr           = 1,
        .type           = eobrd_cantype_strain,
        .canprotversion = {.major = 0, .minor = 0}
    }     
#endif
};    
    

const EOconstvector s_eo_cfg_appDB_constvec_boards = 
{
    .capacity       = sizeof(s_cfg_appDB_boards)/sizeof(eOappTheDB_canboardinfo_t),
    .size           = sizeof(s_cfg_appDB_boards)/sizeof(eOappTheDB_canboardinfo_t), 
    .item_size      = sizeof(eOappTheDB_canboardinfo_t),
    .dummy          = 0,  
    .stored_items   = (void*) s_cfg_appDB_boards,
    .functions      = NULL
};
extern const EOconstvector* const eo_cfg_appDB_thecanboards = &s_eo_cfg_appDB_constvec_boards;



// joints

static const eOappTheDB_mapping2canboard_t s_cfg_appDB_joints[] = 
{
    { // 0 
        EO_INIT(.indexofcanboard)               FOC_ADDRCAN_1_BID,
        EO_INIT(.indexinsidecanboard)           eo_icubCanProto_jm_index_first,
    },    
    { // 1 
        EO_INIT(.indexofcanboard)               FOC_ADDRCAN_2_BID,
        EO_INIT(.indexinsidecanboard)           eo_icubCanProto_jm_index_first,
    }     
};

const EOconstvector s_eo_cfg_appDB_constvec_joints = 
{
    .capacity       = sizeof(s_cfg_appDB_joints)/sizeof(eOappTheDB_mapping2canboard_t),
    .size           = sizeof(s_cfg_appDB_joints)/sizeof(eOappTheDB_mapping2canboard_t), 
    .item_size      = sizeof(eOappTheDB_mapping2canboard_t),
    .dummy          = 0,  
    .stored_items   = (void*) s_cfg_appDB_joints,
    .functions      = NULL         
};
extern const EOconstvector* const eo_cfg_appDB_thejoints_mapping2canboards = &s_eo_cfg_appDB_constvec_joints;


// - in here we have the mapping of the motors into a given can board and its internal index (0, 1). 
// - the same as joints
extern const EOconstvector* const eo_cfg_appDB_themotors_mapping2canboards = &s_eo_cfg_appDB_constvec_joints;



// - in here we have the mapping of the mais sensors into a given can board

//static const eOappTheDB_mapping2canboard_t  s_cfg_appDB_snsrMais[] = 
//{
//    {// 0
//       .indexofcanboard        = MAIS_ADDRCAN_14_BID,
//        .indexinsidecanboard    = eOappTheDB_canboard_noindex
//    }
//};

const EOconstvector  s_eo_cfg_appDB_constvec_snsrMais = 
{
    .capacity       = 0,
    .size           = 0, 
    .item_size      = 0,
    .dummy          = 0,  
    .stored_items   = NULL,
    .functions      = NULL
};

extern const EOconstvector* const eo_cfg_appDB_themaises_mapping2canboards = &s_eo_cfg_appDB_constvec_snsrMais;


// - in here we have the mapping of the strain sensors into a given can board

#if     ( defined(ICUB_DARMSTADT01) || (emBODYrobot_ROBOT_NAME == iCubDarmstadt01) )
static const eOappTheDB_mapping2canboard_t  s_cfg_appDB_snsrStrain[] =
{
    {// 0
        .indexofcanboard        =   STRAIN_ADDRCAN_1_BID,
        .indexinsidecanboard    =   eo_icubCanProto_jm_index_none 
    }
};

const EOconstvector  s_eo_cfg_appDB_constvec_snsrStrain = 
{   
    .capacity       = sizeof(s_cfg_appDB_snsrStrain)/sizeof(eOappTheDB_mapping2canboard_t),
    .size           = sizeof(s_cfg_appDB_snsrStrain)/sizeof(eOappTheDB_mapping2canboard_t), 
    .item_size      = sizeof(eOappTheDB_mapping2canboard_t),
    .dummy          = 0,  
    .stored_items   = (void*) s_cfg_appDB_snsrStrain,
    .functions      = NULL 
};

#else
const EOconstvector  s_eo_cfg_appDB_constvec_snsrStrain = 
{   
    .capacity       = 0,
    .size           = 0, 
    .item_size      = 0,
    .dummy          = 0,  
    .stored_items   = NULL,
    .functions      = NULL 
};
#endif

extern const EOconstvector* const eo_cfg_appDB_thestrains_mapping2canboards = &s_eo_cfg_appDB_constvec_snsrStrain;



// skin
// no skin
const EOconstvector  s_eo_cfg_appDB_constvec_skin = 
{
    .capacity       = 0,
    .size           = 0, 
    .item_size      = 0,
    .dummy          = 0,  
    .stored_items   = NULL,
    .functions      = NULL
};


extern const EOconstvector* const eo_cfg_appDB_theskins_info = &s_eo_cfg_appDB_constvec_skin;


