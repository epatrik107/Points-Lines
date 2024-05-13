//=============================================================================================
// Collection of programs from lecture slides.
// Framework for assignments. Valid from 2020.
//
// Do not change it if you want to submit a homework.
// In the homework, file operations other than printf are prohibited.
//=============================================================================================
#define _USE_MATH_DEFINES		// M_PI
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>

#if defined(__APPLE__)
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/glew.h>		// must be downloaded
#include <GL/freeglut.h>	// must be downloaded unless you have an Apple
#endif

// Resolution of screen
const unsigned int windowWidth = 600, windowHeight = 600;

//--------------------------
/**
 * @struct vec2
 * @brief A structure to represent a 2D vector.
 *
 * This structure represents a 2D vector with x and y coordinates.
 * It includes various mathematical operations that can be performed on 2D vectors.
 */
struct vec2 {
    float x; ///< The x-coordinate of the vector.
    float y; ///< The y-coordinate of the vector.

    /**
     * @brief Construct a new vec2 object.
     *
     * @param x0 The initial x-coordinate of the vector (default is 0).
     * @param y0 The initial y-coordinate of the vector (default is 0).
     */
    vec2(float x0 = 0, float y0 = 0) { x = x0; y = y0; }

    /**
     * @brief Multiply the vector by a scalar.
     *
     * @param a The scalar to multiply the vector by.
     * @return The resulting vector after multiplication.
     */
    vec2 operator*(float a) const { return vec2(x * a, y * a); }

    /**
     * @brief Divide the vector by a scalar.
     *
     * @param a The scalar to divide the vector by.
     * @return The resulting vector after division.
     */
    vec2 operator/(float a) const { return vec2(x / a, y / a); }

    /**
     * @brief Add another vector to this vector.
     *
     * @param v The other vector to add to this vector.
     * @return The resulting vector after addition.
     */
    vec2 operator+(const vec2& v) const { return vec2(x + v.x, y + v.y); }

    /**
     * @brief Subtract another vector from this vector.
     *
     * @param v The other vector to subtract from this vector.
     * @return The resulting vector after subtraction.
     */
    vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); }

    /**
     * @brief Multiply this vector by another vector.
     *
     * @param v The other vector to multiply this vector by.
     * @return The resulting vector after multiplication.
     */
    vec2 operator*(const vec2& v) const { return vec2(x * v.x, y * v.y); }

    /**
     * @brief Negate this vector.
     *
     * @return The negated vector.
     */
    vec2 operator-() const { return vec2(-x, -y); }
};
/**
 * @brief Calculate the dot product of two 2D vectors.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The dot product of the two vectors.
 */
inline float dot(const vec2& v1, const vec2& v2) {
    return (v1.x * v2.x + v1.y * v2.y);
}

/**
 * @brief Calculate the length (magnitude) of a 2D vector.
 *
 * @param v The vector whose length is to be calculated.
 * @return The length of the vector.
 */
inline float length(const vec2& v) { return sqrtf(dot(v, v)); }

/**
 * @brief Normalize a 2D vector.
 *
 * @param v The vector to be normalized.
 * @return The normalized vector.
 */
inline vec2 normalize(const vec2& v) { return v * (1 / length(v)); }

/**
 * @brief Multiply a 2D vector by a scalar.
 *
 * @param a The scalar to multiply the vector by.
 * @param v The vector to be multiplied.
 * @return The result of the multiplication.
 */
inline vec2 operator*(float a, const vec2& v) { return vec2(v.x * a, v.y * a); }
//--------------------------
/**
 * @struct vec3
 * @brief A structure to represent a 3D vector.
 *
 * This structure represents a 3D vector with x, y, and z coordinates.
 * It includes various mathematical operations that can be performed on 3D vectors.
 */
struct vec3 {
    float x; ///< The x-coordinate of the vector.
    float y; ///< The y-coordinate of the vector.
    float z; ///< The z-coordinate of the vector.

    /**
     * @brief Construct a new vec3 object.
     *
     * @param x0 The initial x-coordinate. Default is 0.
     * @param y0 The initial y-coordinate. Default is 0.
     * @param z0 The initial z-coordinate. Default is 0.
     */
    vec3(float x0 = 0, float y0 = 0, float z0 = 0) { x = x0; y = y0; z = z0; }

    /**
     * @brief Construct a new vec3 object from a vec2.
     *
     * @param v The vec2 to construct from.
     */
    vec3(vec2 v) { x = v.x; y = v.y; z = 0; }

