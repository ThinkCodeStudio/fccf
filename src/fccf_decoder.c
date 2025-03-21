#include "fccf_decoder.h"

static enum FCCF_DECODER_STATE FccfDecoder_ctrlAnalyze(
    union fccf_ctrl_frame *ctrl,
    enum FCCF_DECODER_STATE state)
{
    enum FCCF_DECODER_STATE ret = FCCF_DECODER_STATE_ERROR;
    switch (state)
    {
    case FCCF_DECODER_STATE_HEAD:
    case FCCF_DECODER_STATE_DATA_CRC:
    case FCCF_DECODER_STATE_FINISH:
    case FCCF_DECODER_STATE_ERROR:
        break;

    case FCCF_DECODER_STATE_CREL:
        if (ctrl->context.addr_size != 0)
        {
            ret = ctrl->context.m_s_flag ? FCCF_DECODER_STATE_REMOTE : FCCF_DECODER_STATE_HOST;
            break;
        }

    case FCCF_DECODER_STATE_REMOTE:
        if (ctrl->context.addr_size != 0)
        {
            ret = FCCF_DECODER_STATE_HOST;
            break;
        }

    case FCCF_DECODER_STATE_HOST:
        if (ctrl->context.user_code_size != 0)
        {
            ret = FCCF_DECODER_STATE_USER;
            break;
        }

    case FCCF_DECODER_STATE_USER:
        if (ctrl->context.data_len_size != 0)
        {
            ret = FCCF_DECODER_STATE_DATA_SIZE;
            break;
        }

    case FCCF_DECODER_STATE_DATA_SIZE:
        if (ctrl->context.crc_flag)
        {
            ret = FCCF_DECODER_STATE_HEAD_CRC;
            break;
        }

    case FCCF_DECODER_STATE_HEAD_CRC:
        if (ctrl->context.data_len_size != 0)
        {
            ret = FCCF_DECODER_STATE_DATA;
            break;
        }

    case FCCF_DECODER_STATE_DATA:
        if (ctrl->context.data_len_size != 0 && ctrl->context.crc_flag)
        {
            ret = FCCF_DECODER_STATE_DATA_CRC;
            break;
        }
    }

    return ret;
}

void FccfDecoder_init(
    FccfDecoder *decoder,
    fccf_crc_fun crc_fun,
    uint8_t *buf,
    uint32_t len)
{
    decoder->buff.ptr = buf;
    decoder->buff.len = len;
    decoder->buff_count = 0;
    decoder->head = buf;
    decoder->crc_fun = crc_fun;
    decoder->state = FCCF_DECODER_STATE_HEAD;
    decoder->count = 0;
    decoder->pkg.data.len = 0;
    decoder->pkg.host_addr = 0;
    decoder->pkg.remote_addr = 0;
    decoder->pkg.user_code = 0;
}

int FccfDecoder_push(FccfDecoder *decoder, uint8_t frame)
{
    int ret = 1;
    decoder->buff.ptr[decoder->buff_count] = frame;

    const union fccf_ctrl_frame *ctrl = &decoder->head->context.ctrl;

    switch (decoder->state)
    {
    case FCCF_DECODER_STATE_HEAD:
        if (decoder->head->context.begin == FCCF_HEAD_FLAG)
        {
            decoder->buff_count++;
            decoder->state = FCCF_DECODER_STATE_CREL;
        }
        break;

    case FCCF_DECODER_STATE_CREL:
        decoder->state = FccfDecoder_ctrlAnalyze(ctrl, decoder->state);
        break;

    case FCCF_DECODER_STATE_REMOTE:
        if(ctrl->context.addr_size == 1 && )
        break;

    case FCCF_DECODER_STATE_HOST:
        break;

    case FCCF_DECODER_STATE_USER:
        break;

    case FCCF_DECODER_STATE_DATA_SIZE:
        break;

    case FCCF_DECODER_STATE_HEAD_CRC:
        break;

    case FCCF_DECODER_STATE_DATA:
        break;

    case FCCF_DECODER_STATE_DATA_CRC:
        break;

    default:
        break;
    }

    if(decoder->state == FCCF_DECODER_STATE_ERROR){
        ret = -1;
    }
    if(decoder->state == FCCF_DECODER_STATE_FINISH){
        ret = 0;
    }

    return ret;
}

int FccfDecoder_write(FccfDecoder *decoder, uint8_t *data, uint32_t len)
{
}

FccfPkg FccfDecoder_getPkg(FccfDecoder *decoder)
{
}

int FccfDecoder_clear(FccfDecoder *decoder)
{
}