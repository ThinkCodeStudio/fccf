#ifndef __CRC_H__
#define __CRC_H__

#include <stdint.h>

uint16_t ModBusCRC16(uint8_t *puchMsg, uint32_t usDataLen);

#endif