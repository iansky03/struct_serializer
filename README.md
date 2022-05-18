# struct_serializer
struct_serializer is a library for convert C++ struct to JSON and vice versa

# usage
* define your struct
* add macro statement
* use ::dox::serialize::SerializeToJson for convert Struct to JSON, or use 
  ::dox::serialize::DeserializeFromJsonString for paser JSON to Struct

```C++
struct Score {
  std::string subject;
  int value;
};

struct Address {
  std::string country;
  std::string city;
};

struct Student {
  std::string name;
  int age;
  float height;
  Address address;
  std::vector<std::string> hobbies;
  std::vector<Score> scores;
  std::map<std::string, Score> scores_map;
  std::map<std::string, std::string> phone_numbers;
  std::vector<float> vision;
};

STRUCT_META_GLOBAL(Score, subject, value)
STRUCT_META_GLOBAL(Address, country, city)
STRUCT_META_GLOBAL(Student, (name, /person/name_), (age, /person/age_), height, address, hobbies, phone_numbers, scores,
            scores_map, vision)
```

```C++
Student student{"jack", 10, 150.5, {"China", "Shenzhen"}, {"music", "basketball", "movie"}};
student.phone_numbers = {{"phone1", "13888888888"}, {"phone2", "13999999999"}};
student.scores = {{"Chemical", 80}, {"mathematics", 90}, {"physics", 88}};
student.scores_map["Chemical"] = {"Chemical", 80};
student.scores_map["mathematics"] = {"mathematics", 90};
student.scores_map["physics"] = {"physics", 88};
student.vision = {1.0f, 1.2f};

::nlohmann::json student_json = ::dox::serialize::SerializeToJson<Student>(student);

Student new_stucent;
::dox::serialize::DeserializeFromJsonString(new_stucent, student_json.dump());
```

# field type support
the struct field types can be following:
* basic types: such as int、float, and std::string
* container type: std::vector<basic_type>、std::map<std::string, basic_type>
* other struct with STRUCT_META_GLOBAL statement

# macro STRUCT_META_GLOBAL
STRUCT_META_GLOBAL support normal struct definition，or you can assign an alias name for some certain fields with ()

```C++
// the alias name of "name" field is a json_pointer
STRUCT_META_GLOBAL(Student, (name, /person/name_), (age, /person/age_), height, address, hobbies, phone_numbers, scores,
            scores_map, vision)
```

# extension
struct_serializer is base on ::nlohmann::json，you can replace another json lib(even a xml lib).
see the template class in "json.h"

```C++
template <>
class TypeSerializer<Json> { }

template <>
class TypeDeserializer<Json> { }
```