#ifndef __19296P1_H__
#define __19296P1_H__


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define Disp_UP				0x01
#define Disp_Down			0x02
#define Disp_Left			0x04
#define Disp_Right		0x08
#define Disp_Reverse	0x10


extern uchar code Char0808_Up[],Char0808_Down[],Char0808_Left[],Char0808_Right[],Char0808_UpDown[];
extern uchar code Char1608_Up[],Char1608_Down[],Char1608_Left[],Char1608_Right[];
extern uchar code Hanzi1616_Down[],Hanzi1616_Up[],Hanzi1616_Left[],Hanzi1616_Right[];

extern void LCD_Send_PData(uchar data2send);
extern void delay(int i);
extern void delay_us(int i);
extern void SEND_CMD_LCD(uchar data1);
extern void SEND_DATA_LCD(uchar data1);
extern void INIT_LCD();

extern void lcd_address(uchar x,uchar y,x_total,y_total);
extern void SET_LCD_DISP_AREA(uchar Column, uchar Page, Column_Total,Page_Total);
extern void clear_screen(void);
extern void display_8x8(uchar column, uchar page,uchar *text);
extern void display_8x1(uchar column, uchar page,uchar text);
extern void CHAR_Display_16x8(uchar Column, uchar Page,uchar *dp, uchar Disp_Para);
extern void Hanzi_Disp_16x16(uchar Column, uchar Page, uchar *dp, uchar Disp_Para);
extern void disp_24x24(int x,int y,uchar *dp);




/////////////////////////////////////////////////

#endif