load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_test(
    name = "test",
    srcs = ["json_test.cc"],
    deps = [
        "//lib:struct_serialize",
        "@com_github_nlohmann_json//:json",
        "@com_google_googletest//:gtest_main",
    ],
)