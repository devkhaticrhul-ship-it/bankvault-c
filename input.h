#ifndef INPUT_H
#define INPUT_H

int readInt(const char *message);
double readAmount(const char *message);
int readPin(const char *message);
int readLoginPin(const char *message);

void readName(const char *message, char *name, int size);
void readPhone(const char *message, char *phone, int size);
int readYesNo(const char *message);

#endif