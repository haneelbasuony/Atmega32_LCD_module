/*
 * LCD.c
 *
 *  Created on: Oct 17, 2021
 *      Author: LENOVO
 */

#include "../../LIB/STD_TYPES.h"
#include "util/delay.h"

#include "../../MCAL/DIO_V1/DIO_int.h"
#include "LCD_int.h"

#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position

#define PORT_Command PORTD
#define PORT_Instruct PORTA

void DIO_Init(void)
{
	DIO_SetPortDirection(PORT_Command,FULL_HIGH);
	DIO_SetPortDirection(PORT_Instruct,FULL_HIGH);
}
void LCD_Init(void)
{
	DIO_Init();
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(30);

	/* Return Home  */
	LCD_SendCommand(lcd_Home);
	_delay_ms(15);

	/* Function Set  */
	LCD_SendCommand(lcd_FunctionSet8bit);
	_delay_ms(1);

	/* Display ON OFF Control */
	LCD_SendCommand(lcd_DisplayOn);
	_delay_ms(1);

	/* Clear Display */

	LCD_SendCommand(lcd_Clear);
		_delay_ms(15);


	/* Entry Mode Set  */
	LCD_SendCommand(lcd_EntryMode);
	_delay_ms(2);

}

void LCD_SendCommand(u8 u8CmdCpy)
{

	/* Set RS to LOW */
	DIO_SetPinValue(PORTA, PIN0, LOW);

	/* Set R/W to LOW */
	DIO_SetPinValue(PORTA, PIN1, LOW);

	/* Set E to HIGH  */
	DIO_SetPinValue(PORTA, PIN2, HIGH);

	/* Load Command on Data bus */
	DIO_SetPortValue(PORTD, u8CmdCpy);

	/* Set E to LOW */
	DIO_SetPinValue(PORTA, PIN2, LOW);

	/* Wait for E to settle */
	_delay_ms(5);

	/* Set E to HIGH */
	DIO_SetPinValue(PORTA, PIN2, HIGH);

	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(10);

}

void LCD_WriteChar(u8 u8DataCpy)
{
	/* Set RS to HIG */
	DIO_SetPinValue(PORTA, PIN0, HIGH);

	/* Set R/W to LOW */
	DIO_SetPinValue(PORTA, PIN1, LOW);

	/* Set E to HIGH */
	DIO_SetPinValue(PORTA, PIN2, HIGH);

	/* Load Command on Data bus */
	DIO_SetPortValue(PORTD, u8DataCpy);

	/* Set E to LOW */
	DIO_SetPinValue(PORTA, PIN2, LOW);

	/* Wait for E to settle */
	_delay_ms(5);

	/* Set E to HIGH */
	DIO_SetPinValue(PORTA, PIN2, HIGH);

	/* Delay to let the LCD Display the character */
	_delay_ms(10);

}

void LCD_WriteString (u8* pu8StringCpy, u8 u8Index)
{

/* Local loop index */

	u8 iteration=0;
	while (pu8StringCpy[u8Index] != '\0')
	for (iteration=0; iteration<u8Index ; iteration++)
	{

		/* Write Character on LCD */
		LCD_WriteChar(pu8StringCpy[iteration]);

		/* Increment local loop index */
		u8Index++;

		/* Delay to let the LCD show the character */
		_delay_ms(2);
	}

}
