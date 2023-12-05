#ifndef __VOILE_REGISTER_RP2040_H__
#define __VOILE_REGISTER_RP2040_H__

#include "voile_common.h"

typedef volatile uint32_t io_rw_32;
typedef const volatile uint32_t io_ro_32;
typedef volatile uint32_t io_wo_32;
typedef volatile uint16_t io_rw_16;
typedef const volatile uint16_t io_ro_16;
typedef volatile uint16_t io_wo_16;
typedef volatile uint8_t io_rw_8;
typedef const volatile uint8_t io_ro_8;
typedef volatile uint8_t io_wo_8;

#define _REG_(x)

typedef struct { 
    // Reset control
    // 0x01000000 [24]    : usbctrl (1)
    // 0x00800000 [23]    : UART1 (1)
    // 0x00400000 [22]    : UART0 (1)
    // 0x00200000 [21]    : timer (1)
    // 0x00100000 [20]    : tbman (1)
    // 0x00080000 [19]    : sysinfo (1)
    // 0x00040000 [18]    : syscfg (1)
    // 0x00020000 [17]    : spi1 (1)
    // 0x00010000 [16]    : spi0 (1)
    // 0x00008000 [15]    : rtc (1)
    // 0x00004000 [14]    : pwm (1)
    // 0x00002000 [13]    : pll_usb (1)
    // 0x00001000 [12]    : pll_sys (1)
    // 0x00000800 [11]    : pio1 (1)
    // 0x00000400 [10]    : pio0 (1)
    // 0x00000200 [9]     : pads_qspi (1)
    // 0x00000100 [8]     : pads_bank0 (1)
    // 0x00000080 [7]     : jtag (1)
    // 0x00000040 [6]     : io_qspi (1)
    // 0x00000020 [5]     : io_bank0 (1)
    // 0x00000010 [4]     : i2c1 (1)
    // 0x00000008 [3]     : i2c0 (1)
    // 0x00000004 [2]     : dma (1)
    // 0x00000002 [1]     : busctrl (1)
    // 0x00000001 [0]     : adc (1)
    union {
        io_rw_32 allBits;
        struct {
            io_rw_32 unused0 : 22;
            io_rw_32 UART0 : 1;
            io_rw_32 UART1 : 1;
        } slectBit;
    } RESET;    
    // Watchdog select
    // 0x01000000 [24]    : usbctrl (0)
    // 0x00800000 [23]    : uart1 (0)
    // 0x00400000 [22]    : uart0 (0)
    // 0x00200000 [21]    : timer (0)
    // 0x00100000 [20]    : tbman (0)
    // 0x00080000 [19]    : sysinfo (0)
    // 0x00040000 [18]    : syscfg (0)
    // 0x00020000 [17]    : spi1 (0)
    // 0x00010000 [16]    : spi0 (0)
    // 0x00008000 [15]    : rtc (0)
    // 0x00004000 [14]    : pwm (0)
    // 0x00002000 [13]    : pll_usb (0)
    // 0x00001000 [12]    : pll_sys (0)
    // 0x00000800 [11]    : pio1 (0)
    // 0x00000400 [10]    : pio0 (0)
    // 0x00000200 [9]     : pads_qspi (0)
    // 0x00000100 [8]     : pads_bank0 (0)
    // 0x00000080 [7]     : jtag (0)
    // 0x00000040 [6]     : io_qspi (0)
    // 0x00000020 [5]     : io_bank0 (0)
    // 0x00000010 [4]     : i2c1 (0)
    // 0x00000008 [3]     : i2c0 (0)
    // 0x00000004 [2]     : dma (0)
    // 0x00000002 [1]     : busctrl (0)
    // 0x00000001 [0]     : adc (0)
    io_rw_32 unused0;    
    // Reset done
    // 0x01000000 [24]    : usbctrl (0)
    // 0x00800000 [23]    : UART1 (0)
    // 0x00400000 [22]    : UART0 (0)
    // 0x00200000 [21]    : timer (0)
    // 0x00100000 [20]    : tbman (0)
    // 0x00080000 [19]    : sysinfo (0)
    // 0x00040000 [18]    : syscfg (0)
    // 0x00020000 [17]    : spi1 (0)
    // 0x00010000 [16]    : spi0 (0)
    // 0x00008000 [15]    : rtc (0)
    // 0x00004000 [14]    : pwm (0)
    // 0x00002000 [13]    : pll_usb (0)
    // 0x00001000 [12]    : pll_sys (0)
    // 0x00000800 [11]    : pio1 (0)
    // 0x00000400 [10]    : pio0 (0)
    // 0x00000200 [9]     : pads_qspi (0)
    // 0x00000100 [8]     : pads_bank0 (0)
    // 0x00000080 [7]     : jtag (0)
    // 0x00000040 [6]     : io_qspi (0)
    // 0x00000020 [5]     : io_bank0 (0)
    // 0x00000010 [4]     : i2c1 (0)
    // 0x00000008 [3]     : i2c0 (0)
    // 0x00000004 [2]     : dma (0)
    // 0x00000002 [1]     : busctrl (0)
    // 0x00000001 [0]     : adc (0)
    union {
        io_ro_32 allBits;
        struct {
            io_ro_32 unused0 : 22;
            io_ro_32 UART0 : 1;
            io_ro_32 UART1 : 1;
        } slectBit;
    } RESET_DONE;
} voile_rp2040_RESETS_t;

