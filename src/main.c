#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static const uint8_t COLOR_BLACK = 0;
static const uint8_t COLOR_BLUE = 1;
static const uint8_t COLOR_GREEN = 2;
static const uint8_t COLOR_CYAN = 3;
static const uint8_t COLOR_RED = 4;
static const uint8_t COLOR_MAGENTA = 5;
static const uint8_t COLOR_BROWN = 6;
static const uint8_t COLOR_LIGHT_GREY = 7;
static const uint8_t COLOR_DARK_GREY = 8;
static const uint8_t COLOR_LIGHT_BLUE = 9;
static const uint8_t COLOR_LIGHT_GREEN = 10;
static const uint8_t COLOR_LIGHT_CYAN = 11;
static const uint8_t COLOR_LIGHT_RED = 12;
static const uint8_t COLOR_LIGHT_MAGENTA = 13;
static const uint8_t COLOR_LIGHT_BROWN = 14;
static const uint8_t COLOR_WHITE = 15;

uint8_t make_color(uint8_t fg, uint8_t bg)
{
       return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color)
{
       uint16_t c16 = c;
       uint16_t color16 = color;
       return c16 | color16 << 8;
}

size_t strlen(const char* str)
{
       size_t ret = 0;
       while ( str[ret] != 0 )
             ret++;
       return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize()
{
       terminal_row = 0;
       terminal_column = 0;
       terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
       terminal_buffer = (uint16_t*) 0xB8000;
       size_t y, x;
       for ( y = 0; y < VGA_HEIGHT; y++ )
            for ( x = 0; x < VGA_WIDTH; x++ )
            {
                   const size_t index = y * VGA_WIDTH + x;
                   terminal_buffer[index] = make_vgaentry(' ', terminal_color);
            }
} 

void terminal_setcolor(uint8_t color) 
{ 
        terminal_color = color; 
} 

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{ 
        const size_t index = y * VGA_WIDTH + x; 
        terminal_buffer[index] = make_vgaentry(c, color); 
} 

void terminal_putchar(char c) { 
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row); 
        if ( ++terminal_column == VGA_WIDTH ) 
        { 
             terminal_column = 0; 
             if ( ++terminal_row == VGA_HEIGHT ) 
             { 
                   terminal_row = 0; 
             } 
        }
} 
void terminal_writestring(const char* data) 
{ 
       size_t datalen = strlen(data); 
       size_t i; 
       for ( i = 0; i < datalen; i++ ) 
       terminal_putchar(data[i]); 
} 
int main() 
{ 
       terminal_initialize(); 
       terminal_writestring("Hello, kernel World!\n"); 
}

