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
    struct {
        // GPIO status
        // 0x04000000 [26]    : IRQTOPROC (0): interrupt to processors, after override is applied
        // 0x01000000 [24]    : IRQFROMPAD (0): interrupt from pad before override is applied
        // 0x00080000 [19]    : INTOPERI (0): input signal to peripheral, after override is applied
        // 0x00020000 [17]    : INFROMPAD (0): input signal from pad, before override is applied
        // 0x00002000 [13]    : OETOPAD (0): output enable to pad after register override is applied
        // 0x00001000 [12]    : OEFROMPERI (0): output enable from selected peripheral, before register override is applied
        // 0x00000200 [9]     : OUTTOPAD (0): output signal to pad after register override is applied
        // 0x00000100 [8]     : OUTFROMPERI (0): output signal from selected peripheral, before register override is applied
        io_ro_32 unused0;

        // GPIO control including function select and overrides
        // 0x30000000 [29:28] : IRQOVER (0)
        // 0x00030000 [17:16] : INOVER (0)
        // 0x00003000 [13:12] : OEOVER (0)
        // 0x00000300 [9:8]   : OUTOVER (0)
        // 0x0000001f [4:0]   : FUNCSEL (0x1f): Function select.
        union {
            io_rw_32 allBits;
            struct {

                // Function select. 31 == NULL. See GPIO function table for available functions.
                // XIP  : 0,
                // SPI  : 1,
                // UART : 2,
                // I2C  : 3,
                // PWM  : 4,
                // SIO  : 5,
                // PIO0 : 6,
                // PIO1 : 7,
                // GPCK : 8,
                // USB  : 9,
                // NULL : 0x1f,
                io_rw_32 FUNCSEL    : 5;

                io_rw_32            : 3;

                // 0x0 → drive output from peripheral signal selected by funcsel
                // 0x1 → drive output from inverse of peripheral signal selected by funcsel
                // 0x2 → drive output low
                // 0x3 → drive output high
                io_rw_32 OUTOVER    : 2;

                io_rw_32            : 2;

                // 0x0 → drive output enable from peripheral signal selected by funcsel
                // 0x1 → drive output enable from inverse of peripheral signal selected by funcsel
                // 0x2 → disable output
                // 0x3 → enable output
                io_rw_32 OEOVER     : 2;

                io_rw_32            : 2;

                //0x0 → don't invert the peri input
                //0x1 → invert the peri input
                //0x2 → drive peri input low
                //0x3 → drive peri input high
                io_rw_32 INOVER     : 2;

                io_rw_32            : 10;

                //0x0 → don't invert the interrupt
                //0x1 → invert the interrupt
                //0x2 → drive interrupt low
                //0x3 → drive interrupt high
                io_rw_32 IRQOVER    : 2;

                io_rw_32            : 2;

            } selectBit;

        } CTRL;

    } GPIO[30];
    
} voile_rp2040_IO_BANK0_t;

#define voile_rp2040_IO_BANK0 ((voile_rp2040_IO_BANK0_t *)0x40014000u)


typedef struct {
    // Voltage select
    // 0x00000001 [0]     : VOLTAGE_SELECT (0)
    io_rw_32 voltage_select;

    // Pad control register
    // 0x00000080 [7]     : OD (0): Output disable
    // 0x00000040 [6]     : IE (1): Input enable
    // 0x00000030 [5:4]   : DRIVE (1): Drive strength
    // 0x00000008 [3]     : PUE (0): Pull up enable
    // 0x00000004 [2]     : PDE (1): Pull down enable
    // 0x00000002 [1]     : SCHMITT (1): Enable schmitt trigger
    // 0x00000001 [0]     : SLEWFAST (0): Slew rate control
    union {
        io_rw_32 allBits;
        struct {
            io_rw_32 SLEWFAST   : 1;
            io_rw_32 SCHMITT    : 1;
            io_rw_32 PDE        : 1;
            io_rw_32 PUE        : 1;
            io_rw_32 DRIVE      : 2;
            // Input enable 
            io_rw_32 IE         : 1;
            // Output disable. Has priority over output enable from peripherals
            io_rw_32 OD         : 1;
        } selectBit;
    } GPIO[30];
    
} voile_rp2040_PADS_BANK0_t;

