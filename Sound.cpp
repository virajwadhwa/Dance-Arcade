// Sound.cpp
// Runs on any computer
// Sound assets based off the original Space Invaders 
// Import these constants into your SpaceInvaders.c for sounds!
// Jonathan Valvano
// April 19, 2018
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "DAC.h" 
#include "diskio.h"
#include "ff.h"
#include "stdio.h"
#include "Sound.h"
//#include "ST7735.h"

unsigned char buffer[7000];
unsigned char buffer2[7000];
unsigned char buffer_flag[1];
unsigned char buffer2_flag[1];
unsigned static char which_buffer;
unsigned char *buffer_set[2] = {buffer, buffer2};
unsigned char *buff_pointer = buffer_set[which_buffer];
extern uint8_t start_flag;
extern uint8_t cc;

uint8_t trigger_flag;

int index;
int index_copy;

extern "C" void SysTick_Handler(void);
extern uint8_t visualizer_flag;
extern const unsigned short right_arrow_0[];
extern const unsigned short right_arrow_1[];
extern const unsigned short right_arrow_2[];
extern uint8_t after_flag;

unsigned char final_val;
unsigned char x,y,z;
uint8_t static x_flag;
uint8_t static y_flag;
uint8_t static z_flag;
uint8_t static new_line_flag;
uint8_t static comma_flag;
uint8_t end_flag;
uint8_t static c;
uint32_t value = 6999;
uint8_t change_flag;
unsigned static char last_val;
uint8_t while_flag;
uint8_t ready_flag;


const char inFilename[] = "lor.txt";   // 8 characters or fewer test.txt
	//uint8_t c;
	//FRESULT MountFresult;
	static FATFS g_sFatFs;
  extern FRESULT MountFresult;
	
extern FIL Handle,Handle2;

extern FRESULT Fresult;
#define MAXBLOCKS 100
#define FILETESTSIZE 10000
extern UINT successfulreads;
/*
unsigned char x,y,z;
uint8_t static x_flag;
uint8_t static y_flag;
uint8_t static z_flag;
uint8_t static new_line_flag;
uint8_t static comma_flag;
uint8_t static end_flag;
*/

