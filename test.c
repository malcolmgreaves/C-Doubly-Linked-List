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
  const Student *s1 = a;
  const Student *s2 = b;
  if (!strncmp(s1->first_name, s2->first_name, strlen(s1->first_name)) &&
      !strncmp(s2->last_name,  s2->last_name,  strlen(s1->last_name)) &&
      s1->grade == s2->grade &&
      s1->gtid == s2->gtid) {
    return 1;
  } else {
    return 0;
  }
	/* TODO Test if two students are equal */
	/* Two students are equal if all of their fields are equal */
	/* To compare strings the function strncmp will be useful */
	/* Again you can read the man pages for strncmp */
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

        /* Testing the push_back function. Push three people to the front and one to the back.
           Order should be Brandon, Noo, Baron, and then Tinky. */
        // Note that Teletubbies do not make good 2110 students
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        push_front(llist, create_student("Noo", "Noo", 13, 666));
        push_front(llist, create_student("Brandon", "the Destroyer", 200, 54545454));
        push_back(llist, create_student("Tinky", "Winky", 0, 222222222));
        printf("TEST CASE 7\nPush to back. Order should be Brandon, Noo, Baron, Tinky:\n");
        traverse(llist, print_student);
        printf("\n");

        /* Now lets test remove front! Brandon should no longer be in the list */
        remove_front(llist, free_student);
        printf("TEST CASE 8\nRemove front. Brandon should no longer be in the list:\n");
        traverse(llist, print_student);
        printf("\n");

        /* Lets get rid of Tinky. I never liked that guy anyway. */
        remove_back(llist, free_student);
        printf("TEST CASE 9\nRemove back. Tinky should no longer by in the list:\n");
        traverse(llist, print_student);
        printf("\n");

        /* Lets test the index removal before the list gets too small */
        remove_index(llist, 1, free_student);
        printf("TEST CASE 10\nRemove by index. Remove the student at index 1, Baron should no longer be in the list:\n");
        traverse(llist, print_student);
        printf("\n");

        /* K, time for a new list. */
  	empty_list(llist, free_student);
        push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
        push_front(llist, create_student("Noo", "Noo", 13, 666));
        push_front(llist, create_student("Brandon", "the Destroyer", 200, 54545454));
        push_back(llist, create_student("Tinky", "Winky", 0, 222222222));
        push_back(llist, create_student("Tinky", "Winky", 0, 222222222));

        /* Oh no! We've accidentally added Tinky to the list twice but I don't want him there at all!
           Time to test the remove_data function and rid us of Tinky. */
        int removed = remove_data(llist, create_student("Tinky", "Winky", 0, 222222222), student_eq, free_student);
        printf("TEST CASE 11\nRemove data. A new list was created and Twinky was accidentally added twice. I don't want him there at all so lets test the remove data function. Tinky should not be in the list:\n");
        traverse(llist, print_student);
        printf("Occurences removed: %d\n", removed);
        printf("\n");

        /* If we try to remove Tinky again, nothing should happen */
        removed = remove_data(llist, create_student("Tinky", "Winky", 0, 222222222), student_eq, free_student);
        printf("TEST CASE 12\nRemove data. If we try to remove Tinky again nothing should happen:\n");
        traverse(llist, print_student);
        printf("Occurences removed: %d\n", removed);
        printf("\n");

        /* Time to test the retrieval functions */
        printf("TEST CASE 13\nFront. Lets get the front of the list. Should be Brandon:\n");
        print_student(front(llist));
        printf("\n");

        /* Testing the get_index function */
        printf("TEST CASE 14\nGet index. Lets get the student at index 1. Should be Noo:\n");
        print_student(get_index(llist, 1));
        printf("\n");

        /* Test the back function */
        printf("TEST CASE 15\nBack. Let's get the student at the back of the list. Should be Baron:\n");
        print_student(back(llist));
        printf("\n");

        /* Test if the list is empty */
        printf("TEST CASE 16\nIs empty. Is the list empty? (should be no)\n");
        printf(is_empty(llist) ? "Yes\n" : "No\n");
        printf("\n");

        /* Test the size */
        printf("TEST CASE 17\nSize. What is the size of the list? (should be 3)\n");
        printf("%d\n", size(llist));
        printf("\n");

        /* Test if exists */
        printf("TEST CASE 18\nFind occurence. Does the student Baron von Baris exist in the list? (should be yes)\n");
        printf(find_occurrence(llist, create_student("Baron", "von Baris", 92, 123456789), student_eq) ? "Yes\n" : "No\n");
        printf("\n");

        /* Lets test some of the functions on a list size of 0 */
        empty_list(llist, free_student);

        /* Push to front is obviously working at this point */

        /* Test push back */
        push_back(llist, create_student("Baron", "von Baris", 92, 123456789));
        printf("TEST CASE 19\nPush back on empty list:\n");
        traverse(llist, print_student);
        printf("\n");
        empty_list(llist, free_student);

        /* Test remove front on empty list */
        printf("TEST CASE 20\nRemove fromt on empty list: (should fail and return -1)\n");
        printf("%d\n", remove_front(llist, free_student));
        printf("\n");

        /* Test remove index on empty list */
        printf("TEST CASE 21\nRemove index on empty list: (should fail and return -1)\n");
        printf("%d\n", remove_index(llist, 0, free_student));
        printf("\n");

        /* Test remove back on empty list */
        printf("TEST CASE 22\nRemove back on empty list: (should fail and return -1)\n");
        printf("%d\n", remove_back(llist, free_student));
        printf("\n");

        /* And make a new list */
 	/* Testing over clean up*/
 	free(llist);
 	
  	return 0;
}
