#include "buf.h"

#test clear_null_buf_test
    float *a = 0;
    buf_clear(a);
    ck_assert_msg(buf_size(a) == 0, "clear empty");
    ck_assert_msg(a == 0, "clear no-op");
