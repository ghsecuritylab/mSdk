/*
 * core_init.h
 *
 * Created: 2/8/2013 12:30:47 AM
 *  Author: XxXx
 */
/*#####################################################*/
#ifndef CORE_INIT_H_
#define CORE_INIT_H_
/*#####################################################*/
/*#####################################################*/
extern unsigned long FCPU;
extern unsigned long PLL_REF_CLK;

#define HSI_VALUE	16000000//Mhz
#define LSI_VALUE  ((uint32_t)32000)

#if defined(STM32F769I_DISCO)
#define HSE_STARTUP_TIMEOUT    ((uint32_t)5000)   /*!< Time out for HSE start up, in ms */
#define LSE_STARTUP_TIMEOUT    ((uint32_t)5000U)   /*!< Time out for LSE start up, in ms */
#define HSE_VALUE	25000000//Mhz
#define LSE_VALUE  ((uint32_t)32768)    /*!< Value of the External Low Speed oscillator in Hz */
#define EXTERNAL_CLOCK_VALUE    ((uint32_t)25000000) /*!< Value of the Internal oscillator in Hz*/
//#define DATA_IN_ExtSRAM
//#define DATA_IN_ExtSDRAM
#define VECT_TAB_OFFSET  0x00 /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x200. */
#elif defined(MIKROMEDIA_FOR_STM32F4)
#define HSE_STARTUP_TIMEOUT    ((uint32_t)5000)   /*!< Time out for HSE start up, in ms */
#define HSE_VALUE	0//Mhz
#define LSE_VALUE  ((uint32_t)32768)    /*!< Value of the External Low Speed oscillator in Hz */
#define EXTERNAL_CLOCK_VALUE    ((uint32_t)12288000) /*!< Value of the Internal oscillator in Hz*/
//#define DATA_IN_ExtSRAM
//#define DATA_IN_ExtSDRAM
#define VECT_TAB_OFFSET  0x00 /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x200. */
#else
#error Please select a board or write a new configuration
#endif
//*****************************************************************************
//
// The ASSERT macro, which does the actual assertion checking.  Typically, this
// will be for procedure arguments.
//
//*****************************************************************************
#ifdef DEBUG
#define ASSERT(expr) {                                      \
                         if(!(expr))                        \
                         {                                  \
                             __error__(__FILE__, __LINE__); \
                         }                                  \
                     }
#else
#define ASSERT(expr)
#endif
/*#####################################################*/
#define pi 3.14159265358979323846264338327950288419716939937510
/*#####################################################*/
void _core_init(void);
/*#####################################################*/
#ifdef HEADER_INCLUDE_C_FILES
#include "core_init.c"
#endif
/*#####################################################*/
#endif /* CORE_INIT_H_ */
/*#####################################################*/