    /**
     * @brief Multiply the vector by a scalar.
     *
     * @param a The scalar to multiply by.
     * @return The result of the multiplication.
     */
    vec3 operator*(float a) const { return vec3(x * a, y * a, z * a); }

    /**
     * @brief Divide the vector by a scalar.
     *
     * @param a The scalar to divide by.
     * @return The result of the division.
     */
    vec3 operator/(float a) const { return vec3(x / a, y / a, z / a); }

    /**
     * @brief Add another vector to this vector.
     *
     * @param v The vector to add.
     * @return The result of the addition.
     */
    vec3 operator+(const vec3& v) const { return vec3(x + v.x, y + v.y, z + v.z); }

    /**
     * @brief Subtract another vector from this vector.
     *
     * @param v The vector to subtract.
     * @return The result of the subtraction.
     */
    vec3 operator-(const vec3& v) const { return vec3(x - v.x, y - v.y, z - v.z); }

    /**
     * @brief Multiply this vector by another vector.
     *
     * @param v The vector to multiply by.
     * @return The result of the multiplication.
     */
    vec3 operator*(const vec3& v) const { return vec3(x * v.x, y * v.y, z * v.z); }

    /**
     * @brief Negate this vector.
     *
     * @return The negated vector.
     */
    vec3 operator-()  const { return vec3(-x, -y, -z); }
};

/**
 * @brief Calculate the dot product of two 3D vectors.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The dot product of the two vectors.
 */
inline float dot(const vec3& v1, const vec3& v2) { return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z); }

/**
 * @brief Calculate the length (magnitude) of a 3D vector.
 *
 * @param v The vector whose length is to be calculated.
 * @return The length of the vector.
 */
inline float length(const vec3& v) { return sqrtf(dot(v, v)); }

/**
 * @brief Normalize a 3D vector.
 *
 * @param v The vector to be normalized.
 * @return The normalized vector.
 */
inline vec3 normalize(const vec3& v) { return v * (1 / length(v)); }

/**
 * @brief Calculate the cross product of two 3D vectors.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The cross product of the two vectors.
 */
inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

/**
 * @brief Multiply a 3D vector by a scalar.
 *
 * @param a The scalar to multiply the vector by.
 * @param v The vector to be multiplied.
 * @return The result of the multiplication.
 */
inline vec3 operator*(float a, const vec3& v) { return vec3(v.x * a, v.y * a, v.z * a); }

/**
 * @struct vec4
 * @brief A structure to represent a 4D vector.
 *
 * This structure represents a 4D vector with x, y, z, and w coordinates.
 * It includes various mathematical operations that can be performed on 4D vectors.
 */
struct vec4 {
//--------------------------
    float x; ///< The x-coordinate of the vector.
    float y; ///< The y-coordinate of the vector.
    float z; ///< The z-coordinate of the vector.
    float w; ///< The w-coordinate of the vector.

    /**
     * @brief Construct a new vec4 object.
     *
     * @param x0 The initial x-coordinate. Default is 0.
     * @param y0 The initial y-coordinate. Default is 0.
     * @param z0 The initial z-coordinate. Default is 0.
     * @param w0 The initial w-coordinate. Default is 0.
     */
    vec4(float x0 = 0, float y0 = 0, float z0 = 0, float w0 = 0) { x = x0; y = y0; z = z0; w = w0; }
    float& operator[](int j) { return *(&x + j); }
    float operator[](int j) const { return *(&x + j); }

    /**
     * @brief Multiply the vector by a scalar.
     *
     * @param a The scalar to multiply by.
     * @return The result of the multiplication.
     */
    vec4 operator*(float a) const { return vec4(x * a, y * a, z * a, w * a); }

    /**
    * @brief Divide the vector by a scalar.
    *
    * @param d The scalar to divide by.
    * @return The result of the division.
    */
    vec4 operator/(float d) const { return vec4(x / d, y / d, z / d, w / d); }

