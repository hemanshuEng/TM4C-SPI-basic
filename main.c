/**
 * main.c
 *
 * Basic Spi with MAx7219 IC Working Progress
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

int main(void)
{
//    system clock setup(80Mhz);
    SysCtlClockSet(SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0)))
          {

          }
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 16);
    SSIEnable(SSI0_BASE);
    SSIDataPut(SSI0_BASE, 0x0A0A);
    SysCtlDelay(13333);
    SSIDataPut(SSI0_BASE, 0x000F);
    SSIDataPut(SSI0_BASE, 0x000B);
    SSIDataPut(SSI0_BASE, 0x0009);
    SSIDataPut(SSI0_BASE, 0x0100);//clear
    SSIDataPut(SSI0_BASE, 0x010C);//shutdown address
    while(1){
      SSIDataPut(SSI0_BASE, 0xFF00);
//      SysCtlDelay((SysCtlClockGet()/1000*3)*1000);
      SysCtlDelay(133333);
      SSIDataPut(SSI0_BASE, 0x0000);
      SysCtlDelay(133333);
    }
//	return 0;
}
