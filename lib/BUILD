load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "struct_serialize",
    srcs = [
        ],
    hdrs = [
        "macros.h",
        "reflection.h",
        "serialize_base.h",
        "deserialize_base.h",
        "json.h",
        ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_nlohmann_json//:json",
    ],
    alwayslink = True,
)
