/**
 * @file main.cpp
 * @brief This file contains a simple OpenGL program with vertex and fragment shaders.
 */
#include "framework.h"

/**
 * @brief Vertex shader source code in GLSL.
 */
const char *const vertexSource = R"(
    #version 330               // Shader 3.3
    precision highp float;     // normal floats, makes no difference on desktop computers

    uniform mat4 MVP;          // uniform variable, the Model-View-Projection transformation matrix
    layout(location = 0) in vec2 vp;   // Varying input: vp = vertex position is expected in attrib array 0

    /**
     * @brief Main function of the vertex shader.
     */
    void main() {
        gl_Position = vec4(vp.x, vp.y, 0, 1) * MVP;      // transform vp from modeling space to normalized device space
    }
)";

/**
 * @brief Fragment shader source code in GLSL.
 */
const char *const fragmentSource = R"(
    #version 330           // Shader 3.3
    precision highp float; // normal floats, makes no difference on desktop computers

    uniform vec3 color;    // uniform variable, the color of the primitive
    out vec4 outColor;     // computed color of the current pixel

    /**
     * @brief Main function of the fragment shader.
     */
    void main() {
        outColor = vec4(color, 1); // computed color is the color of the primitive
    }
)";

GPUProgram gpuProgram; /**< GPUProgram object for vertex and fragment shaders. */
unsigned int vao; /**< Virtual world on the GPU. */

/**
 * @class Object
 * @brief Represents an object with vertices stored in a vector and associated OpenGL buffers.
 */
class Object {
    std::vector<vec3> vtx; /**< Vector storing the vertices of the object. */
    unsigned int vao; /**< Vertex Array Object (VAO) ID. */
    unsigned int vbo; /**< Vertex Buffer Object (VBO) ID. */

public:
    /**
     * @brief Constructor for the Object class.
     * Initializes VAO and VBO, and sets up vertex attribute pointers.
     */
    Object() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    /**
     * @brief Getter function for the vertex vector.
     * @return Reference to the vertex vector.
     */
    std::vector<vec3> &Vtx() {
        return vtx;
    }

    /**
     * @brief Updates the GPU buffers with the current vertex data.
     */
    void updateGpu() {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vtx.size() * sizeof(vec3), &vtx[0], GL_DYNAMIC_DRAW);
    }

    /**
     * @brief Draws the object with the specified drawing type and color.
     * @param type The type of drawing to perform (e.g., GL_TRIANGLES, GL_LINES, etc.).
     * @param color The color of the object.
     */
    void Draw(int type, vec3 color) {
        if (vtx.size() > 0)
            glBindVertexArray(vao);
        gpuProgram.setUniform(color, "color");
        glDrawArrays(type, 0, vtx.size());
    }

    /**
     * @brief Returns the number of vertices in the object.
     * @return The number of vertices.
     */
    size_t size() const {
        return vtx.size();
    }
};


/**
 * @class PointCollection
 * @brief Represents a collection of points stored in an Object.
 */
class PointCollection {
private:
    Object points; /**< Object storing the points. */

public:
    /**
     * @brief Returns the number of points in the collection.
     * @return The number of points.
     */
    int size() const {
        int count = 0;
        for (size_t i = 0; i < points.size(); i++) {
            count++;
        }
        return count;
    }

    /**
     * @brief Adds a point to the collection.
     * @param p The point to add.
     */
    void addPoint(vec3 p) {
        points.Vtx().push_back(p);
        update();
        printf("Point %3.2f, %3.2f added\n", p.x, p.y);
    }

    /**
     * @brief Updates the GPU buffers with the current point data.
     */
    void update() {
        points.updateGpu();
    }

