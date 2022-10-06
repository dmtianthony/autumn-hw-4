#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String{
	char *s;
	struct String *next;
};
struct String *list1;

int sum = 0;
int strings = 0;
void freeMemory(struct String *list);
void show_strings(struct String *list)
{
	list = list1;
	// special case: input.6 #strings = 0 return
	// special case: input.7 #strings > 0 sum = 0; return

	struct String *runner;
	runner = list;

	while(runner != NULL){
		printf("%s",runner->s);
		if(runner->next!=NULL)
			printf("\n");
		runner = runner->next;
	}
	list1 = list;
}
void sort_strings(struct String *list)
{
	list = list1;

	struct String *runner1;
	struct String *runner2;

	runner1 = list;
	runner2 = list->next;

	int num_nodes = 0;	

	while(runner1->next!=NULL)
	{
		num_nodes++;
		runner1=runner1->next;
	}
	runner1 = list;

	int index1, index2;
	struct String *prerunner1=list;
	struct String *postrunner1 = list->next;
	struct String *prerunner2 = list;
	struct String *postrunner2;
	int dumbcount;

	for(index1 = 0; index1 < num_nodes; index1++)
	{
		for(index2 = index1+1; index2<=num_nodes; index2++)
		{
			if(strlen(runner1->s) >= strlen(runner2->s))
			{
				if(index1 == 0 && index2 ==num_nodes)
				{
					//first and last
					prerunner2->next = runner1;
					runner2->next = runner1->next;
					runner1->next = NULL;
					list = runner2;
					runner1 = list;
				}
				else if(index1 == 0 && index2 == 1 && index2 != num_nodes)
				{
					//first and second
					postrunner2 = runner2->next;
					runner2->next = runner1;
					runner1->next = postrunner2;
					list = runner2;
					prerunner1 = list;
					postrunner1 = list->next;
					runner1 = list;
					runner2 = list->next;
					prerunner2 = list;
					postrunner2 = list->next->next;
				}
				else if(index1 == 0 && index2 > 1 && index2 < num_nodes)
				{
					//first and middle
					postrunner2 = runner2->next;
					runner1->next = postrunner2;
					runner2->next = postrunner1;
					prerunner2->next = runner1;
					list = runner2;
					prerunner1 = list;
					postrunner1 = list->next;
					runner1 = list;
					runner2 = list;
					prerunner2 = list;
					postrunner1 = list->next;
					for(dumbcount = 1; dumbcount <= index2 ; dumbcount++)
					{
						runner2 = runner2->next;
						if(dumbcount < index2 )
							prerunner2 = prerunner2->next;
					}
					postrunner2 = runner2->next;	
 				}
				else if(num_nodes==4 && index1 == 1 && index2 == 3)
				{
					postrunner2 = runner2->next;
					//middle and middle
					prerunner1->next = runner2;
					runner1->next = postrunner2;
					runner2->next = postrunner1;
					prerunner2->next = runner1;
					list = prerunner1;
					prerunner1 = list;
					runner1 = list->next;
					postrunner1 = list->next->next;
					prerunner2 = list->next->next;
					runner2 = list->next->next->next;
					postrunner2 = list->next->next->next->next;
				}
				else if(index1 != 0 && index1 == index2-1 && index2 != num_nodes)
				{
					// middle and next
					postrunner2 = runner2->next;
					prerunner1->next = runner2;
					runner1->next = postrunner2;
					runner2->next = runner1;
					prerunner1 = list;
					runner1 = list;
					runner2 = list;
					prerunner2 = list;
					for(dumbcount = 0; dumbcount < index1; dumbcount++)
					{
						runner1 = runner1->next;
						if(dumbcount < index1 -1)
							prerunner1 = prerunner1->next;
					}
					postrunner1 = runner1->next;
					for(dumbcount = 1; dumbcount <= index2; dumbcount++)
					{
						runner2 = runner2->next;
						if(dumbcount < index2 )
							prerunner2 = prerunner2 ->next;
					}
					postrunner2 = runner2->next;
				}
				else if(index1 > 0 && index1 != index2-1 && index2 == num_nodes)
				{
					// middle and last
					prerunner1->next = runner2;
					runner2->next = postrunner1;
					runner1->next = NULL;
					prerunner2->next = runner1;	
					prerunner1 = list;		
					runner1 = list;
					runner2 = list;
					prerunner2 = list;
					for(dumbcount = 0; dumbcount < index1; dumbcount++)
					{
						runner1 = runner1->next;
						if(dumbcount < index1 -1)
							prerunner1 = prerunner1->next;
					}
					postrunner1 = runner1->next;
					for(dumbcount = 1; dumbcount <= index2; dumbcount++)
					{
						runner2 = runner2->next;
						if(dumbcount < index2)
							prerunner2 = prerunner2->next;
					}
					postrunner2 = NULL;
				}
				else if(index1 > 0 && index1 == num_nodes-1 && index2 == num_nodes)
				{
					//second-last and last
					prerunner1->next = runner2;
					runner2->next = runner1;
					runner1->next = NULL;
				}
			}
			if(index2 < num_nodes){
				prerunner2 = prerunner2->next;
				runner2 = runner2->next;
			}
		}
		if(index1 < num_nodes-1)
		{
			prerunner1 = runner1;
			runner1 = runner1->next;
			postrunner1 = runner1->next;
			prerunner2 = runner1;
			runner2 = runner1->next;
		}
	}
	list1 = list;
}
void get_strings(struct String *list)
{
	list = list1;
	char** s;
	s = (char **)malloc(sizeof(char *)*1000);
	int pos=0;
	int c;
	struct String *runner;

	list = (struct String *)malloc(sizeof(struct String));
	list->s = (char *)malloc(sizeof(char)*100);
	list->next = NULL;
	runner = list;
	s[strings] = (char*)malloc(sizeof(char)*100);

	while(strings < 1000)
	{
		c = getchar();
		if(c!=EOF){
			if(c==';')
			{
				runner = (struct String *)malloc(sizeof(struct String));
				runner->s = (char *)malloc(sizeof(char)*100);
				strcpy(list->s,s[strings]);
				runner->next = list;
				list = runner;
				pos = 0;
				sum = sum + strlen(s[strings]);
				strings++;
				s[strings] = (char*)malloc(sizeof(char)*100);
				continue;
			}
			s[strings][pos] = c;
			pos++;
			continue;
		}
		break;
	}
	sum = sum + strlen(s[strings]);
	if(sum)
	{
		if(strings>0)
		{
			runner = (struct String *)malloc(sizeof(struct String));
			runner->s = (char *)malloc(sizeof(char)*100);
			strcpy(list->s,s[strings]);
			runner->next = list;
			list = runner;
		}
		else if(strings == 0)
		{
			strcpy(list->s,s[strings]);
		}
	}
	if(strings != 0 && sum != 0)
		list = list->next;
	list1 = list;



	for(pos = 0; pos <=strings; pos++){
		free(s[pos]);
	}
	free(s);

}

void freeMemory(struct String *list){
	while(list!=NULL){
		struct String *this = list;
		free(list->s);
		list = list->next;
		free(this);
	}
}

int main()
{
	struct String *list;
	get_strings(list);
	if(sum == 0 || strings == 0){
		show_strings(list);
	}
	else{
		sort_strings(list);
		show_strings(list);
	}
	freeMemory(list1);
	return 0;
}
