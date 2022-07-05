#include <time.h>
#include "main.h"

void getDateTime(char *_sdate, char *_stime)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(_sdate, "%4d.%02d.%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    sprintf(_stime, "%02d:%02d", tm.tm_hour, tm.tm_min);
}

int split(char *buffer, int initial, int *index, char separator)
{
    int total = 0;
    int position = initial;
    int start = initial;

    while (buffer[position] != 0)
    {
        if (buffer[position] == separator || buffer[position] == '\n')
        {
            index[total] = position - start > 0 ? start - initial : -1;
            start = position + 1;
            total++;
            if (buffer[position] == '\n')
            {
                break;
            }
        }
        position++;
    }
    return total;
}
