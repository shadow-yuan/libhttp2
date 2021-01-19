#include <string>
#include "src/utils/testutil.h"
#include "src/utils/slice.h"
#include "src/utils/slice_buffer.h"

class SliceTest {};

TEST(SliceTest, Empty) {
    slice_buffer sb;
    slice s;
}

TEST(SliceTest, Simple) {
    slice s("HelloWorld");
    ASSERT_EQ(s.to_string(), std::string("HelloWorld"));
    slice_buffer sb;
    sb.add_slice(slice("Hello"));
    sb.add_slice(slice("World"));
    slice m = sb.merge();
    ASSERT_EQ(s, m);
}

int main(int argc, char **argv) {
    return test::RunAllTests();
}
