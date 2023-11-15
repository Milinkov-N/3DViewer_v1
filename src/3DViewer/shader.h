#ifndef SHADER_H
#define SHADER_H

class Shader {
 private:
  unsigned int m_Id;

 public:
  void create(const char* vsFilepath, const char* fsFilepath);

  void use();

  void setUniform(const char* name, float value) const;

  void setUniform(const char* name, float v1, float v2, float v3,
                  float v4) const;

  void setUniform(const char* name, float* mat) const;

  const unsigned int& id() const { return m_Id; }
};

#endif  // SHADER_H
