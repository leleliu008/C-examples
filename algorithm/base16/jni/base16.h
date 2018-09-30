#ifdef __cplusplus
extern "C" {
#endif

//base16编码(大写)
//input是要编码的字节数据
//inputLength是要编码的字节数据的长度
char* base16_encode(unsigned char *input, unsigned short inputLength);

//base16解码
//input是Base16编码的字符串
//outputLength是解码后的字节数组的长度
unsigned char* base16_decode(char *input, unsigned short *outputLength);

#ifdef __cplusplus
}
#endif
