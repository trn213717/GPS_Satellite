/*
 * GPS.c
 *
 *  Created on: Jul 26, 2023
 *      Author: Tarun Singh
 *
 */
#include "GPS.h"
#include "main.h"
#include"string.h"
#include "stdio.h"

uint8_t Rxdata[750];
char Txdata[750];
char GPS_Payyload[100];
char GPS_Payyload1[100];
uint8_t buf[2];
float lat[3];
uint8_t Flag = 0;
static int Msgindex;
static int Msgindex1;
char *ptr;
char *ptr1;

float time ,speed_knots, speed;
double Latitude, Longitude,altitude;
int Hours, Min, Sec,date;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void get_location(void){
//	HAL_UART_Transmit(&huart2, (uint8_t*)Txdata, strlen(Txdata), 100);
//	if(Flag = 1){

	HAL_UART_Receive_DMA(&huart1, Rxdata, sizeof(Rxdata));
		Msgindex =0;
		strcpy((Txdata),(char*)(Rxdata));
		ptr=strstr(Txdata,"GPGGA");
		if (*ptr == 'G')
		{
			while(1){
				GPS_Payyload[Msgindex] =*ptr;
				Msgindex++;
				*ptr =*(ptr+Msgindex);
				if(*ptr == '\n')
				{
					GPS_Payyload[Msgindex]='\0';
					break;
				}

			}
//			sscanf(GPS_Payyload,"GPGGA,%f,A,%lf,N,%lf",&time,&Latitude,&Longitude);
			 sscanf(GPS_Payyload, "GPGGA,%f,%lf,%*c,%lf,%*c,%*d,%*d,%*f,%lf,M,%*f,M,,", &time, &Latitude, &Longitude, &altitude);
			Format_data(time, Latitude, Longitude);
			HAL_Delay(1);
//			Flag = 0;

		}


}
void Format_data(float Time, float Lat, float Long){
	char Data[150];

	Hours = (int)Time/10000;
	Min=(int)(Time - (Hours*10000))/100;
	Sec=(int )(Time-((Hours*10000)+(Min*100)));
	Hours += 5;
	Min +=30;
	Hours += Min /60;
	Min %= 60;
	 Hours %= 24;

//	sprintf(Data, "\r\n Time=%d:%d:%d  Lat=%f, Long = %f", Hours+3, Min,Sec, Latitude,Longitude);
	sprintf(Data, "\r\n Time=%d:%d:%d Lat=%f, Long = %f, Altitude = %lf,Speed = %f,date = %d",  Hours, Min,Sec, Latitude/100,Longitude/100, altitude,speed* 0.514444,date);
	HAL_UART_Transmit(&huart2, (uint8_t*)Data, strlen(Data), 100);
	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n\n",3, 100);


}
void get_velocity(void){

	Msgindex1 =0;
			strcpy((Txdata),(char*)(Rxdata));
			ptr1=strstr(Txdata,"GPRMC");
			if (*ptr1 == 'G')
			{
				while(1){
					GPS_Payyload1[Msgindex1] =*ptr1;
					Msgindex1++;
					*ptr1 =*(ptr1+Msgindex1);
					if(*ptr1 == '\n')
					{
						GPS_Payyload1[Msgindex1]='\0';
						break;
					}

				}
				//sscanf(GPS_Payyload,"GPRMC,%*f,%*c,%*lf,%*c,%*lf,%lf,",&speed_knots);
//				sscanf(GPS_Payyload1,"GPRMC,%*f,A,%*f,N,%*f,E,%f,%*f,%d",&speed_knots,&date);
				sscanf(GPS_Payyload1, "GPRMC,%*f,%*c,%*f,%*c,%*f,%*c,%f,%*f,%d,%*f,%*c", &speed, &date);

//				HAL_UART_Transmit(&huart2, (uint8_t*)GPS_Payyload1, strlen(GPS_Payyload1), 100);
//				 sscanf(GPS_Payyload, "GPGGA,%f,%lf,%*c,%lf,%*c,%*d,%*d,%*f,%lf,M,%*f,M,,", &time, &Latitude, &Longitude, &altitude);
//				Format_data(time, Latitude, Longitude);
				HAL_Delay(1);
	//			Flag = 0;

			}


};

