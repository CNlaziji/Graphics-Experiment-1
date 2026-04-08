// glad.c
// 简化版 OpenGL 函数加载器

// 覆盖 GLAPI 宏，避免 dllimport
#define GLAPI

#include <glad/glad.h>
#include <KHR/khrplatform.h>
#include <GLFW/glfw3.h>

#include <stddef.h>

// 函数指针类型
typedef void* (*GLADloadproc)(const char* name);

// 核心 OpenGL 函数指针
typedef void (*PFNGLGENVERTEXARRAYSPROC)(GLsizei, GLuint*);
typedef void (*PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
typedef void (*PFNGLBINDVERTEXARRAYPROC)(GLuint);
typedef void (*PFNGLBINDBUFFERPROC)(GLenum, GLuint);
typedef void (*PFNGLBUFFERDATAPROC)(GLenum, GLsizeiptr, const GLvoid*, GLenum);
typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);
typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint*);
typedef void (*PFNGLDELETEBUFFERSPROC)(GLsizei, const GLuint*);
typedef GLuint (*PFNGLCREATESHADERPROC)(GLenum);
typedef void (*PFNGLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar**, const GLint*);
typedef void (*PFNGLCOMPILESHADERPROC)(GLuint);
typedef void (*PFNGLGETSHADERIVPROC)(GLuint, GLenum, GLint*);
typedef void (*PFNGLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (*PFNGLDELETESHADERPROC)(GLuint);
typedef GLuint (*PFNGLCREATEPROGRAMPROC)(void);
typedef void (*PFNGLATTACHSHADERPROC)(GLuint, GLuint);
typedef void (*PFNGLLINKPROGRAMPROC)(GLuint);
typedef void (*PFNGLGETPROGRAMIVPROC)(GLuint, GLenum, GLint*);
typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (*PFNGLUSEPROGRAMPROC)(GLuint);
typedef void (*PFNGLDELETEPROGRAMPROC)(GLuint);
typedef GLint (*PFNGLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar*);
typedef void (*PFNGLUNIFORM1IPROC)(GLint, GLint);
typedef void (*PFNGLUNIFORM1FPROC)(GLint, GLfloat);
typedef void (*PFNGLUNIFORM3FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void (*PFNGLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);

// 全局函数指针
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;
PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;
PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = NULL;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = NULL;
PFNGLUNIFORM1IPROC glad_glUniform1i = NULL;
PFNGLUNIFORM1FPROC glad_glUniform1f = NULL;
PFNGLUNIFORM3FVPROC glad_glUniform3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = NULL;

// 加载单个函数
static void* load_proc(const char* name, void* user) {
    (void)user;
    return (void*)glfwGetProcAddress(name);
}

// 加载所有必要的 OpenGL 函数
int gladLoadGLLoader(GLADloadproc loadfn) {
    // 加载核心 OpenGL 函数
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)loadfn("glGenVertexArrays");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC)loadfn("glGenBuffers");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)loadfn("glBindVertexArray");
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC)loadfn("glBindBuffer");
    glad_glBufferData = (PFNGLBUFFERDATAPROC)loadfn("glBufferData");
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)loadfn("glVertexAttribPointer");
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)loadfn("glEnableVertexAttribArray");
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)loadfn("glDeleteVertexArrays");
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)loadfn("glDeleteBuffers");
    glad_glCreateShader = (PFNGLCREATESHADERPROC)loadfn("glCreateShader");
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC)loadfn("glShaderSource");
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC)loadfn("glCompileShader");
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)loadfn("glGetShaderiv");
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)loadfn("glGetShaderInfoLog");
    glad_glDeleteShader = (PFNGLDELETESHADERPROC)loadfn("glDeleteShader");
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)loadfn("glCreateProgram");
    glad_glAttachShader = (PFNGLATTACHSHADERPROC)loadfn("glAttachShader");
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)loadfn("glLinkProgram");
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)loadfn("glGetProgramiv");
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)loadfn("glGetProgramInfoLog");
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC)loadfn("glUseProgram");
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)loadfn("glDeleteProgram");
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)loadfn("glGetUniformLocation");
    glad_glUniform1i = (PFNGLUNIFORM1IPROC)loadfn("glUniform1i");
    glad_glUniform1f = (PFNGLUNIFORM1FPROC)loadfn("glUniform1f");
    glad_glUniform3fv = (PFNGLUNIFORM3FVPROC)loadfn("glUniform3fv");
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)loadfn("glUniformMatrix4fv");

    // 检查是否所有函数都加载成功
    return glad_glGenVertexArrays && glad_glGenBuffers && glad_glBindVertexArray && glad_glBindBuffer &&
           glad_glBufferData && glad_glVertexAttribPointer && glad_glEnableVertexAttribArray &&
           glad_glDeleteVertexArrays && glad_glDeleteBuffers && glad_glCreateShader &&
           glad_glShaderSource && glad_glCompileShader && glad_glGetShaderiv &&
           glad_glGetShaderInfoLog && glad_glDeleteShader && glad_glCreateProgram &&
           glad_glAttachShader && glad_glLinkProgram && glad_glGetProgramiv &&
           glad_glGetProgramInfoLog && glad_glUseProgram && glad_glDeleteProgram &&
           glad_glGetUniformLocation && glad_glUniform1i && glad_glUniform1f &&
           glad_glUniform3fv && glad_glUniformMatrix4fv;
}