    /**
     * @brief Add another vector to this vector.
     *
     * @param v The vector to add.
     * @return The result of the addition.
     */
    vec4 operator+(const vec4& v) const { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); }

    /**
    * @brief Subtract another vector from this vector.
    *
    * @param v The vector to subtract.
    * @return The result of the subtraction.
    */
    vec4 operator-(const vec4& v)  const { return vec4(x - v.x, y - v.y, z - v.z, w - v.w); }

    /**
     * @brief Multiply this vector by another vector.
     *
     * @param v The vector to multiply by.
     * @return The result of the multiplication.
     */
    vec4 operator*(const vec4& v) const { return vec4(x * v.x, y * v.y, z * v.z, w * v.w); }

    /**
     * @brief Add another vector to this vector.
     *
     * @param right The vector to add.
     */
    void operator+=(const vec4 right) { x += right.x; y += right.y; z += right.z; w += right.w; }
};

/**
 * @brief Calculate the dot product of two 4D vectors.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The dot product of the two vectors.
 */
inline float dot(const vec4& v1, const vec4& v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

/**
 * @brief Multiply a 4D vector by a scalar.
 *
 * @param a The scalar to multiply the vector by.
 * @param v The vector to be multiplied.
 * @return The result of the multiplication.
 */
inline vec4 operator*(float a, const vec4& v) {
    return vec4(v.x * a, v.y * a, v.z * a, v.w * a);
}

//---------------------------
/**
 * @struct mat4
 * @brief A structure to represent a 4x4 matrix in row-major format.
 *
 * This structure represents a 4x4 matrix with vec4 rows. It includes various constructors and operators for matrix operations.
 */
struct mat4 {
    vec4 rows[4]; ///< The rows of the matrix.

    /**
     * @brief Default constructor for the mat4 structure.
     *
     * This constructor initializes the matrix to an identity matrix.
     */
    mat4() {}

    /**
     * @brief Constructor for the mat4 structure.
     *
     * This constructor initializes the matrix with the given float values.
     */
    mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33) {
        rows[0][0] = m00; rows[0][1] = m01; rows[0][2] = m02; rows[0][3] = m03;
        rows[1][0] = m10; rows[1][1] = m11; rows[1][2] = m12; rows[1][3] = m13;
        rows[2][0] = m20; rows[2][1] = m21; rows[2][2] = m22; rows[2][3] = m23;
        rows[3][0] = m30; rows[3][1] = m31; rows[3][2] = m32; rows[3][3] = m33;
    }

    /**
     * @brief Constructor for the mat4 structure.
     *
     * This constructor initializes the matrix with the given vec4 values.
     */
    mat4(vec4 it, vec4 jt, vec4 kt, vec4 ot) {
        rows[0] = it; rows[1] = jt; rows[2] = kt; rows[3] = ot;
    }

    /**
     * @brief Overload of the [] operator.
     *
     * This operator returns a reference to the vec4 at the given index.
     */
    vec4& operator[](int i) { return rows[i]; }

    /**
     * @brief Overload of the [] operator.
     *
     * This operator returns the vec4 at the given index.
     */
    vec4 operator[](int i) const { return rows[i]; }

    /**
     * @brief Overload of the float* operator.
     *
     * This operator returns a pointer to the first element of the matrix.
     */
    operator float*() const { return (float*)this; }
};

/**
 * @brief Multiply a 4D vector by a 4x4 matrix.
 *
 * @param v The vector to be multiplied.
 * @param mat The matrix to multiply the vector by.
 * @return The result of the multiplication.
 */
inline vec4 operator*(const vec4& v, const mat4& mat) {
    return v[0] * mat[0] + v[1] * mat[1] + v[2] * mat[2] + v[3] * mat[3];
}


/**
 * @brief Multiply two 4x4 matrices.
 *
 * @param left The left matrix to be multiplied.
 * @param right The right matrix to be multiplied.
 * @return The result of the multiplication.
 */
inline mat4 operator*(const mat4& left, const mat4& right) {
    mat4 result;
    for (int i = 0; i < 4; i++) result.rows[i] = left.rows[i] * right;
    return result;
}

/**
 * @brief Generate a translation matrix.
 *
 * @param t The translation vector.
 * @return The translation matrix.
 */
inline mat4 TranslateMatrix(vec3 t) {
    return mat4(vec4(1,   0,   0,   0),
                vec4(0,   1,   0,   0),
                vec4(0,   0,   1,   0),
                vec4(t.x, t.y, t.z, 1));
}

/**
 * @brief Generate a scale matrix.
 *
 * @param s The scale vector.
 * @return The scale matrix.
 */
inline mat4 ScaleMatrix(vec3 s) {
    return mat4(vec4(s.x, 0,   0,   0),
                vec4(0,   s.y, 0,   0),
                vec4(0,   0,   s.z, 0),
                vec4(0,   0,   0,   1));
}

