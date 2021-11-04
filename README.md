Wprowadzenie

Realizacja pewnego języka programowania składa się z:

    kompilatora, generującego kod na maszynę wirtualną, oraz

    interpretera kodu tej maszyny.

Maszyna wirtualna

Instrukcje w kodzie maszyny wirtualnej mają adresy, będące kolejnymi nieujemnymi liczbami całkowitymi, od zera.

Dane maszyny przechowywane są na stosach.

Stos to struktura danych z operacjami włożenia i zdjęcia elementu. Operacje te często nazywa się push i pop. Operacja zdejmująca element daje tę spośród wartości na stosie, która została włożona na stos najpóźniej.

Maszyna ma, numerowane nieujemnymi liczbami całkowitymi, stosy bitów. Ma też stos adresów instrukcji, który dalej będziemy nazywać stosem powrotów.

Maszyna rozpoznaje dziesięć rodzajów instrukcji, o kodach od 0 do 9:

    PUSH_0 stos

    włóż bit 0 na stos o numerze stos,

    PUSH_1 stos

    włóż bit 1 na stos o numerze stos,

    OUTPUT_0

    pisz bit 0 na wyjście,

    OUTPUT_1

    pisz bit 1 na wyjście,

    POP_BRANCH adres stos

    zdejmij bit ze stosu o numerze stos,

    jeśli bit ten ma wartość 0 to przejdź do instrukcji pod adresem adres, w przeciwnym przypadku przejdź do następnej instrukcji,

    INPUT_BRANCH adres

    czytaj bit z wejścia,

    jeśli bit ten ma wartość 0 to przejdź do instrukcji pod adresem adres, w przeciwnym przypadku przejdź do następnej instrukcji,

    JUMP adres

    przejdź do instrukcji pod adresem adres,

    CALL adres

    włóż adres następnej instrukcji, za instrukcją CALL, na stos powrotów i przejdź do instrukcji pod adresem adres,

    RETURN

    zdejmij adres ze stosu powrotów i przejdź do instrukcji pod tym adresem,

    HALT

    zakończ pracę maszyny.

Instrukcja INPUT_BRANCH czyta bity kolejnych znaków wejścia w kolejności od bitów najbardziej znaczących. Po dojściu do końca danych daje osiem kolejnych bitów 1.

Instrukcje OUTPUT_0 i OUTPUT_1 piszą bity kolejnych znaków wyjścia w kolejności od bitów najbardziej znaczących.

Wykonanie programu zaczyna się od instrukcji o adresie 0.

Jeśli instrukcja nie określa inaczej, to po jej wykonaniu przechodzimy do instrukcji znajdującej się w kodzie bezpośrednio za nią.

Jeżeli instrukcja, do której mielibyśmy przejść, nie istnieje, to kod jest błędny.
Kompilowany język

Składnię języka opisuje gramatyka z symbolem początkowym Program:

Program → CiągProcedur ProceduraGłówna
ProceduraGłówna → Treść
CiągProcedur → ε | Procedura CiągProcedur
Procedura → NazwaProcedury Treść
NazwaProcedury → A | B | C | D | E | F | G | H | I | J | K | L | M
               | N | O | P | Q | R | S | T | U | V | W | X | Y | Z
Treść → { CiągInstrukcji }
CiągInstrukcji → ε | Instrukcja CiągInstrukcji
Instrukcja → Wywołanie | Zapis | Wybór
Wywołanie → NazwaProcedury
Zapis → Cel CiągBitów
Cel → NazwaStosu | Specjalna
NazwaStosu → a | b | c | d | e | f | g | h | i | j | k | l | m
           | n | o | p | q | r | s | t | u | v | w | x | y | z
Specjalna → $
CiągBitów → Bit CiągBitów | Bit
Bit → - | +
Wybór → Źródło Treść Treść
Źródło → NazwaStosu | Specjalna

W programie, oprócz znaków reprezentujących symbole końcowe gramatyki, mogą wystąpić, w dowolnym miejscu, separatory:

    spacje, tabulacje, końce wiersza,

    komentarze od ; do końca wiersza.

Nie mają one wpływu na interpretację programu.

Program składa się z ciągu nazwanych procedur oraz anonimowej procedury głównej, odpowiadającej funkcji main() w języku C.

Nazwa procedury jest wielką literą.

Nazwa stosu jest małą literą.

Wykonanie programu zaczyna się od procedury głównej.

Treść procedury jest ciągiem instrukcji.

