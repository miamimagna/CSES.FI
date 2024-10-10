#include <stdio.h>
char si[49], grid[9][9];
int cnt;
int only(int i, int j)
{
    int k = 0;
 
    if (i == 7 && j == 1)
        return 0;
    if (!grid[i - 1][j])
        k++;
    if (!grid[i + 1][j])
        k++;
    if (!grid[i][j - 1])
        k++;
    if (!grid[i][j + 1])
        k++;
    return k == 1;
}
void traverse(size_t k, int i, int j)
{
    int right, up, down, left;
    if (i == 7 && j == 1)
    {
        if (k == 48)
            cnt++;
        return;
    }
    left = !grid[i][j - 1];
    right = !grid[i][j + 1];
    up = !grid[i - 1][j];
    down = !grid[i + 1][j];
    if ((down == up && right == left))
        return;
    grid[i][j] = 1;
    if (left && only(i, j - 1))
    {
        if (si[k] == '?' || si[k] == 'L')
            traverse(k + 1, i, j - 1);
        grid[i][j] = 0;
        return;
    }
    if (right && only(i, j + 1))
    {
        if (si[k] == '?' || si[k] == 'R')
            traverse(k + 1, i, j + 1);
        grid[i][j] = 0;
        return;
    }
    if (up && only(i - 1, j))
    {
        if (si[k] == '?' || si[k] == 'U')
            traverse(k + 1, i - 1, j);
        grid[i][j] = 0;
        return;
    }
    if (down && only(i + 1, j))
    {
        if (si[k] == '?' || si[k] == 'D')
            traverse(k + 1, i + 1, j);
        grid[i][j] = 0;
        return;
    }
    if (down && (si[k] == '?' || si[k] == 'D'))
        traverse(k + 1, i + 1, j);
    if (up && (si[k] == '?' || si[k] == 'U'))
        traverse(k + 1, i - 1, j);
    if (left && (si[k] == '?' || si[k] == 'L'))
        traverse(k + 1, i, j - 1);
    if (right && (si[k] == '?' || si[k] == 'R'))
        traverse(k + 1, i, j + 1);
    grid[i][j] = 0;
}
signed main()
{
    size_t i, j;
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            grid[i][j] = i == 0 || i == 8 || j == 0 || j == 8;
    scanf("%[^\n]%*c", &si);
    traverse(0, 1, 1);
    printf("%d\n", cnt);
}