// 便捷函数
int gladLoadGL(void) {
    return gladLoadGLLoader((GLADloadproc)load_proc);
}

// 函数重定向
void glGenVertexArrays(GLsizei n, GLuint* arrays) {
    glad_glGenVertexArrays(n, arrays);
}

void glGenBuffers(GLsizei n, GLuint* buffers) {
    glad_glGenBuffers(n, buffers);
}

void glBindVertexArray(GLuint array) {
    glad_glBindVertexArray(array);
}

void glBindBuffer(GLenum target, GLuint buffer) {
    glad_glBindBuffer(target, buffer);
}

void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) {
    glad_glBufferData(target, size, data, usage);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) {
    glad_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void glEnableVertexAttribArray(GLuint index) {
    glad_glEnableVertexAttribArray(index);
}

void glDeleteVertexArrays(GLsizei n, const GLuint* arrays) {
    glad_glDeleteVertexArrays(n, arrays);
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers) {
    glad_glDeleteBuffers(n, buffers);
}

GLuint glCreateShader(GLenum type) {
    return glad_glCreateShader(type);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) {
    glad_glShaderSource(shader, count, string, length);
}

void glCompileShader(GLuint shader) {
    glad_glCompileShader(shader);
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint* params) {
    glad_glGetShaderiv(shader, pname, params);
}

void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) {
    glad_glGetShaderInfoLog(shader, maxLength, length, infoLog);
}

void glDeleteShader(GLuint shader) {
    glad_glDeleteShader(shader);
}

GLuint glCreateProgram(void) {
    return glad_glCreateProgram();
}

void glAttachShader(GLuint program, GLuint shader) {
    glad_glAttachShader(program, shader);
}

void glLinkProgram(GLuint program) {
    glad_glLinkProgram(program);
}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params) {
    glad_glGetProgramiv(program, pname, params);
}

void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) {
    glad_glGetProgramInfoLog(program, maxLength, length, infoLog);
}

void glUseProgram(GLuint program) {
    glad_glUseProgram(program);
}

void glDeleteProgram(GLuint program) {
    glad_glDeleteProgram(program);
}

GLint glGetUniformLocation(GLuint program, const GLchar* name) {
    return glad_glGetUniformLocation(program, name);
}

void glUniform1i(GLint location, GLint v0) {
    glad_glUniform1i(location, v0);
}

void glUniform1f(GLint location, GLfloat v0) {
    glad_glUniform1f(location, v0);
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat* value) {
    glad_glUniform3fv(location, count, value);
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    glad_glUniformMatrix4fv(location, count, transpose, value);
}
