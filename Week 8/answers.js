document.addEventListener('DOMContentLoaded', function() {
    let corrects = document.querySelectorAll('.correct');
    for (let j = 0; j < corrects.length; j++) {
      corrects[j].addEventListener('click', function(){
          corrects[j].style.backgroundColor = 'green';
      })
    }

    let incorrects = document.querySelectorAll('.incorrect');
    for (let i = 0; i < incorrects.length; i++) {
        incorrects[i].addEventListener('click', function(){
            incorrects[i].style.backgroundColor = 'red';
        })
    }
    });

    document.addEventListener('DOMContentLoaded', function() {
        const questions = [
            {answer: 'Michael Phelps', id: 'question6' },
            {answer: 'American football', id: 'question7' },
            {answer: 'The Masters', id: 'question8' },
            {answer: 'Brazil', id: 'question9'},
            {answer: 'Michael Jordan', id: 'question10'},
            {answer: 'Refraction', id: 'question11'},
            {answer: 'Photosynthesis', id: 'question12'},
            {answer: 'Supernova', id: 'question13'},
            {answer: 'Catalyst', id: 'question14'},
            {answer: 'Earthquake', id: 'question15'},
            {answer: 'Michelangelo', id: 'question16'},
            {answer: 'Incas', id: 'question17'},
            {answer: 'Communism', id: 'question18'},
            {answer: 'World War I', id: 'question19'},
            {answer: 'Colossus', id: 'question20'},
            {answer: 'Ottawa', id: 'question21'},
            {answer: 'Bering Strait', id: 'question22'},
            {answer: 'Uganda', id: 'question23'},
            {answer: 'Caspian Sea', id: 'question24'},
            {answer: 'Mount Kilimanjaro', id: 'question25'}
        ];

        document.querySelector('#submit').addEventListener('click', function() {
            const input = document.querySelector('input');
            const userAnswer = input.value.trim();
            let answeredCorrectly = false;

            for (const question of questions) {
                if (userAnswer === question.answer) {
                    answeredCorrectly = true;
                    input.style.backgroundColor = 'green';
                    document.querySelector(`#${question.id}`).innerHTML = 'Correct!';
                }
            }

            if (!answeredCorrectly) {
                input.style.backgroundColor = 'red';
            }
        });
    });
