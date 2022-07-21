#include <stdlib.h>
#include <string.h>
#include <sha256sum.h>
#include <CUnit/CUnit.h>

void test_sha256sum_of_bytes() {
    const char *input = "abcd";
    char * sha256sum = sha256sum_of_bytes((unsigned char*)input, strlen(input));
    CU_ASSERT_PTR_NOT_NULL(sha256sum);
    CU_ASSERT_STRING_EQUAL(sha256sum, "88d4266fd4e6338d13b845fcf289579d209c897823b9217da3e161936f031589");
}

void test_sha256sum_of_string() {
    const char *input = "abcd";
    char * sha256sum = sha256sum_of_string(input);
    CU_ASSERT_PTR_NOT_NULL(sha256sum);
    CU_ASSERT_STRING_EQUAL(sha256sum, "88d4266fd4e6338d13b845fcf289579d209c897823b9217da3e161936f031589");
}

void test_sha256sum_of_file() {
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
    if ((NULL == CU_add_test(pSuite, "test sha256sum_of_bytes()",  test_sha256sum_of_bytes)) ||
        (NULL == CU_add_test(pSuite, "test sha256sum_of_string()", test_sha256sum_of_string)) ||
        (NULL == CU_add_test(pSuite, "test sha256sum_of_file()",   test_sha256sum_of_file))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
