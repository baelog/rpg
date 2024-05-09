#include <openssl/md5.h>

int cipher(void *data, size_t size, __u_char digest[MD5_DIGEST_LENGTH])
{
    MD5_CTX context;

    MD5_Init(&context);
    MD5_Update(&context, data, size);
    MD5_Final(digest, &context);

}