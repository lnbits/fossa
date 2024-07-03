#include <cstdlib> // Add this line to include the appropriate header file

// define a list of quote Strings that can be used to print on the receipt
const char* quotes[13] = {
    "It's very attractive to the libertarian viewpoint if we can explain it properly. I'm better with code than with words though.\r\nSatoshi Nakamoto, Dec 14, 2008",
    "In a few decades when the reward gets too small, the transaction fee will become the main compensation for nodes.\r\nSatoshi Nakamoto, Feb 14, 2010",
    "I'm sure that in 20 years there will either be very large transaction volume or no volume.\r\nSatoshi Nakamoto, Feb 14, 2010",
    "Imagine if gold turned to lead when stolen. If the thief gives it back, it turns to gold again.\r\nSatoshi Nakamoto, Aug 11, 2010",
    "If you don't believe me or don't get it, I don't have time to try to convince you, sorry.\r\nSatoshi Nakamoto, Jul 29, 2010",
    "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks.",
    "It would have been nice to get this attention in any other context. WikiLeaks has kicked the hornet's nest, and the swarm is headed towards us.\r\nSatoshi Nakamoto, Dec 11, 2010",
    "Lost coins only make everyone else's coins worth slightly more. Think of it as a donation to everyone.\r\nSatoshi Nakamoto, Jul 21, 2010",
    "Sigh... why delete a wallet instead of moving it aside and keeping the old copy just in case?  You should never delete a wallet.\r\nSatoshi Nakamoto, October 3rd, 2010",
    "It's very attractive to the libertarian viewpoint if we can explain it properly. I'm better with code than with words though.\r\nSatoshi Nakamoto, Nov 14 2008",
    "It's time we had the same thing for money. With e-currency based on cryptographic proof, without the need to trust a third party middleman, money can be secure and transactions effortless.\r\nSatoshi Nakamoto, Jan 11 2009",
    "Sorry to be a wet blanket.  Writing a description for this thing for general audiences is bloody hard.  There's nothing to relate it to.\r\nSatoshi Nakamoto, 05 Jul 2010",
    "Yes, but we can win a major battle in the arms race and gain a new territory of freedom for several years.\r\nSatoshi Nakamoto, 6 Nov 2008"
};

//  function that returns a random quote from the list of quotes
const char* getRandomQuote() {
    return quotes[random(0, 13)];
}