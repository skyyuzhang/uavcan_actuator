#include "internalflash.h"

uint16_t PageError=0;

uint16_t StmFlashReadHalfword(uint32_t WriteAddress)
{
  uint16_t flashData = *(__IO uint16_t*)WriteAddress;
  return flashData;
}
  
void StmFlashWrite(uint32_t WriteAddress,uint16_t *buffer,uint16_t size)
{
  FLASH_EraseInitTypeDef f;
  HAL_FLASH_Unlock();
  f.TypeErase=1;
  f.PageAddress=FLASH_SAVE_ADDR;
  f.NbPages=1;
  if(HAL_FLASHEx_Erase(&f,&PageError)==HAL_OK)
  {  
  }
  for(int i=0;i<size;i++)
  {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,WriteAddress,buffer[i]);
    WriteAddress+=2;
  }
  HAL_FLASH_Lock();
}


void StmFlashRead(uint32_t WriteAddress,uint16_t *buffer,uint16_t size)
{
  
  for(int i=0;i<size;i++)
  {
    buffer[i] =StmFlashReadHalfword(WriteAddress);
    WriteAddress+=2;
  }
 
}


/***************************************

uint16_t STMFLASH_ReadHalfWord(uint32_t faddr)
{
    return *(__IO uint16_t*)faddr;
}

#if STM32_FLASH_WREN 
void STMFLASH_Write_NoCheck(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite)  
{                       
    uint16_t i;
    for(i=0;i<NumToWrite;i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,WriteAddr,pBuffer[i]);
        WriteAddr+=2;
    } 
} 
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE    1024
#else
#define STM_SECTOR_SIZE    2048
#endif         
uint16_t STMFLASH_BUF[STM_SECTOR_SIZE/2];
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite)   
{
    uint32_t secpos;      
    uint16_t secoff;      
    uint16_t secremain; 
    uint16_t i;   
    uint32_t offaddr; 
   
    if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;
   
    HAL_FLASH_Unlock();                  
    offaddr=WriteAddr-STM32_FLASH_BASE;        
    secpos=offaddr/STM_SECTOR_SIZE;           
    secoff=(offaddr%STM_SECTOR_SIZE)/2;        
    secremain=STM_SECTOR_SIZE/2-secoff;        
    if(NumToWrite<=secremain)secremain=NumToWrite;
    while(1)
    {   
        STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
        for(i=0;i<secremain;i++)   
        {
            if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;
        }
        if(i<secremain)               
        {
            FLASH_PageErase(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);    
            FLASH_WaitForLastOperation(FLASH_WAITETIME);           
            CLEAR_BIT(FLASH->CR, FLASH_CR_PER);                       
                                                                       
            for(i=0;i<secremain;i++)
            {
                STMFLASH_BUF[i+secoff]=pBuffer[i];     
            }
            STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
        }else
        {
            FLASH_WaitForLastOperation(FLASH_WAITETIME);          
            STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);
        }
        if(NumToWrite==secremain)break;
        else
        {
            secpos++;                
            secoff=0;                
               pBuffer+=secremain;      
            WriteAddr+=secremain*2;    
               NumToWrite-=secremain;    
            if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;
            else secremain=NumToWrite;
        }     
    };   
    HAL_FLASH_Lock();    
}
#endif

void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead)      
{
     uint16_t i;
    for(i=0;i<NumToRead;i++)
    {
        pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);
        ReadAddr+=2;  
    }

}
   

void Test_Write(uint32_t WriteAddr,uint16_t WriteData)      
{
    STMFLASH_Write(WriteAddr,&WriteData,1);
}

*********************************************/