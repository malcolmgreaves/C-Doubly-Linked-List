#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores Students (first name, last name, grade, gtid)  */
/* Here is the data the user in this case us will be storing into our linked list */
/* YOU ARE REQUIRED TO COMPLETE THIS PART */
typedef struct Student
{
	char* first_name; /* This will be malloc'd!*/
	char* last_name; /* This will also be malloc'd */
	int grade;
	unsigned int gtid;
} Student;

Student* create_student(const char* first_name, const char* last_name, int grade, unsigned int gtid)
{
  Student *s = malloc(sizeof(Student));
  char *f = malloc((strlen(first_name)+1)*sizeof(char));
  char *l = malloc((strlen(last_name)+1)*sizeof(char));
  strncpy(f, first_name, strlen(first_name)+1);
  strncpy(l, last_name, strlen(last_name)+1);
  s->first_name = f;
  s->last_name = l;
  s->grade = grade;
  s->gtid = gtid;

  return s;
	/* First allocate a student on the heap */
	/* Allocate enough space for the first and last names */
	/* AND copy the first and last name to the first and last name fields in the struct */
	/* Set the grade and gtid */
	/* Notice there are two functions that will help you with the second and third steps */
	/* strlen and strncpy will be helpful */
	/* type man strlen and man strncpy to learn how to use them */

	/* DO NOT store the parameters first_name/last_name in the struct you allocate */ 
	
}

/* For these functions below you should never be passed in NULL */
/* You will always get valid data here */
void print_student(void* data)
{
  Student *s = data;
  printf("Student: %s %s\n", s->first_name, s->last_name);
  printf("Grade: %d\n", s->grade);
  printf("GtID: %d\n", s->gtid);
	/* TODO Implement just print out all of the information here. */
	/* Your output should exactly look like this without no weird characters printing out.
	Student: FIRSTNAME LASTNAME
	Grade: GRADE
	GtID: GTID
	*/
	/* printf and the format specifiers %d %s will be useful here 
	Again use the man pages if you don't know how to use printf */
}

void free_student(void* data)
{
  Student *s = data;
  free(s->first_name);
  free(s->last_name);
  free(s);
	/* TODO Implement You are to first free any fields that were malloc'd. */
	/* Then free the struct in this order */
}

int student_eq(const void* a, const void* b)
{
	/* TODO Test if two students are equal */
	/* Two students are equal if all of their fields are equal */
	/* To compare strings the function strncmp will be useful */
	/* Again you can read the man pages for strncmp */
	return 0;
}

/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void) 
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();
  
  	/* What does an empty list contain?  Lets use our handy traversal function */
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

 	/* Lets add a student and then print */
 	push_front(llist, create_student("Nick", "Polive", 56, 239402128));
 	printf("TEST CASE 2\nA List with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	/* Lets remove that student and then print */
 	remove_front(llist, free_student);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	/* Lets add two elements and then print */
 	push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
 	push_front(llist, create_student("George", "Burdell", 65, 902313373));
 	printf("TEST CASE 4\nA List with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

 	/* Test find occurence when the node is not found */
	// Notice the commented line below is BAD because the return value from create_student was malloc'd and you never free it!
	// find_occurence(llist, create_student("Nurse", "Joy", 3, 131313137), student_eq));
	Student* p = create_student("Nurse", "Joy", 3, 131313137);
	printf("TEST CASE 5\nFinding occurence when a node is not in the list should fail: \n");
	printf("%d\n", find_occurrence(llist, p, student_eq));
	/* Remember to FREE everything you malloc I malloc'd space for p and now I am done with it so I free it */
	free_student(p);

  	/* Lets kill the list */
  	empty_list(llist, free_student);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	
 	
 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not you should at least test each function here */
 	
 	/* Testing over clean up*/
 	free(llist);
 	
  	return 0;
}
