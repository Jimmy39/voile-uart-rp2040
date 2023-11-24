#include "voile_uart_rp2040.h"


voile_const_uart_Operate_t voile_const_uart_Operate_rp2040 = {
    .Init = (voile_status_t (*)(const void *, uint32_t))uart_rp2040_Operate_Init,
    .Receive = (voile_status_t (*)(const void *, uint8_t *))uart_rp2040_Operate_Receive,
    .Transmit = (voile_status_t (*)(const void *, uint8_t))uart_rp2040_Operate_Transmit
};

voile_const_uart_Get_t voile_const_uart_Get_rp2040 = {
    .Receive = (uint8_t (*)(const void *))uart_rp2040_Get_Receive
};

/// \tag::uart_reset[]
static inline void uart_reset(uart_inst_t *uart) {
    invalid_params_if(UART, uart != uart0 && uart != uart1);
    reset_block(uart_get_index(uart) ? RESETS_RESET_UART1_BITS : RESETS_RESET_UART0_BITS);
}

static inline void uart_unreset(uart_inst_t *uart) {
    invalid_params_if(UART, uart != uart0 && uart != uart1);
    unreset_block_wait(uart_get_index(uart) ? RESETS_RESET_UART1_BITS : RESETS_RESET_UART0_BITS);
}

voile_status_t uart_rp2040_Operate_Init(voile_const_internal_uart_rp2040_t *uart_p, uint32_t baudrate){
    uart_inst_t *uart = (uart_p->uartId == 0 ? uart0 : uart1);
    uart_reset(uart);
    uart_unreset(uart);

#if PICO_UART_ENABLE_CRLF_SUPPORT
    uart_set_translate_crlf(uart, PICO_UART_DEFAULT_CRLF);
#endif

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