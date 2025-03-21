#include "test.h"
#include "../src/crc.h"

uint8_t test_data[] = {0,0,0,0,0};

int main(){
    // printf("%x\n", ModBusCRC16(test_data, 5));
    TEST(ModBusCRC16(test_data, 5) == 0x2400)
}