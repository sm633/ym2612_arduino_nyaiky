#include <avr/io.h>
#include <util/delay.h>
#define YM_IC (5)
#define YM_CS (4)
#define YM_WR (3)
#define YM_RD (2)
#define YM_A0 (1)
#define YM_A1 (0)
#define YM_CTRL_DDR DDRC
#define YM_CTRL_PORT PORTC
#define YM_DATA_DDR DDRD
#define YM_DATA_PORT PORTD
#define YM_MCLOCK (1)
#define YM_MCLOCK_DDR DDRB

static void write_ym(unsigned char data){
    YM_CTRL_PORT &= ~_BV(YM_CS);
    YM_DATA_PORT = data;
    _delay_us(1);
    YM_CTRL_PORT &= ~_BV(YM_WR);
    _delay_us(5);
    YM_CTRL_PORT |= _BV(YM_CS);
  }
static void setreg(unsigned char reg, unsigned char data){
    YM_CTRL_PORT &= ~_BV(YM_A0);
    write_ym(reg);
    YM_CTRL_PORT = _BV(A0);
    write_ym(data);
  }

int main(void){
    YM_CTRL_DDR |= _BV(YM_IC) | _BV(YM_CS) | _BV(YM_WR) | _BV(YM_RD) | _BV(YM_A0) | _BV(YM_A1);
    YM_DATA_DDR = 0xFF;
    YM_MCLOCK_DDR |= _BV(YM_MCLOCK);
    YM_CTRL_PORT |= _BV(YM_IC) | _BV(YM_CS) | _BV(YM_WR) | _BV(YM_RD);
    YM_CTRL_PORT &= ~(_BV(YM_A0) | _BV(YM_A1));

    TCCR1A = _BV(COM1A0);
    TCCR1B = _BV(WGM12) | _BV(CS10);
    TCCR1C = 0;
    TCNT1 = 0;
    OCR1A = 0;

    YM_CTRL_PORT &= ~_BV(YM_IC);
    _delay_ms(10);
    YM_CTRL_PORT |= _BV(YM_IC);
    _delay_ms(10);

    /* YM2612 Test code */ 
  setreg(0x22, 0x00); // LFO off
  setreg(0x27, 0x00); // Note off (channel 0)
  setreg(0x28, 0x01); // Note off (channel 1)
  setreg(0x28, 0x02); // Note off (channel 2)
  setreg(0x28, 0x04); // Note off (channel 3)
  setreg(0x28, 0x05); // Note off (channel 4)
  setreg(0x28, 0x06); // Note off (channel 5)
  setreg(0x2B, 0x00); // DAC off
  setreg(0x30, 0x71); //
  setreg(0x34, 0x0D); //
  setreg(0x38, 0x33); //
  setreg(0x3C, 0x01); // DT1/MUL
  setreg(0x40, 0x23); //
  setreg(0x44, 0x2D); //
  setreg(0x48, 0x26); //
  setreg(0x4C, 0x00); // Total level
  setreg(0x50, 0x5F); //
  setreg(0x54, 0x99); //
  setreg(0x58, 0x5F); //
  setreg(0x5C, 0x94); // RS/AR 
  setreg(0x60, 0x05); //
  setreg(0x64, 0x05); //
  setreg(0x68, 0x05); //
  setreg(0x6C, 0x07); // AM/D1R
  setreg(0x70, 0x02); //
  setreg(0x74, 0x02); //
  setreg(0x78, 0x02); //
  setreg(0x7C, 0x02); // D2R
  setreg(0x80, 0x11); //
  setreg(0x84, 0x11); //
  setreg(0x88, 0x11); //
  setreg(0x8C, 0xA6); // D1L/RR
  setreg(0x90, 0x00); //
  setreg(0x94, 0x00); //
  setreg(0x98, 0x00); //
  setreg(0x9C, 0x00); // Proprietary
  setreg(0xB0, 0x32); // Feedback/algorithm
  setreg(0xB4, 0xC0); // Both speakers on
  setreg(0x28, 0x00); // Key off
  setreg(0xA4, 0x22); // 
  setreg(0xA0, 0x69); // Set frequency

  /* Program loop */
  for(;;) {
    _delay_ms(1000);
    setreg(0x28, 0xF0); // Key on
    _delay_ms(1000);
    setreg(0x28, 0x00); // Key off
    }
  return 0;
  }
