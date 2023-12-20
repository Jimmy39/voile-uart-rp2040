#ifndef __VOILE_UART_RP2040_H__
#define __VOILE_UART_RP2040_H__

#include "voile_interface_uart.h"
#include "voile_register_rp2040.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"


/**
 * @brief Class for hardware UART in rp2040
 * 
 */
typedef const struct{

    // The functions operate the uart
    voile_const_uart_Operate_t *Operate;

    // The functions get date or status from uart
    voile_const_uart_Get_t *Get;

    // UART0_voile or UART1_voile
    voile_rp2040_UART_t *uartId;

    // Pin number of TXD
    uint8_t txdPin;

    // Pin nubmer of RXD
    uint8_t rxdPin;

} voile_const_internal_uart_rp2040_t;


// uartId defination for UART0
#define UART0_voile ((voile_rp2040_UART_t *)_u(0x40034000))

// uartId defination for UART1
#define UART1_voile ((voile_rp2040_UART_t *)_u(0x40038000))


// The functions operate the uart
extern voile_const_uart_Operate_t voile_const_uart_Operate_rp2040;

// The functions get date or status from uart
extern voile_const_uart_Get_t voile_const_uart_Get_rp2040;


// This micro use to init all function 
#define VOILE_UART_RP2040_FUNCINIT  \
    .Operate = &voile_const_uart_Operate_rp2040,    \
    .Get = &voile_const_uart_Get_rp2040


/**
 * @brief Determine if transmit is available.
 * 
 * @param[in] name :[voile_const_internal_uart_rp2040_t *] This uart object.
 * @return [bool] True means transmit is available.
 * 
 */
static inline bool uart_rp2040_Get_IsWritable(voile_const_internal_uart_rp2040_t *uart_p) {
    return !(uart_p->uartId->UARTFR.selectBit.TXFF);
}

/**
 * @brief Determine if receive is available.
 * 
 * @param[in] name :[voile_const_internal_uart_rp2040_t *] This uart object.
 * @return [bool] True means receive is available.
 * 
 */
static inline bool uart_rp2040_Get_IsReadable(voile_const_internal_uart_rp2040_t *uart_p) {
    return !(uart_p->uartId->UARTFR.selectBit.RXFE);
}

/**
 * @brief Receive byte from uart.
 * 
 * @param[in] name :[voile_const_internal_uart_rp2040_t *] This uart object.
 * @return [uint8_t] Byte for receive.
 *  
 */
static inline uint8_t uart_rp2040_Get_Receive(voile_const_internal_uart_rp2040_t *uart_p) {
    while (!uart_rp2040_Get_IsReadable(uart_p));
    return (uint8_t)uart_p->uartId->UARTDR.allBits;
}

/**
 * @brief Initialise or reinitialise a uart, set baudrate.
 * 
 * @param[in] name :[voile_const_internal_uart_rp2040_t *] This uart object.
 * @param[in] baudrate :[uint32_t] Set buridrate.
 * @return voile_status_t defined in common.h
 * 
 */
static voile_status_t uart_rp2040_Operate_Init(voile_const_internal_uart_rp2040_t *, uint32_t);

/**
 * @brief Transmit byte by uart.
 * 
 * @param[in] name :[voile_const_internal_uart_rp2040_t *] This uart object.
 * @param[in] value :[uint8_t] Byte for transmit.
 * @return voile_status_t defined in common.h
 *  
 */
static inline voile_status_t uart_rp2040_Operate_Transmit(voile_const_internal_uart_rp2040_t *uart_p, uint8_t value) {
    while (!uart_rp2040_Get_IsWritable(uart_p));
    uart_p->uartId->UARTDR.allBits = value;
    return success;
}

/**
 * @brief Receive byte from uart.
 * 
 * @param[in] name :[voile_const_internal_uart_rp2040_t *] This uart object.
 * @param[out] value :[uint8_t *] Byte for receive.
 * @return voile_status_t defined in common.h
 *  
 */
static inline voile_status_t uart_rp2040_Operate_Receive(voile_const_internal_uart_rp2040_t *uart_p, uint8_t *value) {
    while (!uart_rp2040_Get_IsReadable(uart_p));
    *value = (uint8_t)uart_p->uartId->UARTDR.allBits;
    return success;
}

#endif // !__VOILE_UART_RP2040_H
