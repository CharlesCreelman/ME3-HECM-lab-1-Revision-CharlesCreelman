/************************************
 * #pragma directives...
************************************/
#pragma config FEXTOSC = HS
#pragma config RSTOSC = EXTOSC_4PLL 
#pragma config WDTE = OFF        

/************************************
 * #include directives...
 ************************************/
#include <xc.h>

/************************************
 * #define directives...
 ************************************/
#define _XTAL_FREQ 64000000 

/************************************
/ main function
 * ...
************************************/
void main(void) {    
    // setup pin for output (connected to LED)
    LATDbits.LATD7=0;   //set initial output state for left LED
    TRISDbits.TRISD7=0; //set TRIS value for pin (output)
    LATHbits.LATH3=1;   //set initial output state for right LED
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    // setup pin for input (connected to button)
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin 
    TRISFbits.TRISF3=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF3=0; //turn off analogue input on pin 
    int i = 0;
    while (1) { //infinite while loop - repeat forever
        while (PORTFbits.RF2&&PORTFbits.RF3){ //empty while loop (wait for button press)
            i = 1; // resets the i int to 1 after it got set to 0 below in the if statement
            while (i){ //this loop waits for the button to be released before restarting the check button pressed loop
                if (!PORTFbits.RF2&&!PORTFbits.RF3) {LATDbits.LATD7 = !LATDbits.LATD7,LATHbits.LATH3 = !LATHbits.LATH3,i=0;} //toggle LEDS, one should go off whilst the other turns on
            }// doing it this way makes the click reliable and instant
        }
    }
}