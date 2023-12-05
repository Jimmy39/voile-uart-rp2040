#include "voile_uart_rp2040.h"


voile_const_uart_Operate_t voile_const_uart_Operate_rp2040 = {
    .Init = (voile_status_t (*)(const void *, uint32_t))uart_rp2040_Operate_Init,
    .Receive = (voile_status_t (*)(const void *, uint8_t *))uart_rp2040_Operate_Receive,
    .Transmit = (voile_status_t (*)(const void *, uint8_t))uart_rp2040_Operate_Transmit
};

voile_const_uart_Get_t voile_const_uart_Get_rp2040 = {
    .Receive = (uint8_t (*)(const void *))uart_rp2040_Get_Receive,
    .IsWriteable = (bool (*)(const void *))uart_rp2040_Get_IsWritable
};


voile_status_t uart_rp2040_Operate_Init(voile_const_internal_uart_rp2040_t *uart_p, uint32_t baudrate){
    uart_inst_t *uart = ((uart_inst_t *)uart_p->uartId);
    if (uart_p->uartId == UART0_voile){
        voile_rp2040_RESETS_MuskSet->RESET.allBits = 1ul<<22;
        voile_rp2040_RESETS_MuskClear->RESET.allBits = 1ul<<22;
        while (!voile_rp2040_RESETS->RESET_DONE.slectBit.UART0);
    }
    else if (uart_p->uartId == UART1_voile){
        voile_rp2040_RESETS_MuskSet->RESET.allBits = 1ul<<23;
        voile_rp2040_RESETS_MuskClear->RESET.allBits = 1ul<<23;
        while (!voile_rp2040_RESETS->RESET_DONE.slectBit.UART1);
    }
    else{
        return hardwareUnsupportedError;
    }
    // Any LCR writes need to take place before enabling the UART
    uart_set_baudrate(uart, baudrate);
    uart_set_format(uart, 8, 1, UART_PARITY_NONE);

    // Enable FIFOs (must be before setting UARTEN, as this is an LCR access)
    hw_set_bits(&uart_get_hw(uart)->lcr_h, UART_UARTLCR_H_FEN_BITS);
    // Enable the UART, both TX and RX
    uart_get_hw(uart)->cr = UART_UARTCR_UARTEN_BITS | UART_UARTCR_TXE_BITS | UART_UARTCR_RXE_BITS;
    // Always enable DREQ signals -- no harm in this if DMA is not listening
    uart_get_hw(uart)->dmacr = UART_UARTDMACR_TXDMAE_BITS | UART_UARTDMACR_RXDMAE_BITS;
    gpio_set_function(uart_p->txdPin , GPIO_FUNC_UART);
    gpio_set_function(uart_p->rxdPin , GPIO_FUNC_UART);
    return success;
}

voile_status_t voile_uart_rp2040_Operate_SetBaudrate(voile_const_internal_uart_rp2040_t *uart_p, uint32_t baudrate){
    uint32_t baud_rate_div = (8 * clock_get_hz(clk_peri) / baudrate);
    uint32_t baud_ibrd = baud_rate_div >> 7;
    uint32_t baud_fbrd;
    if (baudrate == 0){
        return inputRangeError;
    }
    if (baud_ibrd == 0) {
        baud_ibrd = 1;
        baud_fbrd = 0;
    } else if (baud_ibrd >= 65535) {
        baud_ibrd = 65535;
        baud_fbrd = 0;
    }  else {
        baud_fbrd = ((baud_rate_div & 0x7f) + 1) / 2;
    }
}