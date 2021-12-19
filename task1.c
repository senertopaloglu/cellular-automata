#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int calc_out(int, int, int, int*);

void convert_ruleno(int, int *);

int main(int argc, char **argv) {
  int i,g;
  int *currentgen;
  int *newgen;
  int f, m, l; /*first, middle and lest cells of cell neighbourhood*/
  int out, ruleno, nocells, nogens, middle;
  int binrule_no[8];

  if(argc != 4) {
    printf("error please enter correct arguments, in order\n");
    exit(EXIT_FAILURE);
  }  
  if(!(atoi(argv[1]))) {
    printf("error please enter correct arguments, in order\n");
    exit(EXIT_FAILURE);
  }
  
  if(!(atoi(argv[2]) || atoi(argv[2]) < 0)) {
    printf("error please enter correct arguments, in order\n");
    exit(EXIT_FAILURE);
  }
  if(!(atoi(argv[3]))) {
    printf("error please enter correct arguments, in order\n");
    exit(EXIT_FAILURE);
  } 
  
  nocells = atoi(argv[1]);
  nogens = atoi(argv[2]);
  ruleno = atoi(argv[3]);
  
  convert_ruleno(ruleno, binrule_no);
  
  if(ruleno < 0 || ruleno > 255){
    printf("error please enter correct arguments, in order\n");
    exit(EXIT_FAILURE);
  }
  
  if(nocells < 0) {
    printf("error please enter correct arguments, in order\n");
    exit(EXIT_FAILURE);
  }
  
  if(nogens < 0) {
    printf("error please enter correct arguments, in order\n");
    exit(EXIT_FAILURE);
  }
  
  /* auto all cells set to 0 */
  currentgen = calloc(nocells, sizeof(int));
  newgen = calloc(nocells, sizeof(int));
  
  for(g=0; g < nogens-1; g++) {
  if(g == 0){
  /*first gen - set middle cell or right of middle cell to 0*/
  if(nocells % 2 != 0) {
    middle = nocells / 2;
    currentgen[middle] = 1;
  } else {
    middle = ceil(nocells / 2.0);
    currentgen[middle] = 1;
  }
  for(i=0; i<nocells; i++){
    if(currentgen[i] == 1){
      printf("*");
    }
    if(currentgen[i] == 0){
      printf(" ");
    }
  }
  printf("\n");
  }
    
  /* iterate through every cell calculating position of neighbouring cells */
  /* wrap around */
  for(i=0; i<nocells; i++){
    m = currentgen[i];
    if(i==0) {
      f = currentgen[nocells - 1];
      l  = currentgen[1];
    }
    else if(i==(nocells - 1)) {
      f = currentgen[nocells - 2];
      l = currentgen[0];
    } else {
    f = currentgen[i - 1];
    l = currentgen[i + 1];
    }
    
    /*printf("%d %d %d\n", f, m, l);*/
    
    /*calculate output for new generation*/
    out = calc_out(f, m, l, binrule_no);
    newgen[i] = out;
    
  }
  
  /*printf("*****************\n");*/
  
  for(i=0; i<nocells; i++){
    if(newgen[i] == 1){
      printf("*");
    }
    if(newgen[i] == 0){
      printf(" ");
    }
  } 
  
  printf("\n");
  
  /* after finish current gen and all new gen generated deleted current contents of currentgen */
  for(i=0; i < nocells; i++) {
    currentgen[i] = newgen[i]; 
    /*printf("%d", newgen[i]);*/
  } 
    
  /*printf("\n");*/
  
  
  }
  free(newgen);
  free(currentgen);
  return 0;

}

void convert_ruleno(int rule, int *binrule) {
  char strrule[9]; /* not 8 but 9, since '\0' - array of chars */
  long binaryrule = 0;
  int remainder, i=1; /*temp, index, arrIndex;*/
  
  while(rule != 0) {
    remainder = rule % 2;
    rule /= 2;
    binaryrule += remainder * i;
    i *= 10;
  }
  
  sprintf(strrule, "%08ld", binaryrule);
  
  for (i = 0; strrule[i] != 0; i++){
    binrule[i] = strrule[i] - '0'; /*each char is null terminated so -'0' */
  }
  /*
  index = 0;
  arrIndex = 7;
    while(index < arrIndex)
    {
         Copy value from original array to reverse array 
        temp = binrule[index];
        binrule[index] = binrule[arrIndex];
        binrule[arrIndex] = temp;
        
        index++;
        arrIndex--;
    }
  */
}

int calc_out(int first, int middle, int last, int *rule) {
  if (first == 1 && middle == 1 && last == 1) 
    return rule[0];
  else if (first == 1 && middle == 1 && last == 0) 
    return rule[1];
  else if (first == 1 && middle == 0 && last == 1) 
    return rule[2];
  else if (first == 1 && middle == 0 && last == 0) 
    return rule[3];
  else if (first == 0 && middle == 1 && last == 1) 
    return rule[4];
  else if (first == 0 && middle == 1 && last == 0) 
    return rule[5];
  else if (first == 0 && middle == 0 && last == 1) 
    return rule[6];
  else if (first == 0 && middle == 0 && last == 0) 
    return rule[7];
  return 0;
}

