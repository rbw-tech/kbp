#include <stdio.h>     // Library standar untuk input dan output
#include <stdlib.h>    // Library untuk fungsi standar seperti malloc dan free
#include <omp.h>       // Library OpenMP untuk pemrograman parallel
#include <time.h>      // Library untuk fungsi waktu
#include <math.h>      // Library untuk fungsi matematika seperti sin, cos, dan sqrt

#define ARRAY_SIZE 50000000  // Mendefinisikan ukuran array menjadi 50 juta elemen
#define COMPUTATIONS 100     // Mendefinisikan jumlah komputasi berat per elemen

// Fungsi komputasi berat untuk setiap elemen
double heavy_computation(int x) {
    double result = 0.0;
    // Loop sebanyak COMPUTATIONS untuk melakukan operasi matematika berat
    for(int i = 0; i < COMPUTATIONS; i++) {
        result += sin(x) * cos(x) * sqrt(x + i); // Hitung hasil dari operasi sin, cos, dan sqrt
    }
    return result;  // Mengembalikan hasil komputasi
}

// Fungsi untuk perhitungan serial
double serial_sum(int* arr, int size) {
    double sum = 0.0;
    // Loop untuk menghitung komputasi berat secara serial
    for(int i = 0; i < size; i++) {
        sum += heavy_computation(arr[i]);  // Tambahkan hasil komputasi dari setiap elemen array
    }
    return sum;  // Mengembalikan hasil total
}



// Fungsi untuk perhitungan parallel
double parallel_sum(int* arr, int size) {
    double total = 0.0;
    // Menggunakan pragma OpenMP untuk parallel reduction pada variabel total
    #pragma omp parallel reduction(+:total)
    {
        // Membagi loop untuk dieksekusi secara parallel oleh beberapa thread
        #pragma omp for
        for(int i = 0; i < size; i++) {
            total += heavy_computation(arr[i]);  // Hitung komputasi berat secara parallel
        }
    }
    return total;  // Mengembalikan hasil total komputasi
}

int main() {
    // Menentukan jumlah thread berdasarkan jumlah prosesor yang tersedia
    int num_threads = omp_get_num_procs();
    omp_set_num_threads(num_threads);  // Mengatur jumlah thread yang digunakan
    printf("Jumlah thread yang digunakan: %d\n\n", num_threads);
    
    // Alokasi memori untuk array
    int* data = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (data == NULL) {  // Cek apakah alokasi memori gagal
        printf("Gagal mengalokasi memori!\n");
        return 1;  // Keluar dari program jika alokasi gagal
    }
    
    // Inisialisasi array
    printf("Menginisialisasi array...\n");
    // Mengisi array dengan nilai dari 0 hingga 359 (modulus 360)
    for(int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = i % 360;  // Nilai ini akan digunakan untuk fungsi trigonometri
    }
    
    double start_time, end_time;  // Variabel untuk menyimpan waktu mulai dan akhir
    double serial_result, parallel_result;  // Variabel untuk menyimpan hasil komputasi

    // Test Perhitungan Serial
    printf("\nPerhitungan Serial dimulai...\n");
    start_time = omp_get_wtime();  // Mulai penghitungan waktu
    serial_result = serial_sum(data, ARRAY_SIZE);  // Jalankan fungsi serial
    end_time = omp_get_wtime();  // Catat waktu setelah selesai
    double serial_time = end_time - start_time;  // Hitung waktu yang diambil oleh perhitungan serial
    printf("Waktu Serial   : %.4f detik\n", serial_time);
    printf("Hasil Serial   : %.2f\n", serial_result);

    // Test Perhitungan Parallel
    printf("\nPerhitungan Parallel dimulai...\n");
    start_time = omp_get_wtime();  // Mulai penghitungan waktu
    parallel_result = parallel_sum(data, ARRAY_SIZE);  // Jalankan fungsi parallel
    end_time = omp_get_wtime();  // Catat waktu setelah selesai
    double parallel_time = end_time - start_time;  // Hitung waktu yang diambil oleh perhitungan parallel
    printf("Waktu Parallel : %.4f detik\n", parallel_time);
    printf("Hasil Parallel : %.2f\n", parallel_result);
    
    // Hitung dan tampilkan perbedaan waktu dan speedup
    double time_diff = serial_time - parallel_time;  // Selisih waktu antara serial dan parallel
    double speedup = serial_time / parallel_time;  // Hitung speedup (berapa kali lebih cepat)
    
    printf("\n=== Hasil Analisis ===\n");
    printf("Perbedaan waktu     : %.4f detik\n", time_diff);  // Tampilkan selisih waktu
    printf("Speed up            : %.2fx lebih cepat\n", speedup);  // Tampilkan faktor percepatan
    // Hitung efisiensi berdasarkan jumlah thread
    printf("Efisiensi           : %.2f%%\n", (speedup/num_threads)*100);
    // Verifikasi apakah hasil dari perhitungan serial dan parallel valid (selisihnya < 0.01)
    printf("Verifikasi hasil    : %s\n", 
           fabs(serial_result - parallel_result) < 0.01 ? "VALID" : "TIDAK VALID");
    
    // Pembersihan memori
    free(data);  // Membebaskan memori yang dialokasikan untuk array
    
    printf("\nTekan Enter untuk keluar...");
    getchar();  // Menunggu input user sebelum menutup program
    
    return 0;  // Kembali dari fungsi main menandakan program selesai
}
