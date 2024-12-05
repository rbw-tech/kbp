const itemInput = document.getElementById('itemInput');
const addButton = document.getElementById('addButton');
const itemList = document.getElementById('itemList');

addButton.addEventListener('click', function() {
    const itemText = itemInput.value.trim();
    
    if (itemText !== '') {
        const li = document.createElement('li');
        li.textContent = itemText;
        
        itemList.appendChild(li);
        
        itemInput.value = '';
    }
});

itemInput.addEventListener('keydown', function(event) {
    if (event.key === 'Enter') {
        addButton.click();
    }
});