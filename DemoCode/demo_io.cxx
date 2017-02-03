
#include <stdio.h>
#include <time.h>
#include <iostream>
#include<vector>

double get_cpu_time(){
    return (double)clock() / CLOCKS_PER_SEC;
}

int main()
{
  int N = 512;
  int size = N * N * N;
  //double var[size];
  std::vector<double> var(size, 1.2636263622);
  //for(int i=0;i<size;++i)
  //  var[i] = (double)i;
  
  FILE * fichier2 = fopen("fic.txt", "w");
  double tinit = get_cpu_time();
  for(int i=0;i<size;++i)
    //  std::cout << var[i] << std::endl;
    fprintf(fichier2, "%.10f \t", var[i]); fclose(fichier2);
  std::cout << "txt cpu " << get_cpu_time() - tinit << std::endl;
  
  // binaire
  FILE * fichier = fopen("fic.bin", "wb");
  tinit = get_cpu_time();
  fwrite(&var[0], sizeof(double), size, fichier);
  fclose(fichier);
  std::cout << "bin cpu " << get_cpu_time() - tinit << std::endl;

}
