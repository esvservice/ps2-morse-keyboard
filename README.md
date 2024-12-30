Dit Arduino-programma biedt een Morse-code-toetsenbordfunctionaliteit. Het maakt gebruik van de PS2Keyboard-bibliotheek om invoer van een PS2-toetsenbord te verwerken. De getypte tekens worden opgeslagen in een wachtrij en vervolgens als Morse-code-symbolen verzonden.

Hardware
Arduino Nano ATmega328P
PS2-toetsenbord
LED (pin 13)
Piezo-element (pin 10)

Functionaliteit
Wanneer de gebruiker op het toetsenbord typt, worden de tekens in een wachtrij opgeslagen.
De tekens in de wachtrij worden vervolgens als Morse-code-symbolen verzonden.
De LED en het piezo-element geven visuele en auditieve feedback over de verzonden tekens.
Er zijn speciale functies:
Leegmaken van de wachtrij bij het indrukken van de Escape-toets.
Automatisch verzenden van "CQ CQ CQ DE ON4JES ON4JES ON4JES" bij het indrukken van de '%'-toets.

Bibliotheek
PS2Keyboard-bibliotheek: http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html

Installatie
Download de PS2Keyboard-bibliotheek van de bovenstaande link.
Extraheer de bestanden en kopieer de map PS2Keyboard naar de libraries-map van je Arduino-installatie.
Open je Arduino-IDE en ga naar Schets > Inclusies gebruiken > PS2Keyboard om de bibliotheek toe te voegen aan je sketch.
Compileer en upload het programma naar je Arduino-board.

Gebruik
Sluit het PS2-toetsenbord aan op je Arduino-board.
Open de seriële monitor in de Arduino-IDE.
Typ op het toetsenbord om Morse-code-symbolen te genereren.
De LED en het piezo-element geven feedback over de verzonden tekens.
Druk op de Escape-toets (ESC) om de wachtrij leeg te maken.
Druk op de '%'-toets om "CQ CQ CQ DE ON4JES ON4JES ON4JES" automatisch te verzenden.
Ondersteunde toetsen

Alfanumerieke toetsen:
Alle letters (A-Z) en cijfers (0-9) worden omgezet naar het overeenkomstige Morse-code-symbool en verzonden.
Kleine letters worden automatisch omgezet naar hoofdletters.

Leestekens:
Punt (.)
Komma (,)
Uitroepteken (!)
Vraagteken (?)
Schuine streep (/)
Plus (+)
Koppelteken (-)
Gelijkteken (=)
At-teken (@)
Deze leestekens worden eveneens omgezet naar het overeenkomstige Morse-code-symbool en verzonden.

Spatiebalk, Enter en Newline:
Het indrukken van de spatiebalk, Enter-toets of Newline-teken genereert een lange pauze tussen de Morse-code-symbolen.

Feedback
De LED (pin 13) knippert tijdens het verzenden van Morse-code-symbolen.
Het piezo-element (pin 10) produceert een toon tijdens het verzenden van Morse-code-symbolen.
Deze visuele en auditieve feedback helpen de gebruiker bij het volgen van de Morse-code-transmissie.

Opmerking
Het programma is ontworpen voor gebruik met een Arduino Nano ATmega328P-board.
Wijzig indien nodig de pinnen voor de LED en het piezo-element.
Pas de snelheid in woorden per minuut aan door de WPM-definitie te wijzigen.
