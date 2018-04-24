/*
 *          File: temp_humidity_v2.h
 *        Author: Doug Ferguson
 
 * OVERVIEW:
 * =========
 * This is the "interface" for the module that provides
 * basic functions to read the DHT11 and update string output
 *
 */
extern char *out_string;

/************************ Function Prototypes *********************/


/*
 * Function: loop()
 * Usage: Reads the DHT11
 * ---------------------------
 * 
 */
int dht_loop();
