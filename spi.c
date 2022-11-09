/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.c
 *
 * Description: Source file for the SPI AVR driver
 *
 * Author: Mohamed Mostafa
 *
 *******************************************************************************/
#include "gpio.h"
#include <avr/io.h>
#include "spi.h"
#include "common_macros.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(void)
{

	/* Initialize the direction of the 4 pins used with the SPI module
	 As a MASTER
	 MOSI -----> OUTPUT
	 MISO -----> INPUT
	 SS   -----> OUTPUT
	 SCK  -----> OUTPUT
	 */
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);

	/*
	 1. Enabling the SPI bit
	 2. Setting the SPI as master
	  */
	SET_BIT(SPCR,MSTR);
	SET_BIT(SPCR,SPE);


	/* Clearing the double speed bit to use the clock of the spi master which is Fosc/4 which
	  is maximum clock for the slave
	  _Use clock frequency in the master which is lower than or equal to that of the slave
	  */
    CLEAR_BIT(SPSR,SPI2X);

}
/*
 Initiates the Slave
 */
void SPI_initSlave(void)
{
	/* Initialize the direction of the 4 pins used with the SPI module
		 As a SLAVE
		 MOSI -----> INPUT
		 MISO -----> OUTPUT
		 SS   -----> INPUT
		 SCK  -----> INPUT
		 */
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_INPUT);
	/*
	1. Enabling the SPI bit
	2. Setting the SPI as slave
	 */
	SET_BIT(SPCR,SPE);
	CLEAR_BIT(SPCR,MSTR);


}
/*
 Send and receive one byte because the data register of the SPI is one byte.
 Send and receive at the same time because it's the logic of the SPI
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
	/*
	 Since the data is sent by the master and received by the slave and then sent by the slave and
	 received by the master in the same clock so no need to split the two functions as they also use
	 the same data register.
	 */
	SPDR = data;
	while(BIT_IS_CLEAR(SPSR,SPIF));

	return SPDR;
}
/*
 Send a string using the SPI
 */
void SPI_sendString(const uint8 *str)
{
	uint8 count = 0;
	uint8 recieved_data = 0;
	while(str[count] != '\0')
	{

		/* received_data contains the received data from the other device.
		 * It is a dummy data variable as we just need to send the string to other device.
		 */
		recieved_data = SPI_sendReceiveByte(str[count]);
		count++;
	}

}
/*
 Receiving a string using the SPI
 */
void SPI_receiveString(uint8 *str)
{
	uint8 count=0;

		str[count] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	  while(str[count] != '#')
	  {
		  count++;
		str[count] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	  }
	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[count]='\0';
}




