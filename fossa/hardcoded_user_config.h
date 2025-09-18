// If using hardcoded options 'cp fossa/hardcoded_user_config.h.example fossa/hardcoded_user_config.h',
// then change the values on fossa/hardcoded_user_config.h

#define HARDCODED false // true to use settings below

#define LANGUAGE "en" // Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv
#define CHARGE 5 // % You will charge people for service, set in LNbits extension
#define MAX_AMOUNT 30 // Max amount per withdraw
#define MAX_BEFORE_RESET 300 // Max amount you want to sell in the atm before having to reset power
#define DEVICE_STRING "https://XXXX.lnbits.com/fossa/api/v1/lnurl/XXXXX,XXXXXXXXXXXXXXXXXXXXXX,USD"
#define COIN_AMOUNTS "0.05,0.1,0.2,0.5,1,2"
#define BILL_AMOUNTS "5,10,20,50,100"