#define voile_rp2040_PADS_BANK0 ((voile_rp2040_PADS_BANK0_t *)0x4001c000u)


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
            io_rw_32 unused0    : 22;
            io_rw_32 UART0      : 1;
            io_rw_32 UART1      : 1;
        } selectBit;
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
            io_ro_32 unused0    : 22;
            io_ro_32 UART0      : 1;
            io_ro_32 UART1      : 1;
        } selectBit;
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
        } selectBit;
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
            
            // Clear to send. This bit is the complement of the UART clear to send, nUARTCTS, modem status input. That is, the bit is 1 when nUARTCTS is LOW.
            io_ro_32 CTS    : 1;

            // Data set ready. This bit is the complement of the UART data set ready, nUARTDSR, modem status input. That is, the bit is 1 when nUARTDSR is LOW.
            io_ro_32 DSR    : 1;

            // Data carrier detect. This bit is the complement of the UART data carrier detect, nUARTDCD, modem status input. That is, the bit is 1 when nUARTDCD is LOW.
            io_ro_32 DCD    : 1;

            // UART busy. If this bit is set to 1, the UART is busy transmitting data. This bit remains set until the complete byte, including all the stop bits, has been sent from the shift register. This bit is set as soon as the transmit FIFO becomes non-empty, regardless of whether the UART is enabled or not.
            io_ro_32 BUSY   : 1;

            // Receive FIFO empty. The meaning of this bit depends on the state of the FEN bit in the UARTLCR_H Register. If the FIFO is disabled, this bit is set when the receive holding register is empty. If the FIFO is enabled, the RXFE bit is set when the receive FIFO is empty.
            io_ro_32 RXFE   : 1;

            // Transmit FIFO full. The meaning of this bit depends on the state of the FEN bit in the UARTLCR_H Register. If the FIFO is disabled, this bit is set when the transmit holding register is full. If the FIFO is enabled, the TXFF bit is set when the transmit FIFO is full.
            io_ro_32 TXFF   : 1;

            // Receive FIFO full. The meaning of this bit depends on the state of the FEN bit in the UARTLCR_H Register. If the FIFO is disabled, this bit is set when the receive holding register is full. If the FIFO is enabled, the RXFF bit is set when the receive FIFO is full.
            io_ro_32 RXFF   : 1;

            // Transmit FIFO empty. The meaning of this bit depends on the state of the FEN bit in the Line Control Register, UARTLCR_H. If the FIFO is disabled, this bit is set when the transmit holding register is empty. If the FIFO is enabled, the TXFE bit is set when the transmit FIFO is empty. This bit does not indicate if there is data in the transmit shift register.
            io_ro_32 TXFE   : 1;

            // Ring indicator. This bit is the complement of the UART ring indicator, nUARTRI, modem status input. That is, the bit is 1 when nUARTRI is LOW.
            io_ro_32 RI     : 1;

            io_ro_32        : 23;

        } selectBit;

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

    // Line Control Register, UARTLCR_H
    // 0x00000080 [7]     : SPS (0): Stick parity select
    // 0x00000060 [6:5]   : WLEN (0): Word length
    // 0x00000010 [4]     : FEN (0): Enable FIFOs: 0 = FIFOs are disabled (character mode) that is, the FIFOs become...
    // 0x00000008 [3]     : STP2 (0): Two stop bits select
    // 0x00000004 [2]     : EPS (0): Even parity select
    // 0x00000002 [1]     : PEN (0): Parity enable: 0 = parity is disabled and no parity bit added to the data frame 1 =...
    // 0x00000001 [0]     : BRK (0): Send break
    union {
        io_rw_32 allBits;
        struct {
            io_rw_32 BRK    : 1;
            io_rw_32 PEN    : 1;
            io_rw_32 EPS    : 1;
            io_rw_32 STP2   : 1;
            io_rw_32 FEN    : 1;
            io_rw_32 WLEN   : 2;
            io_rw_32 SPS    : 1;
        } selectBit;
    } UARTLCR_H;

    // Control Register, UARTCR
    // 0x00008000 [15]    : CTSEN (0): CTS hardware flow control enable
    // 0x00004000 [14]    : RTSEN (0): RTS hardware flow control enable
    // 0x00002000 [13]    : OUT2 (0): This bit is the complement of the UART Out2 (nUARTOut2) modem status output
    // 0x00001000 [12]    : OUT1 (0): This bit is the complement of the UART Out1 (nUARTOut1) modem status output
    // 0x00000800 [11]    : RTS (0): Request to send
    // 0x00000400 [10]    : DTR (0): Data transmit ready
    // 0x00000200 [9]     : RXE (1): Receive enable
    // 0x00000100 [8]     : TXE (1): Transmit enable
    // 0x00000080 [7]     : LBE (0): Loopback enable
    // 0x00000004 [2]     : SIRLP (0): SIR low-power IrDA mode
    // 0x00000002 [1]     : SIREN (0): SIR enable: 0 = IrDA SIR ENDEC is disabled
    // 0x00000001 [0]     : UARTEN (0): UART enable: 0 = UART is disabled
    union {
        io_rw_32 allBits;
        struct {
            io_rw_32 UARTEN : 1;
            io_rw_32 unused0: 7;
            io_rw_32 TXE    : 1;
            io_rw_32 RXE    : 1;
        } selectBit;
    } UARTCR;

    // Interrupt FIFO Level Select Register, UARTIFLS
    // 0x00000038 [5:3]   : RXIFLSEL (0x2): Receive interrupt FIFO level select
    // 0x00000007 [2:0]   : TXIFLSEL (0x2): Transmit interrupt FIFO level select
    io_rw_32 unused4;

    // Interrupt Mask Set/Clear Register, UARTIMSC
    // 0x00000400 [10]    : OEIM (0): Overrun error interrupt mask
    // 0x00000200 [9]     : BEIM (0): Break error interrupt mask
    // 0x00000100 [8]     : PEIM (0): Parity error interrupt mask
    // 0x00000080 [7]     : FEIM (0): Framing error interrupt mask
    // 0x00000040 [6]     : RTIM (0): Receive timeout interrupt mask
    // 0x00000020 [5]     : TXIM (0): Transmit interrupt mask
    // 0x00000010 [4]     : RXIM (0): Receive interrupt mask
    // 0x00000008 [3]     : DSRMIM (0): nUARTDSR modem interrupt mask
    // 0x00000004 [2]     : DCDMIM (0): nUARTDCD modem interrupt mask
    // 0x00000002 [1]     : CTSMIM (0): nUARTCTS modem interrupt mask
    // 0x00000001 [0]     : RIMIM (0): nUARTRI modem interrupt mask
    io_rw_32 unused5;

    // Raw Interrupt Status Register, UARTRIS
    // 0x00000400 [10]    : OERIS (0): Overrun error interrupt status
    // 0x00000200 [9]     : BERIS (0): Break error interrupt status
    // 0x00000100 [8]     : PERIS (0): Parity error interrupt status
    // 0x00000080 [7]     : FERIS (0): Framing error interrupt status
    // 0x00000040 [6]     : RTRIS (0): Receive timeout interrupt status
    // 0x00000020 [5]     : TXRIS (0): Transmit interrupt status
    // 0x00000010 [4]     : RXRIS (0): Receive interrupt status
    // 0x00000008 [3]     : DSRRMIS (0): nUARTDSR modem interrupt status
    // 0x00000004 [2]     : DCDRMIS (0): nUARTDCD modem interrupt status
    // 0x00000002 [1]     : CTSRMIS (0): nUARTCTS modem interrupt status
    // 0x00000001 [0]     : RIRMIS (0): nUARTRI modem interrupt status
    io_ro_32 unused6;

    // Masked Interrupt Status Register, UARTMIS
    // 0x00000400 [10]    : OEMIS (0): Overrun error masked interrupt status
    // 0x00000200 [9]     : BEMIS (0): Break error masked interrupt status
    // 0x00000100 [8]     : PEMIS (0): Parity error masked interrupt status
    // 0x00000080 [7]     : FEMIS (0): Framing error masked interrupt status
    // 0x00000040 [6]     : RTMIS (0): Receive timeout masked interrupt status
    // 0x00000020 [5]     : TXMIS (0): Transmit masked interrupt status
    // 0x00000010 [4]     : RXMIS (0): Receive masked interrupt status
    // 0x00000008 [3]     : DSRMMIS (0): nUARTDSR modem masked interrupt status
    // 0x00000004 [2]     : DCDMMIS (0): nUARTDCD modem masked interrupt status
    // 0x00000002 [1]     : CTSMMIS (0): nUARTCTS modem masked interrupt status
    // 0x00000001 [0]     : RIMMIS (0): nUARTRI modem masked interrupt status
    io_ro_32 unused7;

    // Interrupt Clear Register, UARTICR
    // 0x00000400 [10]    : OEIC (0): Overrun error interrupt clear
    // 0x00000200 [9]     : BEIC (0): Break error interrupt clear
    // 0x00000100 [8]     : PEIC (0): Parity error interrupt clear
    // 0x00000080 [7]     : FEIC (0): Framing error interrupt clear
    // 0x00000040 [6]     : RTIC (0): Receive timeout interrupt clear
    // 0x00000020 [5]     : TXIC (0): Transmit interrupt clear
    // 0x00000010 [4]     : RXIC (0): Receive interrupt clear
    // 0x00000008 [3]     : DSRMIC (0): nUARTDSR modem interrupt clear
    // 0x00000004 [2]     : DCDMIC (0): nUARTDCD modem interrupt clear
    // 0x00000002 [1]     : CTSMIC (0): nUARTCTS modem interrupt clear
    // 0x00000001 [0]     : RIMIC (0): nUARTRI modem interrupt clear
    io_rw_32 unused8;

    // DMA Control Register, UARTDMACR
    // 0x00000004 [2]     : DMAONERR (0): DMA on error
    // 0x00000002 [1]     : TXDMAE (0): Transmit DMA enable
    // 0x00000001 [0]     : RXDMAE (0): Receive DMA enable
    union {
        io_rw_32 allBits;
        struct {
            // Receive DMA enable. If this bit is set to 1, DMA for the receive FIFO is enabled
            io_rw_32 RXDMAE     : 1;
            // Transmit DMA enable. If this bit is set to 1, DMA for the transmit FIFO is enabled.
            io_rw_32 TXDMAE     : 1;
            // DMA on error. If this bit is set to 1, the DMA receive request outputs, UARTRXDMASREQ or UARTRXDMABREQ, are disabled when the UART error interrupt is asserted.
            io_rw_32 DMAONERR   : 1;
        } selectBit;
    } UARTDMACR;

} voile_register_rp2040_UART_t;

