#include <http.h>
#include <CUnit/CUnit.h>

void test_http_fetch_1() {
    int resultCode = http_fetch("http://blog.fpliu.com/it", stdout, true, true);
    CU_ASSERT_EQUAL(resultCode, 0);
}

void test_http_fetch_2() {
    int resultCode = http_fetch("http://blog.fpliu.com/it", stdout, false, true);
    CU_ASSERT_EQUAL(resultCode, 0);
}

void test_http_fetch_3() {
    int resultCode = http_fetch("http://blog.fpliu.com/it", stdout, true, false);
    CU_ASSERT_EQUAL(resultCode, 0);
}

void test_http_fetch_4() {
    int resultCode = http_fetch("http://blog.fpliu.com/it", stderr, true, true);
    CU_ASSERT_EQUAL(resultCode, 0);
}

void test_http_fetch_5() {
    int resultCode = http_fetch("http://blog.fpliu.com/it", stderr, false, true);
    CU_ASSERT_EQUAL(resultCode, 0);
}

void test_http_fetch_6() {
    int resultCode = http_fetch("http://blog.fpliu.com/it", stderr, true, false);
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
    if ((NULL == CU_add_test(pSuite, "test http_fetch()", test_http_fetch_1)) ||
        (NULL == CU_add_test(pSuite, "test http_fetch()", test_http_fetch_2)) ||
        (NULL == CU_add_test(pSuite, "test http_fetch()", test_http_fetch_3)) ||
        (NULL == CU_add_test(pSuite, "test http_fetch()", test_http_fetch_4)) ||
        (NULL == CU_add_test(pSuite, "test http_fetch()", test_http_fetch_5)) ||
        (NULL == CU_add_test(pSuite, "test http_fetch()", test_http_fetch_6))) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_run_all_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
