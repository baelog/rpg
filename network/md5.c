#include <openssl/md5.h>
#include <openssl/evp.h>

/**
 * deprecated one
*/
// int cipher(void *data, size_t size, __u_char digest[MD5_DIGEST_LENGTH])
// {
//     MD5_CTX context;

//     MD5_Init(&context);
//     MD5_Update(&context, data, size);
//     MD5_Final(digest, &context);

// }


void cipher(void *data, size_t size, __u_char digest[MD5_DIGEST_LENGTH])
{
    EVP_MD_CTX *mdctx;
    int md5_digest_len = MD5_DIGEST_LENGTH;

    // MD5_Init
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);

    // MD5_Update
    EVP_DigestUpdate(mdctx, data, size);

    // MD5_Final
    EVP_DigestFinal_ex(mdctx, digest, &md5_digest_len);
    EVP_MD_CTX_free(mdctx);
}