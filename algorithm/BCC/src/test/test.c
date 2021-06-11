#include <bcc.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>

void test_bcc() {
    const char *input = "abcd";
    size_t nBytes = strlen(input); 
    unsigned char bccsum = bcc((unsigned char*)input, nBytes);
    CU_ASSERT_EQUAL(bccsum, 1);
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
    if ((NULL == CU_add_test(pSuite, "test bcc()", test_bcc))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
