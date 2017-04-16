/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // TODO
    
    // name of file.
    char nm[50];
    
    // number of file.
    int no = 0;
    
    // check proper usage.
    if(argc != 1)
    {
      printf("Usage: ./recover.\n");
      return 1;
    }
    
    // open the file image to be recovered.
    FILE* raw = fopen("card.raw", "r");
    
    // check if the file is opened.
    if(raw == NULL)
    {
      printf("Cannot Open file.\n");
      return 2;
    }
    
    // file to be created.
    FILE* new;
    
    // where to go.
    int x = 0;   
    // get from file.
    BYTE* read = malloc(sizeof(BYTE) * 512);
    
    while(1)
    {
      if(x == 0)
      {
        // read from file for marker.
        fread(read, 512, 1, raw);
      }
      // even if not contagious.
      x = 0;
      
      // if a jpg file is found.
      if(read[0] == 0xff && read[1] == 0xd8 && read[2] == 0xff && (read[3] == 0xe0 || read[3] == 0xe1))
      {        
        
        // write the name.
        if(no < 10)
          sprintf(nm, "00%d.jpg", no);
        else if(no < 100)
          sprintf(nm, "0%d.jpg", no);
        else
          sprintf(nm, "%d.jpg", no);

        // put to the output file.
        new = fopen(nm, "w");
                 
        // check if the file is not created.
        if(new == NULL)
        {
          printf("Cannot create file.\n");
          return 3;
        }
        
        // write the marker.
        fwrite(read, 1, 512, new);
        
        // read after the marker.
        fread(read, 1, 512, raw);
        
        int exit = 0; 
        while((!(read[0] == 0xff && read[1] == 0xd8 && read[2] == 0xff && (read[3] == 0xe0 || read[3] == 0xe1))) && exit != 1)
        {
          // write to file.
          fwrite(read, 512, 1, new);
          
          // read from file.
          if(fread(read, 512 , 1, raw) == 0)
            exit = 1;
          
          // don't read again cuz contagious file saving.
          x = 1;
          
        }
        
        // close the file.
        fclose(new);
        
        if(exit == 1)
          break;
        // update file number.
        no++;
      }
            
    }
    
    // free the read.
    free(read);
    
    fclose(raw);
    
    return 0;
}
