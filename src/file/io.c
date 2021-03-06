#include "headers/io.h"

extern char* directory;
extern char* keyfiles;

void log_file(char* tag, char* client, char* message)
{
    FILE *f;
    char * filename = (char*)malloc(sizeof(char)*(strlen(LOGFILE)+strlen(directory)+2));
    sprintf(filename, "%s/%s", directory, LOGFILE);
    f = fopen(filename, "a");
    fprintf(f, "<tr><td>%s</td><td>%s</td><td style=\"text-align:end\">%s</td></tr>", tag, client, message);
    fclose(f);
    free(filename);
}

char* load_log()
{
    FILE *f;
    char * filename = (char*)malloc(sizeof(char)*(strlen(LOGFILE)+strlen(directory)+1));
    int chars = 0;
    char * contents;
    sprintf(filename, "%s/%s", directory, LOGFILE);
    f = fopen(filename, "r+");
    while(fgetc(f) != EOF)chars++;
    contents = (char*)malloc(sizeof(char)*(strlen(HTML_BEGIN)+strlen(HTML_END)+chars+strlen(HEADER) + 15));
    rewind(f);
    strcpy(contents, HTML_BEGIN);
    chars = strlen(contents);
    while((contents[chars] = fgetc(f)) != EOF)chars++;
    contents[chars] = 0;
    strcat(contents, HTML_END);
    fclose(f);
    free(filename);
    return contents;
}

void write_pem(const char* type, char* data, const char* file)
{
    FILE *f;
    char * filename = (char*)malloc(sizeof(char)*(strlen(file)+strlen(keyfiles)+2));
    sprintf(filename, "%s/%s", keyfiles, file);
    f = fopen(filename, "w+");
    fprintf(f,"-----BEGIN %s -----\n", type);
    fwrite(data, 1, strlen(data), f);
    fprintf(f,"\n-----END %s -----", type);
    free(data);
    fclose(f);
    free(filename);
}

char* read_key(char* file)
{
    FILE *f;
    char * filename = (char*)malloc(sizeof(char)*(strlen(file)+strlen(keyfiles)+2));
    sprintf(filename, "%s/%s", keyfiles, file);
    f = fopen(filename, "r+");
    char* contents = (char*)malloc(sizeof(char)*KEYLEN*10);
    int i = 0;
    int lastlf;
    while(fgetc(f) != '\n');
    while((contents[i] = fgetc(f)) != EOF){
        if(contents[i] == '\n')lastlf = i;
        i++;
    }
    contents[lastlf] = 0;
    fclose(f);
    free(filename);

    return contents;
}