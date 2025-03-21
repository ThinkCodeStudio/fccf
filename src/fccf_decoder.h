#include "fccf_def.h"

enum FCCF_DECODER_STATE{
    FCCF_DECODER_STATE_HEAD,
    FCCF_DECODER_STATE_CREL,
    FCCF_DECODER_STATE_REMOTE,
    FCCF_DECODER_STATE_HOST,
    FCCF_DECODER_STATE_USER,
    FCCF_DECODER_STATE_DATA_SIZE,
    FCCF_DECODER_STATE_HEAD_CRC,
    FCCF_DECODER_STATE_DATA,
    FCCF_DECODER_STATE_DATA_CRC,
    FCCF_DECODER_STATE_FINISH,
    FCCF_DECODER_STATE_ERROR
};

typedef struct fccf_decoder
{
    FccfBuff buff;
    uint32_t buff_count;
    FccfPkg pkg;
    union fccf_head *head;
    fccf_crc_fun crc_fun;
    enum FCCF_DECODER_STATE state;
    int count;
}FccfDecoder;

void    FccfDecoder_init    (FccfDecoder *decoder, fccf_crc_fun crc_fun, uint8_t *buf, uint32_t len);
int     FccfDecoder_push    (FccfDecoder *decoder, uint8_t frame);
int     FccfDecoder_write   (FccfDecoder *decoder, uint8_t *data, uint32_t len);
FccfPkg FccfDecoder_getPkg  (FccfDecoder *decoder);
int     FccfDecoder_reset   (FccfDecoder *decoder);