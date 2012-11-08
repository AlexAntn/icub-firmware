  
// - include guard ----------------------------------------------------------------------------------------------------
#ifndef _HAL_BRDCFG_MCBSTMF400_H_
#define _HAL_BRDCFG_MCBSTMF400_H_

// - doxy begin -------------------------------------------------------------------------------------------------------

/* @file       hal_brdcfg_mcbstmf400.h
    @brief      This header file defines Interface Pins, eval-board depend macro and low level function prototypes.
    @author     valentina.gaggero@iit.it
    @date       10/09/2010
 **/

// - modules to be built: contains the HAL_USE_* macros ---------------------------------------------------------------
#include "hal_brdcfg_modules.h"

// - external dependencies --------------------------------------------------------------------------------------------

#include "hal_base.h"
#include "hal_stm32_gpio_hid.h"

#ifdef HAL_USE_CAN
    #include "hal_can.h"
#endif//HAL_USE_CAN

#ifdef HAL_USE_EEPROM
    #include "hal_eeprom.h"
    #include "hal_stm32_eeprom_hid.h" 
#endif//HAL_USE_EEPROM

#ifdef HAL_USE_ETH
    #include "hal_eth.h"
#endif//HAL_USE_ETH

#ifdef HAL_USE_GPIO
    #include "hal_gpio.h"
#endif//HAL_USE_GPIO

#ifdef HAL_USE_I2C
    #include "hal_stm32_i2c_hid.h"
#endif//HAL_USE_I2C

#ifdef HAL_USE_LED
    #include "hal_led.h"
#endif//HAL_USE_LED

#ifdef HAL_USE_SPI
    #include "hal_spi.h"
#endif//HAL_USE_SPI


#ifdef HAL_USE_SYS
    #include "hal_stm32_sys_hid.h"
#endif//HAL_USE_SYS

#ifdef HAL_USE_SPI4ENCODER
    #include "hal_spi4encoder.h" 
#endif//HAL_USE_SPI4ENCODER


#include "hal_stm32xx_include.h"



// - public #define  --------------------------------------------------------------------------------------------------



#ifdef HAL_USE_SPI4ENCODER
    #define HAL_BRDCFG_SPI4ENCODER__SPI1_GPIO_PORT_CS_CLOCK			RCC_APB2Periph_GPIOB
    #define HAL_BRDCFG_SPI4ENCODER__SPI2_GPIO_PORT_CS_CLOCK			RCC_APB2Periph_GPIOB
    #define HAL_BRDCFG_SPI4ENCODER__SPI3_GPIO_PORT_CS_CLOCK			RCC_APB2Periph_GPIOB  
#endif//HAL_USE_SPI4ENCODER



// - declaration of public user-defined types ------------------------------------------------------------------------- 
// empty-section

// - declaration of extern public variables, ... but better using use _get/_set instead -------------------------------

#ifdef HAL_USE_CAN
    extern const uint8_t hal_brdcfg_can__supported_mask;//             = 0x03;
    
//     extern const uint32_t hal_brdcfg_can__gpio_clock_canx_rx[];//      = {RCC_AHB1Periph_GPIOH, B};
//     extern const uint32_t hal_brdcfg_can__gpio_clock_canx_tx[];//      = {RCC_AHB1Periph_GPIOI, B};
//     extern const uint8_t hal_brdcfg_can__gpio_pinsource_canx_rx[];//   = {13, 5};
//     extern const uint8_t hal_brdcfg_can__gpio_pinsource_canx_tx[];//   = {9, 13};
//     extern const uint16_t hal_brdcfg_can__gpio_pin_canx_rx[];//        = {GPIO_Pin_13, GPIO_Pin_5};
//     extern const uint16_t hal_brdcfg_can__gpio_pin_canx_tx[];//        = {GPIO_Pin_9, GPIO_Pin_13};
//     extern GPIO_TypeDef* const hal_brdcfg_can__gpio_port_canx_rx[];//  = {GPIOH, GPIOB};
//     extern GPIO_TypeDef* const hal_brdcfg_can__gpio_port_canx_tx[];//  = {GPIOI, GPIOB}; 

    extern const hal_gpio_cfg_t hal_brdcfg_can__gpio_canx_rx[];
    extern const hal_gpio_cfg_t hal_brdcfg_can__gpio_canx_tx[];    
#endif//HAL_USE_CAN

#ifdef HAL_USE_CRC
    extern const uint8_t hal_brdcfg_crc__supported_mask; //            = 0x03;
#endif//HAL_USE_CRC

#ifdef HAL_USE_DISPLAY
    extern const uint8_t hal_brdcfg_display__supported_mask; //         = 0x00;
#endif//HAL_USE_DISPLAY

#ifdef HAL_USE_EEPROM
    extern const uint8_t hal_brdcfg_eeprom__supported_mask; //         = (1 << hal_eeprom_emulatedflash)||(1 << hal_eeprom_i2c_01);
    extern const uint32_t hal_brdcfg_eeprom__emflash_baseaddress;//    = 0x08000000;
    extern const uint32_t hal_brdcfg_eeprom__emflash_totalsize;//      = 256*1024;
    extern const uint32_t hal_brdcfg_eeprom__i2c_01_baseaddress;//     = 0;
    extern const uint32_t hal_brdcfg_eeprom__i2c_01_totalsize;//       = 8*1024;
    extern const hal_eeprom_hw_cfg_t hal_brdcfg_eeprom__i2c_01_device;
