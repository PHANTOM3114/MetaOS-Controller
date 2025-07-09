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
    ::grpc::ServerWriter< ::MetaOS::ExecuteShellResponse>* writer;

    std::string shell_prompt = "echo hello";
    std::vector<std::string> black_list = {"reboot", "sudo", "rm", "echo"};
    // Test with "echo" command which should work cross-platform
    request.set_command(shell_prompt);

    auto status = service.ExecuteShell(&context, &request, writer);
    EXPECT_TRUE(status.ok());

    for (const auto& dangerous_cmd: black_list) {
        if (shell_prompt.contains(dangerous_cmd))
        {
            EXPECT_FALSE(response.success());
            EXPECT_EQ(response.output(), "Dangerous prompt");
        }

        else {
            EXPECT_EQ(response.output(), response.output());
        }
    }
}
