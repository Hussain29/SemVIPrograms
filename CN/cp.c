#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc, char **argv){
    if(argc!=3)
    {
        printf("Incorrect number of command line arguments passed! Please recheck!\n");
        return -1;
    }
    int inputfilefd = open(argv[1], O_RDONLY);
    int outputfilefd = open(argv[2], O_CREAT|O_WRONLY,666);
    struct stat inputfilebuf;
    fstat(inputfilefd, &inputfilebuf);
    int inputfilesize = inputfilebuf.st_size;
    char *buf = (char *)malloc(inputfilesize*sizeof(char));
    int inputread = read(inputfilefd, buf,inputfilesize);
    if(inputread!=-1)
    {
        int writestatus=write(outputfilefd, buf, inputfilesize);
        if(writestatus!=-1)
            printf("Copying successful!");
        close(inputfilefd);
        close(outputfilefd);
        free(buf);
    }
}