/**
 * @brief Generate a rotation matrix.
 *
 * @param angle The angle of rotation.
 * @param w The axis of rotation.
 * @return The rotation matrix.
 */
inline mat4 RotationMatrix(float angle, vec3 w) {
    float c = cosf(angle), s = sinf(angle);
    w = normalize(w);
    return mat4(vec4(c * (1 - w.x*w.x) + w.x*w.x, w.x*w.y*(1 - c) + w.z*s, w.x*w.z*(1 - c) - w.y*s, 0),
                vec4(w.x*w.y*(1 - c) - w.z*s, c * (1 - w.y*w.y) + w.y*w.y, w.y*w.z*(1 - c) + w.x*s, 0),
                vec4(w.x*w.z*(1 - c) + w.y*s, w.y*w.z*(1 - c) - w.x*s, c * (1 - w.z*w.z) + w.z*w.z, 0),
                vec4(0, 0, 0, 1));
}

//---------------------------
/**
 * @class Texture
 * @brief Class for handling texture operations.
 *
 * This class provides functionality for loading, creating, and managing textures.
 */
class Texture {
private:
    /**
     * @brief Load a texture from a file.
     *
     * @param pathname The path to the texture file.
     * @param transparent Whether the texture should be transparent.
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @return A vector of vec4 representing the texture.
     */
    std::vector<vec4> load(std::string pathname, bool transparent, int& width, int& height) {
        FILE * file = fopen(pathname.c_str(), "r");
        if (!file) {
            printf("%s does not exist\n", pathname.c_str());
            width = height = 0;
            return std::vector<vec4>();
        }
        unsigned short bitmapFileHeader[27];					// bitmap header
        fread(&bitmapFileHeader, 27, 2, file);
        if (bitmapFileHeader[0] != 0x4D42) printf("Not bmp file\n");
        if (bitmapFileHeader[14] != 24) printf("Only true color bmp files are supported\n");
        width = bitmapFileHeader[9];
        height = bitmapFileHeader[11];
        unsigned int size = (unsigned long)bitmapFileHeader[17] + (unsigned long)bitmapFileHeader[18] * 65536;
        fseek(file, 54, SEEK_SET);
        std::vector<unsigned char> bImage(size);
        fread(&bImage[0], 1, size, file); 	// read the pixels
        fclose(file);
        std::vector<vec4> image(width * height);
        int i = 0;
        for (unsigned int idx = 0; idx < size; idx += 3) { // Swap R and B since in BMP, the order is BGR
            float alpha = (transparent) ? (bImage[idx] + bImage[idx + 1] + bImage[idx + 2]) / 3.0f / 256.0f : 1.0f;
            image[i++] = vec4(bImage[idx + 2] / 256.0f, bImage[idx + 1] / 256.0f, bImage[idx] / 256.0f, alpha);
        }
        return image;
    }

public:
    unsigned int textureId; ///< The ID of the texture.

    /**
     * @brief Default constructor.
     */
    Texture() { textureId = 0; }

    /**
    * @brief Constructor that creates a texture from a file.
    *
    * @param pathname The path to the texture file.
    * @param transparent Whether the texture should be transparent.
    */
    Texture(std::string pathname, bool transparent = false) {
        textureId = 0;
        create(pathname, transparent);
    }

    /**
     * @brief Constructor that creates a texture from an image.
     *
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @param image The image to create the texture from.
     * @param sampling The sampling method to use.
     */
    Texture(int width, int height, const std::vector<vec4>& image, int sampling = GL_LINEAR) {
        textureId = 0;
        create(width, height, image, sampling);
    }

    /**
     * @brief Copy constructor.
     *
     * @param texture The texture to copy.
     */
    Texture(const Texture& texture) {
        printf("\nError: Texture resource is not copied on GPU!!!\n");
    }

    /**
     * @brief Assignment operator.
     *
     * @param texture The texture to assign.
     */
    void operator=(const Texture& texture) {
        printf("\nError: Texture resource is not copied on GPU!!!\n");
    }

    /**
     * @brief Create a texture from a file.
     *
     * @param pathname The path to the texture file.
     * @param transparent Whether the texture should be transparent.
     */
    void create(std::string pathname, bool transparent = false) {
        int width, height;
        std::vector<vec4> image = load(pathname, transparent, width, height);
        if (image.size() > 0) create(width, height, image);
    }

