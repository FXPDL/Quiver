/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */


void InitApp(void);         /* I/O and Peripheral Initialization */
void init_adc(void);
void init_pwm(void);
void init_timer2(void);
void init_timer0(void);
void InitializeTaps(void);
void ReadSavedSettings(void);
long modulation(long, long);
int scaleA100kPot(double);
int scaleiA100kPot(double);
int scaleA10kPot(double);
int scaleiA10kPot(double);