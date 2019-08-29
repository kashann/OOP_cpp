# OOP_cpp
Some of my work while learning OOP in C++. Written in Visual Studio 2013... might not compile/work properly.

## Specificații proiect C++ Stackoverflow la consolă

Să se implementeze o aplicație consolă care să permită interacțiunea unei comunități de utilizatori în vederea rezolvării de probleme.
Aplicația implementează offline funcțiile platformei online http://stackoverflow.com/. Se poate imagina un terminal neconectat la Internet pe care utilizatorii îl folosesc asincron. Aplicația trebuie sa poată fi utilizată offline pentru primele faze ale proiectului.
Pentru ultima fază a proiectului se va pune la dispoziție un server si un client C++ prin care pot fi primite întrebări și se pot da răspunsuri. În această fază aplicație consolă este folosită de către un singur utilizator activ (se autentifică la pornirea aplicației). 
Componente obligatorii ce trebuie abstractizate și implementate prin clase 
- Conturi Utilizatori; aplicația trebuie sa permită gestiunea unor tipuri diferite de utilizatori (administrator, moderator subiect, utilizator obișnuit);  
- Meniul aplicației consolă; navigarea în aplicația consola se face prin mesaje afișate pe ecran; alegerea unei opțiuni se face natural (scriu text in consola) sau prin indicarea opțiunii (cod numeric, etc) 
- Subiecte/Probleme discutate; aplicația trebuie să permită gestiunea unor tipuri diferite de subiecte de discuție, clasificate în  funcție de domeniul in care se încadrează problema (C++, Java, .NET, etc); fiecare subiect de discuție are asociate răspunsuri de la diferiți utilizatori; un utilizator poate da un singur răspuns pe care îl poate modifica; în momentul în care autorul subiectului/problemei marchează răspunsul corect, discuția se consideră finalizată și nu mai sunt permise alte modificări/intervenții; prin opțiunile aplicației utilizatorii pot filtra discuțiile după categorie, după cuvinte cheie din titlu, după dată, etc.
- Clase de utilizator; în funcție de răspunsurile date și de corectitudinea lor, utilizatorii sunt clasificați pe diferite categorii; astfel se implementează un sistem de bonificare a participării active. 
Pot fi identificate și alte entități care să permită implementare soluției. 
Pentru a salva datele fiecărei sesiuni de lucru, se vor utiliza fișiere binare sau text care să stocheze aceste entități.   

## Cerințe proiect - faza 1
> aceste cerinte sunt orientative; la seminar, in functie de situatie, pot fi stabilite impreuna cu profesorul coordonator alte cerinte 
-	Termenul de predare se stabilește la seminar. 
-	Definirea a minim 5 clase care au legatura cu cerinta proiectului
-	Fiecare clasa trebuie sa contina minim un camp definit dinamic gestionat printr-un pointer si minim un vector definit static; trebuie abordate atat siruri de caractere (char*) cat si vectori de valori numerice
-	In solutie trebuie sa existe minin o clasa ce defineste un camp static si minim o clasa ce defineste un camp constant
-	Toate atributele se definesc pe zona privata a clasei
-	Pentru fiecare atribut se defineste o interfata publica (functii accesor) ce permite citirea si scrierea valorii; functiile de modificare trebuie sa contina minim o regula de validare a valorii
-	Fiecare clasa contine minim 2 metode generice de prelucrare/afisare a atributelor
-	Fiecare clasa contine minim 2 constructori cu parametri, constructor de copiere, destructor si forma supraincarcata a operatorului =
-	Pentru fiecare clasa se supraincarca >> si <<
-	Toate clasele sunt definite intr-un singur fisier sursa
-	Testarea claselor (metoda main) se gaseste intr-un alt fisier sursa
-	Faza 1 se consideră realizată dacă sunt implementate cel puțin 75% din cerinte
> cerintele pentru faza 2 & 3 nu sunt disponibile momentan
