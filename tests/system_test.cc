#include <gtest/gtest.h>
#include <system.hh>
#include <grpcpp/grpcpp.h>

class ProcessingTest : public ::testing::Test {
protected:
    ProcessingImplemantation service;
    grpc::ServerContext context;
    MetaOS::Response response;
};

TEST_F(ProcessingTest, ShutdownSystemRequestTest) {
    MetaOS::ShutdownSystem request;
    auto status = service.ShutdownSystemRequest(&context, request, &response);
    EXPECT_TRUE(status.ok());
    EXPECT_TRUE(response.success());
    EXPECT_EQ(response.output(), "ShutdownSystemRequest");
}

TEST_F(ProcessingTest, OpenAppRequestTest) {
    MetaOS::OpenApp request;
    auto status = service.OpenAppRequest(&context, request, &response);
    EXPECT_TRUE(status.ok());
    EXPECT_TRUE(response.success());
    EXPECT_EQ(response.output(), "OpenAppRequest");
}

TEST_F(ProcessingTest, RunShellScriptRequestTest) {
    MetaOS::RunShellScript request;
    auto status = service.RunShellScriptRequest(&context, request, &response);
    EXPECT_TRUE(status.ok());
    EXPECT_TRUE(response.success());
    
    #if defined(_WIN32) || defined(_WIN64)
        EXPECT_EQ(response.output(), "RunShellScriptRequest Windows");
    #elif defined(__APPLE__) || defined(__MACH__)
        EXPECT_EQ(response.output(), "RunShellScriptRequest MacOS");
    #elif defined(__linux__)
        EXPECT_EQ(response.output(), "RunShellScriptRequest Linux");
    #endif
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
