#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

int add(int a, int b) {
    return a + b;
}

void test_add() {
    CU_ASSERT_EQUAL(add(2, 3), 5);
    CU_ASSERT_EQUAL(add(-1, 1), 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite pSuite = CU_add_suite("Test Suite", 0, 0);
    CU_add_test(pSuite, "test of add()", test_add);
    
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}