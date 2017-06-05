#include "u_include.h"
#include "fsl.h"
#include "fsl_types.h"

static __far fsl_descriptor_t g_fslDes;

uint8_t Self_Flash_Initiallize(void)
{
	uint8_t ret;
	g_fslDes.fsl_flash_voltage_u08 	= 0x00;	// 电压模式为全速模式
	g_fslDes.fsl_frequency_u08		= 0x18; // CPU时钟为24MHz
	g_fslDes.fsl_auto_status_check_u08 = 0x01;	// 状态检查设置(本库未使用) 一般设置成01

	ret = FSL_Init(&g_fslDes);
	if(FSL_OK == ret)
	{
		FSL_Open();
		FSL_PrepareFunctions();
	}
	return ret;
}


uint8_t Self_Flash_WriteExecute(uint32_t dstAddr,uint8_t *srcAddr,uint8_t len)
{
	fsl_write_t writeArg;
    uint8_t 	ret;
    uint16_t    writeBlock;

	/* Calculation write block */
    writeBlock = (uint16_t)(dstAddr/0x400); 
	/* Blanc check execution */
    ret = FSL_BlankCheck(writeBlock);  
	if (ret == FSL_ERR_BLANKCHECK )
	{
        ret = FSL_Erase(writeBlock);                             /* Erase execution */
    }
	else{}/* Do nothing */

	if(FSL_OK == ret)
	{
        writeArg.fsl_data_buffer_p_u08       = srcAddr;
        writeArg.fsl_destination_address_u32 = dstAddr;
        writeArg.fsl_word_count_u08          = len;
        ret = FSL_Write( &writeArg );      /* Write execution */      
    }
	
	if(ret == FSL_OK)
	{
        ret = FSL_IVerify(writeBlock);
    }

	FSL_Close();
	
	return ret;
}














