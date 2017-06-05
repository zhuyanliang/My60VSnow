/*==============================================================================================*/
/* Project      = Flash Self-programming Library (FSL) S50                                      */
/* Module       = fsl.h                                                                         */
/* Device:      = RL78                                                                          */
/* Version      = V1.00                                                                         */
/*==============================================================================================*/
/*                                  COPYRIGHT                                                   */
/*==============================================================================================*/
/* Copyright(c) 2013 Renesas Electronics Corporation                                            */
/*==============================================================================================*/
/* Purpose:                                                                                     */
/*              constant and function prototype definitions used by the FSL                     */
/*                                                                                              */
/*==============================================================================================*/
/*                                                                                              */
/* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.                                            */
/* This program must be used solely for the purpose for which it was furnished                  */
/* by Renesas Electronics Corporation. No part of this program may be reproduced or             */
/* disclosed to others, in any form, without the prior written permission of                    */
/* Renesas Electronics Corporation.                                                             */
/*                                                                                              */
/*==============================================================================================*/

#ifndef __FSL_H_INCLUDED
#define __FSL_H_INCLUDED


/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#include "fsl_types.h"


/*==============================================================================================*/
/* constant definitions                                                                         */
/*==============================================================================================*/

/*status code definitions returned by the FSL functions                                         */
#define   FSL_OK                    0x00      /* no problems                                    */
#define   FSL_ERR_PROTECTION        0x10      /* protection error (access right conflict)       */
#define   FSL_ERR_ERASE             0x1A      /* erase error                                    */
#define   FSL_ERR_BLANKCHECK        0x1B      /* blankcheck error (MRG11)                       */
#define   FSL_ERR_IVERIFY           0x1B      /* internal verify error (MRG11)                  */
#define   FSL_ERR_WRITE             0x1C      /* write error                                    */


/*==============================================================================================*/
/* global function prototypes                                                                   */
/*==============================================================================================*/


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      initialization of flash environment                                            */
/*                                                                                              */
/* Input:        *descriptor_pstr - FSL descriptor                                              */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status_code                                                           */
/*                   = 0x00(FSL_OK), normal and means initialization OK                         */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08  FSL_Init(__far fsl_descriptor_t* descriptor_pstr);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      opens flash environment                                                        */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void  FSL_Open(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      closes flash environment                                                       */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void  FSL_Close(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      prepares following functions to be called                                      */
/*               FSL_BlankCheck, FSL_Erase, FSL_Write, FSL_IVerify                              */
/* Input:        -                                                                              */
/* Output:       -                                                                              */
/* Returned:     -                                                                              */
/*----------------------------------------------------------------------------------------------*/
extern void  FSL_PrepareFunctions(void);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      checks if specified block is blank                                             */
/* Input:        block_u16 - block number has to be checked                                     */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status_code                                                           */
/*                   = 0x00(FSL_OK), normal and means "block is blank"                          */
/*                   = 0x1B(FSL_ERR_BLANKCHECK), blank-check error, means "block is not blank"  */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08  FSL_BlankCheck(fsl_u16 block_u16);


/*----------------------------------------------------------------------------------------------*/
/*  Block type:  FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/*  Purpose:     erases specified block                                                         */
/*  Input:       block_u16 - block number has to be erase                                       */
/*  Output:      -                                                                              */
/*  Returned:    fsl_u08, status_code                                                           */
/*                   = 0x00(FSL_OK), normal and means "block erased successfully"               */
/*                   = 0x10(FSL_ERR_PROTECTION), protection error                               */
/*                   = 0x1A(FSL_ERR_ERASE), erase error                                         */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08  FSL_Erase(fsl_u16 block_u16);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      performs internal verify on specified block                                    */
/* Input:        block_u16 - block number has to be verified                                    */
/* Output:       -                                                                              */
/* Returned:     fsl_u08, status_code                                                           */
/*                   = 0x00(FSL_OK), normal and means "block is verified"                       */
/*                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08  FSL_IVerify(fsl_u16 block_u16);


/*----------------------------------------------------------------------------------------------*/
/* Block type:   FSL command function                                                           */
/*----------------------------------------------------------------------------------------------*/
/* Purpose:      writes N words from the data buffer into flash                                 */
/* Input:        *write_pstr - struct fsl_write_t to write                                      */
/* Output:       -                                                                              */
/* Condition:    1) (&fsl_destination_address MOD 4 == 0)                                       */
/*               2) most significant byte (MSB) of fsl_destination_address_u32 has to be 0x00   */
/*                  Means: 0x00abcdef 24 bit flash address allowed                              */
/*               3) (0 < fsl_word_count_u08 <= 64)                                              */
/*               4) (fsl_word_count_u08 <= sizeof(data buffer))                                 */
/*               ANY CONDITION IS NOT CHECKED BY FSL                                            */
/* Returned:     fsl_u08, status code                                                           */
/*                   = 0x00(FSL_OK), normal                                                     */
/*                   = 0x10(FSL_ERR_PROTECTION), protection error                               */
/*                   = 0x1C(FSL_ERR_WRITE), write error                                         */
/*----------------------------------------------------------------------------------------------*/
extern fsl_u08  FSL_Write(__near fsl_write_t* write_pstr);


#endif
