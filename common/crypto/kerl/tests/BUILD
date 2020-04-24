cc_test(
    name = "test_converter",
    timeout = "short",
    srcs = ["test_converter.c"],
    deps = [
        "//common/crypto/kerl:converter",
        "//common/trinary:trit_tryte",
        "@unity",
    ],
)

cc_test(
    name = "test_kerl",
    timeout = "short",
    srcs = ["test_kerl.c"],
    deps = [
        "//common/crypto/kerl",
        "//common/trinary:trit_tryte",
        ":librust_kerl",
        "@unity",
    ],
)

cc_import(
  name = "librust_kerl",
  hdrs = ["librust_kerl.h"],
  shared_library = "rust_kerl/target/release/librust_kerl.so",
)