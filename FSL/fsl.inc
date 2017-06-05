;=================================================================================================
; Project      = Flash Self-programming Library (FSL) S50
; Module       = fsl.inc
; Device:      = RL78
; Version      = V1.00
;=================================================================================================
;                                  COPYRIGHT
;=================================================================================================
; Copyright(c) 2013 Renesas Electronics Corporation
;=================================================================================================
; Purpose:
;              implementation module of low-level flash memory access
;              CAUTION: Please comment out unused function prototypes 
;                       for code size reduction.
;
;=================================================================================================
;
; RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
; This program must be used solely for the purpose for which it was furnished
; by Renesas Electronics Corporation. No part of this program may be reproduced or
; disclosed to others, in any form, without the prior written permission of
; Renesas Electronics Corporation.
;
;=================================================================================================

$IF (__FSL_INC_INCLUDED)

$ELSE
$SET (__FSL_INC_INCLUDED)


;=================================================================================================
; constant definitions
;=================================================================================================

;status code definitions returned by the FSL functions
FSL_OK                    EQU  (000H)   ; no problems
FSL_ERR_PROTECTION        EQU  (010H)   ; protection error (access right conflict)
FSL_ERR_ERASE             EQU  (01AH)   ; erase error
FSL_ERR_BLANKCHECK        EQU  (01BH)   ; blankcheck error (MRG11)
FSL_ERR_IVERIFY           EQU  (01BH)   ; internal verify error (MRG11)
FSL_ERR_WRITE             EQU  (01CH)   ; write error


;=================================================================================================
; global function prototypes
;=================================================================================================


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      initialization of flash environment                                            
;                                                                                              
; Input:        AX,C - pointer to FSL descriptor                                               
; Output:       -                                                                              
; Returned:     C, status_code                                                                 
;                   = 0x00(FSL_OK), normal and means initialization OK                         
;----------------------------------------------------------------------------------------------
EXTRN _FSL_Init


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      opens flash environment                                                        
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
EXTRN _FSL_Open


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      closes flash environment                                                       
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
EXTRN _FSL_Close


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      prepares following functions to be called                                      
;               FSL_BlankCheck, FSL_Erase, FSL_Write, FSL_IVerify                              
; Input:        -                                                                              
; Output:       -                                                                              
; Returned:     -                                                                              
;----------------------------------------------------------------------------------------------
EXTRN _FSL_PrepareFunctions


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      checks if specified block is blank                                             
; Input:        AX - block number has to be checked                                            
; Output:       -                                                                              
; Returned:     C, status_code                                                                 
;                   = 0x00(FSL_OK), normal and means "block is blank"                          
;                   = 0x1B(FSL_ERR_BLANKCHECK), blank-check error, means "block is not blank"  
;----------------------------------------------------------------------------------------------
EXTRN _FSL_BlankCheck


;----------------------------------------------------------------------------------------------
;  Block type:  FSL command function                                                           
;----------------------------------------------------------------------------------------------
;  Purpose:     erases specified block                                                         
;  Input:       AX - block number has to be erase                                              
;  Output:      -                                                                              
;  Returned:    C, status_code                                                                 
;                   = 0x00(FSL_OK), normal and means "block erased successfully"               
;                   = 0x10(FSL_ERR_PROTECTION), protection error                               
;                   = 0x1A(FSL_ERR_ERASE), erase error                                         
;----------------------------------------------------------------------------------------------
EXTRN _FSL_Erase


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      performs internal verify on specified block                                    
; Input:        AX - block number has to be verified                                           
; Output:       -                                                                              
; Returned:     C, status_code                                                                 
;                   = 0x00(FSL_OK), normal and means "block is verified"                       
;                   = 0x1B(FSL_ERR_IVERIFY), internal verify error                             
;----------------------------------------------------------------------------------------------
EXTRN _FSL_IVerify


;----------------------------------------------------------------------------------------------
; Block type:   FSL command function                                                           
;----------------------------------------------------------------------------------------------
; Purpose:      writes N words from the data buffer into flash                                 
; Input:        AX - pointer to struct fsl_write_str to write                                  
; Output:       -                                                                              
; Condition:    1) (fsl_destination_address_u32 MOD 4 == 0)                                    
;               2) most significant byte (MSB) of fsl_destination_address_u32 has to be 0x00   
;                  Means: 0x00abcdef 24 bit flash address allowed                              
;               3) (0 < fsl_word_count_u08 <= 64)                                              
;               4) (fsl_word_count_u08 <= sizeof(data buffer))                                 
;               ANY CONDITION IS NOT CHECKED BY FSL                                            
; Returned:     C, status code                                                                 
;                   = 0x00(FSL_OK), normal                                                     
;                   = 0x10(FSL_ERR_PROTECTION), protection error                               
;                   = 0x1C(FSL_ERR_WRITE), write error                                         
;----------------------------------------------------------------------------------------------
EXTRN _FSL_Write


$ENDIF
