/*==============================================================================================*/
/* Project      = Flash Self-programming Library (FSL) S50                                      */
/* Module       = fsl_types.h                                                                   */
/* Device:      = RL78                                                                          */
/* Version      = V1.00                                                                         */
/*==============================================================================================*/
/*                                  COPYRIGHT                                                   */
/*==============================================================================================*/
/* Copyright(c) 2013 Renesas Electronics Corporation                                            */
/*==============================================================================================*/
/* Purpose:     definition of types used by the library                                         */
/*==============================================================================================*/
/*                                                                                              */
/* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.                                            */
/* This program must be used solely for the purpose for which it was furnished                  */
/* by Renesas Electronics Corporation. No part of this program may be reproduced or             */
/* disclosed to others, in any form, without the prior written permission of                    */
/* Renesas Electronics Corporation.                                                             */
/*                                                                                              */
/*==============================================================================================*/



#ifndef __FSL_TYPES_H_INCLUDED
#define __FSL_TYPES_H_INCLUDED



/*==============================================================================================*/
/* unsigned type definitions                                                                    */
/*==============================================================================================*/
typedef unsigned char                       fsl_u08;
typedef unsigned int                        fsl_u16;
typedef unsigned long int                   fsl_u32;


/*==============================================================================================*/
/* global constant definitions                                                                  */
/*==============================================================================================*/


/*==============================================================================================*/
/* global type definitions                                                                      */
/*==============================================================================================*/

/* FSL descriptor type */
typedef struct {                                                  /* ---------------------------------------------- */
                  fsl_u08         fsl_flash_voltage_u08;          /* 1, setting of flash voltage mode               */
                  fsl_u08         fsl_frequency_u08;              /* 1, CPU frequency (MHz)                         */
                  fsl_u08         fsl_auto_status_check_u08;      /* 1, disused parameter (01H is recommended)      */
                } fsl_descriptor_t;                               /*------------------------------------------------*/
                                                                  /* 3 bytes in total                               */
                                                                  /*------------------------------------------------*/


/* FSL write type */
typedef struct {                                                  /* -------------------------------------------------- */
                  fsl_u08 __near  *fsl_data_buffer_p_u08;         /* 2, pointer to data buffer                          */
                  fsl_u32         fsl_destination_address_u32;    /* 4, starting address (4-byte aligned) to write data */
                  fsl_u08         fsl_word_count_u08;             /* 1, number of words (1-64) to write data            */
                } fsl_write_t;                                    /*----------------------------------------------------*/
                                                                  /* 7 bytes in total                                   */
                                                                  /*----------------------------------------------------*/


#endif
