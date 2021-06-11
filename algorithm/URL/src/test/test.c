#include <stdlib.h>
#include <string.h>
#include <URL.h>
#include <CUnit/CUnit.h>

void test_url_encode() {
    const char *input = "こんにちは💯";
    size_t inputLength = strlen(input);
    size_t outputLength = 3 * inputLength + 1;
    char output[outputLength];
    memset(output, 0, outputLength);
    int result = url_encode(output, (unsigned char*)input, inputLength, true);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_STRING_EQUAL(output, "%E3%81%93%E3%82%93%E3%81%AB%E3%81%A1%E3%81%AF%F0%9F%92%AF");
}

void test_url_decode() {
    const char *input = "%E3%81%93%E3%82%93%E3%81%AB%E3%81%A1%E3%81%AF%F0%9F%92%AF";
    size_t inputLength = strlen(input);
    size_t outputLength = inputLength + 1;
    unsigned char output[outputLength];
    memset(output, 0, outputLength);
    size_t writenLength = 0;
    int result = url_decode(output, &writenLength, (char*)input);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_STRING_EQUAL(output, "こんにちは💯");
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
    if ((NULL == CU_add_test(pSuite, "test url_encode()", test_url_encode)) ||
        (NULL == CU_add_test(pSuite, "test url_decode()", test_url_decode))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
