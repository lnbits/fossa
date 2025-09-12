// Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv, nl
String translate(String key, String language)
{
  const char *translations = R"(
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
maxaT = Max amount
willT = Using default
loadT = WARNING: load charge
maxrT = WARNING: max reset
printY = WARNING: print bool
langT = WARNING: lang fail

[es]
usbT = Modo de configuracion USB
tapScreenT = TOQUE LA PANTALLA CUANDO TERMINE
scanMeT = ESCANEME Y TOQUE LA PANTALLA CUANDO TERMINE
totalT = Total: 
fossaT = FOSSA! Cajero Bitcoin
satsT = SATS
forT = PARA
fiatT = FIAT!
feedT = alimentame con fiat.
chargeT = % carga
printingT = Imprimiendo
waitT = por favor espere
workingT = Trabajando...
thisVoucherT = Este vale se puede canjear por
ofBitcoinT = de Bitcoin
thankYouT = Gracias
scanMeClaimT = Escaneame con una billetera Lightning para obtener tu Bitcoin
tooMuchFiatT = Demasiado FIAT!
contactOwnerT = Por favor contacte al propietario
failedT = FALLIDO
unableT = no se puede leer lnurl
maxaT = ADVERTENCIA: cantidad maxima
willT = Usando predeterminado
loadT = ADVERTENCIA: carga
maxrT = ADVERTENCIA: reinicio maximo
printY = ADVERTENCIA: impresion bool
langT = ADVERTENCIA: fallo de idioma

[fr]
usbT = Mode config USB
tapScreenT = TOUCHEZ L ECRAN QUAND TERMINE
scanMeT = SCANNEZ MOI ET TOUCHEZ L ECRAN QUAND TERMINE
totalT = Total: 
fossaT = FOSSA! Distributeur Bitcoin
satsT = SATS
forT = POUR
fiatT = FIAT!
feedT = nourrissez moi en fiat.
chargeT = % charge
printingT = Impression
waitT = veuillez patienter
workingT = En cours...
thisVoucherT = Ce bon peut etre echange contre
ofBitcoinT = de Bitcoin
thankYouT = Merci
scanMeClaimT = Scannez moi avec un portefeuille Lightning pour obtenir votre Bitcoin
tooMuchFiatT = Trop de FIAT!
contactOwnerT = Contactez le proprietaire
failedT = ECHOUE
unableT = impossible de lire lnurl
maxaT = AVERTISSEMENT: montant maximal
willT = Utilise par defaut
loadT = AVERTISSEMENT: charge
maxrT = AVERTISSEMENT: reset max
printY = AVERTISSEMENT: impression bool
langT = AVERTISSEMENT: erreur langue

[de]
usbT = USB Konfig Modus
tapScreenT = BERUEHREN SIE DEN BILDSCHIRM WENN FERTIG
scanMeT = SCANNEN SIE MICH UND BERUEHREN SIE DEN BILDSCHIRM WENN FERTIG
totalT = Gesamt: 
fossaT = FOSSA! Bitcoin Automat
satsT = SATS
forT = FUER
fiatT = FIAT!
feedT = fuettere mich mit fiat.
chargeT = % ladung
printingT = Drucken
waitT = bitte warten
workingT = Arbeitet...
thisVoucherT = Gutschein einloesbar fuer
ofBitcoinT = von Bitcoin
thankYouT = Danke
scanMeClaimT = Scannen Sie mich mit einem Lightning Wallet um Bitcoin zu erhalten
tooMuchFiatT = Zu viel FIAT!
contactOwnerT = Bitte Besitzer kontaktieren
failedT = FEHLGESCHLAGEN
unableT = lnurl konnte nicht gelesen werden
maxaT = WARNUNG: Max betrag
willT = Standard wird benutzt
loadT = WARNUNG: ladung
maxrT = WARNUNG: reset max
printY = WARNUNG: druck bool
langT = WARNUNG: sprachfehler

[it]
usbT = Modalita config USB
tapScreenT = TOCCA SCHERMO QUANDO FINITO
scanMeT = SCANSIONAMI E TOCCA SCHERMO QUANDO FINITO
totalT = Totale: 
fossaT = FOSSA! Bancomat Bitcoin
satsT = SATS
forT = PER
fiatT = FIAT!
feedT = dammi fiat.
chargeT = % carica
printingT = Stampa
waitT = attendere
workingT = Lavorando...
thisVoucherT = Questo voucher riscattabile per
ofBitcoinT = di Bitcoin
thankYouT = Grazie
scanMeClaimT = Scansionami con portafoglio Lightning per avere Bitcoin
tooMuchFiatT = Troppo FIAT!
contactOwnerT = Contatta il proprietario
failedT = FALLITO
unableT = impossibile leggere lnurl
maxaT = AVVISO: importo massimo
willT = Usa valore predefinito
loadT = AVVISO: carico
maxrT = AVVISO: reset max
printY = AVVISO: stampa bool
langT = AVVISO: errore lingua

[pt]
usbT = Modo config USB
tapScreenT = TOQUE NA TELA QUANDO TERMINAR
scanMeT = ESCANEIE ME E TOQUE NA TELA QUANDO TERMINAR
totalT = Total: 
fossaT = FOSSA! Caixa Bitcoin
satsT = SATS
forT = PARA
fiatT = FIAT!
feedT = me de fiat.
chargeT = % carga
printingT = Imprimindo
waitT = por favor aguarde
workingT = Trabalhando...
thisVoucherT = Voucher resgatavel por
ofBitcoinT = de Bitcoin
thankYouT = Obrigado
scanMeClaimT = Escaneie com carteira Lightning para receber Bitcoin
tooMuchFiatT = Muito FIAT!
contactOwnerT = Contate o proprietario
failedT = FALHOU
unableT = nao consegue ler lnurl
maxaT = AVISO: valor maximo
willT = Usa padrao
loadT = AVISO: carga
maxrT = AVISO: reset max
printY = AVISO: impressao bool
langT = AVISO: erro idioma

[pl]
usbT = Tryb konfiguracji USB
tapScreenT = DOTKNIJ EKRAN KIEDY GOTOWE
scanMeT = ZESKANUJ MNIE I DOTKNIJ EKRAN KIEDY GOTOWE
totalT = Razem: 
fossaT = FOSSA! Bankomat Bitcoin
satsT = SATS
forT = DLA
fiatT = FIAT!
feedT = daj mi fiat.
chargeT = % ladunek
printingT = Drukowanie
waitT = prosze czekac
workingT = Pracuje...
thisVoucherT = Bon do wymiany na
ofBitcoinT = Bitcoin
thankYouT = Dziekuje
scanMeClaimT = Zeskanuj mnie portfelem Lightning aby dostac Bitcoin
tooMuchFiatT = Za duzo FIAT!
contactOwnerT = Skontaktuj sie z wlascicielem
failedT = NIEUDANE
unableT = nie mozna odczytac lnurl
maxaT = OSTRZEZENIE: max kwota
willT = Uzywa domyslnej
loadT = OSTRZEZENIE: ladunek
maxrT = OSTRZEZENIE: max reset
printY = OSTRZEZENIE: druk bool
langT = OSTRZEZENIE: blad jezyka

[hu]
usbT = USB konfiguracio mod
tapScreenT = ERINTSD A KEPRNYOT HA KESZ
scanMeT = SZKENNELJ ENGEM ES ERINTSD A KEPRNYOT HA KESZ
totalT = Osszesen: 
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = SZAMARA
fiatT = FIAT!
feedT = etess meg fiattal.
chargeT = % toltes
printingT = Nyomtatas
waitT = kerlek varj
workingT = Munkal...
thisVoucherT = Ez a voucher bevalthato
ofBitcoinT = Bitcoin ertekere
thankYouT = Koszonom
scanMeClaimT = Szkenneld meg Lightning tarcaval hogy megkapd Bitcoin
tooMuchFiatT = Tul sok FIAT!
contactOwnerT = Lelj kapcsolatba tulajdonossal
failedT = HIBAS
unableT = nem olvashato lnurl
maxaT = FIGYELEM: max osszeg
willT = Alapertelmezett hasznalva
loadT = FIGYELEM: toltes
maxrT = FIGYELEM: max reset
printY = FIGYELEM: nyomtatas bool
langT = FIGYELEM: nyelvi hiba

[tr]
usbT = USB ayar modu
tapScreenT = BITTIGINDE EKRANA DOKUN
scanMeT = BENI TARA VE BITTIGINDE EKRANA DOKUN
totalT = Toplam: 
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = ICIN
fiatT = FIAT!
feedT = fiat ver.
chargeT = % sarj
printingT = Yazdiriliyor
waitT = lutfen bekle
workingT = Calisiyor...
thisVoucherT = Bu fis karsiliginda kullanilabilir
ofBitcoinT = Bitcoin
thankYouT = Tesekkurler
scanMeClaimT = Bitcoin almak icin beni Lightning cuzdaniyla tarayin
tooMuchFiatT = Cok fazla FIAT!
contactOwnerT = Lutfen sahibi ile iletisime gecin
failedT = BASARISIZ
unableT = lnurl okunamiyor
maxaT = UYARI: max miktar
willT = Varsayilan kullanilacak
loadT = UYARI: yukleme
maxrT = UYARI: max sifirlama
printY = UYARI: yazdirma bool
langT = UYARI: dil hatasi

[ro]
usbT = Mod config USB
tapScreenT = ATINGE ECRANUL CAND TERMINAT
scanMeT = SCANEAZA MA SI ATINGE ECRANUL CAND TERMINAT
totalT = Total: 
fossaT = FOSSA! ATM Bitcoin
satsT = SATS
forT = PENTRU
fiatT = FIAT!
feedT = hraneste ma cu fiat.
chargeT = % incarcare
printingT = Imprimare
waitT = asteapta
workingT = Se lucreaza...
thisVoucherT = Voucher rascumparabil pentru
ofBitcoinT = de Bitcoin
thankYouT = Multumesc
scanMeClaimT = Scaneaza ma cu portofel Lightning pentru Bitcoin
tooMuchFiatT = Prea mult FIAT!
contactOwnerT = Contacteaza proprietarul
failedT = ESUAT
unableT = nu se poate citi lnurl
maxaT = AVERTISMENT: suma maxima
willT = Foloseste implicit
loadT = AVERTISMENT: incarcare
maxrT = AVERTISMENT: reset max
printY = AVERTISMENT: imprimare bool
langT = AVERTISMENT: eroare limba

[fi]
usbT = USB moodi
tapScreenT = KOSKETA NAYTTOA KUN VALMIS
scanMeT = SKANNAA MINUT JA KOSKETA NAYTTOA KUN VALMIS
totalT = Yhteensa: 
fossaT = FOSSA! Bitcoin automaatti
satsT = SATS
forT = VASTAAN
fiatT = FIAT!
feedT = anna minulle fiat.
chargeT = % lataus
printingT = Tulostus
waitT = odota
workingT = Toiminnassa...
thisVoucherT = Kuponki lunastettavissa
ofBitcoinT = Bitcoinista
thankYouT = Kiitos
scanMeClaimT = Skannaa minut Lightning lompakolla saadaksesi Bitcoin
tooMuchFiatT = Liikaa FIAT!
contactOwnerT = Ota yhteytta omistajaan
failedT = EPAAONNISTUI
unableT = ei voi lukea lnurl
maxaT = VAROITUS: max maara
willT = Oletus kaytossa
loadT = VAROITUS: lataus
maxrT = VAROITUS: reset max
printY = VAROITUS: tulostus bool
langT = VAROITUS: kielivirhe

[sv]
usbT = USB konfig lage
tapScreenT = TRYCK PA SKARMEN NAR KLART
scanMeT = SKANNA MIG OCH TRYCK PA SKARMEN NAR KLART
totalT = Totalt: 
fossaT = FOSSA! Bitcoin automat
satsT = SATS
forT = FOR
fiatT = FIAT!
feedT = mata mig med fiat.
chargeT = % laddning
printingT = Skriver ut
waitT = vanligen vantar
workingT = Arbetar...
thisVoucherT = Kupong loses in for
ofBitcoinT = av Bitcoin
thankYouT = Tack
scanMeClaimT = Skanna mig med Lightning planbok for att fa Bitcoin
tooMuchFiatT = For mycket FIAT!
contactOwnerT = Kontakta agaren
failedT = MISSLYCKADES
unableT = kan inte lasa lnurl
maxaT = VARNING: max belopp
willT = Standard anvands
loadT = VARNING: laddning
maxrT = VARNING: max aterstallning
printY = VARNING: skriv bool
langT = VARNING: sprak fel

[nl]
usbT = USB config modus
tapScreenT = TIK SCHERM WANNEER KLAAR
scanMeT = SCAN MIJ EN TIK SCHERM WANNEER KLAAR
totalT = Totaal: 
fossaT = FOSSA! Bitcoin ATM
satsT = SATS
forT = VOOR
fiatT = FIAT!
feedT = voer mij fiat.
chargeT = % lading
printingT = Afdrukken
waitT = even wachten
workingT = Bezig...
thisVoucherT = Voucher inwisselen voor
ofBitcoinT = in Bitcoin
thankYouT = Bedankt
scanMeClaimT = Scan met Lightning wallet om Bitcoin te krijgen
tooMuchFiatT = Te veel FIAT!
contactOwnerT = Contacteer eigenaar
failedT = MISLUKT
unableT = kan lnurl niet lezen
maxaT = WAARSCHUWING: max bedrag
willT = Standaard gebruikt
loadT = WAARSCHUWING: lading
maxrT = WAARSCHUWING: max reset
printY = WAARSCHUWING: print bool
langT = WAARSCHUWING: taal fout
)";

  String line;
  bool inCorrectLanguage = false;
  int startPos = 0;
  int endPos;

  while (startPos < strlen(translations))
  {
    endPos = startPos;
    while (translations[endPos] != '\n' && translations[endPos] != '\0')
    {
      endPos++;
    }
    line = String(translations).substring(startPos, endPos);
    line.trim(); // Trim line
    startPos = endPos + 1;

    if (line.length() == 0)
    {
      continue;
    }

    // Check for language section
    if (line.startsWith("["))
    {
      inCorrectLanguage = (line == "[" + language + "]");
      continue;
    }

    if (inCorrectLanguage)
    {
      int separatorPos = line.indexOf('=');
      if (separatorPos != -1)
      {
        String currentKey = line.substring(0, separatorPos);
        currentKey.trim(); // Trim key separately

        String value = line.substring(separatorPos + 1);
        value.trim(); // Trim value separately

        if (currentKey == key)
        {
          return value;
        }
      }
    }
  }

  return key; // Return the key if no translation is found
}

void translateAll(String language)
{
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
