
/* ******************************* c203.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c203 - Fronta znaků v poli                                          */
/*  Referenční implementace: Petr Přikryl, 1994                               */
/*  Přepis do jazyka C: Václav Topinka, září 2005                             */
/*  Úpravy: Kamil Jeřábek, září 2020                                          */
/* ************************************************************************** */
/*
** Implementujte frontu znaků v poli. Přesnou definici typů naleznete
** v hlavičkovém souboru c203.h (ADT fronta je reprezentována strukturou tQueue,
** která obsahuje pole 'arr' pro uložení hodnot ve frontě a indexy f_index
** a b_index. Všechny implementované funkce musí předpokládat velikost pole
** QUEUE_SIZE, i když ve skutečnosti jsou rozměry statického pole definovány
** MAX_QUEUE. Hodnota QUEUE_SIZE slouží k simulaci fronty v různě velkém poli
** a nastavuje se v testovacím skriptu c203-test.c před testováním
** implementovaných funkcí. Hodnota QUEUE_SIZE může nabývat hodnot v rozsahu
** 1 až MAX_QUEUE.
**
** Index f_index ukazuje vždy na první prvek ve frontě. Index b_index
** ukazuje na první volný prvek ve frontě. Pokud je fronta prázdná, ukazují
** oba indexy na stejné místo. Po inicializaci ukazují na první prvek pole,
** obsahují tedy hodnotu 0. Z uvedených pravidel vyplývá, že v poli je vždy
** minimálně jeden prvek nevyužitý.
**
** Při libovolné operaci se žádný z indexů (f_index i b_index) nesnižuje
** vyjma případu, kdy index přesáhne hranici QUEUE_SIZE. V tom případě
** se "posunuje" znovu na začátek pole. Za tímto účelem budete deklarovat
** pomocnou funkci NextIndex, která pro kruhový pohyb přes indexy pole
** využívá operaci "modulo".
**
** Implementujte následující funkce:
**
**    queueInit ..... inicializace fronty
**    nextIndex ..... pomocná funkce - viz popis výše
**    queueEmpty .... test na prázdnost fronty
**    queueFull ..... test, zda je fronta zaplněna (vyčerpána kapacita)
**    queueFront .... přečte hodnoty prvního prvku z fronty
**    queueRemove ... odstraní první prvek fronty
**    queueGet ...... přečte a odstraní první prvek fronty
**    queueUp ....... zařazení prvku na konec fronty
**
** Své řešení účelně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c203.h"

void queueError (int error_code) {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**
** TUTO FUNKCI, PROSÍME, NEUPRAVUJTE!
*/
	static const char* QERR_STRINGS[MAX_QERR+1] = {"Unknown error","Queue error: UP","Queue error: FRONT","Queue error: REMOVE","Queue error: GET","Queue error: INIT"};
	if ( error_code <= 0 || error_code > MAX_QERR )
		error_code = 0;
	printf ( "%s\n", QERR_STRINGS[error_code] );
	err_flag = 1;
}

void queueInit (tQueue* q) {
/*
** Inicializujte frontu následujícím způsobem:
** - všechny hodnoty v poli q->arr nastavte na '*',
** - index na začátek fronty nastavte na 0,
** - index prvního volného místa nastavte také na 0.
**
** V případě, že funkce dostane jako parametr q == NULL, volejte funkci
** queueError(QERR_INIT).
*/
    
    /*
     * Forcyklus nastaví podle velikosti QUEUE_SIZE počet `*`.
     * Dále nastavíme indexy na 0.
     **/
    
    if(q == NULL){
        queueError(QERR_INIT);
    }else{
        for(int i = QUEUE_SIZE; i > 0; i --){
            q->arr[i-1] = '*';
        }
        q->f_index = 0;
        q->b_index = 0;
    }

	  //solved = FALSE;                  /* V případě řešení, smažte tento řádek! */
}

int nextIndex (int index) {
/*
** Pomocná funkce, která vrací index následujícího prvku v poli.
** Funkci implementujte jako jediný prikaz využívající operace '%'.
** Funkci nextIndex budete využívat v dalších implementovaných funkcích.
*/

    /*
     * Pomocí operace modulo vrátíme index následujícího prvku.
     **/
    return (index + 1) % QUEUE_SIZE;
    
	  //solved = FALSE;                  /* V případě řešení, smažte tento řádek! */

}

