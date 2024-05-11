#include <openssl/md5.h>
#include <string.h>
#include "payload.h"

int create_payload(char *payload, void *request, int offset)
{   __u_char digest[MD5_DIGEST_LENGTH] = {0};

    cipher(request, offset, digest);

    memcpy(payload, request, offset);
	memcpy(payload + offset, digest, sizeof(digest));
}