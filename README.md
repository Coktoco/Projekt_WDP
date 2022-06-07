# 1. Pomysł - EPIc Adventure

Na samym początku przez nasze głowy przechodziły setki różnych pomysłów. Od ambitnych klonów Mario po reinterpretacje nowych Battlefieldów. Jednakże, po dłuższym zastanowieniu, uznaliśmy, że stworzymy coś bardziej autorskiego, nie trzymając się konkretnych wzorców. I tak właśnie zrodziła się idea zaprojektowania „endless runnera” w klimatach tajnego, post-sowieckiego ośrodka badawczego. Miały być roboty, power-upy i jetpacki, czyli wszystko to, czego aktualni gamerzy pragną najbardziej.
Efektem dziesiątek godzin pracy jest nasze najnowsze dzieło, zatytułowane „EPIc Adventure”. 

# 2. Proces instalacji 

- Do uruchomienia naszej gry zalecamy skorzystanie z programu Visual Studio. Można pobrać ten program tutaj: https://visualstudio.microsoft.com/pl/vs/ . Najlepiej, żeby była to wersja community.
- Kolejną niezbędnym krokiem będzie pobranie biblioteki Allegro 5.0, tutorial jak to zrobić znajduje się na tutaj: https://gamefromscratch.com/allegro-tutorial-series-part-1-getting-started/.  *Do produkcji gry korzystaliśmy z wersji Allegro 5.2.7.1*
- Po zainstalowaniu Allegro należy pobrać najbardziej aktualny kod gry wraz z plikami graficznymi z naszego repozytorium: https://github.com/Coktoco/Projekt_WDP . 
- Jeżeli wcześniej Visual Studio zostało połączone z kontem na Githubie, to można po prostu wybrać opcje: „Code -> Open with Visual Studio”, wtedy automatycznie wykona się proces instalacji kodu. 
Jeżeli Visual nie został połączony z Githubem, zawsze istnieje opcja pobrania pliku w formie .zip. Później wystarczy otworzyć plik projektu, który jest zawarty w pobranym folderze, za pomocą Visuala. 

# 3. Prcoes uruchamiania 
- Jeżeli proces instalacji powiódł się i nie pojawiły się żadne dodatkowe komplikacje, to będzie można teraz przystąpić do uruchomienia naszej gry.
- Wystarczy kliknąć w przycisk z zieloną strzałką „Lokalny debuger Windows”.
- To wszystko! Miłej zabawy 😊

# 4. Funkcje - instrukcja obsługi
- <b>Enter</b> - Przejście do ekranu gry z ekranu startowego
- <b>Strzałki</b> - Poruszanie się 
- <b>ESC</b> - Wyłączenie gry
# 4.1 Funkcje - rozgrywka
W grze występują dwa rodzaje „Power-Upów”:
- Kufel piwa: dodaje dodatkowe życie (maksymalna liczba żyć wynosi 3).
- Duch: przyznaje tryb ducha na okres pięciu sekund, który umożliwia przenikanie przez wrogów bez utraty żyć

# 4.2 Funkcje - mechanizm gry
- Losowo generowani wrogowie, posiadający określone hitboxy
- Implementacja aktywnego ekranu tytułowego, wraz z ekranem końcowym
- Zapętlone wyświetlanie tła
- Responsywnie aktualizujące się elementy graficzne tj. wyświetlanie posiadanej ilości żyć w formie serc na ekranie
- Rozbudowane power-upy urozmaicające rozgrywkę 
- Responsywny w czasie rzeczywistym system cieniowania bohatera
- Zapisywanie najlepszego wyniku do pliku tekstowego
- „Easter Egg” nawiązujący do kierunku studiów
- Zaawansowana, autorska grafika

# 5. Cel gry
Cel gry jest prosty: uzyskać jak największy wynik, unikając wrogów bez utraty wszystkich żyć.
- Najlepszy wynik zapisywany jest do pliku „highscore.txt”.

