#include <GL/glut.h>
#include <string>
#include <algorithm>
#include <iostream>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int TABLE_ROWS = 2;
const int TABLE_COLUMNS = 5;
const int ELEMENT_SIZE = 100;
const int ELEMENT_PADDING = 20;
int infoWindowID;
int mouseX = 0;
int mouseY = 0;

struct Element {
    int atomicNumber;
    std::string symbol;
    std::string name;
    int group;
};

Element elements[] = { { 1, "H", "Hydrogen", 1 }, { 2, "He", "Helium", 18 }, {
    3, "Li", "Lithium", 1 }, { 4, "Be", "Beryllium", 2 }, { 5, "B", "Boron",
    13 }, { 6, "C", "Carbon", 14 }, { 7, "N", "Nitrogen", 15 }, { 8, "O",
    "Oxygen", 16 }, { 9, "F", "Fluorine", 17 }, { 10, "Ne", "Neon", 18 } };

Element* selectedElement = nullptr;
int selectedElementWindowID = 0;
bool isStarted = false;
bool isStopped = false;


void displayDeveloper() {
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos2i(10, 50);
    std::string header = "Periodic Table";
    for (char c : header) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}


void displayElementInfo() {
    int infoWindowWidth = 500;
    int infoWindowHeight = 500;
    int infoWindowPosX = (glutGet(GLUT_WINDOW_WIDTH) - infoWindowWidth) / 2;
    int infoWindowPosY = (glutGet(GLUT_WINDOW_HEIGHT) - infoWindowHeight) / 2;
    glutInitWindowPosition(infoWindowPosX, infoWindowPosY);
    glutInitWindowSize(infoWindowWidth, infoWindowHeight);
    infoWindowID = glutCreateWindow("Element Info");

    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, infoWindowWidth, 0, infoWindowHeight);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.2f, 0.2f, 0.2f);
    int textPosX = 10;
    int textPosY = infoWindowHeight -50;
    glRasterPos2i(textPosX, textPosY);

    std::string elementName = "Selected Element: " + selectedElement->name;
    for (char c : elementName) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Draw buttons
    int buttonWidth = 80;
    int buttonHeight = 50;
    int buttonPadding = 20;
    int buttonStartPosX = (infoWindowWidth - buttonWidth) / 12;
    int buttonStartPosY = textPosY - buttonHeight - buttonPadding;
    int buttonStopPosX = (infoWindowWidth - buttonWidth) / 12;
    int buttonStopPosY = textPosY - 2 * (buttonHeight + buttonPadding);
    int buttonExitPosX = (infoWindowWidth - buttonWidth) / 12;
    int buttonExitPosY = textPosY - 3 * (buttonHeight + buttonPadding);

    // Button 1: Start
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2i(buttonStartPosX, buttonStartPosY);
    glVertex2i(buttonStartPosX + buttonWidth, buttonStartPosY);
    glVertex2i(buttonStartPosX + buttonWidth, buttonStartPosY + buttonHeight);
    glVertex2i(buttonStartPosX, buttonStartPosY + buttonHeight);
    glEnd();

    // Button 2: Stop
    glBegin(GL_QUADS);
    glVertex2i(buttonStopPosX, buttonStopPosY);
    glVertex2i(buttonStopPosX + buttonWidth, buttonStopPosY);
    glVertex2i(buttonStopPosX + buttonWidth, buttonStopPosY + buttonHeight);
    glVertex2i(buttonStopPosX, buttonStopPosY + buttonHeight);
    glEnd();

    // Button 3: Exit
    glBegin(GL_QUADS);
    glVertex2i(buttonExitPosX, buttonExitPosY);
    glVertex2i(buttonExitPosX + buttonWidth, buttonExitPosY);
    glVertex2i(buttonExitPosX + buttonWidth, buttonExitPosY + buttonHeight);
    glVertex2i(buttonExitPosX, buttonExitPosY + buttonHeight);
    glEnd();

    // Draw button labels
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(buttonStartPosX + 10, buttonStartPosY + 20);
    std::string labelStart = "Start";
    for (char c : labelStart) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }

    glRasterPos2i(buttonStopPosX + 10, buttonStopPosY + 20);
    std::string labelStop = "Stop";
    for (char c : labelStop) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }

    glRasterPos2i(buttonExitPosX + 10, buttonExitPosY + 20);
    std::string labelExit = "Exit";
    for (char c : labelExit) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }

    glutSwapBuffers();
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Store the mouse coordinates
        mouseX = x;
        mouseY = y;

        // Redraw the scene to update the selected element
        glutPostRedisplay();
    }
}
void drawElement(const Element& element, int row, int col) {
    // Calculate the position of the element
    int x = col * (ELEMENT_SIZE + ELEMENT_PADDING);
    int y = row * (ELEMENT_SIZE + ELEMENT_PADDING);

    // Calculate the center position of the graphic window
    int centerX = WINDOW_WIDTH / 2;
    int centerY = WINDOW_HEIGHT / 2;

    // Calculate the starting position for the element to be in the center
    int startX = centerX - (TABLE_COLUMNS * ELEMENT_SIZE + (TABLE_COLUMNS - 1) * ELEMENT_PADDING) / 2;
    int startY = centerY - (TABLE_ROWS * ELEMENT_SIZE + (TABLE_ROWS - 1) * ELEMENT_PADDING) / 2;

    // Calculate the position of the element in the center
    int centerXPos = startX + x;
    int centerYPos = startY + y;

    // Draw a rectangle for the element
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2i(centerXPos, centerYPos);
    glVertex2i(centerXPos + ELEMENT_SIZE, centerYPos);
    glVertex2i(centerXPos + ELEMENT_SIZE, centerYPos + ELEMENT_SIZE);
    glVertex2i(centerXPos, centerYPos + ELEMENT_SIZE);
    glEnd();

    // Draw the atomic number
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos2i(centerXPos + 5, centerYPos + 15);
    std::string atomicNumber = std::to_string(element.atomicNumber);
    for (char c : atomicNumber) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Draw the symbol
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos2i(centerXPos + 5, centerYPos + 30);
    for (char c : element.symbol) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Draw the name
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos2i(centerXPos + 5, centerYPos + 45);
    for (char c : element.name) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }

    // Draw the group
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos2i(centerXPos + ELEMENT_SIZE - 50, centerYPos + ELEMENT_SIZE - 15);
    std::string group = "Group " + std::to_string(element.group);
    for (char c : group) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }

    // Check if the mouse is within the bounds of the element
    if (mouseX >= centerXPos && mouseX <= centerXPos + ELEMENT_SIZE
        && mouseY >= centerYPos && mouseY <= centerYPos + ELEMENT_SIZE) {
        // Store the selected element
        selectedElement = const_cast<Element*>(&element);

    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the header
    displayDeveloper();

    // Calculate the vertical spacing between rows
    int verticalSpacing = ELEMENT_SIZE + ELEMENT_PADDING;

    // Close the selected element window if it's open
    if (selectedElementWindowID != 0) {
        glutDestroyWindow(selectedElementWindowID);
        selectedElementWindowID = 0;
    }

    // Draw the periodic table
    for (int i = 0; i < TABLE_ROWS; i++) {
        for (int j = 0; j < TABLE_COLUMNS; j++) {
            int index = i * TABLE_COLUMNS + j;
            if (index < sizeof(elements) / sizeof(elements[0])) {
                drawElement(elements[index], i, j);
            }
        }
    }

    // Highlight the selected element, if any
    if (selectedElement != nullptr) {
        int rowIndex = (selectedElement - elements) / TABLE_COLUMNS;
        int colIndex = (selectedElement - elements) % TABLE_COLUMNS;
        int x = colIndex * (ELEMENT_SIZE + ELEMENT_PADDING);
        int y = rowIndex * (ELEMENT_SIZE + ELEMENT_PADDING);
        int startX = (WINDOW_WIDTH - (TABLE_COLUMNS * ELEMENT_SIZE + (TABLE_COLUMNS - 1) * ELEMENT_PADDING)) / 2;
        int startY = (WINDOW_HEIGHT - (TABLE_ROWS * ELEMENT_SIZE + (TABLE_ROWS - 1) * ELEMENT_PADDING)) / 2;
        int centerXPos = startX + x;
        int centerYPos = startY + y;

        // Draw a rectangle around the selected element
        glColor3f(1.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2i(centerXPos, centerYPos);
        glVertex2i(centerXPos + ELEMENT_SIZE, centerYPos);
        glVertex2i(centerXPos + ELEMENT_SIZE, centerYPos + ELEMENT_SIZE);
        glVertex2i(centerXPos, centerYPos + ELEMENT_SIZE);
        glEnd();

        // Open a new window and display the selected element name
        displayElementInfo();
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Periodic Table");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // Register the mouse callback function
    glutMouseFunc(mouseCallback);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutMainLoop();
    return 0;
}
