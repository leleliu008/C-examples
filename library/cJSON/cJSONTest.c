/*
 *参考：http://blog.fpliu.com/it/software/development/language/C/library/cJSON
 */
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"cJSON.h"

int main(int argc, char *argv[]) {
    const char *json = "{\
                            \"name\":\"fpliu\",\
                            \"age\": 18,\
                            \"height\": 180.0,\
                            \"isMale\": true,\
                            \"images\": [\
                                \"1.jpg\", \
                                \"2.png\"\
                            ]\
                        }";
    cJSON *cJSONRoot = cJSON_Parse(json);
    if(NULL != cJSONRoot) {
        cJSON * child = cJSONRoot->child;
        while(NULL != child) {
            int type = child->type;
            char *valueStr = NULL;
            if (cJSON_String == type) {
                valueStr = child->valuestring;
            } else if(cJSON_Number == type) {
                double value = child->valuedouble;
                valueStr = cJSON_PrintUnformatted(child);
            } else if(cJSON_Array == type) {
                valueStr = cJSON_PrintUnformatted(child);
                int count = cJSON_GetArraySize(child);
                for(int i= 0; i < count; i++) {
                    cJSON *arrayItem = cJSON_GetArrayItem(child, i);
                    //递归
                }
            } else if(cJSON_True == type) {
                //TODO
                valueStr = cJSON_PrintUnformatted(child);
            } else if(cJSON_False == type) {
                //TODO
                valueStr = cJSON_PrintUnformatted(child);
            } else {
                valueStr = cJSON_PrintUnformatted(child);
            }
            
            //这里这么写是多此一举，此处仅仅是为了展示字符串操作的正确方法
            int length = strlen(child->string) + strlen(valueStr) + 2;
            char tmp[length];
            memset(tmp, 0, length);
            sprintf(tmp, "%s=%s", child->string, valueStr);

            printf("%s\n", tmp);

            child = child->next;
        }
    }
    return 0;
}
