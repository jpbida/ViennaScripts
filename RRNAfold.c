#include <stdlib.h>
#include "RRNAfold_opts.h"
#include  <stdio.h>
#include  <math.h>
#include  "PS_dot.h"
#include  "utils.h"
#include  "fold_vars.h"
#include  "fold.h"
#include <string.h> 


int main(int argc, char *argv[])
    {
       struct RRNAfold_args_info args_info;
     
       /* let's call our cmdline parser */
       if (RRNAfold_parser (argc, argv, &args_info) != 0)
         exit(1) ;
     
//       for ( unsigned i = 0 ; i < args_info.inputs_num ; ++i )
//         printf("%s\n",args_info.inputs[i]) ;

int type = args_info.fold_type_arg;
char *iname = args_info.input_file_arg;
char *oname = args_info.output_file_arg;
double temp = args_info.temperature_arg;
printf("Using temp: %f",temp);
int length,n,i,j;

/* Reads in a file containing(-I) one sequence per line and outputs (-O) a file containing the corresponiding structures 
*/ 
char *let,*seq1, *struct1,* struct2,* xstruc,*ffname;
float *x,*y,e1, e2, tree_dist, string_dist, profile_dist, kT,**pf1, **pf2;
FILE *fi,*fo;
short *pair_table;
/* open the file */
fi = fopen(iname, "r");
fo = fopen(oname, "a");
if (fi == NULL) {printf("I couldn't open results.dat for reading.\n");}


i=0;//Index used to keep track of line in the file
/* Scanning each line in the file and folding the given sequence */
seq1 = (char* ) space(sizeof(char)*(1000+1));
while (fscanf(fi, "%s\n",seq1) == 1){
	printf("%s\n",seq1);
	length=strlen(seq1);	
        /* fold at 30C instead of the default 37C */
        temperature = temp;      /* must be set *before* initializing  */
        update_fold_params();
	     /* allocate memory for fold(), could be skipped */
             //initialize_fold(strlen(seq1));
             /* allocate memory for structure and fold */
             struct1 = (char* ) space(sizeof(char)*(length+1));
             let = (char* ) space(sizeof(char)*(length+1));
             x = (float* ) space(sizeof(float)*(length+1));
             y = (float* ) space(sizeof(float)*(length+1));
             /* Folding the sequence */
	     e1 =  fold(seq1, struct1);
//             fprintf(fo,"%s\n",struct1);
pair_table=make_pair_table(struct1);
if(type==2){
j=simple_xy_coordinates(pair_table,x,y);	
}else{
j=naview_xy_coordinates(pair_table,x,y);
}
j=0;
let = seq1;
while(j < (length)){
fprintf(fo,"%d,%f,%f,%c,%d,%d\n",i,x[j],y[j],*let,j,(pair_table[(j+1)]-1));
let++;
j++;
}
/* Makes .ps file of RNA fold */
///////////////////////////////////////////
/*
ffname=(char*) space(sizeof(char)*10);
n=sprintf(ffname, "rna%d.ps",i);
printf("%s\n",ffname);
(void) PS_rna_plot(seq1, struct1, ffname);
*/
///////////////////////////////////////////
free_arrays();     /* free arrays used in fold() */
	     i++;
}  /* close the file */
       fclose(fi);
       fclose(fo);
}
