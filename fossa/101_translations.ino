// Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv
String translate(String key, String language) {
  const char* translations = R"(
[en]
usbT = USB config mode
tapScreenT = TAP SCREEN WHEN FINISHED
scanMeT = SCAN ME TAP SCREEN WHEN FINISHED
totalT = Total: 
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = FOR
fiatT = FIAT!
feedT = feed me fiat.
chargeT = % charge
printingT = Printing
waitT = please wait
workingT = Working...
thisVoucherT = This voucher can be redeemed for
ofBitcoinT = of Bitcoin
thankYouT = Thank you
scanMeClaimT = Scan me with a Lightning wallet to get your Bitcoin
tooMuchFiatT = Too much FIAT!
contactOwnerT = Please contact owner
failedT = FAILED
unableT = unable to read lnurl
maxaT = WARNING: max amount
willT = Will use default
loadT = WARNING: load charge
maxrT = WARNING: max reset
printY = WARNING: print bool
langT = WARNING: lang fail

[es]
usbT = Modo de configuracion USB
tapScreenT = TOQUE LA PANTALLA CUANDO TERMINE
scanMeT = ESCANEME TOQUE LA PANTALLA CUANDO TERMINE
totalT = Total:
fossaT = FOSSA! Cajero Bitcoin
satsT = SATS
forT = PARA
fiatT = FIAT!
feedT = dame fiat.
chargeT = % de carga
printingT = Imprimiendo
waitT = por favor espera
workingT = Trabajando...
thisVoucherT = Este vale se puede canjear por
ofBitcoinT = de Bitcoin
thankYouT = Gracias
scanMeClaimT = Escaneame con una billetera Lightning para recibir tu Bitcoin
tooMuchFiatT = Demasiado FIAT!
contactOwnerT = Por favor contacta al propietario
failedT = FALLIDO
unableT = no se puede leer lnurl
maxaT = ADVERTENCIA: cantidad maxima
willT = Usara el valor predeterminado
loadT = ADVERTENCIA: carga de valor
maxrT = ADVERTENCIA: reinicio maximo
printY = ADVERTENCIA: bool de impresion
langT = ADVERTENCIA: error de idioma

[fr]
usbT = Mode de configuration USB
tapScreenT = TOUCHEZ L ECRAN QUAND TERMINE
scanMeT = SCANEZ MOI TOUCHEZ L ECRAN QUAND TERMINE
totalT = Total:
fossaT = FOSSA! Distributeur Bitcoin
satsT = SATS
forT = POUR
fiatT = FIAT!
feedT = nourrissez moi de fiat
chargeT = % charge
printingT = Impression
waitT = veuillez patienter
workingT = En cours...
thisVoucherT = Ce bon peut etre echange contre
ofBitcoinT = de Bitcoin
thankYouT = Merci
scanMeClaimT = Scannez moi avec un portefeuille Lightning pour obtenir votre Bitcoin
tooMuchFiatT = Trop de FIAT !
contactOwnerT = Veuillez contacter le proprietaire
failedT = ECHOUE
unableT = impossible de lire lnurl
maxaT = AVERTISSEMENT: montant maximal
willT = Utilisera la valeur par defaut
loadT = AVERTISSEMENT: charge de chargement
maxrT = AVERTISSEMENT: reinitialisation maximale
printY = AVERTISSEMENT: bool impression
langT = AVERTISSEMENT: echec de langue

[de]
usbT = USB-Konfigurationsmodus
tapScreenT = BERUEHREN SIE DEN BILDSCHIRM WENN FERTIG
scanMeT = SCANNEN SIE MICH BERUEHREN SIE DEN BILDSCHIRM WENN FERTIG
totalT = Gesamt:
fossaT = FOSSA! Bitcoin-Geldautomat
satsT = SATS
forT = FUER
fiatT = FIAT!
feedT = fuettere mich mit Fiat
chargeT = % Ladung
printingT = Drucken
waitT = bitte warten
workingT = Arbeitet...
thisVoucherT = Dieser Gutschein kann eingeloest werden fuer
ofBitcoinT = von Bitcoin
thankYouT = Danke
scanMeClaimT = Scannen Sie mich mit einem Lightning Wallet um Ihr Bitcoin zu erhalten
tooMuchFiatT = Zu viel FIAT!
contactOwnerT = Bitte kontaktieren Sie den Besitzer
failedT = FEHLGESCHLAGEN
unableT = lnurl konnte nicht gelesen werden
maxaT = WARNUNG: Maximalbetrag
willT = Standard wird verwendet
loadT = WARNUNG: Ladefracht
maxrT = WARNUNG: Maximales Zuruecksetzen
printY = WARNUNG: Druck bool
langT = WARNUNG: Sprachfehler

[it]
usbT = Modalita di configurazione USB
tapScreenT = TOCCA LO SCHERMO QUANDO FINITO
scanMeT = SCANSIONAMI TOCCA LO SCHERMO QUANDO FINITO
totalT = Totale:
fossaT = FOSSA! Bancomat Bitcoin
satsT = SATS
forT = PER
fiatT = FIAT!
feedT = dammelo in fiat
chargeT = % carica
printingT = Stampa in corso
waitT = attendere prego
workingT = Funzionamento...
thisVoucherT = Questo voucher puo essere riscattato per
ofBitcoinT = di Bitcoin
thankYouT = Grazie
scanMeClaimT = Scansionami con un portafoglio Lightning per ottenere il tuo Bitcoin
tooMuchFiatT = Troppo FIAT!
contactOwnerT = Per favore contatta il proprietario
failedT = FALLITO
unableT = impossibile leggere lnurl
maxaT = AVVERTENZA: importo massimo
willT = Verra utilizzato il valore predefinito
loadT = AVVERTENZA: carica di carico
maxrT = AVVERTENZA: ripristino massimo
printY = AVVERTENZA: stampa bool
langT = AVVERTENZA: errore di lingua

[pt]
usbT = Modo de configuracao USB
tapScreenT = TOQUE NA TELA QUANDO TERMINAR
scanMeT = ESCANEIE ME TOQUE NA TELA QUANDO TERMINAR
totalT = Total:
fossaT = FOSSA! Caixa eletronico Bitcoin
satsT = SATS
forT = PARA
fiatT = FIAT!
feedT = me de fiat
chargeT = % de carga
printingT = Imprimindo
waitT = por favor aguarde
workingT = Trabalhando...
thisVoucherT = Este voucher pode ser resgatado por
ofBitcoinT = de Bitcoin
thankYouT = Obrigado
scanMeClaimT = Escaneie me com uma carteira Lightning para obter seu Bitcoin
tooMuchFiatT = Muito FIAT!
contactOwnerT = Por favor entre em contato com o proprietario
failedT = FALHOU
unableT = incapaz de ler lnurl
maxaT = AVISO: valor maximo
willT = Usara o valor padrao
loadT = AVISO: carga de valor
maxrT = AVISO: redefinicao maxima
printY = AVISO: bool de impressao
langT = AVISO: falha no idioma

[pl]
usbT = Tryb konfiguracji USB
tapScreenT = DOTKNIJ EKRAN PO UKONCZENIU
scanMeT = SCANUJ MNIE DOTKNIJ EKRAN PO UKONCZENIU
totalT = Razem:
fossaT = FOSSA! Bankomat Bitcoin
satsT = SATS
forT = DLA
fiatT = FIAT!
feedT = daj mi fiat
chargeT = % ladunku
printingT = Drukowanie
waitT = prosze czekac
workingT = Pracuje...
thisVoucherT = Ten bon moze byc wymieniony na
ofBitcoinT = Bitcoin
thankYouT = Dziekuje
scanMeClaimT = Zeskanuj mnie portfelem Lightning aby otrzymac swoj Bitcoin
tooMuchFiatT = Za duzo FIAT!
contactOwnerT = Prosze skontaktowac sie z wlascicielem
failedT = NIEUDANE
unableT = nie mozna odczytac lnurl
maxaT = OSTRZEZENIE: maksymalna kwota
willT = Zostanie uzyta wartosc domyslna
loadT = OSTRZEZENIE: ladunek
maxrT = OSTRZEZENIE: maksymalne zresetowanie
printY = OSTRZEZENIE: bool drukowania
langT = OSTRZEZENIE: blad jezyka

[hu]
usbT = USB konfiguracios mod
tapScreenT = TAP IN EKRANRA HA VEGE
scanMeT = SZKENNELJ ENGEM TAP IN EKRANRA HA VEGE
totalT = Osszesen:
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = SZAMARA
fiatT = FIAT!
feedT = etess meg fiatot
chargeT = % toltes
printingT = Nyomtatas
waitT = kerlek varj
workingT = Munkalkodik...
thisVoucherT = Ez a voucher bevalthato
ofBitcoinT = Bitcoin ertekere
thankYouT = Koszonom
scanMeClaimT = Szkenneld meg egy Lightning tarcaval hogy megkapd a Bitcoinod
tooMuchFiatT = Tul sok FIAT!
contactOwnerT = Kerlek lepj kapcsolatba a tulajdonossal
failedT = HIBAS
unableT = nem sikerult beolvasni az lnurl
maxaT = FIGYELEM: max osszeg
willT = Alapertelmezett ertek lesz hasznalva
loadT = FIGYELEM: toltési arany
maxrT = FIGYELEM: max visszaallitas
printY = FIGYELEM: nyomtatas bool
langT = FIGYELEM: nyelvi hiba

[tr]
usbT = USB ayar modu
tapScreenT = BITTIGINDE EKRANA DOKUNUN
scanMeT = BENI TARAMAK BITTIGINDE EKRANA DOKUNUN
totalT = Toplam:
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = ICIN
fiatT = FIAT!
feedT = fiat ver
chargeT = % sarj
printingT = Yazdiriliyor
waitT = lutfen bekleyin
workingT = Calisiyor...
thisVoucherT = Bu fis sunun karsiliginda kullanilabilir
ofBitcoinT = Bitcoin
thankYouT = Tesekkur ederim
scanMeClaimT = Bitcoin almak icin beni bir Lightning cuzdaniyla tarayin
tooMuchFiatT = Cok fazla FIAT!
contactOwnerT = Lutfen sahibi ile iletisime gecin
failedT = BASARISIZ
unableT = lnurl okunamiyor
maxaT = UYARI: maksimum miktar
willT = Varsayilan kullanilacak
loadT = UYARI: yukleme sarji
maxrT = UYARI: maksimum sifirlama
printY = UYARI: yazdirma bool
langT = UYARI: dil hatasi

[ro]
usbT = Mod configurare USB
tapScreenT = ATINGE ECRANUL CAND GATA
scanMeT = SCANEAZA MA ATINGE ECRANUL CAND GATA
totalT = Total:
fossaT = FOSSA! ATM Bitcoin
satsT = SATS
forT = PENTRU
fiatT = FIAT!
feedT = hraneste-ma cu fiat
chargeT = % incarcare
printingT = Imprimare
waitT = te rog asteapta
workingT = Se lucreaza...
thisVoucherT = Acest voucher poate fi rascumparat pentru
ofBitcoinT = de Bitcoin
thankYouT = Multumesc
scanMeClaimT = Scaneaza-ma cu un portofel Lightning pentru a primi Bitcoin-ul tau
tooMuchFiatT = Prea mult FIAT!
contactOwnerT = Va rugam sa contactati proprietarul
failedT = ESUAT
unableT = incapabil sa citeasca lnurl
maxaT = AVERTISMENT: suma maxima
willT = Va folosi valoarea implicita
loadT = AVERTISMENT: incarcare tarifara
maxrT = AVERTISMENT: resetare maxima
printY = AVERTISMENT: bool imprimare
langT = AVERTISMENT: esec de limba

[fi]
usbT = USB-moodi
tapScreenT = KOSKETA NAYTTOA KUN VALMIS
scanMeT = SKANNAA MINUT KOSKETA NAYTTOA KUN VALMIS
totalT = Yhteensa:
fossaT = FOSSA! Bitcoin-automatti
satsT = SATS
forT = VASTAAN
fiatT = FIAT!
feedT = anna minulle fiat
chargeT = % lataus
printingT = Tulostus
waitT = ole hyva ja odota
workingT = Toiminnassa...
thisVoucherT = Tama kuponki voidaan lunastaa
ofBitcoinT = Bitcoinista
thankYouT = Kiitos
scanMeClaimT = Skannaa minut Lightning-lompakolla saadaksesi Bitcoinisi
tooMuchFiatT = Liikaa FIAT!
contactOwnerT = Ole hyva ja ota yhteytta omistajaan
failedT = EPAAONNISTUI
unableT = ei pysty lukemaan lnurl
maxaT = VAROITUS: enin maara
willT = Oletusarvo kaytossa
loadT = VAROITUS: latausmaksu
maxrT = VAROITUS: enin nollaus
printY = VAROITUS: tulosta bool
langT = VAROITUS: kielivirhe

[sv]
usbT = USB-konfigurationslage
tapScreenT = TRYCK PA SKARMEN NAR KLART
scanMeT = SKANNA MIG TRYCK PA SKARMEN NAR KLART
totalT = Totalt:
fossaT = FOSSA! Bitcoin-automat
satsT = SATS
forT = FOR
fiatT = FIAT!
feedT = mata mig med fiat
chargeT = % laddning
printingT = Skriver ut
waitT = var god vante
workingT = Arbetar...
thisVoucherT = Denna kupong kan losas in for
ofBitcoinT = av Bitcoin
thankYouT = Tack
scanMeClaimT = Skanna mig med en Lightning-plambok for att fa dina Bitcoin
tooMuchFiatT = For mycket FIAT!
contactOwnerT = Var god kontakta agaren
failedT = MISSLYCKADES
unableT = kan inte lasa lnurl
maxaT = VARNING: maxbelopp
willT = Standardvardet anvands
loadT = VARNING: laddningsavgift
maxrT = VARNING: max aterstallning
printY = VARNING: skriv ut bool
langT = VARNING: sprakfel
)";

  String line;
  bool inCorrectLanguage = false;
  int startPos = 0;
  int endPos;

  while (startPos < strlen(translations)) {
    endPos = startPos;
    while (translations[endPos] != '\n' && translations[endPos] != '\0') {
      endPos++;
    }
    line = String(translations).substring(startPos, endPos);
    line.trim();  // Trim line
    startPos = endPos + 1;

    if (line.length() == 0) {
      continue;
    }

    // Check for language section
    if (line.startsWith("[")) {
      inCorrectLanguage = (line == "[" + language + "]");
      continue;
    }

    if (inCorrectLanguage) {
      int separatorPos = line.indexOf('=');
      if (separatorPos != -1) {
        String currentKey = line.substring(0, separatorPos);
        currentKey.trim();  // Trim key separately

        String value = line.substring(separatorPos + 1);
        value.trim();  // Trim value separately

        if (currentKey == key) {
          return value;
        }
      }
    }
  }

  return key;  // Return the key if no translation is found
}

void translateAll(String language) {
  usbT = translate("usbT", language);
  tapScreenT = translate("tapScreenT", language);
  scanMeT = translate("scanMeT", language);
  totalT = translate("totalT", language);
  fossaT = translate("fossaT", language);
  satsT = translate("satsT", language);
  forT = translate("forT", language);
  fiatT = translate("fiatT", language);
  feedT = translate("feedT", language);
  chargeT = translate("chargeT", language);
  printingT = translate("printingT", language);
  waitT = translate("waitT", language);
  workingT = translate("workingT", language);
  thisVoucherT = translate("chargeT", language);
  ofBitcoinT = translate("printingT", language);
  thankYouT = translate("waitT", language);
  scanMeClaimT = translate("workingT", language);
  tooMuchFiatT = translate("tooMuchFiatT", language);
  contactOwnerT = translate("contactOwnerT", language);
  failedT = translate("failedT", language);
  unableT = translate("unableT", language);
  maxaT = translate("maxaT", language);
  willT = translate("willT", language);
  loadT = translate("loadT", language);
  maxrT = translate("maxrT", language);
  printY = translate("printY", language);
  langT = translate("langT", language);
}
