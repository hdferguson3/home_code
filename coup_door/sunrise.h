/*
 *          File: sunrise.h
 *        Author: Doug Ferguson
 
 * OVERVIEW:
 * =========
 * This is the "interface" for the module that provides
 * the sunrise and sunset times
 *
 */
#ifndef __SUNRISE_H__
#define __SUNRISE_H__

/************************ Function Prototypes *********************/


extern char wake_open[30];
extern char sleep_close[30];
extern int get_sunrise();
extern int get_sunset();
extern int get_current();
/*extern int get_sunrise_sunset(void); 
extern double calcObliquityCorrection(double_t);
extern double calcEquationOfTime(double_t);
extern double calcSunApparentLong(double_t);
extern double calcSunDeclination(double_t);
extern double calcHourAngleSunset(double lat, double solarDec);
extern double calcHourAngleSunrise(double lat, double solarDec);
extern double calcJD(int year,int month,int day);
extern double calcSunEqOfCenter(double_t);
*/

#endif /*__MENU_H__*/
