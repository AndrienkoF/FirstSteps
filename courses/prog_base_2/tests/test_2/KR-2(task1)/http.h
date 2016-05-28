/* http.c/htt[.h ARE PROVIDED BY RUSLAN HADYNIAK (PublicHadyniak repo) AND ARE TAKEN *AS IS*!
I DO NOT OWN ANY OF THIS, ALL RIGHTS BELONG TO THE OWNER! */

#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

typedef struct {
    char key[256];
    char value[256];
} keyvalue_t;

typedef struct {
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
} http_request_t;

http_request_t
http_request_parse(const char * const request);

const char *
http_request_getArg(http_request_t * self, const char * key);

const char *
keyvalue_toString(keyvalue_t * self);

#endif // HTTP_H_INCLUDED