int queueEmpty (const tQueue* q) {
/*
** Vrací nenulovou hodnotu, pokud je frona prázdná, jinak vrací hodnotu 0. 
** Funkci je vhodné implementovat jedním příkazem return.
*/

    /*
     * Pokud je splněna rovnost (fronta je prázdná), vrací TRUE == 1, jinak FALSE == 0.
     **/
    return q->b_index == q->f_index;
	  //solved = FALSE;                  /* V případě řešení, smažte tento řádek! */
}

int queueFull (const tQueue* q) {
/*
** Vrací nenulovou hodnotu, je-li fronta plná, jinak vrací hodnotu 0. 
** Funkci je vhodné implementovat jedním příkazem return
** s využitím pomocné funkce nextIndex.
*/

    /*
     * Pokud se následující index b_index rovná f_index, tak jsme na posledním
     * prvku a funkce vrací TRUE == 1, jinak FALSE == 0.
     **/
    return nextIndex(q->b_index) == q->f_index;
	  //solved = FALSE;                  /* V případě řešení, smažte tento řádek! */
}

void queueFront (const tQueue* q, char* c) {
/*
** Prostřednictvím parametru c vrátí znak ze začátku fronty q.
** Pokud je fronta prázdná, ošetřete to voláním funkce queueError(QERR_FRONT).
** Volání této funkce při prázdné frontě je vždy nutné považovat za nekorektní.
** Bývá to totiž důsledek špatného návrhu algoritmu, ve kterém je fronta
** použita. O takové situaci se proto musí programátor-vývojář dozvědět.
** V opačném případě je ladění programů obtížnější!
**
** Při implementaci využijte dříve definované funkce queueEmpty.
*/
    if(queueEmpty(q)){
        queueError(QERR_FRONT);
    }else{
        *c = q->arr[q->f_index];
    }
    
    
	  //solved = FALSE;                  /* V případě řešení, smažte tento řádek! */
}

void queueRemove (tQueue* q) {
/*
** Odstraní znak ze začátku fronty q. Pokud je fronta prázdná, ošetřete
** vzniklou chybu voláním funkce queueError(QERR_REMOVE).
** Hodnotu na uvolněné pozici ve frontě nijak neošetřujte (nepřepisujte).
** Při implementaci využijte dříve definované funkce queueEmpty a nextIndex.
*/
    /*
     * Posunume index prvního prvku fronty, čímž uvolníme tento prvek pro použití.
     * Znam sice zůstane, ale nepočítáme s ním. Znak nebude přečten a může být přepsán,
     * jinak řečeno jej ignorujeme, tento prvek bereme jako prázdný.
     **/
    if(!queueEmpty(q)){
        q->f_index = nextIndex(q->f_index);
    }else{
        queueError(QERR_REMOVE);
    }
    
	  //solved = FALSE;                  /* V případě řešení, smažte tento řádek! */
}

void queueGet (tQueue* q, char* c) {
/*
** Odstraní znak ze začátku fronty a vrátí ho prostřednictvím parametru c.
** Pokud je fronta prázdná, ošetřete to voláním funkce queueError(QERR_GET).
**
** Při implementaci využijte dříve definovaných funkcí queueEmpty,
** queueFront a queueRemove.
*/

    if(!queueEmpty(q)){
        queueFront(q, c);
        queueRemove(q);
    }else{
        queueError(QERR_GET);
    }
	  //solved = FALSE;                  /* V případě řešení, smažte tento řádek! */
}

void queueUp (tQueue* q, char c) {
/*
** Vloží znak c do fronty. Pokud je fronta plná, ošetřete chybu voláním
** funkce queueError(QERR_UP). Vkládání do plné fronty se považuje za
** nekorektní operaci. Situace by mohla být řešena i tak, že by operace
** neprováděla nic, ale v případě použití takto definované abstrakce by se
** obtížně odhalovaly chyby v algoritmech, které by abstrakci využívaly.
**
** Při implementaci využijte dříve definovaných funkcí queueFull a nextIndex.
*/
    /*
     * Vložíme znak do volného prvku a posuneme ukazatel na volný prvek na následující prvek.
     **/
    if(queueFull(q) == 0){
        q->arr[q->b_index] = c;
        q->b_index = nextIndex(q->b_index);
        
    }else{
        queueError(QERR_UP);
    }
    
	  //solved = FALSE;                  /* V případě řešení, smažte tento řádek! */
}
/* Konec příkladu c203.c */
