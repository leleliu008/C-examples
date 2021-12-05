#include <stdlib.h>
#include <string.h>
#include <base64.h>
#include <CUnit/CUnit.h>

void test_get_base64_encode_output_length_in_bytes() {
    CU_ASSERT_EQUAL(get_base64_encode_output_length_in_bytes(1), 4);
    CU_ASSERT_EQUAL(get_base64_encode_output_length_in_bytes(2), 4);
    CU_ASSERT_EQUAL(get_base64_encode_output_length_in_bytes(3), 4);
    CU_ASSERT_EQUAL(get_base64_encode_output_length_in_bytes(4), 8);
    CU_ASSERT_EQUAL(get_base64_encode_output_length_in_bytes(5), 8);
}

void test_base64_encode() {
    const char *input = "abcd";
    size_t  inputBufferSizeInBytes = strlen(input);
    size_t outputBufferSizeInBytes = get_base64_encode_output_length_in_bytes(inputBufferSizeInBytes) + 1;
    char output[outputBufferSizeInBytes];
    memset(output, 0, outputBufferSizeInBytes);
    int result = base64_encode(output, outputBufferSizeInBytes, (unsigned char*)input, inputBufferSizeInBytes);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_STRING_EQUAL(output, "YWJjZA==");
}

void test_base64_decode() {
    const char *input = "YWJjZA==";
    size_t  inputBufferSizeInBytes = strlen(input);
    size_t outputBufferSizeInBytes = (inputBufferSizeInBytes >> 2) * 3 + 1;
    unsigned char output[outputBufferSizeInBytes];
    memset(output, 0, outputBufferSizeInBytes);
    size_t writtenToOutputBufferCountInBytes = 0;
    int result = base64_decode(output, outputBufferSizeInBytes, &writtenToOutputBufferCountInBytes, (char*)input);
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
    if ((NULL == CU_add_test(pSuite, "test base64_encode()", test_base64_encode)) ||
        (NULL == CU_add_test(pSuite, "test base64_decode()", test_base64_decode)) ||
        (NULL == CU_add_test(pSuite, "test base64_decode()", test_get_base64_encode_output_length_in_bytes))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
