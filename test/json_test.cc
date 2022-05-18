#include "lib/json.h"

#include "gtest/gtest.h"

namespace test {

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

template <typename StructName, int FieldIndex>
std::string GetFieldName() {
  auto field_meta = std::get<FieldIndex>(::dox::serialize::StructMeta<Student>());
  return std::get<1>(field_meta);
}

TEST(SerializeTest, Reflection) {
  int args_count = DX_ARGS_SIZE(1, 2, 3, 4, 5, 6, 7, 8, 9);
  ASSERT_EQ(9, args_count);

  ASSERT_EQ("name", (GetFieldName<Student, 0>()));
  ASSERT_EQ("age", (GetFieldName<Student, 1>()));
  ASSERT_EQ("height", (GetFieldName<Student, 2>()));
  ASSERT_EQ("address", (GetFieldName<Student, 3>()));
  ASSERT_EQ("hobbies", (GetFieldName<Student, 4>()));
  ASSERT_EQ("phone_numbers", (GetFieldName<Student, 5>()));
}

TEST(SerializeTest, SerializeToJson) {
  Student student{"jack", 10, 150.5, {"China", "Shenzhen"}, {"music", "basketball", "movie"}};
  student.phone_numbers = {{"phone1", "13888888888"}, {"phone2", "13999999999"}};
  student.scores = {{"Chemical", 80}, {"mathematics", 90}, {"physics", 88}};
  student.scores_map["Chemical"] = {"Chemical", 80};
  student.scores_map["mathematics"] = {"mathematics", 90};
  student.scores_map["physics"] = {"physics", 88};
  student.vision = {1.0f, 1.2f};

  ::nlohmann::json student_json = ::dox::serialize::SerializeToJson<Student>(student);
  ASSERT_EQ(student.name, student_json.at("/person/name_"_json_pointer).get<std::string>());
  ASSERT_EQ(student.age, student_json.at("/person/age_"_json_pointer).get<int>());
  ASSERT_EQ(student.height, student_json.find("height").value());
  ASSERT_EQ(student.address.country, student_json.at("/address/country"_json_pointer).get<std::string>());
  ASSERT_EQ(student.address.city, student_json.at("/address/city"_json_pointer).get<std::string>());
  ASSERT_EQ(student.phone_numbers["phone1"], student_json.at("/phone_numbers/phone1"_json_pointer).get<std::string>());
  ASSERT_EQ(student.phone_numbers["phone2"], student_json.at("/phone_numbers/phone2"_json_pointer).get<std::string>());
  ASSERT_EQ(student.hobbies[0], student_json.at("/hobbies/0"_json_pointer).get<std::string>());
  ASSERT_EQ(student.hobbies[1], student_json.at("/hobbies/1"_json_pointer).get<std::string>());
  ASSERT_EQ(student.hobbies[2], student_json.at("/hobbies/2"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores[0].subject, student_json.at("/scores/0/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores[0].value, student_json.at("/scores/0/value"_json_pointer).get<int>());
  ASSERT_EQ(student.scores[1].subject, student_json.at("/scores/1/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores[1].value, student_json.at("/scores/1/value"_json_pointer).get<int>());
  ASSERT_EQ(student.scores_map["Chemical"].subject,
            student_json.at("/scores_map/Chemical/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores_map["Chemical"].value,
            student_json.at("/scores_map/Chemical/value"_json_pointer).get<int>());
  ASSERT_EQ(student.scores_map["mathematics"].subject,
            student_json.at("/scores_map/mathematics/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores_map["mathematics"].value,
            student_json.at("/scores_map/mathematics/value"_json_pointer).get<int>());
  ASSERT_EQ(student.scores_map["physics"].subject,
            student_json.at("/scores_map/physics/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores_map["physics"].value, student_json.at("/scores_map/physics/value"_json_pointer).get<int>());
}

TEST(SerializeTest, DeserializeFromJson) {
  auto json_str = R"({
    "address":{
        "city":"Shenzhen", "country":"China"
    },
    "person":{"age_":10, "name_":"jack"},
    "height":150.5,
    "hobbies":["music", "basketball", "movie"],
    "phone_numbers":{"phone1":"13888888888", "phone2":"13999999999"},
    "scores":[
        {"subject":"Chemical", "value":80},
        {"subject":"mathematics", "value":90},
        {"subject":"physics", "value":88}
    ],
    "scores_map":{
        "Chemical":{"subject":"Chemical", "value":80},
        "mathematics":{"subject":"mathematics", "value":90},
        "physics":{"subject":"physics", "value":88}
    },
    "vision":[1, 1.2000000476837158]
  })";
  Student student;
  ::dox::serialize::DeserializeFromJsonString(student, json_str);
  auto student_json = ::nlohmann::json::parse(json_str, nullptr, false);
  ASSERT_EQ(student.name, student_json.at("/person/name_"_json_pointer).get<std::string>());
  ASSERT_EQ(student.age, student_json.at("/person/age_"_json_pointer).get<int>());
  ASSERT_EQ(student.height, student_json.find("height").value());
  ASSERT_EQ(student.address.country, student_json.at("/address/country"_json_pointer).get<std::string>());
  ASSERT_EQ(student.address.city, student_json.at("/address/city"_json_pointer).get<std::string>());
  ASSERT_EQ(student.phone_numbers["phone1"], student_json.at("/phone_numbers/phone1"_json_pointer).get<std::string>());
  ASSERT_EQ(student.phone_numbers["phone2"], student_json.at("/phone_numbers/phone2"_json_pointer).get<std::string>());
  ASSERT_EQ(student.hobbies[0], student_json.at("/hobbies/0"_json_pointer).get<std::string>());
  ASSERT_EQ(student.hobbies[1], student_json.at("/hobbies/1"_json_pointer).get<std::string>());
  ASSERT_EQ(student.hobbies[2], student_json.at("/hobbies/2"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores[0].subject, student_json.at("/scores/0/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores[0].value, student_json.at("/scores/0/value"_json_pointer).get<int>());
  ASSERT_EQ(student.scores[1].subject, student_json.at("/scores/1/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores[1].value, student_json.at("/scores/1/value"_json_pointer).get<int>());
  ASSERT_EQ(student.scores_map["Chemical"].subject,
            student_json.at("/scores_map/Chemical/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores_map["Chemical"].value,
            student_json.at("/scores_map/Chemical/value"_json_pointer).get<int>());
  ASSERT_EQ(student.scores_map["mathematics"].subject,
            student_json.at("/scores_map/mathematics/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores_map["mathematics"].value,
            student_json.at("/scores_map/mathematics/value"_json_pointer).get<int>());
  ASSERT_EQ(student.scores_map["physics"].subject,
            student_json.at("/scores_map/physics/subject"_json_pointer).get<std::string>());
  ASSERT_EQ(student.scores_map["physics"].value, student_json.at("/scores_map/physics/value"_json_pointer).get<int>());
}

}  // namespace test