void SysTick_Handler(void) {
	
			x_flag = 0;
			y_flag = 0;
			z_flag = 0;
			comma_flag = 0;
			/*
			if(start_flag) {
				if(MountFresult){
					while(1){};
				}
				const char menu_music[] = "l2y.txt";   // 8 characters or fewer test.txt
				Fresult = f_open(&Handle, menu_music, FA_READ);	// inFilename
				Fresult = f_read(&Handle, &cc, 1, &successfulreads);

				while(cc != '{') {
					Fresult = f_read(&Handle, &cc, 1, &successfulreads);
				}
				start_flag = 0;
				value = 511;
			}
	
			if(buffer_flag[0] == 1) {
						Fresult = f_read(&Handle, &buffer, 512, &successfulreads);
						buffer_flag[0] = 0;
				}
				else if(buffer2_flag[0] == 1) {
						Fresult = f_read(&Handle, &buffer2, 512, &successfulreads);
						buffer2_flag[0] = 0;
				}
				*/
	
			while(change_flag && c != ',') {
				index++;
				c = buff_pointer[index];
			}
			
			change_flag = 0;
			c = buff_pointer[index];			// c = buffer[index]
			if(c==',') {
				if(index >= value) {
					index = 0;
					change_flag = 1;
					if(which_buffer==0) { 
						buffer_flag[0] = 1;
						buffer2_flag[0] = 0;
						which_buffer = 1;
						buff_pointer = buffer_set[which_buffer];
					}
					else {
						buffer_flag[0] = 0;
						buffer2_flag[0] = 1;
						which_buffer = 0;
						buff_pointer = buffer_set[which_buffer];
					}
					//c = buffer[index];
				}
				else {
					index++;
					c = buff_pointer[index];
				}
			}
			
			/*
			if(c=='\n') {
				if(index >= value-1) {
					index = 0;
					change_flag = 1;
					if(buffer_flag[0] == 0) {
						buffer_flag[0] = 1;
						buffer2_flag[0] = 0;
						which_buffer = 1;
					}
					else {
						buffer_flag[0] = 0;
						buffer2_flag[0] = 1;
						which_buffer = 0;
					}
					//c = buffer[index];
				}
				else {
					index++;
					index++;
					c = buffer[index];
				}
				// c could be a comma or digit (assume never newline->brace)
				if(c==',') {
					comma_flag = 1;
				}
				else {
					x = (c-'0');
					x_flag = 1;
				}
			} */ //if(c=='\n') {}
			
			
			if(c==',') {
				comma_flag = 1;
			}
			else if(c=='}') {
				end_flag = 1;
			}
			else {
				x = (c-'0');
				x_flag = 1;
			}				
			
			if(!end_flag) {
				if(c==',') {
					comma_flag = 1;
				}
				if(comma_flag != 1) {
					if(index >= value) {
					index = 0;
					change_flag = 1;
					if(which_buffer==0) {
						buffer_flag[0] = 1;
						buffer2_flag[0] = 0;
						which_buffer = 1;
						buff_pointer = buffer_set[which_buffer];
					}
					else {
						buffer_flag[0] = 0;
						buffer2_flag[0] = 1;
						which_buffer = 0;
						buff_pointer = buffer_set[which_buffer];
					}
					//c = buffer[index];
					}
					else if(!change_flag) {
						index++;
						c = buff_pointer[index];
					}
					if(c==',') {
						comma_flag = 1;
					}
					/*
					else if(c=='\n') {
						if(index >= value-1) {
							index = 0;
							change_flag = 1;
							if(buffer_flag[0] == 0) {
								buffer_flag[0] = 1;
								buffer2_flag[0] = 0;
								which_buffer = 1;
							}
							else {
								buffer_flag[0] = 0;
								buffer2_flag[0] = 1;
								which_buffer = 0;
							}
							//c = buffer[index];
						}
						else {
							index++;
							index++;
							c = buffer[index];
						}
						// c could be a comma or digit (assume never newline->brace)
						if(c==',') {
							comma_flag = 1;
						}
						else {
							y = (c-'0');
							y_flag = 1;
						}	
					} */ //else if(x==1) {}
					
					else if(c=='}') {
						end_flag = 1;
					}
					else {
						y = (c-'0');
						y_flag = 1;
					}
				}				
			}
			
			if(!end_flag) {
				if(c==',') {
					comma_flag = 1;
				}
				if(comma_flag != 1) {
					if(index >= value) {
						index = 0;
						change_flag = 1;
						if(which_buffer==0) {
							buffer_flag[0] = 1;
							buffer2_flag[0] = 0;
							which_buffer = 1;
							buff_pointer = buffer_set[which_buffer];
						}
						else {
							buffer_flag[0] = 0;
							buffer2_flag[0] = 1;
							which_buffer = 0;
							buff_pointer = buffer_set[which_buffer];
						}
						//c = buffer[index];
						}
						else if(!change_flag) {
							index++;
							c = buff_pointer[index];
						}
					if(c==',') {
						comma_flag = 1;
					}/*
					else if(c=='\n') {
						if(index >= value-1) {
							index = 0;
							change_flag = 1;
							if(buffer_flag[0] == 0) {
								buffer_flag[0] = 1;
								buffer2_flag[0] = 0;
								which_buffer = 1;
							}
							else {
								buffer_flag[0] = 0;
								buffer2_flag[0] = 1;
								which_buffer = 0;
							}
							//c = buffer[index];
						}
						else {
							index++;
							index++;
							c = buffer[index];
						}
						if(c != ',') {
							z = (c-'0');
							z_flag = 1;
						}
					} */
					else if(c=='}') {
						end_flag = 1;
					}
					else {
						z = (c-'0');
						z_flag = 1;
					}
				}			
			}
			
		
			/*
		if(end_flag) {
			index = 0;
			// end
		}
			*/
		
		if(!end_flag && x_flag) {
			if(y_flag) {
				x = x * 10;
				x = x + y;
			}
			if(z_flag) {
				x = x * 10;
				x = (x + z);	// x contains final integer
			}
			if(!change_flag) {
				DAC_Out(x);
				final_val = x;
			}
		}
		/*
		if(change_flag) {
				//DAC_Out(last_val);
			}
		*/
		
		if(index >= value) {
					index = 0;
					change_flag = 1;
					if(which_buffer==0) {
						buffer_flag[0] = 1;
						buffer2_flag[0] = 0;
						which_buffer = 1;
						buff_pointer = buffer_set[which_buffer];
					}
					else {
						buffer_flag[0] = 0;
						buffer2_flag[0] = 1;
						which_buffer = 0;
						buff_pointer = buffer_set[which_buffer];
					}
				}
				else if(!change_flag) {
					index++;
				}
				//index_copy = index;				
			
}


void SysTick_Init(uint32_t period) {
	// self written function (helper function made by Viraj)
	// do the SysTick Initialization here
	
  //NVIC_ST_RELOAD_R = period-1;  // reload value
  NVIC_ST_CURRENT_R = 0;  	   // any write will reload counter and clear count
  NVIC_SYS_PRI3_R =  (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x00000000;	// priority 2 -> priority 1	// was 0
  NVIC_ST_CTRL_R = 0x05; 	
}

void Sound_Init(void){
	DAC_Init();
	// NVIC_ST_CTRL_R is set to 0x05 in SysTick_Init();
	SysTick_Init(1); // need a period passed as an argument 

	index = 0;
};

void Sound_Play(uint32_t period){
	
		if (period == 0) {
			// turn off interrupts
			NVIC_ST_CTRL_R &= ~0x02;
		}
		
		else {
			NVIC_ST_CTRL_R &= ~0x01;	// turn off systick
			NVIC_ST_CTRL_R |= 0x02;		// enable interrupts
			NVIC_ST_CURRENT_R = 0;	// set current count to 0 (reset)
			NVIC_ST_RELOAD_R = period-1;  // set reload value
			NVIC_ST_CTRL_R |= 0x01;
		}

		return;
}

