typedef struct Person {
  long ID;
  char *firstname,*surname;
  char sex; /* m or f */
} Person;

#define MaxPersons 200

Person Persons[MaxPersons];

Person *getPerson(long ID) {
  if (ID>=0 && ID<MaxPersons)
    return &Persons[ID];
  else
    return 0;
}

long putPerson(long ID, char * firstname, char* surname, char sex) {
  if (ID>=0 && ID<MaxPersons) {
    Persons[ID].ID=ID;
    Persons[ID].firstname=firstname;
    Persons[ID].surname=surname;
    Persons[ID].sex=sex;
    return 1;
  } else {
    return 0;
   }
}
