#pragma once

#define DX_CONCAT(arg0, arg1) DX_CONCAT_IMPL(arg0, arg1)
#define DX_CONCAT_IMPL(arg0, arg1) arg0##arg1

#define DX_ARGS_ELEM(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, \
a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, \
a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, \
a30, a31, a32, a33, a34, a35, a36, a37, a38, a39, \
a40, a41, a42, a43, a44, a45, a46, a47, a48, a49, a50, \
...) a50

#define DX_ARGS_SIZE(...)                                                                                             \
DX_ARGS_ELEM(__VA_ARGS__, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40,  \
39, 38, 37, 36, 35, 34, 33, 32, 31, 30,                   \
29, 28, 27, 26, 25, 24, 23, 22, 21, 20,                   \
19, 18, 17, 16, 15, 14, 13, 12, 11, 10,                   \
9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define DX_FOR_EACH(macro, ...) DX_CONCAT(DX_FOR_EACH_, DX_ARGS_SIZE(__VA_ARGS__))(macro, __VA_ARGS__)
#define DX_FOR_EACH_0(macro, ...)
#define DX_FOR_EACH_1(macro, arg, ...) macro(arg)
#define DX_FOR_EACH_2(macro, arg, ...) macro(arg), DX_FOR_EACH_1(macro, __VA_ARGS__)
#define DX_FOR_EACH_3(macro, arg, ...) macro(arg), DX_FOR_EACH_2(macro, __VA_ARGS__)
#define DX_FOR_EACH_4(macro, arg, ...) macro(arg), DX_FOR_EACH_3(macro, __VA_ARGS__)
#define DX_FOR_EACH_5(macro, arg, ...) macro(arg), DX_FOR_EACH_4(macro, __VA_ARGS__)
#define DX_FOR_EACH_6(macro, arg, ...) macro(arg), DX_FOR_EACH_5(macro, __VA_ARGS__)
#define DX_FOR_EACH_7(macro, arg, ...) macro(arg), DX_FOR_EACH_6(macro, __VA_ARGS__)
#define DX_FOR_EACH_8(macro, arg, ...) macro(arg), DX_FOR_EACH_7(macro, __VA_ARGS__)
#define DX_FOR_EACH_9(macro, arg, ...) macro(arg), DX_FOR_EACH_8(macro, __VA_ARGS__)
#define DX_FOR_EACH_10(macro, arg, ...) macro(arg), DX_FOR_EACH_9(macro, __VA_ARGS__)
#define DX_FOR_EACH_11(macro, arg, ...) macro(arg), DX_FOR_EACH_10(macro, __VA_ARGS__)
#define DX_FOR_EACH_12(macro, arg, ...) macro(arg), DX_FOR_EACH_11(macro, __VA_ARGS__)
#define DX_FOR_EACH_13(macro, arg, ...) macro(arg), DX_FOR_EACH_12(macro, __VA_ARGS__)
#define DX_FOR_EACH_14(macro, arg, ...) macro(arg), DX_FOR_EACH_13(macro, __VA_ARGS__)
#define DX_FOR_EACH_15(macro, arg, ...) macro(arg), DX_FOR_EACH_14(macro, __VA_ARGS__)
#define DX_FOR_EACH_16(macro, arg, ...) macro(arg), DX_FOR_EACH_15(macro, __VA_ARGS__)
#define DX_FOR_EACH_17(macro, arg, ...) macro(arg), DX_FOR_EACH_16(macro, __VA_ARGS__)
#define DX_FOR_EACH_18(macro, arg, ...) macro(arg), DX_FOR_EACH_17(macro, __VA_ARGS__)
#define DX_FOR_EACH_19(macro, arg, ...) macro(arg), DX_FOR_EACH_18(macro, __VA_ARGS__)
#define DX_FOR_EACH_20(macro, arg, ...) macro(arg), DX_FOR_EACH_19(macro, __VA_ARGS__)
#define DX_FOR_EACH_21(macro, arg, ...) macro(arg), DX_FOR_EACH_20(macro, __VA_ARGS__)
#define DX_FOR_EACH_22(macro, arg, ...) macro(arg), DX_FOR_EACH_21(macro, __VA_ARGS__)
#define DX_FOR_EACH_23(macro, arg, ...) macro(arg), DX_FOR_EACH_22(macro, __VA_ARGS__)
#define DX_FOR_EACH_24(macro, arg, ...) macro(arg), DX_FOR_EACH_23(macro, __VA_ARGS__)
#define DX_FOR_EACH_25(macro, arg, ...) macro(arg), DX_FOR_EACH_24(macro, __VA_ARGS__)
#define DX_FOR_EACH_26(macro, arg, ...) macro(arg), DX_FOR_EACH_25(macro, __VA_ARGS__)
#define DX_FOR_EACH_27(macro, arg, ...) macro(arg), DX_FOR_EACH_26(macro, __VA_ARGS__)
#define DX_FOR_EACH_28(macro, arg, ...) macro(arg), DX_FOR_EACH_27(macro, __VA_ARGS__)
#define DX_FOR_EACH_29(macro, arg, ...) macro(arg), DX_FOR_EACH_28(macro, __VA_ARGS__)
#define DX_FOR_EACH_30(macro, arg, ...) macro(arg), DX_FOR_EACH_29(macro, __VA_ARGS__)
#define DX_FOR_EACH_31(macro, arg, ...) macro(arg), DX_FOR_EACH_30(macro, __VA_ARGS__)
#define DX_FOR_EACH_32(macro, arg, ...) macro(arg), DX_FOR_EACH_31(macro, __VA_ARGS__)
#define DX_FOR_EACH_33(macro, arg, ...) macro(arg), DX_FOR_EACH_32(macro, __VA_ARGS__)
#define DX_FOR_EACH_34(macro, arg, ...) macro(arg), DX_FOR_EACH_33(macro, __VA_ARGS__)
#define DX_FOR_EACH_35(macro, arg, ...) macro(arg), DX_FOR_EACH_34(macro, __VA_ARGS__)
#define DX_FOR_EACH_36(macro, arg, ...) macro(arg), DX_FOR_EACH_35(macro, __VA_ARGS__)
#define DX_FOR_EACH_37(macro, arg, ...) macro(arg), DX_FOR_EACH_36(macro, __VA_ARGS__)
#define DX_FOR_EACH_38(macro, arg, ...) macro(arg), DX_FOR_EACH_37(macro, __VA_ARGS__)
#define DX_FOR_EACH_39(macro, arg, ...) macro(arg), DX_FOR_EACH_38(macro, __VA_ARGS__)
#define DX_FOR_EACH_40(macro, arg, ...) macro(arg), DX_FOR_EACH_39(macro, __VA_ARGS__)
#define DX_FOR_EACH_41(macro, arg, ...) macro(arg), DX_FOR_EACH_40(macro, __VA_ARGS__)
#define DX_FOR_EACH_42(macro, arg, ...) macro(arg), DX_FOR_EACH_41(macro, __VA_ARGS__)
#define DX_FOR_EACH_43(macro, arg, ...) macro(arg), DX_FOR_EACH_42(macro, __VA_ARGS__)
#define DX_FOR_EACH_44(macro, arg, ...) macro(arg), DX_FOR_EACH_43(macro, __VA_ARGS__)
#define DX_FOR_EACH_45(macro, arg, ...) macro(arg), DX_FOR_EACH_44(macro, __VA_ARGS__)
#define DX_FOR_EACH_46(macro, arg, ...) macro(arg), DX_FOR_EACH_45(macro, __VA_ARGS__)
#define DX_FOR_EACH_47(macro, arg, ...) macro(arg), DX_FOR_EACH_46(macro, __VA_ARGS__)
#define DX_FOR_EACH_48(macro, arg, ...) macro(arg), DX_FOR_EACH_47(macro, __VA_ARGS__)
#define DX_FOR_EACH_49(macro, arg, ...) macro(arg), DX_FOR_EACH_48(macro, __VA_ARGS__)
#define DX_FOR_EACH_50(macro, arg, ...) macro(arg), DX_FOR_EACH_49(macro, __VA_ARGS__)

#define DX_BOOL(arg0) DX_CONCAT(PP_BOOL_, arg0)
#define DX_BOOL_0 0
#define DX_BOOL_1 1
#define DX_BOOL_2 1
#define DX_BOOL_3 1
#define DX_BOOL_4 1
#define DX_BOOL_5 1

#define DX_IF(if, then, else) DX_CONCAT(DX_IF_, DX_BOOL(if))(then, else)
#define DX_IF_1(then, else) then
#define DX_IF_0(then, else) else

// 判断参数是否是"("开头
#define DX_IS_BEGIN_PARENS(...) \
DX_IS_BEGIN_PARENS_PROCESS(DX_IS_BEGIN_PARENS_CONCAT(DX_IS_BEGIN_PARENS_PRE_, DX_IS_BEGIN_PARENS_EAT __VA_ARGS__))

#define DX_IS_BEGIN_PARENS_PROCESS(...) DX_IS_BEGIN_PARENS_PROCESS_0(__VA_ARGS__)
#define DX_IS_BEGIN_PARENS_PROCESS_0(arg0, ...) arg0

#define DX_IS_BEGIN_PARENS_CONCAT(arg0, ...) DX_IS_BEGIN_PARENS_CONCAT_IMPL(arg0, __VA_ARGS__)
#define DX_IS_BEGIN_PARENS_CONCAT_IMPL(arg0, ...) arg0##__VA_ARGS__

#define DX_IS_BEGIN_PARENS_PRE_1 1,
#define DX_IS_BEGIN_PARENS_PRE_DX_IS_BEGIN_PARENS_EAT 0,
#define DX_IS_BEGIN_PARENS_EAT(...) 1
