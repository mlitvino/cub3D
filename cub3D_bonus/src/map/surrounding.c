#include "cub3D.h"

static int is_walkable(char c)
{
    return (c == '0' || c == 'N' || c == 'S'
        || c == 'E' || c == 'W' || c == 'D' || c == 'B' || c == 'C' || c == 'F');
}

static int is_allowed_adjacent(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S'
        || c == 'E' || c == 'W' || c == 'D'|| c == 'B' || c == 'C' || c == 'F');
}


static int check_single_neighbor(char **map, int n_row, int n_col, int height, int width)
{
    char neighbor;

    if (n_row >= 0 && n_row < height &&
        n_col >= 0 && n_col < width)
    {
        neighbor = map[n_row][n_col];
        if (!is_allowed_adjacent(neighbor))
            return (0);
    }
    else
        return (0);
    return (1);
}

static int check_neighbors(char **map, int row, int col, int height, int width)
{
    int delta_row;
    int delta_col;
    int n_row;
    int n_col;

    delta_row = -1;
    while (delta_row <= 1)
    {
        delta_col = -1;
        while (delta_col <= 1)
        {
            if (!(delta_row == 0 && delta_col == 0))
            {
                n_row = row + delta_row;
                n_col = col + delta_col;
                if (!check_single_neighbor(map, n_row, n_col, height, width))
                    return (0);
            }
            delta_col++;
        }
        delta_row++;
    }
    return (1);
}

int is_valid_surrounding(char **map, int height, int width)
{
    int row = 0;
    int col;

    while (row < height)
    {
        col = 0;
        while (col < width)
        {
            char current = map[row][col];
            if (is_walkable(current))
            {
                if (!check_neighbors(map, row, col, height, width))
                    return (0);
            }
            col++;
        }
        row++;
    }
    return (1);
}
