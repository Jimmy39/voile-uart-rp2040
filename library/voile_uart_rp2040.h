#ifndef __VOILE_UART_RP2040_H__
#define __VOILE_UART_RP2040_H__

#include "voile_interface_uart.h"
#include "voile_register_rp2040.h"
#include "hardware/clocks.h"

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/uart.h"

#include "hardware/structs/uart.h"
#include "hardware/resets.h"
#include "hardware/timer.h"

#include "pico/assert.h"
#include "pico.h"


#include "pico/stdlib.h"
#include "hardware/uart.h"
/**
 * @brief Class for hardware UART in rp2040
 * 
 */
typedef const struct{
    voile_const_uart_Operate_t *Operate;    ///< Operate the uart
    voile_const_uart_Get_t *Get;            ///< Get date or status from uart
    voile_register_rp2040_UART_t *uartId;   ///< UART0_voile or UART1_voile
    uint8_t txdPin;
    uint8_t rxdPin;
} voile_const_internal_uart_rp2040_t;

#define UART0_voile ((voile_register_rp2040_UART_t *)_u(0x40034000))
#define UART1_voile ((voile_register_rp2040_UART_t *)_u(0x40038000))

extern voile_const_uart_Operate_t voile_const_uart_Operate_rp2040;
extern voile_const_uart_Get_t voile_const_uart_Get_rp2040;

#define VOILE_UART_RP2040_FUNCINIT  \
    .Operate = &voile_const_uart_Operate_rp2040,    \
    .Get = &voile_const_uart_Get_rp2040




static inline uint8_t uart_rp2040_Get_Receive(voile_const_internal_uart_rp2040_t *uart_p) {
    uart_inst_t *uart = ((uart_inst_t *)(uart_p->uartId) == uart0 ? uart0 : uart1);
    uint8_t value;
    uart_read_blocking(uart, &value, 1);
    return value;
}


static inline bool uart_rp2040_Get_IsWritable(voile_const_internal_uart_rp2040_t *uart_p) {
    return !(uart_p->uartId->UARTFR.slectBit.TXFF);
}


voile_status_t uart_rp2040_Operate_Init(voile_const_internal_uart_rp2040_t *, uint32_t);

voile_status_t voile_uart_rp2040_Operate_SetBaudrate(voile_const_internal_uart_rp2040_t *, uint32_t);

static inline voile_status_t uart_rp2040_Operate_Transmit(voile_const_internal_uart_rp2040_t *uart_p, uint8_t value) {
    while (!uart_rp2040_Get_IsWritable(uart_p));
    uart_p->uartId->UARTDR.allBits = value;
    return success;
}

static inline voile_status_t uart_rp2040_Operate_Receive(voile_const_internal_uart_rp2040_t *uart_p, uint8_t *value) {
    uart_inst_t *uart = ((uart_inst_t *)(uart_p->uartId) == uart0 ? uart0 : uart1);
    uart_read_blocking(uart, value, 1);
    return success;
}

#endif // !__VOILE_UART_RP2040_H
