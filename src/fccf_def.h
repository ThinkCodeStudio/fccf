#include <stdint.h>

#define FCCF_HEAD_FLAG 0xAF

typedef uint16_t (*fccf_crc_fun)(uint8_t *data, uint32_t len);

typedef struct fccf_buff
{
    uint8_t *ptr;
    uint32_t len;
}FccfBuff;


union fccf_ctrl_frame
{
    uint8_t val;
    struct{
        uint8_t m_s_flag:1;
        uint8_t crc_flag:1;
        uint8_t addr_size:2;
        uint8_t user_code_size:2;
        uint8_t data_len_size:2;
    } context;
};

union fccf_head
{
    uint8_t buf[2];
    struct{
        uint8_t begin;
        union fccf_ctrl_frame ctrl;
    } context;
};

typedef struct fccf_pkg
{
    uint32_t remote_addr;
    uint32_t host_addr;
    uint32_t user_code;
    struct fccf_buff data;
}FccfPkg;

typedef void(*Fccf_ReceiveCb)(FccfPkg *receive_pkg, FccfPkg *send_pkg);
typedef void(*Fccf_SendFinishCb)();

typedef struct fccf_cb
{
    Fccf_ReceiveCb receive;
    Fccf_SendFinishCb send_finish;
}FccfCb;