# Pharmacy_sys
#### a simple CRUD system with the dynamic change of behaviors at run time using the strategy design pattern.
* you could insert meds and choose if they are vitamins or sedatives, delete, show all meds, search, update price and behaviors.
* you could update their preservation behavior whether to be in low temp or high, and also it's dosage behavior to be pills or injects.
* vitamins preservation default behavior is to be kept in moderate temp, and it's dosage to be pills.
* sedatives preservation default behavior is to be kept in low temp, and it's dosage to be injects.
* you could change the dosage dynamically at run time with the med id, every time you set a new dosage you will be asked for:
- inject behavior: needle size and number of injects a day.
- pill behavior: concentration of pills and number of pills a day.
* you will be asked for the med id, price, type, and dosage by its default behavior every time you insert a med.
