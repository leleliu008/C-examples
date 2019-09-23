#ifdef __cplusplus
extern "C" {
#endif

char*          url_encode      (unsigned char *input, unsigned short inputLength, unsigned short isUpper);
char*          url_encode_upper(unsigned char *input, unsigned short inputLength);
char*          url_encode_lower(unsigned char *input, unsigned short inputLength);

unsigned char* url_decode(char *input, unsigned short *outputLength);

#ifdef __cplusplus
}
#endif
