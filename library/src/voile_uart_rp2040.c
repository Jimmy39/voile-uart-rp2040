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
    voile_uart_rp2040_Operate_SetBaudrate(uart_p, baudrate);
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
static uint32_t uart_disable_before_lcr_write(uart_inst_t *uart) {
    // Notes from PL011 reference manual:
    //
    // - Before writing the LCR, if the UART is enabled it needs to be
    //   disabled and any current TX + RX activity has to be completed
    //
    // - There is a BUSY flag which waits for the current TX char, but this is
    //   OR'd with TX FIFO !FULL, so not usable when FIFOs are enabled and
    //   potentially nonempty
    //
    // - FIFOs can't be set to disabled whilst a character is in progress
    //   (else "FIFO integrity is not guaranteed")
    //
    // Combination of these means there is no general way to halt and poll for
    // end of TX character, if FIFOs may be enabled. Either way, there is no
    // way to poll for end of RX character.
    //
    // So, insert a 15 Baud period delay before changing the settings.
    // 15 Baud is comfortably higher than start + max data + parity + stop.
    // Anything else would require API changes to permit a non-enabled UART
    // state after init() where settings can be changed safely.
    uint32_t cr_save = uart_get_hw(uart)->cr;

    if (cr_save & UART_UARTCR_UARTEN_BITS) {
        hw_clear_bits(&uart_get_hw(uart)->cr,
            UART_UARTCR_UARTEN_BITS | UART_UARTCR_TXE_BITS | UART_UARTCR_RXE_BITS);

        uint32_t current_ibrd = uart_get_hw(uart)->ibrd;
        uint32_t current_fbrd = uart_get_hw(uart)->fbrd;

        // Note: Maximise precision here. Show working, the compiler will mop this up.
        // Create a 16.6 fixed-point fractional division ratio; then scale to 32-bits.
        uint32_t brdiv_ratio = 64u * current_ibrd + current_fbrd;
        brdiv_ratio <<= 10;
        // 3662 is ~(15 * 244.14) where 244.14 is 16e6 / 2^16
        uint32_t scaled_freq = clock_get_hz(clk_peri) / 3662ul;
        uint32_t wait_time_us = brdiv_ratio / scaled_freq;
        busy_wait_us(wait_time_us);
    }

    return cr_save;
}
static void uart_write_lcr_bits_masked(uart_inst_t *uart, uint32_t values, uint32_t write_mask) {
    invalid_params_if(UART, uart != uart0 && uart != uart1);

    // (Potentially) Cleanly handle disabling the UART before touching LCR
    uint32_t cr_save = uart_disable_before_lcr_write(uart);

    hw_write_masked(&uart_get_hw(uart)->lcr_h, values, write_mask);

    uart_get_hw(uart)->cr = cr_save;
}
voile_status_t voile_uart_rp2040_Operate_SetBaudrate(voile_const_internal_uart_rp2040_t *uart_p, uint32_t baudrate){
    if (baudrate > 8 * clock_get_hz(clk_peri) / (1ul << 7)){
        uart_p->uartId->UARTIBRD = 1;
        uart_p->uartId->UARTFBRD = 0;
        uart_write_lcr_bits_masked(uart_p->uartId, 0, 0);
        return inputRangeError;
    } 
    else if (baudrate < 8 * clock_get_hz(clk_peri) / (65535ul << 7)) {
        uart_p->uartId->UARTIBRD = 65535;
        uart_p->uartId->UARTFBRD = 0;
        uart_write_lcr_bits_masked(uart_p->uartId, 0, 0);
        return inputRangeError;
    }
    else {
        uart_p->uartId->UARTIBRD = (8 * clock_get_hz(clk_peri) / baudrate)>>7;
        uart_p->uartId->UARTFBRD = (((8 * clock_get_hz(clk_peri) / baudrate) & 0x7f) + 1) / 2;
    }
    uart_write_lcr_bits_masked(uart_p->uartId, 0, 0);
    return success;
}
