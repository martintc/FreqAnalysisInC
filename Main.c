#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Data Structure
 * Character and Count
 */

struct character_stats {
	char l;
	long count;
};

/*
 * Declaring functions
 */
int create_data_structure();
float calc_percent(long char_num, long total_chars);

/*
 * Main function
 */
int main () {

	char file_name[180];
	long total_chars = 0;

	char charList[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};	

	puts("Document Frequency Analysis in C\n");
	puts("----------------------------------\n");
	puts("Enter a file name (path included is needed): ");
	scanf("%s", file_name);
	puts("----------------------------------\n");
	puts("Generating the list.....\n");
	struct character_stats list[26];	
	if (create_data_structure(charList, list) == 0) {
		puts("List is generated!\n ------------------------\n");
	} else {
		puts("Error generating list. Exiting program....\n");
		return -1;
	}
	printf("Opening file %s\n", file_name);
	FILE *f;
	f = fopen(file_name, "r");
	if (f == NULL) {
		puts("Error. Exiting program!");
		exit(1);
	} else {
		puts("File is opened.\n");
	}
	puts("Now analyzing.............\n");

	char ch;
	while (ch != EOF) {
		ch = fgetc(f);
		if (isupper(ch)) {
				ch = tolower(ch);
		}
		for (int i = 0; i < 26;  i++) {
			if (ch == list[i].l) {
				list[i].count++;
				total_chars++;
			}
		}
	}
	puts("Results:\n");
	printf("Total characters: %li\n", total_chars);
	
	for (int i = 0; i < 26; i++) {
		printf("%c : %li    %8.6f\n", list[i].l, list[i].count, calc_percent(list[i].count, total_chars));
	}
	puts("-------------------\n");

	fclose(f);

	return 0;
}

/*
 * create_data_structure(char charsList[], struct data_structure)
 * Creates an array using the data structure
 * Each symbol from chars is placed into a data structure from above
 * Count is automatically initialized to 0
 */
int create_data_structure (char chars[], struct character_stats list[]) {
	for (int i = 0; i < 26; i++) {
		list[i].l = chars[i];
		list[i].count = 0;
		printf("%c: %lx\n", list[i].l, list[i].count);
	}
	puts("\n");
	return 0;
}

/*
 * calc_percent (long char_number, long total_chars)
 * calculates the percentage of a character's presence in a file
 * compared to the rest of the document
 */
float calc_percent (long char_num, long total_chars) {
	return (float) char_num / total_chars;
}
