// request_utils.h

#ifndef REQUEST_UTILS_H
#define REQUEST_UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_ACCEPTS 5
#define MAX_LENGTH 50
#define MAX_URL_LEN 256
#define MAX_HEADER_LENGTH 1000
#define MAX_BODY_LENGTH 10000
#define MAX_RESPONSE_LENGTH 2000
#define MAX_FIELD_LENGTH 1000

void print_strings(char** strings);

char** check_accept_field(char* accept_field);

char* check_file_type(char* url);

bool check_file_exists(const char* filename);

char *get_content_type(char *content_type_value);

char* build_200_response(char* message);

char* build_400_response();

char* build_404_response();

char* build_406_response();

char *build_413_response();

char* build_500_response();

int create_file(char* file_name, char* extension);

int write_in_file(char* file_name, char* content);

int delete_file(char *filename);

char* map_file_type_content_type(char* content_format);

char* map_file_type_file_extension(char* file_type);

int get_file_size(const char *url);

char *get_file_contents(const char *url);

char* build_http_delete_response(char* url, char* msg);

char* build_http_get_response(char* url, char* msg);

char* build_http_head_response(char* url, char* msg);

char* build_http_post_response(char* url, char* msg);

char* build_http_put_response(char* url, char* msg);

#endif