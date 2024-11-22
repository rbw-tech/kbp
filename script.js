/**
* Inisialisasi semua fungsi setelah DOM selesai dimuat
* Event listener untuk memastikan semua elemen HTML tersedia sebelum JavaScript dijalankan
*/
document.addEventListener('DOMContentLoaded', function() {
    // Mendapatkan referensi elemen-elemen yang diperlukan
    const form = document.getElementById('regForm');         // Form Registrasi
    const modal = document.getElementById('successModal');   // Modal Sukses
    const closeBtn = document.querySelector('.close-modal'); // Tombol tutup modal

    /**
    * Event handler untuk submit form
    * Menangani proses pengiriman form dan menampilkan feedback
    */
    form.addEventListener('submit', function(e) {
        e.preventDefault(); // Mencegah form melakukan submit default
        
        // Mengatur tampilan loading state pada tombol submit
        const submitBtn = this.querySelector('button[type="submit"]');
        const originalText = submitBtn.textContent;                        // Menyimpan text asli tombol
        submitBtn.textContent = 'Processing...';                           // Mengubah text menjadi loading
        submitBtn.disabled = true;                                         // Menonaktifkan tombol selama proses

        /**
        * Simulasi panggilan API dengan setTimeout
        * Dalam implementasi nyata, ini akan diganti dengan actual API call
        */
        
        // Simulate API call
        setTimeout(() => {
            modal.classList.add('show');             // Menampilkan modal sukses
            
            // Mereset form dan tombol ke kondisi awal
            form.reset();                            // Mengosongkan form
            submitBtn.textContent = originalText;    // Mengembalikan text tombol
            submitBtn.disabled = false;              // Mengaktifkan kembali tombol
        }, 1500);
    });

   /**
    * Event handlers untuk menutup modal
    * Dua cara: melalui tombol close atau klik di luar modal
    */
    closeBtn.addEventListener('click', () => modal.classList.remove('show'));
    window.addEventListener('click', (e) => {
        if (e.target === modal) modal.classList.remove('show');
    });

   /**
    * Handler untuk tombol Enroll di setiap program card
    * Mengatur auto-fill form dan smooth scroll
    */
    const enrollBtns = document.querySelectorAll('.enroll-btn');
    enrollBtns.forEach(btn => {
        btn.addEventListener('click', (e) => {
            e.stopPropagation();                                                             // Mencegah event bubbling ke card
            const program = e.target.closest('.program-card').dataset.program;               // Mendapatkan jenis program dari data attribute
            document.getElementById('programSelect').value = program;                        // Auto-fill dropdown program
            document.getElementById('registration').scrollIntoView({ behavior: 'smooth' });  // Scroll halus ke form registrasi
        });
    });

   /**
    * Konfigurasi Intersection Observer untuk animasi scroll
    * Menambahkan animasi saat elemen muncul dalam viewport
    */
    const observerOptions = {
        threshold: 0.1,                     // Trigger saat 10% elemen terlihat
        rootMargin: '0px 0px -50px 0px'     // Offset trigger
    };

    const observer = new IntersectionObserver(entries => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.classList.add('visible');       // Menambahkan class untuk animasi
            }
        });
    }, observerOptions);

   /**
    * Menerapkan observer ke semua section
    * Mengamati setiap section untuk trigger animasi
    */
    document.querySelectorAll('section').forEach(section => {
        observer.observe(section);
    });
});
