#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#include "SMBus.h"
#include "libF75111.h"
//#include "libF75113.h"
#define OPTIONAL_ARGUMENT_IS_PRESENT \
    ((optarg == NULL && optind < argc && argv[optind][0] != '-') \
     ? (bool) (optarg = argv[optind++]) \
     : (optarg != NULL))

//extern platform Platform;
F75111_Address m_F75111;
BYTE addr;
typedef struct
{
	unsigned char Cycle;		/* 周期计时 周期 &#61; 每次执行的中断时间*0xff */
	unsigned char Duty;		/* 当前占空比 */
	void (*IO_HIGH)(void);		/* 高电平函数 */
	void (*IO_LOW)(void);		/* 低电平函数 */
}PWM_CONFIG;
PWM_CONFIG red_pwm_config;
PWM_CONFIG green_pwm_config;
int signalhandler_count;
struct timespec localtimes;
/*typedef struct
{
	double t_off;
	double t_on;
	char *led_pin_number;
}LED_CONFIG;*/

//pthread_t t1;
LED_CONFIG LED_C;

bool flash_stop;
///////////////////////////////
/*void *thread1(void *LED_C)
{
	int ret;
	LED_CONFIG *config;
	config = (LED_CONFIG *) LED_C;
	while(flash_stop)
	{

		ret=F75111_Led_Control(config->led_pin_number,false);
		if(!ret)
		{
			flash_stop=0;
			printf("error led name\n");
			break;	
		}
		usleep((config->t_on)*1000000);

		F75111_Led_Control(config->led_pin_number,true);			
		//printf("error led name\n");
		usleep((config->t_off)*1000000);	
		
		printf("pin_number %d t_on \n",1);
		F75111_SetDigitalOutput_Pin(1,false);
		usleep(1*1000000);
		
		printf("pin_number %d t_off \n",1);
		F75111_SetDigitalOutput_Pin(1,true);
		usleep(1*1000000);				
	}
}*/
/*void *thread2()
{
	while(1)
	{
		printf("pin_number %d t_on \n",2);
		F75111_SetDigitalOutput_Pin(2,false);
		usleep(0.15*1000000);
		
		printf("pin_number %d t_off \n",2);
		F75111_SetDigitalOutput_Pin(2,true);
		usleep(0.25*1000000);				
	}
}*/

////////////////////////////     
     
char program_name[100] = "Sample";
void printf_help(int exval)
{
	printf("Usage: %s [OPTION] \n\n", program_name);
	printf(" [options] 				\n");
	printf(" -h	--help                                  printf this help and exit\n");
	/*printf(" -w <output_pin_number>			        wtire output pin number with pin_status\n");
	printf(" -r <input_pin_number>			        read input pin number status\n");
	printf(" -W                                             write all output pin status\n");
	printf(" -R                                             read all input pin status\n");
	printf(" -s <pin_status>				pin status = 'h' or 'H' 'l' or 'L', with 'w' or 'r' without parameters, 0x00 - 0xff	\n");*/
	printf(" -m <LED color> <t_off> <t_on>			LED color: LED1_GREEN LED1_RED LED1_BLUE \n");
	printf("						t_off: led off times	t_off range > 0.05	\n");
	printf("						t_on:  led on  times	t_on range > 0x05	\n");
	printf("						stop led, Both t_on an t_off input 0 at the same time\n");
//	printf("Sample: %s -w 1 -s 1       		write output pin 1 write true \n",program_name);
//	printf("Sample: %s -W -s 0xff      		writeoutput pin all  write true \n",program_name);
//	printf("Sample: %s -r 1  			read input pin 1	\n",program_name);
//	printf("Sample: %s -R 				read input all pin	\n",program_name);
	printf("Sample: %s -m LED1_GREEN 0.5 0.5 			\n",program_name);
	printf("Sample: %s -m LED2_RED 2 3 			\n",program_name);
	//printf("Sample: %s -m LED3_BLUE 1.2 2.7 			\n",program_name);
	printf("Sample: %s -m LED1 0 0		stop  led 1 flash		\n",program_name);
	printf("Sample: %s -m LED2 0 0		stop  led 2 flash		\n",program_name);	
	printf("Sample: %s -m LED 0 0			stop all led flash		\n",program_name);

	SMBus_Uninstall();
	exit(exval);
}
int htoi(char *p)
{
       /*
        * Look for 'x' as second character as in '0x' format
        */
       if ((p[1] == 'x')  || (p[1] == 'X'))
               return(strtol(&p[2], (char **)0, 16));
       else
               return(strtol(p, (char **)0, 16));
}
int DioRange(char *number)
{
    int diorange;

    diorange = atoi(number);

    if(diorange < 1 || diorange > 8)
    {
        printf("Diorank range is 1-8.\n");
        printf_help(0);
        exit(EXIT_FAILURE);

    }
	return diorange;
}

