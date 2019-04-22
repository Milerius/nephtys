#include <filesystem>
#include <iostream>
#include <nephtys/utils/pretty_function.hpp>
#include <nephtys/client/world/world.hpp>

int main()
{
    loguru::set_thread_name("main thread");
    loguru::add_file((std::filesystem::temp_directory_path() / "nephtys.client.error.log").string().c_str(),
                     loguru::Append, loguru::Verbosity_ERROR);
    loguru::add_file((std::filesystem::temp_directory_path() / "nephtys.client.latest.log").string().c_str(),
                     loguru::Truncate, loguru::Verbosity_INFO);
    VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);

    nephtys::client::world world;
    return world.run().value();
}