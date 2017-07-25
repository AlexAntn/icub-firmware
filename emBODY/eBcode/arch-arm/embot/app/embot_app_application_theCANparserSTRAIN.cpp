/*
 * Copyright (C) 2017 iCub Facility - Istituto Italiano di Tecnologia
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


// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "embot_app_application_theCANparserSTRAIN.h"



// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "embot.h"

#include <new>

#include "embot_hw.h"
#include "embot_app_canprotocol.h"

#include "embot_app_theCANboardInfo.h"

#include "embot_app_application_theSTRAIN.h"


// --------------------------------------------------------------------------------------------------------------------
// - pimpl: private implementation (see scott meyers: item 22 of effective modern c++, item 31 of effective c++
// --------------------------------------------------------------------------------------------------------------------


struct embot::app::application::theCANparserSTRAIN::Impl
{    
    Config config;
        
    bool txframe;
    bool recognised;
    
    embot::app::canprotocol::Clas cls;
    std::uint8_t cmd;    
    std::uint8_t canaddress;
        
    embot::hw::can::Frame reply;
    

    Impl() 
    {   
        recognised = false;        
        txframe = false;
        cls = embot::app::canprotocol::Clas::none;
        cmd = 0;        
        canaddress = 0;        
    }
    
   
    bool process(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    
    
//    bool process_set_brdcfg(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);   
//    bool process_set_trgcfg(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);      
    bool process_set_txmode(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_set_serial(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_serial(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_set_candatarate(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_set_fullscales(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_fullscales(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_eeprom_status(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);    
    bool process_save2ee(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_ch_adc(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_set_offset(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_offset(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);       
    bool process_set_matrix_value(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_matrix_value(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);     
    bool process_set_matrix_gain(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_matrix_gain(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_set_calib_bias(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_calib_bias(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies); 
    bool process_set_curr_bias(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_curr_bias(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies); 
    bool process_set_amp_gain(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);
    bool process_get_amp_gain(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies);      
};


bool embot::app::application::theCANparserSTRAIN::Impl::process(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    txframe = false;
    recognised = false;
    
    if(false == embot::app::canprotocol::frameis4board(frame, canaddress))
    {
        recognised = false;
        return recognised;
    }
        
    // now get cls and cmd
    cls = embot::app::canprotocol::frame2clas(frame);
    cmd = embot::app::canprotocol::frame2cmd(frame);
    
    
    // the basic can handle only some messages ...
    
    switch(cls)
    {
        
        case embot::app::canprotocol::Clas::pollingAnalogSensor:
        {
            // only embot::app::canprotocol::aspollCMD::SKIN_SET_BRD_CFG, SKIN_SET_TRIANG_CFG, SET_TXMODE            
            if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_TXMODE) == cmd)
            {
                txframe = process_set_txmode(frame, replies);
                recognised = true;
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_SERIAL_NO) == cmd)
            { 
                txframe = process_set_serial(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_SERIAL_NO) == cmd)
            { 
                txframe = process_get_serial(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_CANDATARATE) == cmd)
            { 
                txframe = process_set_candatarate(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_FULL_SCALES) == cmd)
            { 
                txframe = process_get_fullscales(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_FULL_SCALES) == cmd)
            { 
                txframe = process_set_fullscales(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_EEPROM_STATUS) == cmd)
            { 
                txframe = process_get_eeprom_status(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SAVE2EE) == cmd)
            { 
                txframe = process_save2ee(frame, replies);
                recognised = true;                
            } 
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_CH_ADC) == cmd)
            { 
                txframe = process_get_ch_adc(frame, replies);
                recognised = true;                
            }  
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_CH_DAC_offset) == cmd)
            { 
                txframe = process_get_offset(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_CH_DAC_offset) == cmd)
            { 
                txframe = process_set_offset(frame, replies);
                recognised = true;                
            }    
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_MATRIX_RC) == cmd)
            { 
                txframe = process_get_matrix_value(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_MATRIX_RC) == cmd)
            { 
                txframe = process_set_matrix_value(frame, replies);
                recognised = true;                
            } 
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_MATRIX_G) == cmd)
            { 
                txframe = process_get_matrix_gain(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_MATRIX_G) == cmd)
            { 
                txframe = process_set_matrix_gain(frame, replies);
                recognised = true;                
            }    
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_CALIB_TARE_bias) == cmd)
            { 
                txframe = process_get_calib_bias(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_CALIB_TARE_bias) == cmd)
            { 
                txframe = process_set_calib_bias(frame, replies);
                recognised = true;                
            }              
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_CURR_TARE_bias) == cmd)
            { 
                txframe = process_get_curr_bias(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_CURR_TARE_bias) == cmd)
            { 
                txframe = process_set_curr_bias(frame, replies);
                recognised = true;                
            } 
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::GET_AMP_GAIN) == cmd)
            { 
                txframe = process_get_amp_gain(frame, replies);
                recognised = true;                
            }
            else if(static_cast<std::uint8_t>(embot::app::canprotocol::aspollCMD::SET_AMP_GAIN) == cmd)
            { 
                txframe = process_set_amp_gain(frame, replies);
                recognised = true;                
            }  
        } break;

        
        default:
        {
            txframe = false;
            recognised = false;
        } break;
    }    
    
    
    return recognised;
}




//bool embot::app::application::theCANparserSTRAIN::Impl::process_set_brdcfg(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
//{
//    embot::app::canprotocol::Message_aspoll_SKIN_SET_BRD_CFG msg;
//    msg.load(frame);
//      
//    embot::app::application::theSkin &theskin = embot::app::application::theSkin::getInstance();    
//    theskin.configure(msg.info);
//            
//    return msg.reply();        
//}


//bool embot::app::application::theCANparserSTRAIN::Impl::process_set_trgcfg(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
//{
//    embot::app::canprotocol::Message_aspoll_SKIN_SET_TRIANG_CFG msg;
//    msg.load(frame);
//      
//    embot::app::application::theSkin &theskin = embot::app::application::theSkin::getInstance();    
//    theskin.configure(msg.info);
//    
//    return msg.reply();        
//}


//bool embot::app::application::theCANparserSTRAIN::Impl::process_set_accgyrosetup(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
//{
//    embot::app::canprotocol::Message_aspoll_ACC_GYRO_SETUP msg;
//    msg.load(frame);
//      
//    embot::app::application::theIMU &theimu = embot::app::application::theIMU::getInstance();    
//    theimu.configure(msg.info);
//    
//    return msg.reply();        
//}


bool embot::app::application::theCANparserSTRAIN::Impl::process_set_txmode(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_TXMODE msg(embot::app::canprotocol::Board::strain2);
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    if(true == msg.info.transmit)
    {
        thestrain.start();        
    }
    else
    {
        thestrain.stop();     
    }
                  
    return msg.reply();        
}


bool embot::app::application::theCANparserSTRAIN::Impl::process_set_serial(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_SERIAL_NO msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.configure(msg.info);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_serial(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_SERIAL_NO msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_SERIAL_NO::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.get_serial(replyinfo);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}


bool embot::app::application::theCANparserSTRAIN::Impl::process_set_candatarate(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_CANDATARATE msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.configure(msg.info.txperiod);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_set_fullscales(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_FULL_SCALES msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.configure(msg.info);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_fullscales(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_FULL_SCALES msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_FULL_SCALES::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    replyinfo.channel = msg.info.channel;
    thestrain.get_fullscale(msg.info.channel, replyinfo.fullscale);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_eeprom_status(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_EEPROM_STATUS msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_EEPROM_STATUS::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    

    thestrain.get_eepromstatus(replyinfo.saved);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}


bool embot::app::application::theCANparserSTRAIN::Impl::process_save2ee(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SAVE2EE msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    
    embot::app::canprotocol::Message_aspoll_SAVE2EE::ReplyInfo replyinfo;
    
    replyinfo.ok = thestrain.save2eeprom();
                  
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;       
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_ch_adc(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_CH_ADC msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_CH_ADC::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    replyinfo.channel = msg.info.channel;
    replyinfo.valueisraw = msg.info.getrawvalue;   

    thestrain.get_adc(replyinfo.channel, replyinfo.valueisraw, replyinfo.adcvalue);
    
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}


bool embot::app::application::theCANparserSTRAIN::Impl::process_set_offset(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_CH_DAC_offset msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.configure(msg.info);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_offset(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_CH_DAC_offset msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_CH_DAC_offset::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    replyinfo.channel = msg.info.channel;
    thestrain.get_offset(replyinfo.channel, replyinfo.offset);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}


bool embot::app::application::theCANparserSTRAIN::Impl::process_set_matrix_value(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_MATRIX_RC msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.set(msg.info);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_matrix_value(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_MATRIX_RC msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_MATRIX_RC::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    replyinfo.row = msg.info.row;
    replyinfo.col = msg.info.col;
    thestrain.get(replyinfo);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_set_matrix_gain(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_MATRIX_G msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.set(msg.info);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_matrix_gain(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_MATRIX_G msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_MATRIX_G::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.get(replyinfo);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}


bool embot::app::application::theCANparserSTRAIN::Impl::process_set_calib_bias(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_CALIB_TARE_bias msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.set(msg.info);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_calib_bias(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_CALIB_TARE_bias msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_CALIB_TARE_bias::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    replyinfo.channel = msg.info.channel;
    thestrain.get(replyinfo);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}


bool embot::app::application::theCANparserSTRAIN::Impl::process_set_curr_bias(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_CURR_TARE_bias msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.set(msg.info);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_curr_bias(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_CURR_TARE_bias msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_CURR_TARE_bias::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    replyinfo.channel = msg.info.channel;
    thestrain.get(replyinfo);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}


bool embot::app::application::theCANparserSTRAIN::Impl::process_set_amp_gain(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_SET_AMP_GAIN msg;
    msg.load(frame);
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    thestrain.set(msg.info);
                  
    return msg.reply();        
}

bool embot::app::application::theCANparserSTRAIN::Impl::process_get_amp_gain(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{
    embot::app::canprotocol::Message_aspoll_GET_AMP_GAIN msg;
    msg.load(frame);
    
    embot::app::canprotocol::Message_aspoll_GET_AMP_GAIN::ReplyInfo replyinfo;
    
    embot::app::application::theSTRAIN &thestrain = embot::app::application::theSTRAIN::getInstance();    
    
    replyinfo.channel = msg.info.channel;
    thestrain.get(replyinfo);
        
    embot::hw::can::Frame frame0;
    if(true == msg.reply(frame0, canaddress, replyinfo))
    {
        replies.push_back(frame0);
        return true;
    }        

    return false;    
}

// --------------------------------------------------------------------------------------------------------------------
// - the class
// --------------------------------------------------------------------------------------------------------------------



embot::app::application::theCANparserSTRAIN::theCANparserSTRAIN()
: pImpl(new Impl)
{       

}

   
        
bool embot::app::application::theCANparserSTRAIN::initialise(Config &config)
{
    pImpl->config = config;
    
    embot::app::theCANboardInfo &canbrdinfo = embot::app::theCANboardInfo::getInstance();
    
    // retrieve address
    pImpl->canaddress = canbrdinfo.getCANaddress();
    
    return true;
}
  


bool embot::app::application::theCANparserSTRAIN::process(const embot::hw::can::Frame &frame, std::vector<embot::hw::can::Frame> &replies)
{    
    return pImpl->process(frame, replies);
}





// - end-of-file (leave a blank line after)----------------------------------------------------------------------------


