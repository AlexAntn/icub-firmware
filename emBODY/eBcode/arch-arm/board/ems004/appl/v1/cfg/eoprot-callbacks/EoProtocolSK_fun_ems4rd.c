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

/* @file       EoProtocolSK_fun_ems4rd.c
    @brief      This file keeps the user-defined functions used in every ems board ebx for endpoint mc
    @author     valentina.gaggero@iit.it
    @date       05/04/2012
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdlib.h" 
#include "string.h"
#include "stdio.h"
#include "hal.h"

#include "EoCommon.h"
#include "EOarray.h"
#include "EOnv_hid.h"

#include "EOSkin.h"
#include "EoProtocol.h"

//application
#include "EOtheEMSapplBody.h"
#include "EOicubCanProto_specifications.h"





// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "EoProtocolSK.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section 

// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------

// marco.accame: we start with a silent skin and with an empty status_arrayofcandata.
// then we put skin in sigmode eosk_sigmode_signal only if robotInterface orders it to the board.


extern void eoprot_fun_INIT_sk_skin_config_sigmode(const EOnv* nv)
{
    eOsk_sigmode_t *sigmode = (eOsk_sigmode_t*)nv->ram;
    
    *sigmode = eosk_sigmode_dontsignal; 
}


extern void eoprot_fun_INIT_sk_skin_status_arrayofcandata(const EOnv* nv)
{
    EOarray_of_skincandata_t *tmp = (EOarray_of_skincandata_t*)nv->ram;
    tmp = tmp;
    // marco.accame: items of array are eOsk_candata_t. its capacity is:
    uint16_t capacity = sizeof(tmp->data) / sizeof(eOsk_candata_t);    
    // eo_array_New() initialises capacity and itemsize and also sets size to 0 
    EOarray *array = eo_array_New(capacity, sizeof(eOsk_candata_t), nv->ram);
}


extern void eoprot_fun_UPDT_sk_skin_config_sigmode(const EOnv* nv, const eOropdescriptor_t* rd)
{
    eOresult_t                      res;
    uint8_t                         i;
    eOsk_skinId_t                   skId = eoprot_ID2index(rd->id32);
    eOsk_sigmode_t                  *sigmode = (eOsk_sigmode_t*)nv->ram;
    EOappCanSP                      *appCanSP_ptr = eo_emsapplBody_GetCanServiceHandle(eo_emsapplBody_GetHandle());
    eOappTheDB_cfg_skinInfo_t       *skconfig_ptr = NULL;
    uint8_t                         boardEndAddr;
    eOicubCanProto_msgDestination_t msgdest;
    
    
    
    res = eo_appTheDB_GetSkinConfigPtr(eo_appTheDB_GetHandle(), skId,  &skconfig_ptr);
    if(eores_OK != res)
    {
        return;
    }
            
    boardEndAddr = skconfig_ptr->boardAddrStart + skconfig_ptr->numofboards;
    
   
    switch(*sigmode)
    {
        case eosk_sigmode_dontsignal:
        {
            //in old way it not exist
            //in new way:
            icubCanProto_as_sigmode_t sigmode = icubCanProto_as_sigmode_dontsignal;
            
            for(i=skconfig_ptr->boardAddrStart; i<boardEndAddr; i++)
            {
                msgdest.dest = ICUBCANPROTO_MSGDEST_CREATE(0, i);
                eOicubCanProto_msgCommand_t   msgCmd = 
                {
                    EO_INIT(.class) icubCanProto_msgCmdClass_pollingAnalogSensor,
                    EO_INIT(.cmdId) ICUBCANPROTO_POL_AS_CMD__SET_TXMODE
                };
                res = eo_appCanSP_SendCmd(appCanSP_ptr, skconfig_ptr->connected2emsport, msgdest, msgCmd,  &sigmode);
                if(eores_OK != res)
                {
                    return;
                }
            }
        } break;
        
        case eosk_sigmode_signal:
        {
            icubCanProto_as_sigmode_t sigmode = icubCanProto_as_sigmode_signal;
            
            for(i=skconfig_ptr->boardAddrStart; i<boardEndAddr; i++)
            {
                msgdest.dest = ICUBCANPROTO_MSGDEST_CREATE(0, i);
                eOicubCanProto_msgCommand_t   msgCmd = 
                {
                    EO_INIT(.class) icubCanProto_msgCmdClass_pollingAnalogSensor,
                    EO_INIT(.cmdId) ICUBCANPROTO_POL_AS_CMD__SET_TXMODE
                };
                res = eo_appCanSP_SendCmd(appCanSP_ptr, skconfig_ptr->connected2emsport, msgdest, msgCmd,  &sigmode);
                if(eores_OK != res)
                {
                    return;
                }
            }
        } break;

        case eosk_sigmode_signal_oldway:
        {
            eOicubCanProto_msgCommand_t msgCmd = 
            {
                EO_INIT(.class) icubCanProto_msgCmdClass_skinBoard,
                EO_INIT(.cmdId) ICUBCANPROTO_POL_SK_CMD__TACT_SETUP
            };
            
            for(i=skconfig_ptr->boardAddrStart; i<boardEndAddr; i++)
            {
                
                msgdest.dest = ICUBCANPROTO_MSGDEST_CREATE(0, i);
                res = eo_appCanSP_SendCmd(appCanSP_ptr, skconfig_ptr->connected2emsport, msgdest, msgCmd, NULL);
                if(eores_OK != res)
                {
                    return;
                }
                
                if(0xE == i)
                {
                    eOicubCanProto_msgCommand_t msgCmd2 = 
                    {
                        EO_INIT(.class) icubCanProto_msgCmdClass_skinBoard,
                        EO_INIT(.cmdId) ICUBCANPROTO_POL_SK_CMD__TACT_SETUP2
                    };
                    
                    res = eo_appCanSP_SendCmd(appCanSP_ptr, skconfig_ptr->connected2emsport, msgdest, msgCmd2, NULL);
                    if(eores_OK != res)
                    {
                        return;
                    }
                }
            }
        } break;
        
        default:
        {
        } break;
    }

}



extern void eoprot_fun_UPDT_sk_skin_cmmnds_boardscfg(const EOnv* nv, const eOropdescriptor_t* rd)
{
    eOresult_t                      res;
    uint8_t                         i;
    eOsk_skinId_t                   skId = eoprot_ID2index(rd->id32);
    eOsk_cmd_boardsCfg_t            *brdCfg = (eOsk_cmd_boardsCfg_t*)nv->ram;
    EOappCanSP                      *appCanSP_ptr = eo_emsapplBody_GetCanServiceHandle(eo_emsapplBody_GetHandle());
    eOappTheDB_cfg_skinInfo_t       *skconfig_ptr = NULL;
    eOicubCanProto_msgDestination_t msgdest;
    icubCanProto_skinboard_config_t canProto_skcfg;
    
    eOicubCanProto_msgCommand_t msgCmd = 
    {
        EO_INIT(.class) icubCanProto_msgCmdClass_skinBoard,
        EO_INIT(.cmdId) ICUBCANPROTO_POL_SK_CMD__SET_BRD_CFG
    };
    
    res = eo_appTheDB_GetSkinConfigPtr(eo_appTheDB_GetHandle(), skId,  &skconfig_ptr);
    if(eores_OK != res)
    {
        return;
    }

    
    canProto_skcfg.skintype = (icubCanProto_skinType_t)brdCfg->cfg.skintype; // the cast is safe as there are the asserts above
    canProto_skcfg.period   = brdCfg->cfg.period;
    canProto_skcfg.noload   = brdCfg->cfg.noload;
    
    for(i = brdCfg->addrstart; i<=brdCfg->addrend; i++ )
    {
        msgdest.dest = ICUBCANPROTO_MSGDEST_CREATE(0, i);
        res = eo_appCanSP_SendCmd(appCanSP_ptr, skconfig_ptr->connected2emsport, msgdest, msgCmd,  &canProto_skcfg);
        if(eores_OK != res)
        {
            return;
        }
    }

}


extern void eoprot_fun_UPDT_sk_skin_cmmnds_trianglescfg(const EOnv* nv, const eOropdescriptor_t* rd)
{
    eOresult_t                          res;
    eOsk_skinId_t                       skId = eoprot_ID2index(rd->id32);
    eOsk_cmd_trianglesCfg_t             *trgsCfg = (eOsk_cmd_trianglesCfg_t*)nv->ram;
    EOappCanSP                          *appCanSP_ptr = eo_emsapplBody_GetCanServiceHandle(eo_emsapplBody_GetHandle());
    eOappTheDB_cfg_skinInfo_t           *skconfig_ptr = NULL;
    eOappTheDB_cfg_skinInfo_t           **prova = NULL;
    eOicubCanProto_msgDestination_t     msgdest;
    icubCanProto_skintriangles_config_t canProto_trgscfg;
    
    eOicubCanProto_msgCommand_t msgCmd = 
    {
        EO_INIT(.class) icubCanProto_msgCmdClass_skinBoard,
        EO_INIT(.cmdId) ICUBCANPROTO_POL_SK_CMD__SET_TRIANG_CFG
    };

    prova = &skconfig_ptr;
    prova = prova;
    res = eo_appTheDB_GetSkinConfigPtr(eo_appTheDB_GetHandle(), skId,  &skconfig_ptr);
    if(eores_OK != res)
    {
        return;
    }
    
    
    canProto_trgscfg.idstart   = trgsCfg->idstart;
    canProto_trgscfg.idend     = trgsCfg->idend;
    canProto_trgscfg.flags     = trgsCfg->cfg.enable;
    canProto_trgscfg.shift     = trgsCfg->cfg.shift;
    canProto_trgscfg.CDCoffset = trgsCfg->cfg.CDCoffset;

    

    msgdest.dest = ICUBCANPROTO_MSGDEST_CREATE(0, trgsCfg->boardaddr);

    res = eo_appCanSP_SendCmd(appCanSP_ptr, skconfig_ptr->connected2emsport, msgdest, msgCmd,  &canProto_trgscfg);
    if(eores_OK != res)
    {
        return;
    }

}

// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------




// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------




// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------



