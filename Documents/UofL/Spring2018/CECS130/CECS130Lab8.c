/*---------------------------------------------------------------------*/
/* Brandon Hutton */
/* CECS 130 Lab 8 */
/* 3/20/18 */
/* Description: Phonebook V3*/
/*---------------------------------------------------------------------*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int friends = 0;	//Number of contacts
int position = -1;	//Positon variable used for searches

//Creates a person data structure
struct personType
{
	char firstName[20];	//Person's first name up to 20 characters
	char lastName[20];	//Person's last name up to 20 characters
	char number[8];		//8 digit phone number
};

//PROTOTYPES
void addFriend(struct personType *phonebook);		
void removeFriend(struct personType *phonebook, char firstName[], char lastName[]);
void showEntries(struct personType *phonebook);
void sortEntries(struct personType *phonebook, char firstName[], char lastName[], char number[]);
void findNumber(struct personType *phonebook, char firstName[], char lastName[]);
void randomNumber(struct personType *phonebook);
void clearContacts(struct personType *phonebook);
void writeEntries(FILE *stream, struct personType *phonebook);
void loadEntries(FILE *stream, struct personType *phonebook, char firstName[], char lastName[], char number[]);

/*
		ADD FRIEND METHOD
								*/
void addFriend(struct personType *phonebook)
{
	friends++;		//Adds one to the friend counter
	realloc(phonebook,(friends+1)*48*sizeof(char)); //Allocated more memory for the new friend
	if(phonebook == NULL)	//Checks to see if the memory could be allocated
	{
		printf("ERROR: Unable to allocate required memory.");
	}
	else
	{
		//Sets information for a new friend
		printf("First Name:");
		scanf("%s",phonebook[friends-1].firstName);
		printf("Last Name:");
		scanf("%s",phonebook[friends-1].lastName);
		printf("Phone Number:");
		scanf("%s",phonebook[friends-1].number);
		printf("Added Friend Successfully\n\n");
	}
}

/*
		REMOVE FRIEND METHOD
								*/
void removeFriend(struct personType *phonebook, char firstName[], char lastName[])
{
	//Loops through the phonebook to see if theres a match and if so position is set
	int x=0;
	for(x;x<friends;x++)
	{
		if(strcmp(phonebook[x].firstName,firstName)==0 && strcmp(phonebook[x].lastName, lastName)==0)
		{
			position = x;
		}
	}
	
	//Checks to see if the contact exists before removing
	if(position != -1)
	{				
		//Deletes the friend and moves the other contacts into the empty slots before it
		for(position;position<friends;position++)
		{
			phonebook[position] = phonebook[position+1];
		}
		printf("Removed Friend Successfully!\n\n");
		friends--;		//Subtracts from the friend counter
		realloc(phonebook, (friends+1)*48*sizeof(char));	//Allocates less memory as there are less friends
		if(phonebook == NULL)		//Checks to see if memory could be reallocated
		{
			printf("ERROR: Unable to allocate required memory.");
		}
	}
	else
	{
		printf("ERROR: Contact not found!\n\n");
	}
	position = -1;		//Resets postion for next use
}

/*
		SHOW ENTRIES METHOD
								*/
void showEntries(struct personType *phonebook)
{
	printf("Phone Book Entries:\n");
	//Prints each contact
	int x=0;
	for(x;x<friends;x++)
	{
		printf("%s %s %s\n",phonebook[x].firstName,phonebook[x].lastName,phonebook[x].number);
	}
	printf("\n");
}

/*
		SORT ENTRIES METHOD
								*/
void sortEntries(struct personType *phonebook, char firstName[], char lastName[], char number[])
{
	//Loops through the contacts
	int x=0;
	int y=0;
    for(x; x < friends-1 ; x++){
        for(y=x+1; y< friends; y++)
        {
            if(strcmp(phonebook[x].lastName, phonebook[y].lastName) > 0)
            {
            	//Changes to previous spot if first string is greater than second string
            	strcpy(firstName,phonebook[x].firstName);
                strcpy(lastName,phonebook[x].lastName);
                strcpy(number,phonebook[x].number);
                strcpy(phonebook[x].firstName,phonebook[y].firstName);
                strcpy(phonebook[x].lastName,phonebook[y].lastName);
                strcpy(phonebook[x].number,phonebook[y].number);
                strcpy(phonebook[y].firstName,firstName);
                strcpy(phonebook[y].lastName,lastName);
                strcpy(phonebook[y].number,number);
            }
        }
    }
	printf("Last names sorted successfully!\n\n");
}

/*
		FIND NUMBER METHOD
								*/
void findNumber(struct personType *phonebook, char firstName[], char lastName[])
{
	//Loops through contacts
	int x=0;
	for(x;x<friends;x++)
	{
		//Saves position of the name if it matches
		if(strcmp(phonebook[x].firstName,firstName)==0 && strcmp(phonebook[x].lastName,lastName)==0)
		{
			position = x;
			break;
		}
	}
	//Prints the person's number if found
	if(position >= 0)
	{
		printf("%s %s's phone number is %s\n\n",firstName,lastName,phonebook[position].number);
	}
	else
	{
		printf("ERROR: Person not found!\n\n");
	}
	position = -1;		//Resets position for next use
}

/*
		RANDOM NUMBER METHOD
								*/
