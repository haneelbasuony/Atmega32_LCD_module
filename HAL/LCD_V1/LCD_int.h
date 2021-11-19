/*
 * LCD_int.h
 *
 *  Created on: Oct 17, 2021
 *      Author: LENOVO
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_



void LCD_Init(void);

void LCD_SendCommand(u8 u8CmdCpy);

void LCD_WriteChar(u8 u8DataCpy);

void LCD_WriteString (u8* pu8StringCpy, u8 u8Index);

void Gotoxy (u8 Y,u8 X);
void LCD_WriteExtraChar (u8 Y,u8 X);
void DIO_Init(void);

#endif /* LCD_INT_H_ */
