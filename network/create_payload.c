#include <openssl/md5.h>
#include <string.h>

int create_payload(char *payload, void *request, int offset)
{   __u_char digest[MD5_DIGEST_LENGTH] = {0};

    cipher(request, sizeof(*request), digest);

    printf("respose size %d \n", offset);
    memcpy(payload, (char*)request, offset);
	memcpy(payload + offset, digest, sizeof(digest));

    write(1, payload, sizeof(payload));
}