
/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                              Úpravy: Kamil Jeřábek, září 2020
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      DisposeList ... zrušení všech prvků seznamu,
**      InitList ...... inicializace seznamu před prvním použitím,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam předá
** někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int errflg;
int solved;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	
    /*
     * Vytvoříme prázdný list, ukazatele tedy ukazují na NULL.
     **/
    
    L->Act = NULL;
    L->First = NULL;
    

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DisposeList (tList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/
	
    
    /*
     * Zrušíme aktivní prvek.
     * Uložíme si adresu prvního prvku.
     * Následující prvek nastavíme jako první.
     * Uvolníme uložený prvek.
     * Opakujeme, dokud není seznam prázdný (First == NULL)
     **/
    
    L->Act = NULL;
    tElemPtr item = L->First;
    while(item != NULL){
        L->First = L->First->ptr;
        free(item);
        item = L->First;
    }
    //L->First = NULL;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void InsertFirst (tList *L, int val) {
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
    
    /*
     * Alokujeme novou položku item.
     * Zkontrolujeme, zda-li se alokovala, pokud ne, zavoláme funkci Error(),
     * pokud ano, přiřadíme obdržená data do položky.
     * Dále se podíváme, zda-li je seznam prázdný.
     * Pokud se jedná o prázdná seznam, nastavíme ukazatel položky na NULL
     * (položka je první a zároveň poslední) a položku přidělíme na první místo.
     * V opačném případě nastavíme ukazatel položky na položku, jenž je na prvním místě
     * a přidělíme novou položku na první místo.
     **/
    
    
    tElemPtr item = NULL;
    
    item =  malloc(sizeof(struct tElem));
    
    //tElem item = (tElemPtr *)malloc(sizeof(tElemPtr));
    if(item == NULL){
        Error();
    }else{
        item->data = val;
        
        
        if(L->First == NULL){
            item->ptr = NULL;
            L->First = item;
        }else{
            item->ptr = L->First;
            L->First = item;
        }
    }
    
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	
    /*
     * Nastavíme aktivní prvek na první položku.
     **/
    L->Act = L->First;
    

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void CopyFirst (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
	
    /*
     * Pokud seznam obsahuje alespoň jednu položku, tak uložíme její hodnotu (prvního prvku)
     do *val.
     **/
    
    if(L->First != NULL){
        *val = L->First->data;
    }else{
        Error();
    }

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DeleteFirst (tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
    
    /*
     * Zkontroluje, jestli není seznam prázdný.
     * Zkontroluje, zda-li není první prvek aktivním prvkem, pokud ano, zruší aktivitu.
     * První prvek uložíme do item, jako první prvek nastavíme následující prvek
     * a prvek item uvolníme.
     **/
	
    if(L->First != NULL){
        
        if(L->First == L->Act){
            L->Act = NULL;
        }
        
        tElemPtr item = L->First;
        L->First = L->First->ptr;
        free(item);
        
    }

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}	

void PostDelete (tList *L) {
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/
    
    /*
     * Zkontrolujeme, že existuje aktivní prvek.
     * Zkontrolujeme, že existuje následovník pro aktivní prvek.
     * Uložíme následovníka aktivního prvku do pomocné item,
     * a jako nového následovníka nastavíme prvek následující za prvkem,
     * který chceme uvolnit.
     * Uvolníme prvek item.
     **/
    
    if(L->Act != NULL){
        if(L->Act->ptr != NULL){
            tElemPtr item = L->Act->ptr;
            L->Act->ptr = L->Act->ptr->ptr;
            free(item);
        }
    }
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void PostInsert (tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
    
    /*
     * Zkontrolujeme, že máme aktivní prvek.
     * Alokujeme prostor pro nový prvek, pokud se alokace nepovedla, zavoláme funkci Error().
     * Nově vzniklému prvku nastavíme obdržená data z parametru funkce.
     * Dále mu nastavíme ukazatel na prvek, jenž následuje za aktivním prvekem.
     * Nastavíme ukaztel aktivního prvku na prvek item.
     **/
    
    if(L->Act != NULL){
     
         tElemPtr item = NULL;
     
         item =  malloc(sizeof(struct tElem));
        
        if(item == NULL){
            Error();
        }else{
            item->data = val;
            item->ptr = L->Act->ptr;
            L->Act->ptr = item;
        }
    }
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Copy (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
    
    /*
     * Zkontroluje, zdali je aktivní prvek, pokud ne, volá funkci Error().
     * Nastaví do proměnné *val, obdržené v parametru, hodnotu aktivního prvku.
     **/
    
    if(L->Act != NULL){
        *val = L->Act->data;
    }else{
        Error();
    }
	
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Actualize (tList *L, int val) {
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/
    
    /*
     * Zkontroluji zda-li je seznam aktivní, pokud ano, změním aktivnímu prvku hodnotu.
     **/
    
    if(L->Act != NULL){
        L->Act->data = val;
    }
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
    
    /*
     * Zkontroluji zda-li je seznam aktivní, pokud ano, posunu aktivní prvek
     **/

    if(L->Act != NULL){
        L->Act = L->Act->ptr;
    }
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int Active (tList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
    
    return L->Act != NULL;
	
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

/* Konec c201.c */
