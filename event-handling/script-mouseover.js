const hoverButton = document.getElementById('hoverButton');
const messageText = document.getElementById('messageText');

hoverButton.addEventListener('mouseover', function() {
    messageText.textContent = 'Mouse is over the button!';
});

hoverButton.addEventListener('mouseout', function() {
    messageText.textContent = '';
});