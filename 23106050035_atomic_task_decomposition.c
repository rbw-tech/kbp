#include <stdio.h>    // Untuk fungsi input/output
#include <omp.h>      // Untuk fungsi-fungsi OpenMP
#include <stdlib.h>   // Untuk fungsi malloc dan free
#include <time.h>     // Untuk pengukuran waktu

// Konstanta untuk ukuran array dan chunk
#define ARRAY_SIZE 1000000000  // Ukuran array: 1 miliyar elemen untuk menunjukkan perbedaan performa
#define CHUNK_SIZE 100000      // Ukuran chunk: jumlah elemen yang diproses per thread dalam satu waktu

// Fungsi untuk menginisialisasi array dengan optimasi SIMD
void initializeArray(int* arr, int size) {
    // Paralel loop dengan optimasi SIMD untuk vectorization
    #pragma omp parallel for simd schedule(static, CHUNK_SIZE)
    for(int i = 0; i < size; i++) {
        // Menggunakan modulo untuk membuat pola data yang teratur
        // Membantu dalam branch prediction dan cache utilization
        arr[i] = i % 100;
    }
}

int main() {
    // Mulai mengukur waktu total program
    double total_start = omp_get_wtime();
    
    // Alokasi memori untuk array utama
    int* numbers = (int*)malloc(ARRAY_SIZE * sizeof(int));
    // Pengecekan keberhasilan alokasi memori
    if (numbers == NULL) {
        printf("Error: Gagal mengalokasi memori\n");
        return 1;
    }
    
    // Mulai mengukur waktu inisialisasi array
    double init_start = omp_get_wtime();
    initializeArray(numbers, ARRAY_SIZE);
    double init_time = omp_get_wtime() - init_start;
    
    // Dapatkan jumlah thread yang tersedia
    int num_threads = omp_get_max_threads();
    
    // Alokasi array untuk menyimpan hasil parsial dari setiap thread
    // Menggunakan calloc untuk menginisialisasi semua elemen dengan 0
    long long* partial_sums = (long long*)calloc(num_threads, sizeof(long long));
    if (partial_sums == NULL) {
        printf("Error: Gagal mengalokasi memori untuk partial sums\n");
        free(numbers);
        return 1;
    }
    
    // Variabel untuk menyimpan total akhir
    long long total = 0;
    
    // Mulai mengukur waktu komputasi paralel
    double compute_start = omp_get_wtime();
    
    // Mulai region paralel
    #pragma omp parallel
    {
        // Dapatkan ID thread saat ini
        int thread_id = omp_get_thread_num();
        // Variabel lokal untuk menyimpan jumlah parsial per thread
        long long local_sum = 0;
        
        // Distribusi loop ke semua thread
        // nowait: thread tidak perlu menunggu thread lain selesai
        #pragma omp for schedule(static, CHUNK_SIZE) nowait
        for(int i = 0; i < ARRAY_SIZE; i++) {
            // Akumulasi ke variabel lokal
            local_sum += numbers[i];
        }
        
        // Simpan hasil perhitungan lokal ke array partial sums
        partial_sums[thread_id] = local_sum;
    }
    
    // Gabungkan semua hasil parsial dari setiap thread
    for(int i = 0; i < num_threads; i++) {
        total += partial_sums[i];
    }
    
    // Hitung waktu komputasi paralel
    double compute_time = omp_get_wtime() - compute_start;
    
    // Mulai verifikasi dengan perhitungan serial
    double serial_start = omp_get_wtime();
    long long serial_total = 0;
    
    // Loop serial untuk verifikasi hasil
    for(int i = 0; i < ARRAY_SIZE; i++) {
        serial_total += numbers[i];
    }
    
    // Hitung waktu komputasi serial dan total
    double serial_time = omp_get_wtime() - serial_start;
    double total_time = omp_get_wtime() - total_start;
    
    // === Tampilkan semua hasil dan statistik ===
    
    // Tampilkan hasil komputasi
    printf("\n=== HASIL KOMPUTASI ===\n");
    printf("Hasil parallel   : %lld\n", total);
    printf("Hasil serial    : %lld\n", serial_total);
    
    // Tampilkan statistik waktu
    printf("\n=== STATISTIK WAKTU ===\n");
    printf("Waktu inisialisasi  : %.6f detik\n", init_time);
    printf("Waktu parallel      : %.6f detik\n", compute_time);
    printf("Waktu serial        : %.6f detik\n", serial_time);
    printf("Total waktu program : %.6f detik\n", total_time);
    // Hitung dan tampilkan speedup
    printf("Speedup            : %.2fx\n", serial_time/compute_time);
    
    // Tampilkan konfigurasi yang digunakan
    printf("\n=== KONFIGURASI ===\n");
    printf("Jumlah elemen   : %d\n", ARRAY_SIZE);
    printf("Ukuran chunk    : %d\n", CHUNK_SIZE);
    printf("Jumlah thread   : %d\n", num_threads);
    
    // Verifikasi kebenaran hasil
    if(total == serial_total) {
        printf("\nVERIFIKASI: SUKSES\n");
    } else {
        printf("\nVERIFIKASI: GAGAL\n");
    }
    
    // Pembersihan memori yang telah dialokasikan
    free(numbers);
    free(partial_sums);
    
    return 0;
}