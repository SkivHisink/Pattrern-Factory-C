#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "factory.h"
#include "point.h"
#include "circle.h"
#include "rect.h"
#include "line.h"
#include "new.h"
#define TRUE 1
#define FALSE 0

static int char_to_int(char symbol) {
	return symbol - 48;
}

static void scan_numbers(char* str, int* coords, int i)
{
	int j = 0;
	short minus = 0;
	if (str[j] == '-') {
		++minus;
		++j;
	}
	while (str[j] != '\0' && str[j] != '\n') {
		coords[i] = coords[i] * 10 + char_to_int(str[j]);
		if (str == NULL)
			break;
		++j;
	}
	if (minus == 1) {
		coords[i] = (-coords[i]);
	}
}

static void* make_detail(char** str_mass) {
	int coords[4] = { 0 };
	if (str_mass == NULL) {
		return NULL;
	}
	int i = 0;
	if (!strcmp(str_mass[0], "line")) {
		for (int j = 0; j < 4; ++j) {
			scan_numbers(str_mass[1 + j], coords, j);
		}
		return new(Line, coords[0], coords[1], coords[2], coords[3]);
	}
	else if (!strcmp(str_mass[0], "point")) {
		for (int j = 0; j < 2; ++j) {

			scan_numbers(str_mass[1 + j], coords, j);
		}
		return new(Point, coords[0], coords[1]);
	}
	else if (!strcmp(str_mass[0], "rect")) {
		for (int j = 0; j < 4; ++j) {

			scan_numbers(str_mass[1 + j], coords, j);
		}
		return new(Rect, coords[0], coords[1], coords[2], coords[3]);
	}
	else if (!strcmp(str_mass[0], "circle")) {
		for (int j = 0; j < 3; ++j) {

			scan_numbers(str_mass[1 + j], coords, j);
		}
		return new(Circle, coords[0], coords[1], coords[2]);
	}
	else {
		return NULL;
	}
}

static void** store_detail(void** factory_store, size_t* counter, size_t* f_s_size, char** parcered_str) {
	if (parcered_str[0][0] == '\n') {
		return factory_store;
	}
	factory_store[*counter] = make_detail(parcered_str);
	(*counter)++;
	if ((*counter) + 2 > * f_s_size) {
		size_t newSize = (*f_s_size) * 2;
		void** buffer = (void**)malloc(sizeof(void*) * newSize);
		if (buffer == NULL) {
			return 0;
		}
		memcpy(buffer, factory_store, sizeof(void**));
		for (size_t k = 0; k < *counter; k++) {
			buffer[k] = factory_store[k];
		}
		free(factory_store);
		factory_store = buffer;
		*f_s_size = newSize;
	}
	return factory_store;
}

int Factory(char* name_of_file) {
	FILE* _Stream;
	if (strstr(name_of_file, "stdin")) {
		_Stream = stdin;
	}
	else {
		_Stream = fopen(name_of_file, "r");
	}
	if (_Stream == NULL) {
		return 0;
	}
	size_t counter = 0;
	size_t f_s_size = FACTORY_STORE_SIZE;
	if (f_s_size < 1) {
		return 0;
	}
	void** factory_store = (void**)malloc(f_s_size * sizeof(void*));
	if (factory_store == NULL) {
		return 0;
	}

	size_t buffer_size = READ_BUFFER_SIZE;
	int* read_buffer = (int*)malloc(buffer_size * sizeof(int));
	if (read_buffer == NULL) {
		return 0;
	}

	size_t integ_buffer_size = READ_BUFFER_SIZE;
	if (integ_buffer_size < 1) {
		return 0;
	}
	char** parcered_str = (char**)malloc(6 * sizeof(char*));
	if (parcered_str == NULL) {
		return 0;
	}
	for (int i = 0; i < 6; ++i) {
		parcered_str[i] = (char*)malloc(integ_buffer_size * sizeof(char));
		if (parcered_str == 0) {
			return 0;
		}
	}

	size_t j = 0;
	size_t i_p = 0;
	size_t begin_p = 0;
	while ((read_buffer[j] = getc(_Stream)) != EOF) {
		if (_Stream == stdin && (j > 1)) {
			if ((char)read_buffer[j - 1] == read_buffer[j] && (char)read_buffer[j] == '\n') {
				parcered_str[0][0] = '\n';
				break;
			}
		}
		if (j > 1 && (read_buffer[j - 1] != read_buffer[j] != ' ') && (read_buffer[j] == ' ' || read_buffer[j] == '\n')) {
			int k;
			for (k = 0; begin_p + k < j; ++k) {
				parcered_str[i_p][k] = (char)read_buffer[begin_p + k];
			}
			parcered_str[i_p][k] = '\0';
			++i_p;
			begin_p = j + 1;
		}
		if ((char)read_buffer[j] == '\n') {
			parcered_str[i_p][0] = '\n';
			if (i_p > 2) {
				factory_store = store_detail(factory_store, &counter, &f_s_size, parcered_str);
			}
			i_p = 0;
		}
		++j;
		if (j + 1 > buffer_size) {
			size_t newSize = buffer_size * 2;
			int* buffer = (int*)malloc(sizeof(int) * newSize);
			if (buffer == NULL) {
				return 0;
			}
			memcpy(buffer, read_buffer, sizeof(int*));
			for (size_t k = 0; k < j; ++k) {
				buffer[k] = read_buffer[k];
			}
			free(read_buffer);
			read_buffer = buffer;
			buffer_size = newSize;
		}
	}
	if (counter > 0) {
		factory_store = store_detail(factory_store, &counter, &f_s_size, parcered_str);
		for (size_t k = 0; k < counter; ++k) {
			draw(factory_store[k]);
			delete(factory_store[k]);
		}
	}
	free(factory_store);
	for (int i = 0; i < 6; ++i) {
		free(parcered_str[i]);
	}
	free(parcered_str);
	free(read_buffer);
	if (_Stream != stdin) {
		fclose(_Stream);
	}
	return 0;
}