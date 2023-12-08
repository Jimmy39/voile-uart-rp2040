#include "voile_uart_rp2040.h"


voile_const_uart_Operate_t voile_const_uart_Operate_rp2040 = {
    .Init = (voile_status_t (*)(const void *, uint32_t))uart_rp2040_Operate_Init,
    .Receive = (voile_status_t (*)(const void *, uint8_t *))uart_rp2040_Operate_Receive,
    .Transmit = (voile_status_t (*)(const void *, uint8_t))uart_rp2040_Operate_Transmit
};

voile_const_uart_Get_t voile_const_uart_Get_rp2040 = {
    .Receive = (uint8_t (*)(const void *))uart_rp2040_Get_Receive,
    .IsWriteable = (bool (*)(const void *))uart_rp2040_Get_IsWritable,
    .IsReadable = (bool (*)(const void *))uart_rp2040_Get_IsReadable
};


static voile_status_t uart_rp2040_Operate_Init(voile_const_internal_uart_rp2040_t *uart_p, uint32_t baudrate){
    uart_inst_t *uart = ((uart_inst_t *)uart_p->uartId);
    uint32_t cr_save;
    voile_status_t status = success;
    if (uart_p->uartId == UART0_voile){
        voile_rp2040_RESETS_MuskSet->RESET.allBits = 1ul<<22;
        voile_rp2040_RESETS_MuskClear->RESET.allBits = 1ul<<22;
        while (!voile_rp2040_RESETS->RESET_DONE.selectBit.UART0);
    }
    else if (uart_p->uartId == UART1_voile){
        voile_rp2040_RESETS_MuskSet->RESET.allBits = 1ul<<23;
        voile_rp2040_RESETS_MuskClear->RESET.allBits = 1ul<<23;
        while (!voile_rp2040_RESETS->RESET_DONE.selectBit.UART1);
    }
    else{
        return hardwareUnsupportedError;
    }
      
    // PL011 needs a (dummy) LCR_H write to latch in the divisors.
    // Any LCR writes need to take place before enabling the UART. 
    if (baudrate > 8 * clock_get_hz(clk_peri) / (1ul << 7)){
        uart_p->uartId->UARTIBRD = 1;
        uart_p->uartId->UARTFBRD = 0;
        status = hardwareUnsupportedError;
    } 
    else if (baudrate < 8 * clock_get_hz(clk_peri) / (65535ul << 7)) {
        uart_p->uartId->UARTIBRD = 65535;
        uart_p->uartId->UARTFBRD = 0;
        status = hardwareUnsupportedError;
    }
    else {
        uart_p->uartId->UARTIBRD = (8 * clock_get_hz(clk_peri) / baudrate)>>7;
        uart_p->uartId->UARTFBRD = (((8 * clock_get_hz(clk_peri) / baudrate) & 0x7f) + 1) / 2;
    }
    uart_set_format(uart, 8, 1, UART_PARITY_NONE);
 
    // (Potentially) Cleanly handle disabling the UART before touching LCR
    cr_save = uart_p->uartId->UARTCR.allBits;
    if (uart_p->uartId->UARTCR.selectBit.UARTEN) {
        voile_rp2040_UART_MuskClear(uart_p->uartId)->UARTCR.allBits = 1ul<<0 | 1ul<<8 | 1ul<<9;

        // Note: Maximise precision here. Show working, the compiler will mop this up.
        // Create a 16.6 fixed-point fractional division ratio; then scale to 32-bits.
        // 3662 is ~(15 * 244.14) where 244.14 is 16e6 / 2^16
        busy_wait_us((((uart_p->uartId->UARTIBRD<<6) + uart_p->uartId->UARTFBRD)<<10) * 3662ul / clock_get_hz(clk_peri));
    }
    uart_p->uartId->UARTLCR_H.selectBit.WLEN = 8u - 5u;
    uart_p->uartId->UARTLCR_H.selectBit.STP2 = 1u - 1u;
    uart_p->uartId->UARTLCR_H.selectBit.PEN = 0;
    
    // Enable FIFOs (must be before setting UARTEN, as this is an LCR access)
    uart_p->uartId->UARTLCR_H.selectBit.FEN = 1;

    uart_p->uartId->UARTCR.allBits = cr_save;
    // Enable the UART, both TX and RX
    voile_rp2040_UART_MuskSet(uart_p->uartId)->UARTCR.allBits = 1ul<<0 | 1ul<<8 | 1ul<<9;

    // Always enable DREQ signals -- no harm in this if DMA is not listening
    uart_p->uartId->UARTDMACR.allBits = 1ul<<0 | 1ul<<1;
    voile_rp2040_PADS_BANK0->GPIO[uart_p->txdPin].selectBit.OD = 0;
    voile_rp2040_PADS_BANK0->GPIO[uart_p->txdPin].selectBit.IE = 1;
    voile_rp2040_IO_BANK0->GPIO[uart_p->txdPin].CTRL.allBits = 2u;
    voile_rp2040_PADS_BANK0->GPIO[uart_p->rxdPin].selectBit.OD = 0;
    voile_rp2040_PADS_BANK0->GPIO[uart_p->rxdPin].selectBit.IE = 1;
    voile_rp2040_IO_BANK0->GPIO[uart_p->rxdPin].CTRL.allBits = 2u;

    return status;
}
