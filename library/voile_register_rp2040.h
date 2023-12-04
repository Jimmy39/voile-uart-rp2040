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
} voile_register_rp2040_UART_t;

#define voile_rp2040_UART0 ((voile_register_rp2040_UART_t *)_u(0x40034000))
#define voile_rp2040_UART1 ((voile_register_rp2040_UART_t *)_u(0x40038000))


#endif // !__VOILE_REGISTER_RP2040_H__