    /**
     * @brief Searches for the nearest point to a given position.
     * @param pos The position to search around.
     * @return The nearest point to the given position.
     */
    vec3 searchNearestP(vec3 pos) {
        if (points.Vtx().size() == 0) {
            return vec3(0, 0, 1);
        }
        vec3 est = points.Vtx()[0];
        float minD = sqrt((pos.x - est.x) * (pos.x - est.x) + (pos.y - est.y) * (pos.y - est.y));
        for (int i = 1; i < points.Vtx().size(); i++) {
            float d = sqrt((pos.x - points.Vtx()[i].x) * (pos.x - points.Vtx()[i].x) +
                           (pos.y - points.Vtx()[i].y) * (pos.y - points.Vtx()[i].y));
            if (d < minD) {
                minD = d;
                est = points.Vtx()[i];
            }
        }
        return est;
    }

    /**
     * @brief Draws the points in the collection with the specified color.
     * @param color The color of the points.
     */
    void Draw(vec3 color) {
        points.Draw(GL_POINTS, color);
    }
};

/**
 * @class Line
 * @brief Represents a line defined by two points in 2D space.
 */
class Line {
private:
    vec3 p1; /**< First point of the line. */
    vec3 p2; /**< Second point of the line. */
    vec3 p3; /**< Third point of the line (for drawing). */
    vec3 p4; /**< Fourth point of the line (for drawing). */
    float a; /**< Coefficient 'a' of the line equation. */
    float b; /**< Coefficient 'b' of the line equation. */
    float c; /**< Coefficient 'c' of the line equation. */
    float px; /**< Parametric vector x-component. */
    float py; /**< Parametric vector y-component. */

public:
    /**
     * @brief Default constructor for the Line class.
     */
    Line() {}

    /**
     * @brief Constructor for the Line class.
     * @param p1 First point of the line.
     * @param p2 Second point of the line.
     */
    Line(vec3 p1, vec3 p2) {
        if (p1.x == p2.x) {
            this->a = 1;
            this->b = 0;
            this->c = -p1.x;
        } else {
            this->a = p2.y - p1.y;
            this->b = p1.x - p2.x;
            this->c = -a * p1.x - b * p1.y;
        }
        this->px = p2.x - p1.x;
        this->py = p2.y - p1.y;
        this->p1 = p1;
        this->p2 = p2;
        if (this->b != 0) {
            this->p3 = vec3(-1.0f, (-a * -1.0f - c) / b, 1);
            this->p4 = vec3(1.0f, (-a * 1.0f - c) / b, 1);
        } else {
            this->p3 = vec3(p1.x, -1.0f, 1);
            this->p4 = vec3(p1.x, 1.0f, 1);
        }
    }

    /**
     * @brief Finds the intersection point of two lines.
     * @param line2 The second line to intersect with.
     * @return The intersection point of the two lines.
     */
    vec3 findIntersectionPoint(Line line2) {
        float a1 = this->getA(), b1 = this->getB(), c1 = this->getC();
        float a2 = line2.getA(), b2 = line2.getB(), c2 = line2.getC();
        float determinant = a1 * b2 - a2 * b1;

        if (determinant == 0) {
            return {0, 0, 1};
        } else {
            float x = (b1 * c2 - b2 * c1) / determinant;
            float y = (a2 * c1 - a1 * c2) / determinant;

            return {x, y, 1};
        }
    }

    /**
     * @brief Moves the line to a new position.
     * @param clickP The new position to move the line to.
     */
    void move(vec3 clickP) {
        float a, b;
        a = this->getA();
        b = this->getB();
        float newC = -a * clickP.x - b * clickP.y;
        this->setP1(vec3(-1.0f, (-a * -1.0f - newC) / b, 1));
        this->setP2(vec3(1.0f, (-a * 1.0f - newC) / b, 1));
        this->setP3(vec3(-1.0f, (-a * -1.0f - newC) / b, 1));
        this->setP4(vec3(1.0f, (-a * 1.0f - newC) / b, 1));
    }

