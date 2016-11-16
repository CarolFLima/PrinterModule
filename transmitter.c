// PIC16F883 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <stdio.h>
#include <xc.h>
#define _XTAL_FREQ 8000000

void USART_init(void)
{
    // p154 Asynchronous Transmission Set-up
    // 1 -  SPBRGH, SPBRG register pa SPBRGH, SPBRG register pair
    TXSTAbits.BRGH = 1;
    SPBRGH = 0;
    SPBRG = 12; 
    
    // 2 - Set SPEN bit and clear SYNC for asynchronous operation
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;     
    
    // 3 - Disable 9-bit reception
    TXSTAbits.TX9 = 0;
    
    // 4 - Enable the transmission
    TXSTAbits.TXEN = 1;
    
    // 5 - Enable interruptions
    PIE1bits.TXIE = 0;      
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    
    // 6 - Clear RCIF
    PIR1bits.RCIF = 0;

    
    // 7 - Load 8-bit data into TXREG to transmit 
}   

void USART_putc(unsigned char c)
{
    while (!PIR1bits.TXIF );    // wait until transmit shift register is empty
        TXREG = c;               // write character to TXREG and start transmission
    
}

void USART_int (int i) //CANCELA
{
    while(!PIR1bits.TXIF);
        TXREG = i;
}

void USART_puts(unsigned char *s)
{
    int i;
    for(i=0;s[i]!='\0';i++)
        USART_putc(s[i]);
    
}

void PRINTER_init(){
    
//    USART_putc(27);
//    USART_putc(55);
//    USART_putc(7);
//    USART_putc(100);
//    USART_putc(80);
//    //
//    USART_putc(18);
//    USART_putc(35);
//    USART_putc(0);
//    
}

void main()
{
    TRISC = 0x00;
    RC0 = 0;
    RC1 = 0;
    RC2 = 0;
    USART_init();
    //PRINTER_init();
    
    // Centering text
    USART_putc(27);
    USART_putc(97);
    USART_putc(1);

    // Double width and double height
    USART_putc(29); 
    USART_putc(33);
    USART_putc(161);
    USART_puts("IC-UFAL"); 
    USART_putc(10);   // Print LF
    __delay_ms(100);

    char pswrd[] = "P0003";
    // Regular width and regular height
    USART_putc(29); 
    USART_putc(33);
    USART_putc(0);
    // Centering text
    USART_putc(27);
    USART_putc(97);
    USART_putc(1);
    USART_puts("Sua senha:");
    __delay_ms(100);

    // Centering text
    USART_putc(27);
    USART_putc(97);
    USART_putc(1);
    USART_puts("----------");
    __delay_ms(100);

    // Centering text
    USART_putc(27);
    USART_putc(97);
    USART_putc(1);
    // Double width and double height
    USART_putc(29); 
    USART_putc(33);
    USART_putc(161);
    USART_puts(pswrd);
    __delay_ms(100);

    // Centering text
    USART_putc(27);
    USART_putc(97);
    USART_putc(1);
    USART_puts("----------");
    __delay_ms(100);
    USART_putc(10);   // Print LF
    USART_putc(10);   // Print LF

   // do { } while (1>0); // do nothing
    
//    int flag = 0;
//    while(1){
//      RC0 = !RC0;
//      if(flag == 0) {
//        char str[] = "SUA SENHA EH 2016 SIM";
//
//        USART_puts(str); 
//        RC2 = !RC2;
//        USART_putc(10);
//        __delay_ms(100);
//        flag = 1;
//      }
//      
//      else {
//          RC1 = !RC1;
//      }
//    }
    
    return;
}
