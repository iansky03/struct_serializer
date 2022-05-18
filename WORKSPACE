workspace(name = "struct_serializer")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-main",
    urls = ["https://github.com/google/googletest/archive/master.zip"],
)

http_archive(
    name = "com_github_nlohmann_json",
    build_file = "//third_party/json:json.BUILD",
    sha256 = "61e605be15e88deeac4582aaf01c09d616f8302edde7adcaba9261ddc3b4ceca",
    strip_prefix = "include",
    urls = ["https://github.com/nlohmann/json/releases/download/v3.10.2/include.zip"],
)
