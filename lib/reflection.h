#pragma once

#include <string>
#include <tuple>

#include "lib/macros.h"

namespace dox {
namespace serialize {

// Struct成员宏定义，最终输出std::tuple用于成员信息描述
// tuple字段含义分别为member_pointer, field_name, alias_name(alias_name用于序列化，对应json name、xml tag等)
// 输入参数格式为单个字段名称field_name(此时默认alias_name == field_name) 或者带括号的名称列表(name, alias)
#define STRUCT_FIELD_META(FieldName)               \
  DX_CONCAT(DX_IF_, DX_IS_BEGIN_PARENS(FieldName)) \
  (STRUCT_FIELD_META_REAL(FieldName), STRUCT_FIELD_META_REAL((FieldName)))

#define STRUCT_FIELD_META_REAL(arg) STRUCT_FIELD_META_IMPL arg
#define STRUCT_FIELD_META_IMPL(...) DX_CONCAT(STRUCT_FIELD_META_IMPL_, DX_ARGS_SIZE(__VA_ARGS__))(__VA_ARGS__)
#define STRUCT_FIELD_META_IMPL_1(FieldName) std::make_tuple(&_Struct::FieldName, #FieldName, #FieldName)
#define STRUCT_FIELD_META_IMPL_2(FieldName, AliasName) std::make_tuple(&_Struct::FieldName, #FieldName, #AliasName)

template <typename T>
struct is_field_pointer : std::false_type {};

template <typename C, typename T>
struct is_field_pointer<T C::*> : std::true_type {};

template <typename T>
constexpr auto is_field_pointer_v = is_field_pointer<T>::value;

template <typename T>
struct has_struct_meta_member {
  template <typename U>
  static void check(decltype(&U::StructMeta));

  template <typename U>
  static int check(...);

  enum {value = std::is_void_v<decltype(check<T>(0))>};
};

//template <typename T>
//inline constexpr std::enable_if_t<has_struct_meta_member<T>::value == 0, std::tuple<>> StructMeta() {
//  return std::make_tuple();
//}
//
//template <typename T>
//inline constexpr std::enable_if_t<has_struct_meta_member<T>::value == 1, decltype(T::StructMeta())> StructMeta() {
//  return T::StructMeta();
//}

template <typename T>
inline constexpr auto StructMetaImpl(const T& t) {
  return std::make_tuple();
}

template <typename T>
inline constexpr auto StructMeta() {
  return StructMetaImpl(T{});
}

#define STRUCT_META(StructName, ...)                                     \
  inline static constexpr auto StructMeta() {                            \
    using _Struct = StructName;                                          \
    return std::make_tuple(DX_FOR_EACH(STRUCT_FIELD_META, __VA_ARGS__)); \
  }

#define STRUCT_META_GLOBAL(StructName, ...)                              \
  constexpr auto StructMetaImpl(const StructName& s) {                   \
    using _Struct = StructName;                                          \
    return std::make_tuple(DX_FOR_EACH(STRUCT_FIELD_META, __VA_ARGS__)); \
  }

template <typename Tuple, typename Fn, std::size_t... I>
inline constexpr void ForEachTuple(Tuple&& tuple, Fn&& fn, std::index_sequence<I...>) {
  ((void)fn(std::get<I>(std::forward<Tuple>(tuple))), ...);
}

template <typename Tuple, typename Fn>
inline constexpr void ForEachTuple(Tuple&& tuple, Fn&& fn) {
  ForEachTuple(std::forward<Tuple>(tuple), std::forward<Fn>(fn),
               std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
}

}  // namespace serialize
}  // namespace dox