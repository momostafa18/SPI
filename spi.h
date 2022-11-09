/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.h
 *
 * Description: Header file for the SPI AVR driver
 *
 * Author: Mohamed Mostafa
 *
 *******************************************************************************/
#ifndef SPI_H_
#define SPI_H_
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Default value used as dummy string to be sent when receiving a string */
#define SPI_DEFAULT_DATA_VALUE 0x00

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 Initiates the Master
 */
void SPI_initMaster(void);

/*
 Initiates the Slave
 */
void SPI_initSlave(void);
/*
 Send and receive one byte because the data register of the SPI is one byte.
 Send and receive at the same time because it's the logic of the SPI
 */
uint8 SPI_sendReceiveByte(uint8 data);

/*
 Send a string using the SPI
 */
void SPI_sendString(const uint8 *str);

/*
 Receiving a string using the SPI
 */
void SPI_receiveString(uint8 *str);

#endif /* SPI_H_ */