#define voile_rp2040_UART0 ((voile_register_rp2040_UART_t *)(0x40034000u))
#define voile_rp2040_UART1 ((voile_register_rp2040_UART_t *)(0x40038000u))
#define voile_rp2040_UART_XOR(x) ((voile_register_rp2040_UART_t *)((uint32_t)x+0x1000u))
#define voile_rp2040_UART0_XOR ((voile_register_rp2040_UART_t *)(0x40034000u+0x1000u))
#define voile_rp2040_UART1_XOR ((voile_register_rp2040_UART_t *)(0x40038000u+0x1000u))
#define voile_rp2040_UART_MuskSet(x) ((voile_register_rp2040_UART_t *)((uint32_t)x+0x2000u))
#define voile_rp2040_UART0_MuskSet ((voile_register_rp2040_UART_t *)(0x40034000u+0x2000u))
#define voile_rp2040_UART1_MuskSet ((voile_register_rp2040_UART_t *)(0x40038000u+0x2000u))
#define voile_rp2040_UART_MuskClear(x) ((voile_register_rp2040_UART_t *)((uint32_t)x+0x3000u))
#define voile_rp2040_UART0_MuskClear ((voile_register_rp2040_UART_t *)(0x40034000u+0x3000u))
#define voile_rp2040_UART1_MuskClear ((voile_register_rp2040_UART_t *)(0x40038000u+0x3000u))

#endif // !__VOILE_REGISTER_RP2040_H__