/*void signalhandler(int pin_number)
{
	//PWM_Control(&red_pwm_config,1);
	//usleep(1000);
	PWM_Control(&green_pwm_config,2);
	//printf("red_pwm_config.Cycle = 0x%x , red_pwm_config.Cycle = 0x%x \n",red_pwm_config.Cycle,green_pwm_config.Cycle);
	//signalhandler_count++;
	//printf("signalhandler_count = %d\n",signalhandler_count);
}*/

/*int PWM_Control(PWM_CONFIG* pwm,int pin_number)
{
	struct tm *tmp;
	
	if(pwm->Duty >= pwm->Cycle)
		F75111_SetDigitalOutput_Pin(pin_number,true);
	else
		F75111_SetDigitalOutput_Pin(pin_number,false);
	
	if(++pwm->Cycle >= 0x3)
		pwm->Cycle = 1;
		
	clock_gettime(CLOCK_REALTIME, &localtimes);
    printf("localtimes.tv_sec=%ld ,localtimes.tv_nsec= %ld\n",localtimes.tv_sec,localtimes.tv_nsec);
 
}*/

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("OUCH, did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
     {
     	Led1_Stop();
	Led2_Stop();
        exit(0);
     }
     else
          signal(SIGINT, INThandler);
     getchar(); // Get new line character
}
int main(int argc, char *argv[])
{
	
	iopl(3);                        //I/O Port Permissions

	int opt, option_index;
	int pin_number=0;
	char *led_pin_number,*tmp_led,*tmp_off,*tmp_on;
	double  t_off=0,t_on=0;
	BYTE pin_data=0;
	char pin_status;
	tmp_led=(char *)malloc(sizeof(char*));
	tmp_off=(char *)malloc(sizeof(char*));
	tmp_on=(char *)malloc(sizeof(char*));
	const char *short_options = "hr:w:s:mWRc";
	
	static struct option long_options[] = {             //long_options
        {"help",	no_argument,        NULL,	'h'},   //0:no_argument, 1:required_argument they define in "getopt.h"
        {"read",	required_argument,  NULL,	'r'},
        {"write",	required_argument,  NULL,	'w'},
        {"set",		required_argument,  NULL,	's'},
        {"clear",		required_argument,  NULL,	'c'},
        
        {NULL, 0, 0, '\0'}
    };		         

	signal(SIGINT, INThandler);
	strcpy(program_name, argv[0]);
	if (argc == 1) printf_help(1);     

    while((opt = getopt_long(argc, argv, short_options,long_options, &option_index)) != -1)
	{
		switch(opt){
			case 'h':
				printf_help(0);
				break;
				
			case 'r':
				pin_status='r';
				pin_number=DioRange(optarg);
				printf("pin_number  = %d \n",pin_number);			
				break;
				
			case 'R':
				pin_status='R';
				break;
				
			case 'w':
				pin_status='w';
				pin_number=DioRange(optarg);
				//printf("optarg = %s\n",optarg);
				printf("pin_number  = %d \n",pin_number);
				break;
			case 'W':
				pin_status='W';
				break;				
			case 's':
				if((*optarg == 'h')||(*optarg == 'H'))
					pin_data=true;
				else if((*optarg == 'l')||(*optarg == 'L'))
					pin_data=false;
				else
					pin_data=htoi(optarg);
				break;
				
			case 'm':
				if (argc < 5) 
				{
					printf_help(1);
				}
				pin_status='m';
				//pin_number=DioRange(argv[2]);
				led_pin_number=argv[2];
				t_off=atof(argv[3]);
				t_on=atof(argv[4]);
				if(t_off < 0.05 || t_on < 0.05)
				    printf_help(1);
				//printf("pin_number= %d \n",pin_number);
				printf("led_pin_number= %s \n",led_pin_number);
				printf("t_off =%.2f sec , t_on=%.2f sec \n",t_off,t_on);
				break;
			case 'c':
				//pthread_mutex_destroy(&gSMBusMemPtr->LockSection);
				printf("SMBus_Install\n");
				SMBus_Install();
				printf("SMBus_Fix\n");
				SMBus_Fix();
				
				printf("SMBus_Uninstall \n");
				SMBus_Uninstall();
				
				exit(0);
				break;
			default :
				printf("getopt return code 0x%o \n",opt);
				
				printf_help(0);
				break;
		}
	}

	if(SMBus_Install())
	{
		printf("SMBus_Install success \n");
		//return 0;
	}
	m_F75111.bAddress=0x9c;
	//if(!F75111_Init())
	if(!F75111_ALL_OUTPUT_INIT())
	{
		printf("F75111 init fail \n");
		//SMBus_Uninstall();
		exit(0);
	} 
	
	/*if(!F75113_Init())
	{
		printf("F75113 init fail \n");
		//SMBus_Uninstall();
		exit(0);
	}*/
	
	switch(pin_status){
		case 'r':
			printf("get single digatal input pin_number = %d \n",pin_number);
			printf("pin_number %d = %d \n",pin_number ,F75111_GetDigitalInput_Pin(pin_number));
			break;
			
		case 'R':
			printf("get all digatal input \n");
			printf("input data = 0x%x \n",F75111_GetDigitalInput());
			break;
				
		case 'w':
			printf("pin_number = %d , pin_data = 0x%x \n",pin_number,pin_data );
			F75111_SetDigitalOutput_Pin(pin_number,pin_data);
			break;
		case 'W':
			printf("Set all digital output = 0x%x\n",pin_data);
			F75111_SetDigitalOutput(pin_data);
			break;
				
		case 'm':
			bzero(&LED_C,sizeof(LED_C));

			LED_C.t_on=t_on;
			LED_C.t_off=t_off;
			LED_C.color=led_pin_number;
			
			if(strstr(LED_C.color,"LED1")!=NULL)
			{
				if(LED_C.t_on == 0 && LED_C.t_off == 0 )
					LED_C.flash=0;
				else LED_C.flash=1;			
				Led1_Control(LED_C);
				//printf("GET LED1\n");
			}
			if(strstr(LED_C.color,"LED2")!=NULL)
			{
				if(LED_C.t_on == 0 && LED_C.t_off == 0 )
					LED_C.flash=0;
				else LED_C.flash=1;			
				Led2_Control(LED_C);
				//printf("GET LED2\n");
			}
			/*if(strstr(LED_C.color,"LED3")!=NULL)
			{
				if(LED_C.t_on == 0 && LED_C.t_off == 0 )
					LED_C.flash=0;
				else LED_C.flash=1;			
				Led3_Control(LED_C);
				//printf("GET LED3\n");
			}*/
			
			while(1)
			{
				
				printf("change setting : <LED_number> <t_off> <t_on>\n");
				scanf("%s %s %s",tmp_led,tmp_off,tmp_on);
				//printf("led_pin_number = %s  \n",led_pin_number);
				//printf("tmp_off = %s tmp_on = %s \n",tmp_off,tmp_on);
				
				if((atof(tmp_off) >= 0.05) && (atof(tmp_off) >= 0.05))
					{
					LED_C.t_off=atof(tmp_off);
					LED_C.t_on=atof(tmp_on);
					LED_C.color=tmp_led;
					printf("new setting : LED_number=%s t_on=%.2f sec t_off=%.2f sec\n",LED_C.color,LED_C.t_on,LED_C.t_off);		

					if(strstr(LED_C.color,"LED1")!=NULL)
					{
						Led1_Control(LED_C);
						//printf("GET LED1\n");
					}
					if(strstr(LED_C.color,"LED2")!=NULL)
					{
						Led2_Control(LED_C);
						//printf("GET LED2\n");
					}
					/*if(strstr(LED_C.color,"LED3")!=NULL)
					{
						Led3_Control(LED_C);
						//printf("GET LED3\n");
					}*/
					
					//printf("LED_C.flash %d\n",LED_C.flash);
				}
				else if((atof(tmp_off) == 0) &&  (atof(tmp_on) == 0))
				{
					LED_C.color=tmp_led;
					if(strstr(LED_C.color,"LED1")!=NULL)
					{
						Led1_Stop();
						//printf("led1 stop\n");
					}
					if(strstr(LED_C.color,"LED2")!=NULL)
					{
						Led2_Stop();
						//printf("led2 stop\n");
					}
					/*if(strstr(LED_C.color,"LED3")!=NULL)
					{
						Led3_Stop();
						//printf("led3 stop\n");
					}*/
					if(strstr(LED_C.color,"LED")!=NULL)
					{
						Led1_Stop();
						Led2_Stop();
						//Led3_Stop();
					}
				}
				else
				{
					printf("t_off t_on range >= 0.05 \n");
				}
				//sleep(5);
				//pause();
			}
			
			break;
		
    }
 	SMBus_Uninstall();
    //printf_help(0);
	return 0;
}




