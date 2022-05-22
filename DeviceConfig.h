#ifndef __DEVIDECONFIG_H
#define __DEVIDECONFIG_H


/* Register DEVCFG3 */
#pragma config PGL1WAY = OFF                // Permission Group Lock One Way Configuration
#pragma config PMDL1WAY = OFF               // Peripheral Module Disable Configuration
#pragma config IOL1WAY = OFF                // Peripheral Pin Select Configuration

/* Register DEVCFG2 */
#pragma config FPLLIDIV = DIV_1             // System PLL Input Clock Divider
#pragma config FPLLRNG =  RANGE_8_16_MHZ    // System PLL Divided Input Clock Frequency Range
#pragma config FPLLICLK = PLL_FRC           // System PLL Input Clock Select
#pragma config FPLLMULT = MUL_60            // System PLL Feedback Divider
#pragma config FPLLODIV = DIV_4             // Default System PLL Output Divisor
#pragma config BORSEL = HIGH                // Brown-out trip voltage
#pragma config UPLLEN = OFF                 // USB PLL Enable

/* Register DEVCFG1 */
#pragma config FNOSC = SPLL                 // Oscillator Selection
#pragma config DMTINTV = WIN_127_128        // DMT Count Window Interval
#pragma config FSOSCEN = OFF                // Secondary Oscillator Enable
#pragma config IESO = OFF                   // Internal External Switchover
#pragma config POSCMOD = EC                 // Primary Oscillator Configuration
#pragma config OSCIOFNC = OFF               // CLKO Enable Configuration
#pragma config FCKSM = CSECME               // Clock Switching and Monitoring Selection Configuration
#pragma config WDTPS = PS1048576            // Watchdog Timer Postscale Select
#pragma config WDTSPGM = STOP               // Watchdog Timer Stop During Flash Programming
#pragma config WINDIS = NORMAL              // Watchdog Timer Window Mode
#pragma config FWDTEN = OFF                 // Watchdog Timer Enable
#pragma config FWDTWINSZ = WINSZ_25         // Watchdog Timer Window Size
#pragma config DMTCNT = DMT31               // Deadman Timer Count Select
#pragma config FDMTEN = OFF                 // Deadman Timer enable

/* Register DEVCFG0 */
#pragma config DEBUG = OFF                  // Background Debugger Enable
#pragma config JTAGEN = OFF                 // JTAG Enable
#pragma config ICESEL = ICS_PGx1            // ICE/ICD Comm Channel Select
#pragma config TRCEN = OFF                  // Trace Enable
#pragma config BOOTISA = MIPS32             // Boot ISA Selection
#pragma config FECCCON = ECC_DECC_DISABLE_ECCON_WRITABLE   // Dynamic Flash ECC Configuration
#pragma config FSLEEP = OFF                 // Flash Sleep Mode
#pragma config DBGPER = PG_ALL              // Debug Mode CPU Access Permission
#pragma config SMCLR = MCLR_NORM            // Soft Master Clear Enable bit
#pragma config SOSCGAIN = G2                // Secondary Oscillator Gain Control bits
#pragma config SOSCBOOST = ON               // Secondary Oscillator Boost Kick Start Enable bit
#pragma config POSCGAIN = G2                // Primary Oscillator Gain Control bits
#pragma config POSCBOOST = ON               // Primary Oscillator Boost Kick Start Enable bit
#pragma config POSCFGAIN = G3               // Primary Oscillator Fine Gain Control bits
#pragma config POSCAGCDLY = AGCRNG_x_25ms   // AGC Gain Search Step Settling Time Control
#pragma config POSCAGC = Automatic          // Primary Oscillator Gain Control bit
#pragma config EJTAGBEN = NORMAL            // EJTAG Boot

/* Register DEVCP0 */
#pragma config CP = OFF                     // Code Protect

void Set_MaxSpeed_Mode(void){   
	unsigned int caching;
	
    // Unlock Sequence
    asm volatile("di"); // Disable all interrupts
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;  

    // PB1DIV
    // Peripheral Bus 1 cannot be turned off, so there's no need to turn it on
    PB1DIVbits.PBDIV = 1; // Peripheral Bus 1 Clock Divisor Control (PBCLK1 is SYSCLK divided by 2)

    // PB2DIV
    PB2DIVbits.ON = 1; // Peripheral Bus 2 Output Clock Enable (Output clock is enabled)
    PB2DIVbits.PBDIV = 1; // Peripheral Bus 2 Clock Divisor Control (PBCLK2 is SYSCLK divided by 2)

    // PB3DIV
    PB3DIVbits.ON = 1; // Peripheral Bus 2 Output Clock Enable (Output clock is enabled)
    PB3DIVbits.PBDIV = 1; // Peripheral Bus 3 Clock Divisor Control (PBCLK3 is SYSCLK divided by 2)

    // PB4DIV
    PB4DIVbits.ON = 1; // Peripheral Bus 4 Output Clock Enable (Output clock is enabled)
    while (!PB4DIVbits.PBDIVRDY); // Wait until it is ready to write to
    PB4DIVbits.PBDIV = 0; // Peripheral Bus 4 Clock Divisor Control (PBCLK4 is SYSCLK divided by 1)

    // PB5DIV
    PB5DIVbits.ON = 1; // Peripheral Bus 5 Output Clock Enable (Output clock is enabled)
    PB5DIVbits.PBDIV = 1; // Peripheral Bus 5 Clock Divisor Control (PBCLK5 is SYSCLK divided by 2)

    // PB7DIV
    PB7DIVbits.ON = 1; // Peripheral Bus 7 Output Clock Enable (Output clock is enabled)
    PB7DIVbits.PBDIV = 0; // Peripheral Bus 7 Clock Divisor Control (PBCLK7 is SYSCLK divided by 1)

    // PRECON - Set up prefetch
    PRECONbits.PFMSECEN = 0; // Flash SEC Interrupt Enable (Do not generate an interrupt when the PFMSEC bit is set)
    PRECONbits.PREFEN = 0b11; // Predictive Prefetch Enable (Enable predictive prefetch for any address)
    PRECONbits.PFMWS = 0b010; // PFM Access Time Defined in Terms of SYSCLK Wait States (Two wait states)

    // Set up caching
    caching = _mfc0(16, 0);
    caching &= ~0x07;
    caching |= 0b011; // K0 = Cacheable, non-coherent, write-back, write allocate
    _mtc0(16, 0, caching);  

    // Lock Sequence
    SYSKEY = 0x33333333;
    asm volatile("ei"); // Enable all interrupts
}
#endif /* __DEVIDECONFIG_H */