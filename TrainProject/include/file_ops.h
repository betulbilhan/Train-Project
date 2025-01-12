#ifndef FILE_OPS_H
#define FILE_OPS_H
// #include "train.h"
typedef struct Train Train;

void train_status_to_file(Train *t, const char *filename);
void print_file_contents(const char *filename);
#endif