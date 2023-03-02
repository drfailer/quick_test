#include <iostream>
#include "quick_test.hpp"

BEGIN_TEST_FUNCTION(main_test)
  ASSERT_EQL(1, 2);

  BEGIN_TEST_GRP("simple test");
    ASSERT(1 == 2);
    ASSERT(2 == 2);
    ASSERT_EQL(2.0, 2.1);
  END_TEST_GRP();
END_TEST_FUNCTION()

int main(int, char**)
{
  CALL(main_test);
  return 0;
}
