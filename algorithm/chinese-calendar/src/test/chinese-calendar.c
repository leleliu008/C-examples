#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <chinese-calendar.h>

void test_solar2lunar() {
    char* result = solar2lunar(2021, 6, 14);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "五月初五");
}

void test_jieri() {
    char* result = solar2lunar(2021, 6, 14);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "五月初五");
    char* jieRi = jieri(2021, 6, 14, result);
    CU_ASSERT_PTR_NOT_NULL(jieRi);
    CU_ASSERT_STRING_EQUAL(jieRi, "端午节");
}

void test_jieqi() {
    char* jieQi = jieqi(2021, 6, 5);
    CU_ASSERT_PTR_NOT_NULL(jieQi);
    CU_ASSERT_STRING_EQUAL(jieQi, "芒种");
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
    if ((NULL == CU_add_test(pSuite, "test solar2lunar()", test_solar2lunar)) ||
        (NULL == CU_add_test(pSuite, "test jieri()", test_jieri)) ||
        (NULL == CU_add_test(pSuite, "test jieqi()", test_jieqi))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
