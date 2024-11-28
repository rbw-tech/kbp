// Nyari semua div yang ada, terus dikasih warna coklat
const containers = document.querySelectorAll('div');
containers.forEach(container => {
   container.style.backgroundColor = '#6c4b15'; // Warna coklat
});

// Ngubah link yang tadinya # jadi ke Google
const link = document.querySelector('a');
if (link) {
   link.href = 'https://www.google.com';
}

// Nyari semua list, terus diubah textnya pake List Baru 1,2,3
// Sekalian stylenya diubah jadi warna putih, background abu-abu, font Arial ukuran 18px  
const listItems = document.querySelectorAll('.list');
listItems.forEach((item, index) => {
   item.textContent = `List Baru ${index + 1}`;
   
   item.style.color = 'white';
   item.style.backgroundColor = '#808080';
   item.style.fontSize = '18px';
   item.style.fontFamily = 'Arial';
});

// Nyari semua paragraf terus diubah jadi warna putih
const paragraphs = document.querySelectorAll('p');
paragraphs.forEach(p => {
   p.style.color = 'white';
});
