// request_parsing.h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifndef REQUEST_PARSING_H
#define REQUEST_PARSING_H

#define MAX_FIELDS 10
#define MAX_FIELD_LENGTH 1000

char* parse_url(char* first_line);

char* parse_method(char* first_line);

char** parse_header(char* message);

char* parse_content_type_field(char** headers);

char* parse_content_length_field(char** headers);

char* parse_accept_field(char** headers);

char* get_accept_encoding(char** headers);

char* parse_body(char* http_message);

#endif