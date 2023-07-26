/*
 * GPS.h
 *
 *  Created on: Jul 26, 2023
 *      Author: gk842
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_



void get_location(void);
void get_GPGGA(void);
void Format_data(float Time, float Lat, float Long);
void get_velocity(void);

#endif /* INC_GPS_H_ */
