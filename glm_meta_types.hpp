#ifndef GLM_META_TYPES_HPP
#define GLM_META_TYPES_HPP

#include "../meta_utils/meta_utils.hpp"

inline meta_utils::MetaType VEC2 = meta_utils::MetaType(
    "glm::vec2",
    // from-string lambda
    "[](const std::string &s) { "
    "  std::regex r(R\"(\\s*\\(?\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*,\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*\\)?\\s*)\"); "
    "  std::smatch m; "
    "  if (std::regex_match(s, m, r)) { "
    "    return glm::vec2(std::stof(m[1]), std::stof(m[2])); "
    "  } "
    "  throw std::invalid_argument(\"Invalid glm::vec2 string\"); }",

    // to-string lambda
    "[](const glm::vec2 &v) { "
    "  std::ostringstream oss; "
    "  oss << '(' << v.x << \", \" << v.y << ')'; "
    "  return oss.str(); }",

    // serialize-to-bytes
    "[](const glm::vec2 &v) { "
    "  std::vector<uint8_t> buf(sizeof(glm::vec2)); "
    "  std::memcpy(buf.data(), &v, sizeof(glm::vec2)); "
    "  return buf; }",

    // get-size
    "[](const glm::vec2 &v) { return sizeof(glm::vec2); }",

    // deserialize-from-bytes
    "[](const std::vector<uint8_t> &buf) { "
    "  glm::vec2 v; "
    "  std::memcpy(&v, buf.data(), sizeof(glm::vec2)); "
    "  return v; }",

    // regex
    R"(\s*\(?\s*[-+]?[0-9]*\.?[0-9]+\s*,\s*[-+]?[0-9]*\.?[0-9]+\s*\)?\s*)");

inline meta_utils::MetaType VEC3 = meta_utils::MetaType(
    "glm::vec3",
    // from-string lambda
    "[](const std::string &s) { "
    "  std::regex "
    "r(R\"(\\s*\\(?\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*,\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*,\\s*([-+]?[0-9]*\\.?[0-9]+)\\s*\\)?"
    "\\s*)\"); "
    "  std::smatch m; "
    "  if (std::regex_match(s, m, r)) { "
    "    return glm::vec3(std::stof(m[1]), std::stof(m[2]), std::stof(m[3])); "
    "  } "
    "  throw std::invalid_argument(\"Invalid glm::vec3 string\"); }",

    // to-string lambda
    "[](const glm::vec3 &v) { "
    "  std::ostringstream oss; "
    "  oss << '(' << v.x << \", \" << v.y << \", \" << v.z << ')'; "
    "  return oss.str(); }",

    // serialize-to-bytes
    "[](const glm::vec3 &v) { "
    "  std::vector<uint8_t> buf(sizeof(glm::vec3)); "
    "  std::memcpy(buf.data(), &v, sizeof(glm::vec3)); "
    "  return buf; }",

    // get-size
    "[](const glm::vec3 &v) { return sizeof(glm::vec3); }",

    // deserialize-from-bytes
    "[](const std::vector<uint8_t> &buf) { "
    "  glm::vec3 v; "
    "  std::memcpy(&v, buf.data(), sizeof(glm::vec3)); "
    "  return v; }",

    // regex
    R"(\s*\(?\s*[-+]?[0-9]*\.?[0-9]+\s*,\s*[-+]?[0-9]*\.?[0-9]+\s*,\s*[-+]?[0-9]*\.?[0-9]+\s*\)?\s*)");

inline meta_utils::MetaType MAT4 = meta_utils::MetaType(
    "glm::mat4",
    // from-string lambda
    "[](const std::string &s) { "
    "  std::regex r(R\"(([-+]?[0-9]*\\.?[0-9]+))\"); "
    "  std::sregex_iterator it(s.begin(), s.end(), r), end; "
    "  std::vector<float> vals; "
    "  for (; it != end; ++it) vals.push_back(std::stof((*it)[1])); "
    "  if (vals.size() != 16) "
    "    throw std::invalid_argument(\"Invalid glm::mat4 string; expected 16 floats\"); "
    "  return glm::make_mat4(vals.data()); }",

    // to-string lambda
    "[](const glm::mat4 &m) { "
    "  std::ostringstream oss; "
    "  oss << '[' << m[0][0] << \", \" << m[0][1] << \", \" << m[0][2] << \", \" << m[0][3] << \"]\\n\" "
    "      << '[' << m[1][0] << \", \" << m[1][1] << \", \" << m[1][2] << \", \" << m[1][3] << \"]\\n\" "
    "      << '[' << m[2][0] << \", \" << m[2][1] << \", \" << m[2][2] << \", \" << m[2][3] << \"]\\n\" "
    "      << '[' << m[3][0] << \", \" << m[3][1] << \", \" << m[3][2] << \", \" << m[3][3] << ']'; "
    "  return oss.str(); }",

    // serialize-to-bytes
    "[](const glm::mat4 &m) { "
    "  std::vector<uint8_t> buf(sizeof(glm::mat4)); "
    "  std::memcpy(buf.data(), &m, sizeof(glm::mat4)); "
    "  return buf; }",

    // get-size
    "[](const glm::mat4 &m) { return sizeof(glm::mat4); }",

    // deserialize-from-bytes
    "[](const std::vector<uint8_t> &buf) { "
    "  glm::mat4 m; "
    "  std::memcpy(&m, buf.data(), sizeof(glm::mat4)); "
    "  return m; }",

    // regex
    R"(([-+]?[0-9]*\.?[0-9]+[,\s]*){16})");

inline void register_glm_meta_types() {
    meta_utils::MetaInclude glm_include("glm/glm.hpp", meta_utils::MetaInclude::Type::System);
    meta_utils::MetaInclude glm_include_1("glm/gtc/type_ptr.hpp", meta_utils::MetaInclude::Type::System);

    // === VEC2 ===
    {
        meta_utils::MetaType mt = VEC2;
        mt.includes_required.push_back(glm_include);
        mt.includes_required.push_back(glm_include_1);
        meta_utils::meta_types.add_new_concrete_type(mt);
    }

    // === VEC3 ===
    {
        meta_utils::MetaType mt = VEC3;
        mt.includes_required.push_back(glm_include);
        mt.includes_required.push_back(glm_include_1);
        meta_utils::meta_types.add_new_concrete_type(mt);
    }

    // === MAT4 ===
    {
        meta_utils::MetaType mt = MAT4;
        mt.includes_required.push_back(glm_include);
        mt.includes_required.push_back(glm_include_1);
        meta_utils::meta_types.add_new_concrete_type(mt);
    }
}

#endif // GLM_META_TYPES_HPP
