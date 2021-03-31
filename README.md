# Pharmacy_sys
#### a simple CRUD system with the dynamic change of behaviors at run time using the strategy design pattern, and by simple factory method there is no more creating unnecesarry instances in the code, instead, it's created with the name of the type, and by factory method the pharmacy store is chosen at run time.
* you could insert meds and choose if they are vitamins or sedatives, and of cairo or alex pharmacy, delete, show all meds, search, update price and behaviors and pharmacy store.
* you could update their preservation behavior whether to be in low temp or high, and also it's dosage behavior to be pills or injects, and their pharmacy store to be alex or cairo.
* preservation default behavior in alex pharmacy is to be kept in moderate temp, and it's dosage to be pills.
* preservation default behavior in cairo pharmacy is to be kept in low temp, and it's dosage to be injects.
* you could change the dosage dynamically at run time with the med id, every time you set a new dosage you will be asked for:
  - set to inject behavior: needle size and number of injects a day.
  - set to pill behavior: concentration of pills and number of pills a day.
* you will be asked for the med id, price, type, and dosage by its default behavior every time you insert a med.
