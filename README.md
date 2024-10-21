# EV-Charger
## Descriere
* Acest proiect simulează o stație de încărcare pentru un vehicul electric folosind LED-uri și două butoane.
	* Stația poate avea două stări: „liberă” (indicată prin aprinderea LED RGB verde) și „ocupată” (indicată prin aprinderea unui LED RGB roșu).
	* Încărcarea poate fi vazută prin patru LED-uri, fiecare reprezentând un procent de încărcare (25%, 50%, 75%, 100%).
	* Apăsarea butonului de start pornește încărcarea, iar LED-urile clipesc treptat pentru a arăta progresul fiecărei etape.
	* Dacă butonul de stop este ținut apăsat mai mult de 1 secundă, încărcarea se oprește si toate LED-urile clipesc de trei ori.
	* După oprirea procesului, stația revine automat la starea „liberă” (LED RGB verde).
  * Pentru a prinde corect apăsarile butoanelor am folosit tehnica de debouncing.
## Componente utilizate
* 4x LED-uri roșii (pentru a simula procentul de încărcare)
* 1x LED RGB (pentru starea de liber sau ocupat)
* 8x Rezistoare (7x 220, 2x 1K)
* 2x Butoane (pentru start încărcare și stop încărcare)
* Linii de legătură
* Breadboard
## Setup fizic
![1](https://github.com/user-attachments/assets/791330d4-7071-4744-9eae-7e8c5846dac1)
![2](https://github.com/user-attachments/assets/c3d783a8-d2a6-4aeb-8e65-94ab59a5ece2)
![3](https://github.com/user-attachments/assets/4ecc59c3-d8a8-4bdc-95c1-fe5465f8f7af)
## Funcționalitatea montajului fizic
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/VQCF18vdndk/0.jpg)](https://www.youtube.com/watch?v=VQCF18vdndk)
## Schema Electrică
![Screenshot 2024-10-20 221126](https://github.com/user-attachments/assets/99501f5a-aeb2-4f7e-8a50-b3955c2eacab)

