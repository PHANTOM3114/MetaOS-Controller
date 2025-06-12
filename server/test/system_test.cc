#include <gtest/gtest.h>
#include <system.hh>

class ProcessingTest : public ::testing::Test {
protected:
    ProcessingImplemantation service;
    grpc::ServerContext context;
    MetaOS::ExecuteShellResponse response;
};

TEST_F(ProcessingTest, ExecuteShellRequestTest) {
    MetaOS::ExecuteShellRequest request;
    // Test with "echo" command which should work cross-platform
    request.set_command("echo hello");

    auto status = service.ExecuteShell(&context, &request, &response);
    EXPECT_TRUE(status.ok());
    EXPECT_TRUE(response.success());

    // Echo adds a newline at the end
    EXPECT_EQ(response.output(), "hello\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}