    // Getters and setters
    float getA() const {
        return a;
    }
    float getB() const {
        return b;
    }
    float getC() const {
        return c;
    }
    void setP1(const vec3 &p1) {
        Line::p1 = p1;
    }
    void setP2(const vec3 &p2) {
        Line::p2 = p2;
    }
    void setP3(const vec3 &p3) {
        Line::p3 = p3;
    }
    void setP4(const vec3 &p4) {
        Line::p4 = p4;
    }
    float getPx() const {
        return px;
    }
    float getPy() const {
        return py;
    }
    const vec3 &getP3() const {
        return p3;
    }
    const vec3 &getP4() const {
        return p4;
    }
    const vec3 &getP2() const {
        return p2;
    }
    const vec3 &getP1() const {
        return p1;
    }
};
/**
 * @class LineCollection
 * @brief Represents a collection of lines.
 */
class LineCollection {
private:
    Object lines; /**< Object storing the lines. */
    bool firstClick = false; /**< Flag indicating the first click when drawing a line. */
    vec3 startPoint; /**< Start point of the line when drawing. */
public:
    bool firstCLick = false;
    /**
     * @brief Returns the number of lines in the collection.
     * @return The number of lines.
     */
    Object &getLines() {
        return lines;
    }

    /**
     * @brief Returns whether the first click has occurred when drawing a line.
     * @return True if the first click has occurred, false otherwise.
     */
    int index(Line l1) {
        for (int i = 0; i < lines.Vtx().size(); i += 4) {
            bool isSameLine = (lines.Vtx()[i].x == l1.getP1().x && lines.Vtx()[i].y == l1.getP1().y &&
                               lines.Vtx()[i + 1].x == l1.getP2().x && lines.Vtx()[i + 1].y == l1.getP2().y) ||
                              (lines.Vtx()[i].x == l1.getP2().x && lines.Vtx()[i].y == l1.getP2().y &&
                               lines.Vtx()[i + 1].x == l1.getP1().x && lines.Vtx()[i + 1].y == l1.getP1().y);

            if (isSameLine) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @brief Adds a line to the collection.
     * @param l The line to add.
     */
    void addLine(Line l) {
        float a, b, c, px, py;
        lines.Vtx().push_back(l.getP1());
        lines.Vtx().push_back(l.getP2());
        lines.Vtx().push_back(l.getP3());
        lines.Vtx().push_back(l.getP4());
        a = l.getA();
        b = l.getB();
        c = -a * l.getP1().x - b * l.getP1().y;
        px = l.getPx();
        py = l.getPy();
        printf("Line added\n");
        printf("\tImplicit: %3.2f x + %3.2f y + %3.2f = 0\n", a, b, c);
        printf("\tParametric: r<t> = <%3.2f, %3.2f> + <%3.2f, %3.2f>t\n", l.getP1().x, l.getP1().y, px, py);
        update();
    }

    /**
     * @brief Starts drawing a line from a given point.
     * @param startPoint The starting point of the line.
     */
    void startDrawing(vec3 startPoint) {
        firstCLick = true;
        this->startPoint = startPoint;

    }

    /**
     * @brief Finishes drawing a line to a given point.
     * @param endPoint The end point of the line.
     */
    void finishDrawing(vec3 endPoint) {
        firstCLick = false;
        addLine(Line(startPoint, endPoint));
    }

    /**
     * @brief Checks if the drawing is in the first click phase.
     * @return True if in the first click phase, false otherwise.
     */
    bool isFirst() const {
        return firstCLick;
    }

    /**
     * @brief Updates the GPU buffers with the current line data.
     */
    void update() {
        lines.updateGpu();
    }

    /**
    * @brief Draws the lines in the collection.
    * @param type The type of drawing (e.g., GL_LINES, GL_LINE_STRIP, etc.).
    * @param color The color of the lines.
    */
    void Draw(int type, vec3 color) {
        lines.Draw(type, color);
    }

    /**
     * @brief Finds the nearest line to a given position.
     * @param clickP The position to search around.
     * @return The index of the nearest line.
     */
    int findNearestLine(vec3 clickP) {
        float minDistance = 20;
        int nearestLine = -1;
        for (size_t i = 0; i < lines.Vtx().size(); i += 4) {
            vec3 firstPoint = lines.Vtx()[i];
            vec3 secPoint = lines.Vtx()[i + 1];
            vec3 lineVector = secPoint - firstPoint;
            vec3 pointVector = clickP - firstPoint;

            float distanceLine = length(cross(lineVector, pointVector)) / length(lineVector);

            if (distanceLine < minDistance && distanceLine < 0.01) {
                minDistance = distanceLine;
                nearestLine = i;
            }
        }

        return nearestLine;
    }

};

PointCollection *points; /**< Pointer to a PointCollection object. */
LineCollection *lines; /**< Pointer to a LineCollection object. */

/**
 * @brief Initializes the OpenGL context.
 */
 void onInitialization() {
    glViewport(0, 0, windowWidth, windowHeight);

    glGenVertexArrays(1, &vao);    // get 1 vao id
    glBindVertexArray(vao);        // make it active

    unsigned int vbo;        // vertex buffer object
    glGenBuffers(1, &vbo);    // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Geometry with 24 bytes (6 floats or 3 x 2 coordinates)
    float vertices[] = {-0.8f, -0.8f, -0.6f, 1.0f, 0.8f, -0.2f};
    glBufferData(GL_ARRAY_BUFFER,    // Copy to GPU target
                 sizeof(vertices),  // # bytes
                 vertices,            // address
                 GL_STATIC_DRAW);    // we do not change later

    glEnableVertexAttribArray(0);  // AttribArray 0
    glVertexAttribPointer(0,       // vbo -> AttribArray 0
                          2, GL_FLOAT, GL_FALSE, // two floats/attrib, not fixed-point
                          0, NULL);             // stride, offset: tightly packed


    points = new PointCollection();
    lines = new LineCollection();
    // create program for the GPU
    gpuProgram.create(vertexSource, fragmentSource, "outColor");
    glPointSize(10.0f);
    glLineWidth(3.0f);
}

/**
 * @brief Handles the display event.
 */
void onDisplay() {
    glClearColor(128 / 255.0f, 128 / 255.0f, 128 / 255.0f, 1.0f);     // background color
    glClear(GL_COLOR_BUFFER_BIT); // clear frame buffer

    // Set color to (0, 1, 0) = green
    int location = glGetUniformLocation(gpuProgram.getId(), "color");
    glUniform3f(location, 1.0f, 0.0f, 0.0f); // 3 floats

    float MVPtransf[4][4] = {1, 0, 0, 0,    // MVP matrix,
                             0, 1, 0, 0,    // row-major!
                             0, 0, 1, 0,
                             0, 0, 0, 1};

    location = glGetUniformLocation(gpuProgram.getId(), "MVP");    // Get the GPU location of uniform variable MVP
    glUniformMatrix4fv(location, 1, GL_TRUE,
                       &MVPtransf[0][0]);    // Load a 4x4 row-major float matrix to the specified location

    glBindVertexArray(vao);  // Draw call


    lines->Draw(GL_LINES, vec3(0, 1, 1));
    points->Draw(vec3(1, 0, 0));

    glutSwapBuffers(); // exchange buffers for double buffering
}

enum Key {

    p, l, m, i
};
Key current = p;


/**
 * @brief Handles the keyboard event when a key is pressed.
 */
 void onKeyboard(unsigned char key, int pX, int pY) {
    if (key == 'p') {
        current = p;
        printf("Define points\n");
    }
    if (key == 'l') {
        current = l;
        printf("Define lines\n");
    }

    if (key == 'm') {
        current = m;
        printf("Move\n");
    }
    if (key == 'i') {
        current = i;
        printf("Intersect\n");
    }
}


/**
 * @brief Handles the keyboard event when a key is released.
 */
 void onKeyboardUp(unsigned char key, int pX, int pY) {
    if (key == 'p') {
        current = p;
    }
    if (key == 'l') {
        current = l;
    }
    if (key == 'm') {
        current = m;
    }
    if (key == 'i') {
        current = i;
    }

}

Line l1; /**< First line for intersection calculation. */
Line l2; /**< Second line for intersection calculation. */
Line moved; /**< Line being moved. */
int idx; /**< Index of the line being moved. */
bool firstLine = false; /**< Flag indicating the first line for intersection calculation. */


/**
 * @brief Handles the mouse motion event.
 */
 void onMouseMotion(int pX,
                   int pY) {    // pX, pY are the pixel coordinates of the cursor in the coordinate system of the operation system
    // Convert to normalized device space
    float cX = 2.0f * pX / windowWidth - 1;    // flip y axis
    float cY = 1.0f - 2.0f * pY / windowHeight;
    if (idx != -1 && current == m) {
        moved.move(vec3(cX, cY, 1));
        lines->getLines().Vtx()[idx] = lines->getLines().Vtx()[idx + 2] = moved.getP1();
        lines->getLines().Vtx()[idx + 1] = lines->getLines().Vtx()[idx + 3] = moved.getP2();;
        lines->update();
        glutPostRedisplay();
    }
}

/**
 * @brief Handles the mouse click event.
 */
 void onMouse(int button, int state, int pX,
             int pY) { // pX, pY are the pixel coordinates of the cursor in the coordinate system of the operation system
    // Convert to normalized device space
    float cX = 2.0f * pX / windowWidth - 1;    // flip y axis
    float cY = 1.0f - 2.0f * pY / windowHeight;
    char *buttonStat;
    switch (state) {
        case GLUT_DOWN: {
            buttonStat = "pressed";
            break;
        }

        case GLUT_UP:
            buttonStat = "released";
            break;
    }

    switch (button) {
        case GLUT_LEFT_BUTTON: {
            if (current == p && state == GLUT_DOWN) {
                points->addPoint(vec3(cX, cY, 1));
                points->update();
                glutPostRedisplay();
            }
            if (current == l && state == GLUT_DOWN && points->size()>=2) {
                if (!lines->isFirst()) {
                    lines->startDrawing(points->searchNearestP(vec3(cX, cY, 1)));

                } else {
                    lines->finishDrawing(points->searchNearestP(vec3(cX, cY, 1)));
                    lines->update();
                    glutPostRedisplay();
                }
            }

            if (current == i && state == GLUT_DOWN) {
                vec3 clickPos = vec3(cX, cY, 1);
                idx = lines->findNearestLine(clickPos);
                if (idx != -1) {
                    if (!firstLine) {
                        l1 = Line(lines->getLines().Vtx()[idx], lines->getLines().Vtx()[idx + 1]);
                        firstLine = true;
                    } else {
                        l2 = Line(lines->getLines().Vtx()[idx], lines->getLines().Vtx()[idx + 1]);
                        points->addPoint(l1.findIntersectionPoint(l2));
                        points->update();
                        glutPostRedisplay();
                        l1 = l2 = Line(vec3(0, 0, 0), vec3(0, 0, 0));
                        firstLine = false;
                        idx = -1;
                    }
                }
            }
            if (current == m && state == GLUT_DOWN) {
                idx = lines->findNearestLine(vec3(cX, cY, 1));
                moved = Line(lines->getLines().Vtx()[idx], lines->getLines().Vtx()[idx + 1]);
            } else if (current == m && state != GLUT_DOWN) {
                idx = -1;
                moved = Line(vec3(0, 0, 0), vec3(0, 0, 0));

            }

        }
            break;

        case GLUT_MIDDLE_BUTTON:
            printf("Middle button %s at (%3.2f, %3.2f)\n", buttonStat, cX, cY);
            break;
        case GLUT_RIGHT_BUTTON:
            printf("Right button %s at (%3.2f, %3.2f)\n", buttonStat, cX, cY);
            break;
    }

}

/**
 * @brief Handles the idle event.
 */
 void onIdle() {
    long time = glutGet(GLUT_ELAPSED_TIME); // elapsed time since the start of the program
}
