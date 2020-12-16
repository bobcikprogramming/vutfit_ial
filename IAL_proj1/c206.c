
/* c206.c **********************************************************}
 {* Téma: Dvousměrně vázaný lineární seznam
 **
 **                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
 **                            Přepracované do jazyka C: Martin Tuček, říjen 2004
 **                                            Úpravy: Kamil Jeřábek, září 2020
 **
 ** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
 ** Užitečným obsahem prvku seznamu je hodnota typu int.
 ** Seznam bude jako datová abstrakce reprezentován proměnnou
 ** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
 ** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
 ** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
 **
 ** Vaším úkolem je implementovat následující operace, které spolu
 ** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
 ** obousměrně vázaný lineární seznam:
 **
 **      DLInitList ...... inicializace seznamu před prvním použitím,
 **      DLDisposeList ... zrušení všech prvků seznamu,
 **      DLInsertFirst ... vložení prvku na začátek seznamu,
 **      DLInsertLast .... vložení prvku na konec seznamu,
 **      DLFirst ......... nastavení aktivity na první prvek,
 **      DLLast .......... nastavení aktivity na poslední prvek,
 **      DLCopyFirst ..... vrací hodnotu prvního prvku,
 **      DLCopyLast ...... vrací hodnotu posledního prvku,
 **      DLDeleteFirst ... zruší první prvek seznamu,
 **      DLDeleteLast .... zruší poslední prvek seznamu,
 **      DLPostDelete .... ruší prvek za aktivním prvkem,
 **      DLPreDelete ..... ruší prvek před aktivním prvkem,
 **      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
 **      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
 **      DLCopy .......... vrací hodnotu aktivního prvku,
 **      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
 **      DLPred .......... posune aktivitu na předchozí prvek seznamu,
 **      DLSucc .......... posune aktivitu na další prvek seznamu,
 **      DLActive ........ zjišťuje aktivitu seznamu.
 **
 ** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
 ** implementovaných v rámci tohoto příkladu, není-li u funkce
 ** explicitně uvedeno něco jiného.
 **
 ** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
 ** předá někdo jako parametr hodnotu NULL.
 **
 ** Svou implementaci vhodně komentujte!
 **
 ** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
 ** Proto zde používáme pojem funkce i pro operace, které by byly
 ** v algoritmickém jazyce Pascalovského typu implemenovány jako
 ** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
 **/

#include "c206.h"

int solved;
int errflg;

