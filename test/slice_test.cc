#include <deque>
#include <string>
#include "src/utils/testutil.h"
#include "src/utils/slice.h"
#include "src/utils/slice_buffer.h"

class SliceTest {};

struct testobject {
    slice s1;
    slice s2;
};

TEST(SliceTest, Empty) {
    slice_buffer sb;
    slice s;
    testobject obj;
    obj.s1.assign("Hello");
    obj.s2.assign("World");
}

TEST(SliceTest, Deque) {
    slice_buffer sb;
    slice s;
    testobject obj;
    obj.s1.assign("Hello");
    obj.s2.assign("World");

    std::deque<testobject> vs;
    vs.push_back(obj);
}

TEST(SliceTest, Simple) {
    slice s("HelloWorld");
    ASSERT_EQ(s.to_string(), std::string("HelloWorld"));
    slice_buffer sb;
    sb.add_slice(slice("Hello"));
    sb.add_slice(slice("World"));
    slice m = sb.merge();
    ASSERT_EQ(s.to_string(), m.to_string());
}

int main(int argc, char **argv) {
    return test::RunAllTests();
}
