#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "lib/reflection.h"

namespace dox {
namespace serialize {

template <typename Model>
class TypeSerializer {
 public:
  template <typename Value>
  static void SerializeFieldValueTo(Model& model, const Value& value, const std::string& alias_name) {}
};

template <typename StructName, typename FieldMeta, typename Model>
void SerializeField(StructName& obj, const FieldMeta& field_meta, Model& model);

template <typename T, typename Model>
inline Model SerializeTo(T& obj) {
  auto struct_meta = StructMeta<T>();
  static_assert(std::tuple_size<decltype(struct_meta)>::value != 0,
                "StructMeta<T>() for type T should be specialized to return  FieldMeta tuples, like ((&T::field, "
                "field_name, alias_name), ...)");
  Model model;
  ForEachTuple(struct_meta, [&obj, &model](auto&& field_meta) { SerializeField(obj, field_meta, model); });
  return model;
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename MemberPtr>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value == 0)> SerializeFieldValue(
    T& obj, Model& model, const MemberPtr& member_ptr, const FieldMeta& field_meta,
    const FieldStructMeta& field_struct_meta) {
  auto value = obj.*member_ptr;
  auto alias_name = std::get<2>(field_meta);
  TypeSerializer<Model>::SerializeFieldValueTo(model, value, alias_name);
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename MemberPtr>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value > 0)> SerializeFieldValue(
    T& obj, Model& model, const MemberPtr& member_ptr, const FieldMeta& field_meta,
    const FieldStructMeta& field_struct_met) {
  auto field_value = obj.*member_ptr;
  auto alias_name = std::get<2>(field_meta);
  auto field_model = SerializeTo<std::decay_t<decltype(field_value)>, Model>(field_value);
  TypeSerializer<Model>::SerializeFieldValueTo(model, field_model, alias_name);
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value == 0)> SerializeVectorFieldValue(
    T& obj, Model& model, std::vector<Element> T::*ptr, const FieldMeta& field_meta,
    FieldStructMeta field_struct_meta) {
  std::vector<Element> items = obj.*ptr;
  // Vector 基本类型处理
  TypeSerializer<Model>::SerializeFieldValueTo(model, items, std::get<2>(field_meta));
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value > 0)> SerializeVectorFieldValue(
    T& obj, Model& model, std::vector<Element> T::*ptr, const FieldMeta& field_meta,
    FieldStructMeta field_struct_meta) {
  std::vector<Element> items = obj.*ptr;
  // Vector Struct类型处理
  std::vector<Model> element_models;
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    auto element_model = SerializeTo<Element, Model>(*iter);
    element_models.push_back(element_model);
  }
  TypeSerializer<Model>::SerializeFieldValueTo(model, element_models, std::get<2>(field_meta));
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
void SerializeFieldValue(T& obj, Model& model, std::vector<Element> T::*ptr, const FieldMeta& field_meta,
                         FieldStructMeta field_struct_meta) {
  auto element_struct_schema = StructMeta<Element>();
  SerializeVectorFieldValue(obj, model, ptr, field_meta, element_struct_schema);
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value == 0)> SerializeMapFieldValue(
    T& obj, Model& model, std::map<std::string, Element> T::*ptr, const FieldMeta& field_meta,
    FieldStructMeta field_struct_meta) {
  std::map<std::string, Element> items = obj.*ptr;
  // Map element基本类型处理
  TypeSerializer<Model>::SerializeFieldValueTo(model, items, std::get<2>(field_meta));
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value > 0)> SerializeMapFieldValue(
    T& obj, Model& model, std::map<std::string, Element> T::*ptr, const FieldMeta& field_meta,
    FieldStructMeta field_struct_meta) {
  std::map<std::string, Element> items = obj.*ptr;
  std::map<std::string, Model> element_models;
  // Map Struct类型处理
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    auto element_model = SerializeTo<Element, Model>(iter->second);
    element_models[iter->first] = element_model;
  }
  TypeSerializer<Model>::SerializeFieldValueTo(model, element_models, std::get<2>(field_meta));
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
void SerializeFieldValue(T& obj, Model& model, std::map<std::string, Element> T::*ptr, const FieldMeta& field_meta,
                         FieldStructMeta field_struct_meta) {
  auto element_struct_schema = StructMeta<Element>();
  SerializeMapFieldValue(obj, model, ptr, field_meta, element_struct_schema);
}

template <typename StructName, typename FieldMeta, typename Model>
void SerializeField(StructName& obj, const FieldMeta& field_meta, Model& model) {
  static_assert(std::tuple_size<FieldMeta>::value >= 2 && is_field_pointer_v<std::tuple_element_t<0, FieldMeta>>,
                "FieldMeta tuple should be (&T::field, field_name, alias_name)");

  auto member_ptr = std::get<0>(field_meta);
  auto field_value = obj.*(member_ptr);
  auto field_struct_meta = StructMeta<std::decay_t<decltype(field_value)>>();
  SerializeFieldValue(obj, model, member_ptr, field_meta, field_struct_meta);
}

}  // namespace serialize
}  // namespace dox
