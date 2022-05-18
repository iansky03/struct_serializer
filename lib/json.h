#pragma once

#include <map>
#include <memory>
#include <string>

#include "lib/deserialize_base.h"
#include "lib/serialize_base.h"

#include "nlohmann/json.hpp"

namespace dox {
namespace serialize {

using Json = ::nlohmann::json;
using JsonPointer = Json::json_pointer;

inline bool StrStartsWith(const std::string_view& str, const std::string_view& target) {
  return str.size() >= target.size() && str.substr(0, target.size()) == target;
}

template <typename Value>
inline void SetJsonField(Json& json, const Value& value, const std::string& key) {
  if (StrStartsWith(key, "/")) {
    json[JsonPointer(key)] = value;
  } else {
    json[key] = value;
  }
}

template <typename Value>
inline Value GetJsonField(const Json& json, const std::string& key) {
  if (!StrStartsWith(key, "/")) {
    auto sub_json = json.find(key);
    if (sub_json == json.end()) {
      return Value();
    }
    return sub_json->get<Value>();
  }
  JsonPointer json_pointer(key);
  if (!json.contains(json_pointer)) {
    return Value();
  }
  return json.at(json_pointer).get<Value>();
}

template <>
class TypeSerializer<Json> {
 public:
  template <typename Value>
  static void SerializeFieldValueTo(Json& model, const Value& value, const std::string& alias_name) {
    SetJsonField(model, value, alias_name);
  }

  template <typename Value>
  static void SerializeFieldValueTo(Json& model, const std::vector<Value>& value, const std::string& alias_name) {
    SetJsonField(model, ::nlohmann::json(value), alias_name);
  }

  template <typename Value>
  static void SerializeFieldValueTo(Json& model, const std::map<std::string, Value>& value,
                                    const std::string& alias_name) {
    ::nlohmann::json sub_json;
    for (auto iter = value.begin(); iter != value.end(); ++iter) {
      sub_json[iter->first] = iter->second;
    }
    SetJsonField(model, sub_json, alias_name);
  }
};

template <>
class TypeDeserializer<Json> {
 public:
  template <typename Value>
  static void GetFieldValue(const Json& json_body, Value& value, const std::string& alias_name) {
    value = GetJsonField<Value>(json_body, alias_name);
  }

  template <typename Value>
  static void GetFieldValue(const Json& json_body, std::vector<Value>& values, const std::string& alias_name) {
    auto sub_json = GetJsonField<Json>(json_body, alias_name);
    for (auto& elem : sub_json) {
      values.push_back(elem.get<Value>());
    }
  }

  static void GetFieldValue(const Json& json_body, std::vector<Json>& values, const std::string& alias_name) {
    auto sub_json = GetJsonField<Json>(json_body, alias_name);
    for (auto& elem : sub_json) {
      values.push_back(elem);
    }
  }

  template <typename Value>
  static void GetFieldValue(const Json& json_body, std::map<std::string, Value>& values,
                            const std::string& alias_name) {
    auto sub_json = GetJsonField<Json>(json_body, alias_name);
    for (auto it = sub_json.begin(); it != sub_json.end(); ++it) {
      values[it.key()] = *it;
    }
  }

  static void GetFieldValue(const Json& json_body, std::map<std::string, Json>& values, const std::string& alias_name) {
    auto sub_json = GetJsonField<Json>(json_body, alias_name);
    for (auto it = sub_json.begin(); it != sub_json.end(); ++it) {
      values[it.key()] = it.value();
    }
  }
};

template <typename T>
inline Json SerializeToJson(T& obj) {
  return SerializeTo<T, Json>(obj);
}

template <typename T>
inline Json SerializeToJsonString(T& obj) {
  auto json = SerializeTo<T, Json>(obj);
  return json.dump();
}

template <typename T>
inline void DeserializeFromJson(T& obj, const Json& json) {
  DeserializeFrom<T, Json>(obj, json);
}

template <typename T>
inline void DeserializeFromJsonString(T& obj, const std::string& json_str) {
  auto json = ::nlohmann::json::parse(json_str, nullptr, false);
  DeserializeFromJson(obj, json);
}

}  // namespace serialize
}  // namespace dox
