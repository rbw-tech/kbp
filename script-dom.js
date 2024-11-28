const containers = document.querySelectorAll('div');
containers.forEach(container => {
    container.style.backgroundColor = '#6c4b15'; // Brownish color
});

const link = document.querySelector('a');
if (link) {
    link.href = 'https://www.google.com';
}

const listItems = document.querySelectorAll('.list');
listItems.forEach((item, index) => {
    item.textContent = `List Baru ${index + 1}`;
    
    item.style.color = 'white';
    item.style.backgroundColor = '#808080';
    item.style.fontSize = '18px';
    item.style.fontFamily = 'Arial';
});

const paragraphs = document.querySelectorAll('p');
paragraphs.forEach(p => {
    p.style.color = 'white';
});