#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
#include <omp.h>

#include"hashtable.h"

#include "sorting.h"

using namespace std;

//benchmark functions
void benchmark_quicksort();
void benchmark_hybridquicksort();
void benchmark_mergesort();
void benchmark_heapsort();
void benchmark_shellsort_2n();
void benchmark_shellsort_3n();


int main(int argc, char** argv) {

  Catch::Session().run();
  int eingabe;
  double belegungsfaktor;
  do {
	  cout << "Waehlen Sie die Kollisionsstrategie an :" << endl;
	  cout << "1. Lineares Sondieren" << endl << "2. Quadratisches Sondieren (standardmaessig)" << endl << "3. Doppeltes Hashing" << endl;
	  cout << "eingabe :";
	  cin >> eingabe;
  } while (eingabe < 1 || eingabe>3);
  cout << "Waehlen Sie die Belegungsfaktor an (standard = 0.6) :";
  cin >> belegungsfaktor;
  if (!belegungsfaktor)
	  belegungsfaktor = 0.6;
  HashTable table(1000, belegungsfaktor, eingabe);
  int anzahl = 200;
  int Ugrenz = 1000;
  for (int i = 0; i < anzahl; i++) {
	  int element = Ugrenz + rand() % 501;
	  table.insert(element);
  }
  cout << "Anzahl der Kollisionen : " << table.getCollisionCount() << endl;
  std::cout << "\nPress Enter to run measurement" << std::endl;
  std::cin.get();

  //benchmark_quicksort();
  benchmark_hybridquicksort();
  //benchmark_mergesort();
 // benchmark_heapsort();
  //benchmark_shellsort_2n();
  //benchmark_shellsort_3n();
  
  return 0;
}


//executes benchmark for quicksort
void benchmark_quicksort() {

  //file stream
  ofstream quicksort_measurement;
  quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

  //benchmark parameters / variables
  double dtime;
  int n_start = 1000;
  int n_step = 1000;
  int n_end = 1000000;

  vector<int> V;

  //actual benchmark loop
  for (int n = n_start; n<=n_end; n += n_step) {
	
	//"progress bar"
    std::cout << "Running Quicksort with n: " << n << std::endl;

	//generate n random integers
	sorting::randomizeVector(V, n);

	//start measurement
    dtime = omp_get_wtime();
    
	//execzute sorting algorithm
    sorting::QuickSort(V,0,V.size()-1);

	//stop time
    dtime = omp_get_wtime() - dtime;

	//write to file
    quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
  }

  //close file handle
  quicksort_measurement.close();
}

void benchmark_hybridquicksort() {

	//file stream
	ofstream hybridquicksort_measurement;
	hybridquicksort_measurement.open("hybridquicksort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Hybridquicksort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::HybridQuickSort(V, 0, V.size() - 1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		hybridquicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	hybridquicksort_measurement.close();
}
void benchmark_mergesort() {

	//file stream
	ofstream mergesort_measurement;
	mergesort_measurement.open("mergesort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;


	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Mergesort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);
		vector<int>V2(n, 0);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::MergeSort(V, V2, 0, V.size() - 1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		mergesort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	mergesort_measurement.close();
}
void benchmark_heapsort() {

	//file stream
	ofstream heapsort_measurement;
	heapsort_measurement.open("heapsort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Heapsort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::HeapSort(V, V.size() - 1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		heapsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	heapsort_measurement.close();
}

void benchmark_shellsort_2n() {

	//file stream
	ofstream shellsort_2n_measurement;
	shellsort_2n_measurement.open("shellsort_2n.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running shellsort_2n with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::ShellSort_2n(V, V.size());

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		shellsort_2n_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	shellsort_2n_measurement.close();
}

void benchmark_shellsort_3n() {

	//file stream
	ofstream shellsort_3n_measurement;
	shellsort_3n_measurement.open("shellsort_3n.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running shellsort_3n with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::ShellSort_3n(V, V.size());

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		shellsort_3n_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	shellsort_3n_measurement.close();
}










