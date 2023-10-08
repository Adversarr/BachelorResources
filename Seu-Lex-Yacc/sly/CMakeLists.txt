include_directories(include)
include(FetchContent)

file(GLOB SLY_HEADER include/sly/*.h)
file(GLOB SLY_SRC src/*.cpp)
# Use SPDLOG for logging.
message("Fetching SPDLOG")
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        76fb40d95455f249bd70824ecfcae7a8f0930fa3 # release-1.10.0
)
FetchContent_MakeAvailable(spdlog)
message("Fetch Complete!")
# find_package(spdlog REQUIRED)
add_library(sly ${SLY_SRC} ${SLY_HEADER})

target_link_libraries(sly PUBLIC spdlog::spdlog)