Są trzy rodzaje instrukcji:

    wywołanie

    Powoduje wykonanie wskazanej procedury. Po jej zakończeniu wracamy do miejsca wywołania.

    zapis

    Wkłada niepusty ciąg bitów na stos o podanej nazwie lub, jeśli zamiast nazwy stosu jest nazwa specjalna $, pisze ten ciąg na wyjście.

    Bit o wartości 0 jest reprezentowany przez znak - a bit o wartości 1 jest reprezentowany przez znak +.

    Bity są zapisywane na stos, lub pisane na wyjście, w kolejności wystąpienia w ciągu, od lewej do prawej.

    wybór

    Wykonuje jeden z dwóch ciągów instrukcji w zależności od wartości bitu.

    Jeśli w instrukcji podana jest nazwa stosu, to wyboru dokonujemy na podstawie wartości bitu zdjętego z tego stosu.

    Jeśli, zamiast nazwy stosu, jest podana nazwa specjalna $, to wyboru dokonujemy na podstawie bitu wczytanego z wejścia.

    Jeżeli bit ma wartość 1 to wykonywany jest pierwszy z podanych ciągów instrukcji, w przeciwnym przypadku wykonuje się drugi ciąg instrukcji.

Polecenie

Napisz kompilator, tłumaczący program w opisanym powyżej języku na kod maszyny wirtualnej.

Testując rozwiązanie można wykonać generowany kod za pomocą interpretera, którego implementacja jest w pliku interpreter.c dołączonym do treści zadania.

Interpreter zakłada poprawność wykonywanego kodu. W przypadku wykrycia błędu zgłasza naruszenie asercji.
Postać danych

Dane kompilatora to program w języku opisanym powyżej.
Postać wyniku

Wynik pracy kompilatora to tekstowy zapis kodu maszyny wirtualnej.

Każda instrukcja maszyny jest w jednym wierszu. Są tam, kolejno, rozdzielone pojedynczymi spacjami, kod instrukcji oraz zero, jeden lub dwa argumenty.

W kodzie wynikowym instrukcja HALT musi wystąpić dokładnie jeden raz i musi być ostatnią instrukcją w programie.
Przykłady

Do treści zadania dołączone są pliki .in z przykładowymi danymi, pliki .out z wynikami wzorcowymi i pliki .vm z kodem maszyny wirtualnej, wygenerowanym przez rozwiązanie wzorcowe.

    Dla danych przyklad1.in polecenie:

    < przyklad1.in ./kompilator | tee przyklad1.vm | ./interpreter > przyklad1.out

    utworzy plik przyklad1.out. Plik z kodem maszyny wirtualnej może mieć postać przyklad1.vm.

    Dla danych przyklad2.in polecenie:

    < przyklad2.in ./kompilator | tee przyklad2.vm | ./interpreter > przyklad2.out

    utworzy pliki przyklad2.out. Plik z kodem maszyny wirtualnej może mieć postać przyklad2.vm.

    Dla danych przyklad3.in polecenie:

    (./kompilator < przyklad3.in | tee przyklad3.vm ; echo "kompilator") | ./interpreter > przyklad3.out

    utworzy plik przyklad3.out. Plik z kodem maszyny wirtualnej może mieć postać przyklad3.vm.

Walidacja i testy

  Rozwiązania zostaną poddane walidacji, wstępnie badającej zgodność ze specyfikacją.

  Walidacja sprawdzi działanie programu na przykładach dołączonych do treści zadania.

  Pomyślne przejście walidacji jest warunkiem dopuszczenia programu do testów poprawności. Program, który walidacji nie przejdzie, dostanie zerową ocenę poprawności.

  Walidacja i testy zostaną przeprowadzone na komputerze students.

  Programy będą kompilowane poleceniem:

    gcc -std=c11 -pedantic -Wall -Wextra -Werror -fstack-protector-strong -g nazwa.c -o nazwa

  gdzie nazwa.c to nazwa pliku z kodem źródłowym.

  Wymagane są wszystkie wymienione opcje kompilatora. Nie będą do nich dodawane żadne inne.

  Zwracamy uwagę, że poszczególne wersje kompilatora gcc mogą się różnić sposobem obsługi tych samych opcji. Przed wysłaniem rozwiązania warto więc skompilować je i przetestować na students, w sposób opisany powyżej.

  Podczas walidacji i testów, program nazwa będzie uruchamiany pod kontrolą programu Valgrind poleceniem:

    valgrind --leak-check=full -q ./nazwa

  Jeśli Valgrind wykryje błąd, to nawet, gdyby wynik był prawidłowy uznamy, że program testu nie przeszedł.

  Opcja -q powoduje, że jedynymi komunikatami, wypisywanymi przez program Valgrind, są komunikaty o błędach.

  Opcja --leak-check=full wskazuje Valgrindowi, że powinien, między innymi, szukać wycieków pamięci.

  Przyjmujemy, że wynik funkcji main() inny niż 0 informuje o błędzie wykonania programu.
