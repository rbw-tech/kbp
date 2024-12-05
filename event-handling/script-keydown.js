const inputField = document.getElementById('inputField');
const keyDisplay = document.getElementById('keyDisplay');

inputField.addEventListener('keydown', function(event) {
    keyDisplay.textContent = `Key terakhir yang ditekan: ${event.key}`;
});