#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   * treeLs
   * Recursive function for listing all files in a directory
   * Takes a directory to list and a level at which to start indentation
*/
void treeLs(char *directory, int level);

int main( int argc, char *argv[] )
{
	FILE *fp;
	char currentDir[1035];

	// Check if use wants to list current directory or specific
	if (argc == 1)
	{
		// Get current directory
		fp = popen("/bin/pwd", "r");
		fgets(currentDir, sizeof(currentDir)-1, fp);
		pclose(fp);

		// Remove trailing newline
		currentDir[strlen(currentDir)-1] = 0;
	}
	else
	{
		// Get directory to list
		strcpy(currentDir, argv[1]);
	}

	// List the directory recursively
	treeLs(currentDir, 0);

	return 0;
}

/*
   * treeLs
   * Recursive function for listing all files in a directory
   * Takes a directory to list and a level at which to start indentation
*/
void treeLs(char *directory, int level)
{
	FILE *fp;
	char item[1035];
	char command[1035];
	int isDir;

	// Capture output of ls in directory
	strcpy(command, "");
	strcat(command, "ls ");
	strcat(command, directory);

	fp = popen(command, "r");

	// Read the output an item at a time
	while (fgets(item, sizeof(item)-1, fp) != NULL) {
		// Remove trailing newline from item
		item[strlen(item)-1] = 0;
		
		// Print tabs
		for (int i = 0; i < level; i++)
			printf("\t");

		// List the item
		printf("%s\n", item);

		// Test if item is a directory
		strcpy(command, "");
		strcat(command, "test -d ");
		strcat(command, directory);
		strcat(command, "/");
		strcat(command, item);
		isDir = system(command);


		// If item is a directory, recursively list its children
		if (isDir == 0)
		{
			// Get the new directory 
			char newDirectory[1035];
			strcpy(newDirectory, "");
			strcat(newDirectory, directory);
			strcat(newDirectory, "/");
			strcat(newDirectory, item);

			// Recursively list
			treeLs(newDirectory, level+1);
		}
	}

	// Close the ls output stream
	pclose(fp);
}
