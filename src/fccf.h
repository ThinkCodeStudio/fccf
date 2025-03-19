
#include <stdint.h>

enum FCCF_SLAVE_STATE{

};

typedef struct fccf_slave
{
    FccfBuff rx_fifo;
    FccfPkg rx_pkg;
    FccfBuff tx_buff;
    FccfPkg tx_pkg;
    union fccf_ctrl_frame ctrl_frame;

    uint32_t slave_addr;

    FccfCb *cb;
}FccfSlave;

typedef FccfSlave* FccfSlave_t;


struct fccf_buff FccfBuff_create(uint8_t *buf, uint32_t len);

void    FccfSlave_init      (FccfSlave_t fccf, uint32_t addr, struct fccf_buff rx_buff, struct fccf_buff tx_buff);
void    FccfSlave_setCb     (FccfSlave_t fccf, FccfCb*);
int     FccfSlave_recWrite  (FccfSlave_t fccf, uint8_t *data, uint32_t len);
int     FccfSlave_recPush   (FccfSlave_t fccf, uint8_t frame);
int     FccfSlave_handler   (FccfSlave_t fccf);
