#define _POSIX_C_SOURCE 200809L // For getline
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// http://www.cse.yorku.ca/~oz/hash.html
unsigned long djb2(const unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

typedef struct {
	const char* k;
	int v;
} Entry;

typedef struct {
	Entry* entries;
	size_t size;
	size_t count;
} HashMap;

HashMap HashMap_new(size_t size);
Entry* HashMap_get(HashMap* hm, const char* k);
void HashMap_rehash(HashMap* hm);
void HashMap_insert(HashMap* hm, const char* k, int v);
Entry* HashMap_get_or_default(HashMap* hm, const char* k, int d);

HashMap HashMap_new(size_t size) {
	HashMap hm = {0};
	hm.entries = calloc(size, sizeof(Entry));
	hm.size = size;
	return hm;
}

Entry* HashMap_get(HashMap* hm, const char* k) {
	if (hm->entries == NULL) {
		return NULL;
	}

	size_t h = djb2(k) % hm->size;

	for (int i = 0; i < hm->size; i++) {
		Entry* e = &hm->entries[(i + h) % hm->size];
		if (e->k == NULL) {
			break;
		}
		if (strcmp(e->k, k) == 0) {
			return e;
		}
	}

	return NULL;
}

#define DEFAULT_SIZE 16
#define LOAD_FACTOR 0.75f

void HashMap_rehash(HashMap* hm) {
	//printf("Rehash %ld %ld %f\n", hm->count, hm->size, (float)hm->count / hm->size);

	HashMap rehash = HashMap_new(hm->size * 2);

	for (int i = 0; i < hm->size; i++) {
		Entry* e = &hm->entries[i];
		if (e->k != NULL) {
			HashMap_insert(&rehash, e->k, e->v);
		}
	}

	free(hm->entries);
	*hm = rehash;
}

void HashMap_insert(HashMap* hm, const char* k, int v) {
	//printf("Insert %s %d\n", k, v);

	if (hm->entries == NULL) {
		hm->entries = calloc(DEFAULT_SIZE, sizeof(Entry));
		hm->size = DEFAULT_SIZE;
		hm->count = 0;
	}

	if (k == NULL) {
		printf("Null key\n");
		return;
	}

	if ((float)hm->count / hm->size > LOAD_FACTOR) {
		HashMap_rehash(hm);
	}

	size_t h = djb2(k) % hm->size;

	Entry* e;
	for (int i = 0; i < hm->size; i++) {
		e = &hm->entries[(i + h) % hm->size];
		if (e->k == NULL) {
			break;
		}
		if (strcmp(e->k, k) == 0) {
			return; // No duplicates
		}
	}

	e->k = k;
	e->v = v;

	hm->count++;
}

Entry* HashMap_get_or_default(HashMap* hm, const char* k, int d) {
	//printf("Insert %s %d\n", k, v);

	if (hm->entries == NULL) {
		hm->entries = calloc(DEFAULT_SIZE, sizeof(Entry));
		hm->size = DEFAULT_SIZE;
		hm->count = 0;
	}

	if (k == NULL) {
		printf("Null key\n");
		return NULL;
	}

	if ((float)hm->count / hm->size > LOAD_FACTOR) {
		HashMap_rehash(hm);
	}

	size_t h = djb2(k) % hm->size;

    Entry* e;
    int i2 = h;
	for (int i = 0; i < hm->size; i++) {
		e = &hm->entries[i2];
		if (e->k == NULL) {
			break;
		}
		if (strcmp(e->k, k) == 0) {
			return e;
		}

        i2++;
        if (i2 == hm->size) {
            i2 = 0;
        }
	}

	e->k = k;
	e->v = d;

	hm->count++;

	return e;
}

// Make me a function to get a list of lines from a file
// Copilot generated this
char** getLinesFromFile(const char* filename, size_t* lineCount) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	char** lines = NULL;
	char* line = NULL;
	size_t n = 0;
	size_t count = 0;

	while (getline(&line, &n, file) != -1) {
		lines = realloc(lines, (count + 1) * sizeof(char*));
		*strchr(line, '\n') = '\0'; // Remove newline
		lines[count] = strdup(line);
		count++;
	}

	free(line);
	fclose(file);

	*lineCount = count;
	return lines;
}

int main() {
	size_t lineCount;
	char** lines = getLinesFromFile("words.txt", &lineCount);

	clock_t start = clock();

	HashMap freq = {0};

	for (int i = 0; i < lineCount; i++) {
		char* line = lines[i];

		Entry* e = HashMap_get_or_default(&freq, line, 0);
		e->v++;
	}

	clock_t end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f\n", cpu_time_used);

	// for (int i = 0; i < freq.size; i++) {
	// 	Entry* e = &freq.entries[i];
	// 	if (e->k != NULL) {
	// 		printf("%s %d\n", e->k, e->v);
	// 		free(e->k);
	// 	}
	// }

	free(lines);
	free(freq.entries);

	return 0;
}