    /**
     * @brief Create a texture from an image.
     *
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @param image The image to create the texture from.
     * @param sampling The sampling method to use.
     */
    void create(int width, int height, const std::vector<vec4>& image, int sampling = GL_LINEAR) {
        if (textureId == 0) glGenTextures(1, &textureId);  				// id generation
        glBindTexture(GL_TEXTURE_2D, textureId);    // binding

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, &image[0]); // To GPU
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampling); // sampling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampling);
    }

    /**
     * @brief Destructor.
     */
    ~Texture() {
        if (textureId > 0) glDeleteTextures(1, &textureId);
    }
};

/**
 * @class GPUProgram
 * @brief A class to handle GPU programs.
 *
 * This class is responsible for creating, linking, and using GPU programs. It also provides methods to set uniform variables in the GPU program.
 */
class GPUProgram {
    unsigned int shaderProgramId = 0; ///< The ID of the shader program.
    unsigned int vertexShader = 0; ///< The ID of the vertex shader.
    unsigned int geometryShader = 0; ///< The ID of the geometry shader.
    unsigned int fragmentShader = 0; ///< The ID of the fragment shader.
    bool waitError = true; ///< Flag to indicate whether to wait for an error.

    /**
     * @brief Get error information.
     * @param handle The handle to the shader.
     */
     void getErrorInfo(unsigned int handle) { // shader error report
        int logLen, written;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            std::string log(logLen, '\0');
            glGetShaderInfoLog(handle, logLen, &written, &log[0]);
            printf("Shader log:\n%s", log.c_str());
            if (waitError) getchar();
        }
    }

    /**
     * @brief Check if a shader could be compiled.
     * @param shader The shader to check.
     * @param message The error message to display if the shader could not be compiled.
     * @return True if the shader could be compiled, false otherwise.
     */
    bool checkShader(unsigned int shader, std::string message) { // check if shader could be compiled
        int OK;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &OK);
        if (!OK) {
            printf("%s!\n", message.c_str());
            getErrorInfo(shader);
            return false;
        }
        return true;
    }

    /**
     * @brief Check if a shader program could be linked.
     * @param program The program to check.
     * @return True if the program could be linked, false otherwise.
     */
    bool checkLinking(unsigned int program) { 	// check if shader could be linked
        int OK;
        glGetProgramiv(program, GL_LINK_STATUS, &OK);
        if (!OK) {
            printf("Failed to link shader program!\n");
            getErrorInfo(program);
            return false;
        }
        return true;
    }

    /**
     * @brief Get the location of a uniform variable in the GPU program.
     * @param name The name of the uniform variable.
     * @return The location of the uniform variable.
     */
    int getLocation(const std::string& name) {	// get the address of a GPU uniform variable
        int location = glGetUniformLocation(shaderProgramId, name.c_str());
        if (location < 0) printf("uniform %s cannot be set\n", name.c_str());
        return location;
    }

