/******************************************************
 * Program: methods.h
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: function prototypes
 * Input:
 * Output:
 * ******************************************************/


#include <string>
#include "Course.h"
#include "University.h"

int welcome_page();
bool prompt_to_quit();
bool is_integer(std::string &);
void update_files(University &);
int prompt_for_index(University &);
void view_entire_catalog(University &);
void copy(University &, Course &);

