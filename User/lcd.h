#ifndef LCD_H
#define LCD_H

void lcd_init(void);
void TIMER1_IRQHandler(void);
void init_timer1(void);
void start_timer1(void);

void print_coords(void);
#endif