#endif//HAL_USE_EEPROM



#ifdef HAL_USE_ENCODER
    extern const uint32_t hal_brdcfg_encoder__supported_mask; //         = 0x01ff;
#endif//HAL_USE_ENCODER


#ifdef HAL_USE_ETH
    extern const uint8_t hal_brdcfg_eth__supported_mask; //         = 0x01;
    
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_RMII_REF_CLK;
    
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_RMII_TX_EN;
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_RMII_TXD0;
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_RMII_TXD1;
    
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_RMII_CRS_DV;
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_RMII_RXD0;
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_RMII_RXD1;  
    
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_MDC;
    extern const hal_gpio_cfg_t hal_brdcfg_eth__gpio_ETH_MDIO;    

    extern const hal_eth_phymode_t hal_brdcfg_eth__phymode;    
#endif//HAL_USE_ETH

#ifdef HAL_USE_GPIO
    extern const uint16_t hal_brdcfg_gpio__supported_mask[];
#endif//HAL_USE_GPIO


#ifdef HAL_USE_I2C
    extern const uint8_t hal_brdcfg_i2c__supported_mask;
    extern const hal_gpio_cfg_t hal_brdcfg_i2c__scl[];
    extern const hal_gpio_cfg_t hal_brdcfg_i2c__sda[]; 
    extern const hal_i2c_hw_cfg_t  hal_brdcfg_i2c__hwcfg;
#endif//HAL_USE_I2C


#ifdef HAL_USE_LED
    extern const hal_gpio_val_t hal_brdcfg_led__value_on;
    extern const hal_gpio_val_t hal_brdcfg_led__value_off;
    extern const uint8_t hal_brdcfg_led__supported_mask;
    extern const hal_gpio_cfg_t hal_brdcfg_led__cfg[];    
#endif//HAL_USE_LED 

#ifdef HAL_USE_SPI
    extern const uint8_t hal_brdcfg_spi__supported_mask;
    extern const hal_gpio_cfg_t hal_brdcfg_spi__miso[];
    extern const hal_gpio_cfg_t hal_brdcfg_spi__mosi[];
    extern const hal_gpio_cfg_t hal_brdcfg_spi__sck[];
#endif//HAL_USE_SPI

#ifdef HAL_USE_SPI4ENCODER
    extern const uint8_t hal_brdcfg_spi4encoder__supported_mask; 
#endif//HAL_USE_SPI4ENCODER

#ifdef  HAL_USE_SYS
    extern const hal_sys_hid_clock_cfg_t hal_brdcfg_sys__clockcfg;
#endif//HAL_USE_SYS            

#ifdef HAL_USE_SWITCH
    extern const hal_boolval_t hal_brdcfg_switch__supported;
#endif//HAL_USE_SWITCH

#ifdef HAL_USE_TIMER
    extern const uint8_t hal_brdcfg_timer__supported_mask;
#endif//HAL_USE_TIMER

#ifdef HAL_USE_WATCHDOG
    extern const uint8_t hal_brdcfg_watchdog__supported_mask;
#endif//HAL_USE_WATCHDOG



// - declaration of extern public functions ---------------------------------------------------------------------------

#ifdef HAL_USE_SYS
    extern void hal_brdcfg_sys__clock_config(void);
    extern void hal_brdcfg_sys__gpio_default_init(void);
#endif

#ifdef HAL_USE_CAN
    extern void hal_brdcfg_can__phydevices_init(hal_can_port_t port);
    extern void hal_brdcfg_can__phydevices_enable(hal_can_port_t port);
    extern void hal_brdcfg_can__phydevices_disable(hal_can_port_t port);
#endif//HAL_USE_CAN



#ifdef HAL_USE_EEPROM
    extern hal_result_t hal_brdcfg_eeprom__wp_init(void);
    extern hal_result_t hal_brdcfg_eeprom__wp_enable(void);
    extern hal_result_t hal_brdcfg_eeprom__wp_disable(void);
#endif//HAL_USE_EEPROM   


#ifdef HAL_USE_ETH  
    extern hal_bool_t hal_brdcfg_eth__phy_initialise(void);
    extern void hal_brdcfg_eth__phy_configure(hal_eth_phymode_t *phymode);
#endif//HAL_USE_ETH


#ifdef HAL_USE_I2C
    extern void hal_brdcfg_i2c__ontimeouterror(void);
#endif//HAL_USE_I2C 


#ifdef HAL_USE_SPI4ENCODER
    extern void hal_brdcfg_spi4encoder__chipSelect_init(hal_spi_port_t spix);
    extern void hal_brdcfg_spi4encoder__encoder_enable(hal_spi_port_t spix, hal_spi_mux_t e);
    extern void hal_brdcfg_spi4encoder__encoder_disable(hal_spi_port_t spix, hal_spi_mux_t e);  
#endif//HAL_USE_SPI4ENCODER


#ifdef HAL_USE_SWITCH  
    // but the swicth is not present in the mcbstm32c
    extern void hal_brdcfg_switch__MCO_config(void);
#endif//HAL_USE_SWITCH


#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------


