
#include <stdint.h>
#include "stm32f1xx_hal.h"
#define STM32_FLASH_SIZE    64
#define STM32_FLASH_WREN    1
#define FLASH_WAITETIME     50000
#define STM32_FLASH_BASE    0x8000000
#define FLASH_SAVE_ADDR 0x800F000
#define SECTOR_SIZE 1024









void StmFlashWrite(uint32_t WriteAddress,uint16_t *buffer,uint16_t size);
void StmFlashRead(uint32_t WriteAddress,uint16_t *buffer,uint16_t size);
void StmFlashWriteHalfword(uint32_t WriteAddress,uint16_t data);
uint16_t StmFlashReadHalfword(uint32_t WriteAddress);





/****
uint8_t STMFLASH_GetStatus(void);                
uint8_t STMFLASH_WaitDone(uint16_t time);         
uint8_t STMFLASH_ErasePage(uint32_t paddr);           
uint8_t STMFLASH_WriteHalfWord(uint32_t faddr, uint16_t dat);
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);         
uint16_t STMFLASH_ReadLenByte(uint32_t ReadAddr,uint16_t Len);   
void STMFLASH_WriteLenByte(uint32_t WriteAddr,uint32_t DataToWrite,uint16_t Len);                     
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);        
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead);          
***********/