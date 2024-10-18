/****************************************************************************

        This program counts the Hamilton cycles of a graph recording
        the output as a text file of SQL statements. for the sake of 
        computational efficiency, as direct database interactions 
        were too slow for larger computations.The included script 
        "transform_sql" restructures the output.txt file into a batch 
        insert format for efficient SQL database updates.
        
        This program is a slight variation of Gordon Royle's allcycs
        program which was designed to find all the cycles of a given 
        length in a graph. If no length is given, then it is simply to
        record cycles of each length up to n for a graph of n vertices.
        
******************************************************************************/


#include "gtools.h"

static int min,max,verbose;
void allcycs();
void showvec();

main(argc,argv)
int argc;
char **argv;

{

        graph *g;
        int m,n;
        int codetype;
        FILE *infile;

        int *data,*used,*cyc;
        int i,v;
        char *g6;
        FILE *outfile;
        outfile = fopen("output.txt", "w");  // Open for writing. Use "a" for appending.
        if (outfile == NULL) {
                fprintf(stderr, "Error opening file for writing\n");
                exit(1);
        }

        infile = opengraphfile(NULL,&codetype,0,1);

        if (argc < 2) {
                fprintf(stderr,"%s -[qv] [min [max]] < (graphs)\n",argv[0]);
                exit(0);
        }

        if (argv[1][0] == '-') {

                if (argv[1][1] == 'q') verbose = 0;
                if (argv[1][1] == 'v') verbose = 1;

        }
        else {
                fprintf(stderr,"%s -[qv] [min [max]] < (graphs)\n",argv[0]);
                exit(0);
        }

        if (argc == 2) {
                min = 0;
                max = 10000;
        }

        if (argc == 3) {

                min = max = atoi(argv[2]);
        }

        if (argc == 4)  {
                min = atoi(argv[2]);
                max = atoi(argv[3]);
        }


        while ((g = readg(infile,NULL,0,&m,&n)) != NULL)
        {
                data = (int *) calloc(n+1,sizeof(int));
                used = (int *) calloc(n,sizeof(int));
                cyc = (int *) calloc(n,sizeof(int));

                for (v=0;v<1;v++)
                {

                        bzero(used,n*sizeof(int));

                        cyc[0] = v;

                        for (i=0;i<=v;i++)
                        used[i] = 1;

                        allcycs(g,m,n,cyc,1,used,data);
                }
		//writeg6(stdout,g,m,n);
                g6 = ntog6(g,m,n);
                size_t len = strlen(g6);
                if (len > 0 && g6[len - 1] == '\n') {
                        g6[len - 1] = '\0'; // Replace the newline with a null terminator
                }
                //printf("%d\n",data[n]);
                fprintf(outfile, "INSERT INTO testgraphs (g6string,vertices, HCs) VALUES ('%s',%d,%d);\n", g6, 32, data[n]);


                free(g);
                free(data); free(used); free(cyc); 
        }
        fclose(outfile);

}

void
allcycs(g,m,n,cyc,len,used,data)
graph *g;
int m,n,*cyc,len,*used,*data;
{

        int i;

        if (len > max)
        return;

        if (ISELEMENT(g+m*cyc[len-1],cyc[0]) && cyc[1] < cyc[len-1])
        {
            data[len]++;

            if (min <= len && len <= max && verbose)
            {
            printf("%d ",len);
            for (i=0;i<len;i++)
            printf("%d ",cyc[i]);
            printf("\n");
            }
        }

        i = -1;
        while ((i=nextelement(g+m*cyc[len-1],m,i)) >= 0)
        {
                if (used[i] == 1)
                continue;

                used[i] = 1;
                cyc[len] = i;

                allcycs(g,m,n,cyc,len+1,used,data);

                used[i] = 0;
        }
}


/*****************************************************************************

        This is a trivial code fragment, simply designed to print out a
        vector. The vector v of length n is printed out to the file fp,
        with offset being added to every entry (in case we want to do things
        like convert nauty input to Cayley input etc).

        Author: Gordon Royle
        Date:   August 1992

******************************************************************************/

void
showvec(fp,v,n,offset)
FILE *fp;
int *v,n,offset;
{
        register int i;

        for (i=0;i<n;i++)
        fprintf(fp,"%d ",v[i]+offset);
        fprintf(fp,"\n");
}

