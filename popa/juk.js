// Пример: всплывающее окно при нажатии на кнопку "Отправить"
const contactForm = document.querySelector('#contacts form');

if (contactForm) {
    contactForm.addEventListener('submit', function(event) {
        event.preventDefault(); // Предотвращаем отправку формы
        alert('Сообщение отправлено!'); // Простое всплывающее окно
    });
}