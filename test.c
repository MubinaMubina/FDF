

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	rows;
	int	cols;
	int	**matrix;
	int	i;

	rows = 3;
	cols = 4;
	// Step 1: allocate array of row pointers
	matrix = malloc(rows * sizeof(int *));
	if (matrix == NULL)
		return (1);
	// Step 2: allocate each row
	i = 0;
	while (i < rows)
	{
		matrix[i] = malloc(cols * sizeof(int));
		if (matrix[i] == NULL)
			return (1);
		i++;
	}
	// Step 3: use the array
	i = 0;
	while (i < rows)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = i * cols + j;
		}
		i++;
	}
	// Step 4: print
	i = 0;
	while(i < rows)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
		i++;
	}
	// Step 5: free memory (reverse order)
	for (int i = 0; i < rows; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
	return (0);
}


