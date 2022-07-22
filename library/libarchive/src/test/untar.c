#include <untar.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>

void test_untar_list() {
    int resultCode = untar_list("test.tar.xz", ARCHIVE_EXTRACT_TIME);
    CU_ASSERT_EQUAL(resultCode, 0);
}

void test_untar_extract() {
    const char * tempDir = mkdtemp("tmp.XXXXXXXXXX");
    int resultCode = untar_extract(tempDir, "test.tar.xz", ARCHIVE_EXTRACT_TIME, true, 0);
    CU_ASSERT_EQUAL(resultCode, 0);
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
    if ((NULL == CU_add_test(pSuite, "test http_fetch()", test_untar_list)) ||
        (NULL == CU_add_test(pSuite, "test http_fetch()", test_untar_extract))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