void DLError() {
    /*
     ** Vytiskne upozornění na to, že došlo k chybě.
     ** Tato funkce bude volána z některých dále implementovaných operací.
     **/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
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
    
    L->First = NULL;
    L->Last = NULL;
    L->Act = NULL;
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDisposeList (tDLList *L) {
    /*
     ** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
     ** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
     ** uvolněny voláním operace free.
     **/
    
    /*
     * Uložíme si adresu prvního prvku.
     * Následující prvek nastavíme jako první.
     * Uvolníme uložený prvek.
     * Opakujeme, dokud není seznam prázdný (First == NULL)
     * Zrušíme aktivní prvek.
     * Ukazatel L->Last nastavíme na NULL.
     **/
    
    tDLElemPtr item = L->First;
    while(item != NULL){
        L->First = L->First->rptr;
        free(item);
        item = L->First;
    }
    //L->First = NULL;
    L->Act = NULL;
    L->Last = NULL;
    
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertFirst (tDLList *L, int val) {
    /*
     ** Vloží nový prvek na začátek seznamu L.
     ** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
     ** volá funkci DLError().
     **/
    
    /*
     * Alokujeme novou položku item.
     * Zkontrolujeme, zda-li se alokovala, pokud ne, zavoláme funkci Error(),
     * pokud ano, přiřadíme obdržená data do položky.
     * Dále se podíváme, zda-li je seznam prázdný.
     * Pokud se jedná o prázdná seznam, nastavíme ukazatel L->First a L->Last na novou položku
     * (položka je první a zároveň poslední) a položku přidělíme na první místo.
     * V opačném případě nastavíme ukazatel položky na položku, jenž je na prvním místě,
     * dále z dosavadní první položky nastavíme ukazatel doleva na novou položku
     * a přidělíme novou položku na první místo.
     **/
    
    tDLElemPtr item = NULL;
    
    item =  malloc(sizeof(struct tDLElem));
    
    if(item == NULL){
        DLError();
    }else{
        item->data = val;
        item->rptr = NULL;
        item->lptr = NULL;
        
        if(L->First == NULL){
            L->Last = item;
            L->First = item;
        }else{
            item->rptr = L->First;
            L->First->lptr = item;
            L->First = item;
        }
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertLast(tDLList *L, int val) {
    /*
     ** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
     ** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
     ** volá funkci DLError().
     **/
    
    /*
     * Alokujeme novou položku item.
     * Zkontrolujeme, zda-li se alokovala, pokud ne, zavoláme funkci Error(),
     * pokud ano, přiřadíme obdržená data do položky.
     * Dále se podíváme, zda-li je seznam prázdný.
     * Pokud se jedná o prázdná seznam, nastavíme ukazatel L->First a L->Last na novou položku
     * (položka je první a zároveň poslední) a položku přidělíme na první místo.
     * V opačném případě nastavíme ukazatel (doleva) položky na položku, jenž je na posledním místě,
     * dále z dosavadní poslední položky nastavíme ukazatel doprava na novou položku
     * a přidělíme novou položku na poslední místo.
     **/
    
    tDLElemPtr item = NULL;
    
    item =  malloc(sizeof(struct tDLElem));
    
    if(item == NULL){
        DLError();
    }else{
        item->data = val;
        item->rptr = NULL;
        item->lptr = NULL;
        
        if(L->First == NULL){
            L->Last = item;
            L->First = item;
        }else{
            item->lptr = L->Last;
            L->Last->rptr = item;
            L->Last = item;
        }
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLFirst (tDLList *L) {
    /*
     ** Nastaví aktivitu na první prvek seznamu L.
     ** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
     ** aniž byste testovali, zda je seznam L prázdný.
     **/
    
    L->Act = L->First;
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLLast (tDLList *L) {
    /*
     ** Nastaví aktivitu na poslední prvek seznamu L.
     ** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
     ** aniž byste testovali, zda je seznam L prázdný.
     **/
    
    L->Act = L->Last;
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyFirst (tDLList *L, int *val) {
    /*
     ** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
     ** Pokud je seznam L prázdný, volá funkci DLError().
     **/
    
    /*
     * Pokud seznam obsahuje alespoň jednu položku, tak uložíme její hodnotu (prvního prvku)
     do *val.
     **/
    
    if(L->First != NULL){
        *val = L->First->data;
    }else{
        DLError();
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyLast (tDLList *L, int *val) {
    /*
     ** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
     ** Pokud je seznam L prázdný, volá funkci DLError().
     **/
    
    /*
     * Pokud seznam obsahuje alespoň jednu položku, tak uložíme její hodnotu (posledního prvku)
     do *val.
     **/
    
    if(L->First != NULL){
        *val = L->Last->data;
    }else{
        DLError();
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDeleteFirst (tDLList *L) {
    /*
     ** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
     ** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
     **/
    
    /*
     * Zkontroluje, jestli není seznam prázdný.
     * Zkontroluje, zda-li není první prvek aktivním prvkem, pokud ano, zruší aktivitu.
     * První prvek uložíme do item, jako první prvek nastavíme následující prvek,
     * nastavíme mu ukazatel doleva na NULL a prvek item uvolníme.
     **/
    
    if(L->First != NULL){
        
        if(L->First == L->Act){
            L->Act = NULL;
        }
        
        tDLElemPtr item = L->First;
        if(L->First == L->Last){
            L->First = NULL;
            L->Last = NULL;
        }else{
            L->First = L->First->rptr;
            L->First->lptr = NULL;
        }
        
        free(item);
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDeleteLast (tDLList *L) {
    /*
     ** Zruší poslední prvek seznamu L.
     ** Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
     ** Pokud byl seznam L prázdný, nic se neděje.
     **/
    
    /*
     * Zkontroluje, jestli není seznam prázdný.
     * Zkontroluje, zda-li není poslední prvek aktivním prvkem, pokud ano, zruší aktivitu.
     * Poslední prvek uložíme do item, jako poslední prvek nastavíme předcházející prvek,
     * nastavíme mu ukazatel doprava na NULL a prvek item uvolníme.
     **/
    
    if(L->First != NULL){
        
        if(L->Last == L->Act){
            L->Act = NULL;
        }
        
        tDLElemPtr item = L->Last;
        if(L->First == L->Last){
            L->First = NULL;
            L->Last = NULL;
        }else{
            L->Last = L->Last->lptr;
            L->Last->rptr = NULL;
        }
        
        free(item);
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostDelete (tDLList *L) {
    /*
     ** Zruší prvek seznamu L za aktivním prvkem.
     ** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
     ** posledním prvkem seznamu, nic se neděje.
     **/
    
    /*
     * Zkontrolujeme, že existuje aktivní prvek.
     * Zkontrolujeme, že že se nejedná o poslední prvek.
     * Uložíme následovníka aktivního prvku do pomocné item,
     * a jako nového následovníka nastavíme prvek následující za prvkem,
     * který chceme uvolnit.
     * Uvolníme prvek item.
     **/
    
    if(L->Act != NULL){
        if(L->Act != L->Last){
            tDLElemPtr item = L->Act->rptr;
            if(item == L->Last){
                L->Act->rptr = NULL;
                L->Last = L->Act;
            }else{
                L->Act->rptr->rptr->lptr = L->Act;
                L->Act->rptr = L->Act->rptr->rptr;
            }
            free(item);
        }
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreDelete (tDLList *L) {
    /*
     ** Zruší prvek před aktivním prvkem seznamu L .
     ** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
     ** prvním prvkem seznamu, nic se neděje.
     **/
    
    /*
     * Zkontrolujeme, že existuje aktivní prvek.
     * Zkontrolujeme, že se nejedná o první prvek.
     * Uložíme předchůdce aktivního prvku do pomocné item,
     * a jako nového předchůdce nastavíme prvek předcházející před prvkem,
     * který chceme uvolnit.
     * Uvolníme prvek item.
     **/
    
    if(L->Act != NULL){
        if(L->Act != L->First){
            tDLElemPtr item = L->Act->lptr;
            if(item == L->First){
                L->Act->lptr = NULL;
                L->First = L->Act;
            }else{
                L->Act->lptr->lptr->rptr = L->Act;
                L->Act->lptr = L->Act->lptr->lptr;
            }
            free(item);
        }
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostInsert (tDLList *L, int val) {
    /*
     ** Vloží prvek za aktivní prvek seznamu L.
     ** Pokud nebyl seznam L aktivní, nic se neděje.
     ** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
     ** volá funkci DLError().
     **/
    
    /*
     * Zkontrolujeme, že máme aktivní prvek.
     * Alokujeme prostor pro nový prvek, pokud se alokace nepovedla, zavoláme funkci Error().
     * Nově vzniklému prvku nastavíme obdržená data z parametru funkce.
     * Dále mu nastavíme ukazatel na prvek, jenž následuje za aktivním prvekem
     * a na aktivní prvek.
     * Nastavíme ukaztel aktivního prvku na prvek item.
     **/
    
    if(L->Act != NULL){
        
        tDLElemPtr item = NULL;
        
        item =  malloc(sizeof(struct tDLElem));
        
        if(item == NULL){
            DLError();
        }else{
            item->data = val;
            item->rptr = L->Act->rptr;
            item->lptr = L->Act;
            if(item->rptr == NULL){
                L->Last = item;
            }else{
                L->Act->rptr->lptr = item;
            }
            L->Act->rptr = item;
        }
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreInsert (tDLList *L, int val) {
    /*
     ** Vloží prvek před aktivní prvek seznamu L.
     ** Pokud nebyl seznam L aktivní, nic se neděje.
     ** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
     ** volá funkci DLError().
     **/
    
    /*
     * Zkontrolujeme, že máme aktivní prvek.
     * Alokujeme prostor pro nový prvek, pokud se alokace nepovedla, zavoláme funkci Error().
     * Nově vzniklému prvku nastavíme obdržená data z parametru funkce.
     * Dále mu nastavíme ukazatel na prvek, jenž předchází aktivnímu prveku
     * a na aktivní prvek.
     * Nastavíme ukaztel (doleva) aktivního prvku na prvek item.
     **/
    
    if(L->Act != NULL){
        
        tDLElemPtr item = NULL;
        
        item =  malloc(sizeof(struct tDLElem));
        
        if(item == NULL){
            DLError();
        }else{
            item->data = val;
            item->lptr = L->Act->lptr;
            item->rptr = L->Act;
            if(item->lptr == NULL){
                L->First = item;
            }else{
                L->Act->lptr->rptr = item;
            }
            L->Act->lptr = item;
        }
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopy (tDLList *L, int *val) {
    /*
     ** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
     ** Pokud seznam L není aktivní, volá funkci DLError ().
     **/
    
    /*
     * Zkontroluje, zdali je aktivní prvek, pokud ne, volá funkci Error().
     * Nastaví do proměnné *val, obdržené v parametru, hodnotu aktivního prvku.
     **/
    
    if(L->Act != NULL){
        *val = L->Act->data;
    }else{
        DLError();
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLActualize (tDLList *L, int val) {
    /*
     ** Přepíše obsah aktivního prvku seznamu L.
     ** Pokud seznam L není aktivní, nedělá nic.
     **/
    
    /*
     * Zkontroluji zda-li je seznam aktivní, pokud ano, změním aktivnímu prvku hodnotu.
     **/
    
    if(L->Act != NULL){
        L->Act->data = val;
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLSucc (tDLList *L) {
    /*
     ** Posune aktivitu na následující prvek seznamu L.
     ** Není-li seznam aktivní, nedělá nic.
     ** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
     **/
    
    /*
     * Zkontroluji zda-li je seznam aktivní, pokud ano, posunu aktivitu prvku na následující.
     **/
    
    if(L->Act != NULL){
        L->Act = L->Act->rptr;
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}


void DLPred (tDLList *L) {
    /*
     ** Posune aktivitu na předchozí prvek seznamu L.
     ** Není-li seznam aktivní, nedělá nic.
     ** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
     **/
    
    /*
     * Zkontroluji zda-li je seznam aktivní, pokud ano, posunu aktivitu prvku na předchozí.
     **/
    
    if(L->Act != NULL){
        L->Act = L->Act->lptr;
    }
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int DLActive (tDLList *L) {
    /*
     ** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
     ** Funkci je vhodné implementovat jedním příkazem return.
     **/
    
    return L->Act != NULL;
    
    //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

/* Konec c206.c*/
