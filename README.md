# voile-uart-rp2040
uart operation library for rp2040 in voile library

For more informations about voile library, see [voile-library](https://github.com/Jimmy39/voile-library).

## Dependence
This library use with:

**[voile-interface-uart](https://github.com/Jimmy39/voile-interface-uart)** : Define interface to use uart.

**[voile_register_rp2040.h](https://github.com/Jimmy39/voile-register/blob/main/library/raspberrypi/voile_register_rp2040.h)** : Registers defination.

**RP2040 SDK** : Use timmer and clock.

**[voile-common](https://github.com/Jimmy39/voile-library)** : Some common defination.


## Class voile_const_internal_uart_rp2040_t

This library defines struct ```voile_const_internal_uart_rp2040_t```:

```C
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
    voile_register_rp2040_UART_t *uartId;

    // Pin number of TXD
    uint8_t txdPin;

    // Pin nubmer of RXD
    uint8_t rxdPin;

} voile_const_internal_uart_rp2040_t;
```

### Define
You should define and init struct at _devicelist.c_

```C
#include "voile_uart_rp2040.h"

voile_const_internal_uart_rp2040_t uart = {
    
    // This micro init all function 
    VOILE_UART_RP2040_FUNCINIT,

    // UART0_voile or UART1_voile
    .uartId = UART0_voile,

    // Pin number of TXD
    .txdPin = 0,

    // Pin nubmer of RXD
    .rxdPin = 1

};
```

### Declare
And declare at _devicelist.h_ as ```voile_uart_t```. 

```C
#include "voile_interface_uart.h"

extern voile_uart_t myUART;
```

struct ```voile_uart_t``` is the public part of struct ```voile_const_internal_uart_rp2040_t```, defined in [voile-interface-uart](https://github.com/Jimmy39/voile-interface-uart).

### Usage

See [voile-interface-uart](https://github.com/Jimmy39/voile-interface-uart).
