#include <stdlib.h>
#include <string.h>
#include <sysinfo.h>
#include <CUnit/CUnit.h>

void test_sysinfo_kind() {
    char osKind[31] = {0};

    int ret = sysinfo_kind(osKind, 30);

    CU_ASSERT_EQUAL(ret, 0);
}

void test_sysinfo_type() {
    char osType[31] = {0};

    int ret = sysinfo_type(osType, 30);

    CU_ASSERT_EQUAL(ret, 0);
}

void test_sysinfo_arch() {
    char osArch[31] = {0};

    int ret = sysinfo_arch(osArch, 30);

    CU_ASSERT_EQUAL(ret, 0);
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
    if ((NULL == CU_add_test(pSuite, "test sysinfo_kind()", test_sysinfo_kind)) ||
        (NULL == CU_add_test(pSuite, "test sysinfo_type()", test_sysinfo_type)) ||
        (NULL == CU_add_test(pSuite, "test sysinfo_arch()", test_sysinfo_arch))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
