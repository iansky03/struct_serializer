#pragma once

#include <map>
#include <vector>

#include "lib/reflection.h"

namespace dox {
namespace serialize {

template <typename Model>
class TypeDeserializer {
 public:
  template <typename Value>
  static void GetFieldValue(const Model& model, Value& value, const std::string& alias_name) {}
};

template <typename StructName, typename FieldMeta, typename Model>
void DeserializeField(StructName& obj, const FieldMeta& field_meta, const Model& model);

template <typename T, typename Model>
inline void DeserializeFrom(T& obj, const Model& model) {
  auto struct_meta = StructMeta<T>();
  static_assert(std::tuple_size<decltype(struct_meta)>::value != 0,
                "StructMeta<T>() for type T should be specialized to return  FieldMeta tuples, like ((&T::field, "
                "field_name, alias_name), ...)");

  ForEachTuple(struct_meta, [&obj, &model](auto&& field_meta) { DeserializeField(obj, field_meta, model); });
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename MemberPtr>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value == 0)> DeserializeFieldValue(
    T& obj, const Model& model, const MemberPtr& member_ptr, const FieldMeta& field_meta,
    const FieldStructMeta& field_struct_meta) {
  auto alias_name = std::get<2>(field_meta);
  auto& field_value = obj.*member_ptr;
  TypeDeserializer<Model>::GetFieldValue(model, field_value, alias_name);
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename MemberPtr>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value > 0)> DeserializeFieldValue(
    T& obj, const Model& model, const MemberPtr& member_ptr, const FieldMeta& field_meta,
    const FieldStructMeta& field_struct_met) {
  auto alias_name = std::get<2>(field_meta);
  Model sub_model;
  TypeDeserializer<Model>::GetFieldValue(model, sub_model, alias_name);
  auto& field_value = obj.*(member_ptr);
  DeserializeFrom(field_value, sub_model);
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value == 0)> DeserializeVectorFieldValue(
    T& obj, const Model& model, std::vector<Element> T::*ptr, const FieldMeta& field_meta,
    FieldStructMeta field_struct_meta) {
  auto alias_name = std::get<2>(field_meta);
  // Vector 基本类型处理
  std::vector<Element> elements;
  TypeDeserializer<Model>::GetFieldValue(model, elements, alias_name);
  obj.*ptr = elements;
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value > 0)> DeserializeVectorFieldValue(
    T& obj, const Model& model, std::vector<Element> T::*ptr, const FieldMeta& field_meta,
    FieldStructMeta field_struct_meta) {
  auto alias_name = std::get<2>(field_meta);
  std::vector<Model> sub_models;
  TypeDeserializer<Model>::GetFieldValue(model, sub_models, alias_name);
  std::vector<Element>& elements = obj.*(ptr);
  elements.clear();
  for (auto iter = sub_models.begin(); iter != sub_models.end(); ++iter) {
    Element elem;
    DeserializeFrom(elem, *iter);
    elements.push_back(elem);
  }
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
void DeserializeFieldValue(T& obj, const Model& model, std::vector<Element> T::*ptr, const FieldMeta& field_meta,
                           FieldStructMeta field_struct_meta) {
  auto element_struct_schema = StructMeta<Element>();
  DeserializeVectorFieldValue(obj, model, ptr, field_meta, element_struct_schema);
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value == 0)> DeserializeMapFieldValue(
    T& obj, const Model& model, std::map<std::string, Element> T::*ptr, const FieldMeta& field_meta,
    FieldStructMeta field_struct_meta) {
  auto alias_name = std::get<2>(field_meta);
  // Map 基本类型处理
  std::map<std::string, Element> elements;
  TypeDeserializer<Model>::GetFieldValue(model, elements, alias_name);
  obj.*ptr = elements;
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
std::enable_if_t<(std::tuple_size<FieldStructMeta>::value > 0)> DeserializeMapFieldValue(
    T& obj, const Model& model, std::map<std::string, Element> T::*ptr, const FieldMeta& field_meta,
    FieldStructMeta field_struct_meta) {
  auto alias_name = std::get<2>(field_meta);
  std::map<std::string, Model> sub_models;
  TypeDeserializer<Model>::GetFieldValue(model, sub_models, alias_name);
  std::map<std::string, Element>& elements = obj.*(ptr);
  elements.clear();
  for (auto iter = sub_models.begin(); iter != sub_models.end(); ++iter) {
    Element elem;
    DeserializeFrom(elem, iter->second);
    elements[iter->first] = elem;
  }
}

template <typename T, typename Model, typename FieldMeta, typename FieldStructMeta, typename Element>
void DeserializeFieldValue(T& obj, const Model& model, std::map<std::string, Element> T::*ptr,
                           const FieldMeta& field_meta, FieldStructMeta field_struct_meta) {
  auto element_struct_schema = StructMeta<Element>();
  DeserializeMapFieldValue(obj, model, ptr, field_meta, element_struct_schema);
}

template <typename StructName, typename FieldMeta, typename Model>
void DeserializeField(StructName& obj, const FieldMeta& field_meta, const Model& model) {
  static_assert(std::tuple_size<FieldMeta>::value >= 2 && is_field_pointer_v<std::tuple_element_t<0, FieldMeta>>,
                "FieldMeta tuple should be (&T::field, field_name, alias_name)");

  auto member_ptr = std::get<0>(field_meta);
  auto field_value = obj.*(member_ptr);
  auto field_struct_meta = StructMeta<std::decay_t<decltype(field_value)>>();
  DeserializeFieldValue(obj, model, member_ptr, field_meta, field_struct_meta);
}

}  // namespace serialize
}  // namespace dox
