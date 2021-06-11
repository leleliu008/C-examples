#include <stdlib.h>
#include <string.h>
#include <base16.h>
#include <CUnit/CUnit.h>

void test_base16_encode() {
    const char *input = "abcd";
    size_t inputLength = strlen(input);
    size_t outputLength = inputLength << 1;
    char output[outputLength + 1];
    memset(output, 0, outputLength + 1);
    int result = base16_encode(output, (unsigned char*)input, inputLength, true);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_STRING_EQUAL(output, "61626364");
}

void test_base16_decode() {
    const char *input = "61626364";
    size_t inputLength = strlen(input);
    size_t outputLength = inputLength >> 1;
    unsigned char output[outputLength + 1];
    memset(output, 0, outputLength + 1);
    int result = base16_decode(output, (char*)input);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_STRING_EQUAL(output, "abcd");
}

// http://cunit.sourceforge.net/example.html
int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test base16_encode()", test_base16_encode)) ||
        (NULL == CU_add_test(pSuite, "test base16_decode()", test_base16_decode))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
