#ifndef GRID_H
#define GRID_H

class Grid {
public:
	// Constructor with default size and step
    Grid    (int GridSize = 50, float GridStep = 1.0f);

    // Draw grid
    void    DrawGrid();

private:
    // Size and step
    int         GridSize;
    float       GridStep;
};

#endif // GRID_H