public:
    /**
     * @brief Constructor.
     * @param _waitError Flag to indicate whether to wait for an error.
     */
    GPUProgram(bool _waitError = true) { shaderProgramId = 0; waitError = _waitError; }

    /**
     * @brief Copy constructor.
     * @param program The program to copy.
     */
    GPUProgram(const GPUProgram& program) {
        if (program.shaderProgramId > 0) printf("\nError: GPU program is not copied on GPU!!!\n");
    }

    /**
     * @brief Assignment operator.
     * @param program The program to assign.
     */
    void operator=(const GPUProgram& program) {
        if (program.shaderProgramId > 0) printf("\nError: GPU program is not copied on GPU!!!\n");
    }

    /**
    * @brief Get the ID of the shader program.
    * @return The ID of the shader program.
    */
    unsigned int getId() { return shaderProgramId; }

    /**
     * @brief Create a GPU program.
     * @param vertexShaderSource The source code of the vertex shader.
     * @param fragmentShaderSource The source code of the fragment shader.
     * @param fragmentShaderOutputName The output name of the fragment shader.
     * @param geometryShaderSource The source code of the geometry shader.
     * @return True if the program was created successfully, false otherwise.
     */
    bool create(const char * const vertexShaderSource,
                const char * const fragmentShaderSource, const char * const fragmentShaderOutputName,
                const char * const geometryShaderSource = nullptr)
    {
        // Create vertex shader from string
        if (vertexShader == 0) vertexShader = glCreateShader(GL_VERTEX_SHADER);
        if (!vertexShader) {
            printf("Error in vertex shader creation\n");
            exit(1);
        }
        glShaderSource(vertexShader, 1, (const GLchar**)&vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        if (!checkShader(vertexShader, "Vertex shader error")) return false;

        // Create geometry shader from string if given
        if (geometryShaderSource != nullptr) {
            if (geometryShader == 0) geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            if (!geometryShader) {
                printf("Error in geometry shader creation\n");
                exit(1);
            }
            glShaderSource(geometryShader, 1, (const GLchar**)&geometryShaderSource, NULL);
            glCompileShader(geometryShader);
            if (!checkShader(geometryShader, "Geometry shader error")) return false;
        }

        // Create fragment shader from string
        if (fragmentShader == 0) fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        if (!fragmentShader) {
            printf("Error in fragment shader creation\n");
            exit(1);
        }

        glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        if (!checkShader(fragmentShader, "Fragment shader error")) return false;

        shaderProgramId = glCreateProgram();
        if (!shaderProgramId) {
            printf("Error in shader program creation\n");
            exit(1);
        }
        glAttachShader(shaderProgramId, vertexShader);
        glAttachShader(shaderProgramId, fragmentShader);
        if (geometryShader > 0) glAttachShader(shaderProgramId, geometryShader);

        // Connect the fragmentColor to the frame buffer memory
        glBindFragDataLocation(shaderProgramId, 0, fragmentShaderOutputName);	// this output goes to the frame buffer memory

        // program packaging
        glLinkProgram(shaderProgramId);
        if (!checkLinking(shaderProgramId)) return false;

        // make this program run
        glUseProgram(shaderProgramId);
        return true;
    }

    /**
     * @brief Use the GPU program.
     */
    void Use() { 		// make this program run
        glUseProgram(shaderProgramId);
    }

    /**
     * @brief Set a uniform variable in the GPU program.
     * @param i The value to set.
     * @param name The name of the uniform variable.
     */
    void setUniform(int i, const std::string& name) {
        int location = getLocation(name);
        if (location >= 0) glUniform1i(location, i);
    }

    /**
     * @brief Set a uniform variable in the GPU program.
     * @param f The value to set.
     * @param name The name of the uniform variable.
     */
    void setUniform(float f, const std::string& name) {
        int location = getLocation(name);
        if (location >= 0) glUniform1f(location, f);
    }

    /**
     * @brief Set a uniform variable in the GPU program.
     * @param v The value to set.
     * @param name The name of the uniform variable.
     */
    void setUniform(const vec2& v, const std::string& name) {
        int location = getLocation(name);
        if (location >= 0) glUniform2fv(location, 1, &v.x);
    }

    /**
     * @brief Set a uniform variable in the GPU program.
     * @param v The value to set.
     * @param name The name of the uniform variable.
     */
    void setUniform(const vec3& v, const std::string& name) {
        int location = getLocation(name);
        if (location >= 0) glUniform3fv(location, 1, &v.x);
    }

    /**
     * @brief Set a uniform variable in the GPU program.
     * @param v The value to set.
     * @param name The name of the uniform variable.
     */
    void setUniform(const vec4& v, const std::string& name) {
        int location = getLocation(name);
        if (location >= 0) glUniform4fv(location, 1, &v.x);
    }

    /**
    * @brief Set a uniform variable in the GPU program.
    * @param mat The value to set.
    * @param name The name of the uniform variable.
    */
    void setUniform(const mat4& mat, const std::string& name) {
        int location = getLocation(name);
        if (location >= 0) glUniformMatrix4fv(location, 1, GL_TRUE, mat);
    }

    /**
     * @brief Set a uniform variable in the GPU program.
     * @param texture The texture to set.
     * @param samplerName The name of the sampler.
     * @param textureUnit The texture unit to use.
     */
    void setUniform(const Texture& texture, const std::string& samplerName, unsigned int textureUnit = 0) {
        int location = getLocation(samplerName);
        if (location >= 0) {
            glUniform1i(location, textureUnit);
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            glBindTexture(GL_TEXTURE_2D, texture.textureId);
        }
    }

    /**
     * @brief Destructor.
     */
    ~GPUProgram() { if (shaderProgramId > 0) glDeleteProgram(shaderProgramId); }
};