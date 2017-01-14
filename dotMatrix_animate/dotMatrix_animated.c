#include <wiringPi.h>
#include <stdio.h>
#include <time.h>

#define   SDI   0   //serial data input
#define   RCLK  1   //memory clock input(STCP)
#define   SRCLK 2   //shift register clock input(SHCP)

#define	  FRAME_RATE	0.25

/*unsigned char sprites[4][8] = {
				{0x00,0x36,0x7f,0x7f,0x7f,0x3e,0x1c,0x08},
				{0x00,0x00,0x14,0x3e,0x3e,0x1c,0x08,0x00},
				{0x00,0x00,0x14,0x2a,0x22,0x14,0x08,0x00},
                                {0x00,0x36,0x49,0x41,0x41,0x22,0x14,0x08}
				};
*/
unsigned char sprites[4][8] = {
                                {0x00,0x36,0x7f,0x7f,0x7f,0x3e,0x1c,0x08},
                                {0x00,0x00,0x14,0x3e,0x3e,0x1c,0x08,0x00},
                                {0x00,0x00,0x14,0x2a,0x22,0x14,0x08,0x00},
                                {0x00,0x36,0x49,0x41,0x41,0x22,0x14,0x08}
                                };

unsigned char inverted_line[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

void init(void)
{
	pinMode(SDI, OUTPUT); //make P0 output
	pinMode(RCLK, OUTPUT); //make P0 output
	pinMode(SRCLK, OUTPUT); //make P0 output

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

void display_sprite(unsigned char sprite[8])
{
	int i,j;
	unsigned char dat;
	clock_t stop;

	stop=clock()+(FRAME_RATE*CLOCKS_PER_SEC);
        while(clock()<stop) {
	for(i=0;i<8;i++){
		unsigned short dat = (inverted_line[i] << 8) | sprite[i];
		for(j=0;j<16;j++){
			digitalWrite(SDI, 0x8000 & (dat << j));
        	        digitalWrite(SRCLK, 1);
               		digitalWrite(SRCLK, 0);
		}
        	digitalWrite(RCLK, 1);
        	digitalWrite(RCLK, 0);
	}
	}
}

int main(void)
{
	int i;

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	init();

	while(1){
		for(i=0;i<(sizeof(sprites)/8);i++){
			display_sprite(sprites[i]);
		}
	}

	return 0;
}
