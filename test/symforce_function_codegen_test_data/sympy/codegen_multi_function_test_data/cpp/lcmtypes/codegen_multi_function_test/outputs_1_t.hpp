/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __codegen_multi_function_test_outputs_1_t_hpp__
#define __codegen_multi_function_test_outputs_1_t_hpp__

#include <lcm/lcm_coretypes.h>

#include "lcmtypes/codegen_multi_function_test/values_vec_t.hpp"
#include "lcmtypes/codegen_multi_function_test/values_vec_t.hpp"

namespace codegen_multi_function_test
{

class outputs_1_t
{
    public:
        double     foo;

        double     bar;

        double     scalar_vec_out[3];

        codegen_multi_function_test::values_vec_t values_vec_out[3];

        codegen_multi_function_test::values_vec_t values_vec_2D_out[2][1];

    public:
        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline int encode(void *buf, int offset, int maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline int getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to read while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline int decode(const void *buf, int offset, int maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "outputs_1_t"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static uint64_t _computeHash(const __lcm_hash_ptr *p);
};

int outputs_1_t::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int outputs_1_t::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int outputs_1_t::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t outputs_1_t::getHash()
{
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* outputs_1_t::getTypeName()
{
    return "outputs_1_t";
}

int outputs_1_t::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->foo, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->bar, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->scalar_vec_out[0], 3);
    if(tlen < 0) return tlen; else pos += tlen;

    for (int a0 = 0; a0 < 3; a0++) {
        tlen = this->values_vec_out[a0]._encodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    for (int a0 = 0; a0 < 2; a0++) {
        for (int a1 = 0; a1 < 1; a1++) {
            tlen = this->values_vec_2D_out[a0][a1]._encodeNoHash(buf, offset + pos, maxlen - pos);
            if(tlen < 0) return tlen; else pos += tlen;
        }
    }

    return pos;
}

int outputs_1_t::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->foo, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->bar, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->scalar_vec_out[0], 3);
    if(tlen < 0) return tlen; else pos += tlen;

    for (int a0 = 0; a0 < 3; a0++) {
        tlen = this->values_vec_out[a0]._decodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    for (int a0 = 0; a0 < 2; a0++) {
        for (int a1 = 0; a1 < 1; a1++) {
            tlen = this->values_vec_2D_out[a0][a1]._decodeNoHash(buf, offset + pos, maxlen - pos);
            if(tlen < 0) return tlen; else pos += tlen;
        }
    }

    return pos;
}

int outputs_1_t::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += __double_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, 3);
    for (int a0 = 0; a0 < 3; a0++) {
        enc_size += this->values_vec_out[a0]._getEncodedSizeNoHash();
    }
    for (int a0 = 0; a0 < 2; a0++) {
        for (int a1 = 0; a1 < 1; a1++) {
            enc_size += this->values_vec_2D_out[a0][a1]._getEncodedSizeNoHash();
        }
    }
    return enc_size;
}

uint64_t outputs_1_t::_computeHash(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for(fp = p; fp != NULL; fp = fp->parent)
        if(fp->v == outputs_1_t::getHash)
            return 0;
    const __lcm_hash_ptr cp = { p, outputs_1_t::getHash };

    uint64_t hash = 0x56da9f927edddf51LL +
         codegen_multi_function_test::values_vec_t::_computeHash(&cp) +
         codegen_multi_function_test::values_vec_t::_computeHash(&cp);

    return (hash<<1) + ((hash>>63)&1);
}

}

#endif
