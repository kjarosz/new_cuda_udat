#include <iostream>
#include <cstring>
#include <cstdio>



#include "file_manip.h"
#include "signatures.h"



void print_help()
{
  printf("Usage:\n");
  printf("<program> <directory>\n");
}



int load_subdirectories(char *directory, char **&filenames, int &buffer_size)
{
  buffer_size = 64;
  filenames = alloc_filename_buffers(buffer_size);
  int file_idx = 0;

  char buffer[FILENAME_MAX];
  DIR * root_dir;
  if(root_dir = opendir(directory))
  {
    dirent *ent;
    while (ent = readdir(root_dir))
    {
      // Ignoring '.' and '..'.
      if (ent->d_name[0] == '.')
        continue;

      join_paths(buffer, directory, ent->d_name);

      // Ignore non-directories.
      DIR *sub_dir = opendir(buffer);
      if (!sub_dir)
        continue;
      closedir(sub_dir);

      strcpy(filenames[file_idx], ent->d_name);
      file_idx++;

      if (file_idx >= buffer_size)
      {
        extend_filename_buffers(filenames, buffer_size, buffer_size*2);
        buffer_size *= 2;
      }
    }
    closedir(root_dir);
  }

  return file_idx;
}



int main(int argc, char *argv[])
{
  if (argc < 2)
    print_help();

  char *directory = argv[1];
  char **filenames;
  int filename_buffer_size;
  int dir_count = load_subdirectories(directory, filenames, filename_buffer_size);
  
  CUDASignatures signatures;
  signatures.compute(filenames, dir_count);
  signatures.save_in(directory);

  free_filename_buffers(filenames, filename_buffer_size);

  return 0;
}