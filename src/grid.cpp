#include "grid.h"
#include <GL/freeglut.h>

Grid::Grid(int Size, float Step) : GridSize(Size), GridStep(Step) {}

void Grid::DrawGrid()
{
    glColor3f(0.5f, 0.5f, 0.5f);    // Grey color for the grid
    glBegin(GL_LINES);

    for (int i = -GridSize; i <= GridSize; ++i) {
        // Lines parallel to X-axis
        glVertex3f(-GridSize * GridStep, 0.0f, i * GridStep);
        glVertex3f(GridSize * GridStep, 0.0f, i * GridStep);

        // Lines parallel to Z-axis
        glVertex3f(i * GridStep, 0.0f, -GridSize * GridStep);
        glVertex3f(i * GridStep, 0.0f, GridSize * GridStep);
    }
    glEnd();
}