void randomNumber(struct personType *phonebook)
{
	//Gets a random number between 1 and the amount of contacts
	srand(time(NULL));
	int r = rand() % friends;
	//Checks to see if there are contacts, if not an error is printed
	if(rand>=0)
	{
		printf("%s %s : %s\n\n",phonebook[r].firstName,phonebook[r].lastName,phonebook[r].number);
	}
	else
	{
		printf("ERROR: There are no entries.");
	}
}

/*
		CLEAR CONTACTS METHOD
								*/
void clearContacts(struct personType *phonebook)
{
	phonebook = NULL;		//Clears entries
	friends = 0;			//Resets contacts to zero
	realloc(phonebook, (friends+1)*48*sizeof(char));		//Allocates less memeory
	printf("Deleted contacts succesfully\n\n");
}

/*
		WRITE ENTRIES METHOD
								*/
void writeEntries(FILE *stream, struct personType *phonebook)
{
	char path[50];					//path to file
	printf("Enter path to file:");
	scanf("%s",&path);
	stream = fopen(path,"w");		//opens file
	//Checks to see if file exists
	if(stream == NULL)
	{
		printf("ERROR: FILE NOT FOUND!\n\n");
	}
	else
	{
		//Loops through contacts and copies each to the file
		int x=0;
		for(x;x<friends;x++)
		{
			fprintf(stream, "%s\t%s\t%s\n",phonebook[x].firstName,phonebook[x].lastName,phonebook[x].number);
		}
		printf("Entries written succesfully!\n\n");
		fclose(stream);				//closes file
	}
}

/*
		LOAD ENTRIES METHOD	
								*/
void loadEntries(FILE *stream, struct personType *phonebook, char firstName[], char lastName[], char number[])
{
	char path[50];					//path to file
	printf("Enter path to file:");
	scanf("%s",&path);
	stream = fopen(path,"r");		//opens file
	//Checks to see if file exists
	if(stream==NULL)
	{
		printf("ERROR: FILE NOT FOUND!\n\n");
	}
	else
	{
		//Scans in contacts from file until the end of file is reached
		int x=0;
		while(1)
		{
			fscanf(stream,"%s",firstName);
			fscanf(stream,"%s",lastName);
			fscanf(stream,"%s\n",number);
			strcpy(phonebook[x].firstName, firstName);
			strcpy(phonebook[x].lastName, lastName);
			strcpy(phonebook[x].number, number);
			x++;
			if(feof(stream))
			{
				break;
			}
		}
		friends = x;			//sets friends equal to the number of contacts scanned in
		fclose(stream);			//closes file
	}
	printf("Contacts loaded succesfully\n\n");
}

int main(int argc, char *argv[])
{
	
	int selection = -1;		//Menu selection
	struct personType *phonebook = malloc(48*sizeof(char));	//Pointer of personType with enough memory for 1 friend
	
	//Checks to see if there is enough memory for even 1 friend, if not program is terminated
	if(phonebook == NULL)
	{
		printf("ERROR: Unable to allocate required memory.");
		return 0;
	}
	
	//First and last name arrays used for the deletion option and for sorting
	char lastName[20];
	char firstName[20];
	char number[8];
	
	//Files
	FILE *pWrite;
	FILE *pRead;
	
	while(selection !=0)	//Continues to take more selection after first run
	{
		/*
				Menu
						*/
		printf("Phone Book\n"
				"1) Add Friend\n"
				"2) Delete Friend\n"
				"3) Show phone book\n"
				"4) Sort Entries\n"
				"5) Find Number\n"
				"6) Random Friend\n"
				"7) Delete Contacts\n"
				"8) Write Entries to File\n"
				"9) Load Entries from File\n"
				"0) Exit\n");
				
		//Gets selection
		printf("What is your selection?");
		scanf("%d",&selection);
		
		//Handles different selections
		switch(selection)
		{
			/*
					ADD FRIEND
									*/
			case 1:
				addFriend(phonebook);
			break;
			/*
					Delete Friend
										*/
			case 2:
				//Scans in names to be compared to the phonebook's contacts
				printf("First Name:");
				scanf("%s",&firstName);
				printf("Last Name:");
				scanf("%s",&lastName);
				removeFriend(phonebook, firstName, lastName);
			break;
			/*
					SHOW ENTRIES
										*/
			case 3:
				showEntries(phonebook);
			break;
			/*
					SORT ENTRIES
										*/
			case 4:
				sortEntries(phonebook, firstName, lastName, number);
			break;
			/*
					FIND NUMBER
										*/
			case 5:
				//Scans in info
				printf("Enter first name: ");
				scanf("%s",&firstName);
				printf("Enter last name: ");
				scanf("%s",&lastName);
				findNumber(phonebook, firstName, lastName);
			break;
			/*
					RANDOM NUMBER
										*/
			case 6:
				randomNumber(phonebook);				
			break;
			/*
					CLEAR CONTACTS
										*/
			case 7:
				clearContacts(phonebook);
			break;
			/*
					WRITE CONTACTS
										*/
			case 8:
				writeEntries(pWrite,phonebook);
			break;
			/*
					READ CONTACTS
										*/
			case 9:
				loadEntries(pRead, phonebook, firstName,lastName,number);
			break;
			/*
					EXIT
								*/
			case 0:
			free(phonebook);	//Gives memory back to the system
			printf("Closing phone book...");
				return 0;
			break;
		}
	}
}

