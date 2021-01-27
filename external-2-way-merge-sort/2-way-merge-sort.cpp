#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include <algorithm>

#define PAGE_SIZE 10 // how many numbers in one page

bool two_way_merge_sort(char*, char*);
void connect_tail(FILE*, FILE*);

int main(int argc, char* argv[])
{
    if (argc < 3) {
        puts("Usage:\n"
             "2-way-merge-sort [input file] [output file]");
        return 0;
    }
    two_way_merge_sort(argv[1], argv[2]);
    return 0;
}

bool two_way_merge_sort(char* in_name, char* out_name)
{
    FILE *in = fopen(in_name, "r");
    if (!in) {
        puts("cannot open input file");
        return false;
    }

    struct stat st = {0};
    if (stat("tmp", &st) == -1) {
        mkdir("tmp", 0700);
        puts("create tmp directory");
    }
    
    puts("--- PASS 0 ---");
    bool hasnext = true;
    int page_num = 0;
    while (hasnext) {
        int i = 0;
        int *page_arr = new int[PAGE_SIZE];
        if (!page_arr) {
            puts("Failed to allocate memory.");
            fclose(in);
            return false;
        }
    
        for (; i < PAGE_SIZE; i++) {
            if (fscanf(in, "%d", page_arr + i) == EOF) {
                hasnext = false;
                break;
            }
        }

        if (i == 0) {
            delete[] page_arr;
            break;
        }

        std::sort(page_arr, page_arr + i);
        char tmp_file_name[20];
        sprintf(tmp_file_name, "tmp/0_%d", page_num);
        FILE *page_file = fopen(tmp_file_name, "w");
        if (!page_file) {
            puts("Failed to open temporary file.");
            delete[] page_arr;
            fclose(in);
            return false;
        }

        for (int j = 0; j < i; j++) {
            fprintf(page_file, "%d\n", page_arr[j]);
        }
        fclose(page_file);
        printf("save tmp file: %s\n", tmp_file_name);
        delete[] page_arr;
        page_num++;
    }
    fclose(in);

    /* other pass */
    int level = 0;
    while (page_num > 1) {
        printf("--- PASS %d ---\n", level + 1);
        int page = 0;
        for (; page + 1 < page_num; page += 2) {
            char first_name[20], second_name[20], third_name[20];
            sprintf(first_name, "tmp/%d_%d", level, page);
            sprintf(second_name, "tmp/%d_%d", level, page + 1);
            sprintf(third_name, "tmp/%d_%d", level + 1, page >> 1);
            FILE *first = fopen(first_name, "r");
            FILE *second = fopen(second_name, "r");
            FILE *third = fopen(third_name, "w");
            if (!first || !second || !third) {
                puts("cannot open temporary file");
                return false;
            }

            int a, b;
            fscanf(first, "%d", &a);
            fscanf(second, "%d", &b);
            while (true) {
                if (a < b) {
                    fprintf(third, "%d\n", a);
                    if (fscanf(first, "%d", &a) == EOF) {
                        fprintf(third, "%d\n", b);
                        connect_tail(third, second);
                        break;
                    }                   
                } else {
                    fprintf(third, "%d\n", b);
                    if (fscanf(second, "%d", &b) == EOF) {
                        fprintf(third, "%d\n", a);
                        connect_tail(third, first);
                        break;
                    }
                }
            }
            fclose(first);
            fclose(second);
            fclose(third);
            printf("save temporary file: %s\n", third_name);
            remove(first_name);
            printf("remove temporary file: %s\n", first_name);
            remove(second_name);
            printf("remove temporary file: %s\n", second_name);
        }

        /* deal with single page */
        if (page < page_num) {
            char single_name[20], new_name[20]; 
            sprintf(single_name, "tmp/%d_%d", level, page);
            sprintf(new_name, "tmp/%d_%d", level + 1, page >> 1);
            rename(single_name, new_name);
            printf("rename %s as %s\n", single_name, new_name);
            page += 2;
        }
        page_num = page >> 1;
        level++;
    }

    /* finalize */
    char single_name[20];
    sprintf(single_name, "tmp/%d_0", level);
    rename(single_name, out_name);
    printf("rename %s as %s\n", single_name, out_name);
    
    /* remove temporary directory */
    system("exec rm -r tmp");
    puts("remove temporary directory");
    return true;
}

void connect_tail(FILE* fp, FILE* tail)
{
    int n;
    while (fscanf(tail, "%d", &n) != EOF) {
        fprintf(fp, "%d\n", n);
    }
}