#define voile_rp2040_RESETS ((voile_rp2040_RESETS_t *)(0x4000c000u))
#define voile_rp2040_RESETS_XOR ((voile_rp2040_RESETS_t *)(0x4000c000u+0x1000u))
#define voile_rp2040_RESETS_MuskSet ((voile_rp2040_RESETS_t *)(0x4000c000u+0x2000u))
#define voile_rp2040_RESETS_MuskClear ((voile_rp2040_RESETS_t *)(0x4000c000u+0x3000u))


typedef struct {
    // Data Register, UARTDR
    // 0x00000800 [11]    : OE (0): Overrun error
    // 0x00000400 [10]    : BE (0): Break error
    // 0x00000200 [9]     : PE (0): Parity error
    // 0x00000100 [8]     : FE (0): Framing error
    // 0x000000ff [7:0]   : DATA (0): Receive (read) data character
    union {
        io_rw_32 allBits;
        struct {
            io_rw_32 DATA   : 8;
            io_rw_32 FE     : 1;
            io_rw_32 PE     : 1;
            io_rw_32 BE     : 1;
            io_rw_32 OE     : 1;
        } slectBit;
    } UARTDR;    
    // Receive Status Register/Error Clear Register, UARTRSR/UARTECR
    // 0x00000008 [3]     : OE (0): Overrun error
    // 0x00000004 [2]     : BE (0): Break error
    // 0x00000002 [1]     : PE (0): Parity error
    // 0x00000001 [0]     : FE (0): Framing error
    io_rw_32 unused0;

    uint32_t unused1[4];
    
    // Flag Register, UARTFR
    // 0x00000100 [8]     : RI (0): Ring indicator
    // 0x00000080 [7]     : TXFE (1): Transmit FIFO empty
    // 0x00000040 [6]     : RXFF (0): Receive FIFO full
    // 0x00000020 [5]     : TXFF (0): Transmit FIFO full
    // 0x00000010 [4]     : RXFE (1): Receive FIFO empty
    // 0x00000008 [3]     : BUSY (0): UART busy
    // 0x00000004 [2]     : DCD (0): Data carrier detect
    // 0x00000002 [1]     : DSR (0): Data set ready
    // 0x00000001 [0]     : CTS (0): Clear to send
    union {
        io_ro_32 allBits;
        struct {
            io_ro_32 CTS    : 1;
            io_ro_32 DSR    : 1;
            io_ro_32 DCD    : 1;
            io_ro_32 BUSY   : 1;
            io_ro_32 RXFE   : 1;
            io_ro_32 TXFF   : 1;
            io_ro_32 RXFF   : 1;
            io_ro_32 TXFE   : 1;
            io_ro_32 RI     : 1;     
        } slectBit;        
    } UARTFR;

    uint32_t unused2;
    
    // IrDA Low-Power Counter Register, UARTILPR
    // 0x000000ff [7:0]   : ILPDVSR (0): 8-bit low-power divisor value
    io_rw_32 unused3;

    // Integer Baud Rate Register, UARTIBRD
    // 0x0000ffff [15:0]  : BAUD_DIVINT (0): The integer baud rate divisor
    io_rw_32 UARTIBRD;
    
    // Fractional Baud Rate Register, UARTFBRD
    // 0x0000003f [5:0]   : BAUD_DIVFRAC (0): The fractional baud rate divisor
    io_rw_32 UARTFBRD;

} voile_register_rp2040_UART_t;

#define voile_rp2040_UART0 ((voile_register_rp2040_UART_t *)(0x40034000u))
#define voile_rp2040_UART1 ((voile_register_rp2040_UART_t *)(0x40038000u))
#define voile_rp2040_UART0_XOR ((voile_register_rp2040_UART_t *)(0x40034000u+0x1000u))
#define voile_rp2040_UART1_XOR ((voile_register_rp2040_UART_t *)(0x40038000u+0x1000u))
#define voile_rp2040_UART0_MuskSet ((voile_register_rp2040_UART_t *)(0x40034000u+0x2000u))
#define voile_rp2040_UART1_MuskSet ((voile_register_rp2040_UART_t *)(0x40038000u+0x2000u))
#define voile_rp2040_UART0_MuskClear ((voile_register_rp2040_UART_t *)(0x40034000u+0x3000u))
#define voile_rp2040_UART1_MuskClear ((voile_register_rp2040_UART_t *)(0x40038000u+0x3000u))

#endif // !__VOILE_REGISTER_RP2040_H__
