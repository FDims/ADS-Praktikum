#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <iostream>
#include <string>

 template <typename Tf> class List
{
    /*
    Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse
    List kann ein Stapel oder Warteschlange realisiert werden.
    */
private:
    struct form
    {
        std::string start    = "<< ";
        std::string zwischen = ", ";
        std::string ende     = " >>\n";
    } list_form;
    Node<Tf>* head_tail; // Zeiger auf Kopf- und End-Element -> next der 1. Knoten;
                     // -> prev der letzte Knoten
    int  list_size;  // Länge der Kette
    bool temp; // normalerweise false; ist true, wenn es sich um eine temor�re
               // Liste handelt die innerhalb der überladenen Operatoren
               // angelegt wird
public:
    List();
    List(const List<Tf>& _List); // Kopie Konstruktor
    ~List();
    void insertFront(Tf value);     // Einfügen eines Knotens am Anfang
    void insertFront(List<Tf>& _List); // Einfügen einer vorhandenen Liste am Anfang
    void insertBack(Tf value);      // Einfügen eines Knotesn am Ende
    void insertBack(List<Tf>& _List);  // Einfügen einer vorhandenen Liste am Ende
    bool getFront(Tf& value);       // Entnehmen eines Knoten am Anfang
    bool getBack(Tf& value);        // Entnehmen eines Knoten am Ende
    bool del(Tf value);             // löschen eines Knotens [key]
    bool search(Tf value);          // Suchen eines Knoten
    bool swap(Tf value1, Tf value2); // Knoten in der Liste vertauschen
    int  size(void);               // Größe der Lise (Anzahl der Knoten)
    bool test(void);               // Überprüfen der Zeigerstruktur der Liste
    void format(const std::string& start,
                const std::string& zwischen,
                const std::string& ende);
    // Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
    // start: stirng vor der Ausgabe der Liste
    // zwischen: string zwischen Listenknoten
    // ende: string am Ende der Liste
    List<Tf>& operator=(const List<Tf>& _List); // Zuweisungsoperator definieren
    List<Tf>&
    operator+(const List<Tf>& List_Append); // Listen zusammenführen zu einer Liste
    template <typename Tf>
    friend std::ostream & operator<<(std::ostream& stream,
        const List<Tf> &   Liste); // Ausgabeoperator überladen
    friend Node<Tf>* get_anker(List<Tf>& l);
    friend Tf   get_AnzahlNodes(List<Tf>& l);
};
#endif

 template <typename Tf>List<Tf>::List()
 {
     /*
         Konstruktor für eine leere Liste
     */
     head_tail = new Node<Tf>;
     list_size = 0;
     temp = false;
     head_tail->next = head_tail;
     head_tail->prev = head_tail;
 }

 //gegeben
 template <typename Tf>List<Tf>::List(const List& _List)
 {
     /*
         Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
         in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
         sollen.
     */
     list_form = _List.list_form;
     head_tail = new Node<Tf>;
     list_size = 0;
     temp = _List.temp;
     head_tail->next = head_tail;
     head_tail->prev = head_tail;
     Node<Tf>* tmp_node;
     tmp_node = _List.head_tail->next;
     while (tmp_node != _List.head_tail)
     {
         head_tail->prev =
             new Node<Tf>(tmp_node->value, head_tail->prev->next, head_tail->prev);
         head_tail->prev->prev->next = head_tail->prev;
         list_size++;
         tmp_node = tmp_node->next;
     }
     /*
         Ist die übergebene Liste eine temporäre Liste? -> aus Operator +
     */
     if (_List.temp)
         delete& _List;
 }

 template <typename Tf>List<Tf>::~List()
 {
     //ToDo
 /*
     Dekonstruktor
     Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.
 */
     Node<Tf>* ptr = head_tail; //hils/copypointer

     if (ptr->next = head_tail) { //leere Liste
         delete head_tail;//direkt delete
     }
     else {
         ptr = ptr->next;//auf die naechste Knote gehen 
         ptr->prev->next = head_tail; //next-Pointer von Head_Tail direkt nach der selbst zeigen, damin kein Fehler beim delete der 1. Knote

         while (ptr->next != head_tail) {
             ptr = ptr->next;//auf weitere Knote gehen
             delete ptr->prev;//Prev-knote loeschen
             ptr->prev = head_tail;//Prev-Pointer zu dem Head_Tail verbinden/zeigen
         }
         delete head_tail;//delete Head_Tail
         list_size = 0;//Size reset
     }
 }

 template <typename Tf> void List<Tf>::insertFront(Tf value)
 {
     //ToDo
 /*
     Einfuegen eines neuen Knotens am Anfang der Liste
     Einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
 */
     Node<Tf>* eintrag = new Node<Tf>(value, head_tail->next, head_tail);//neue Knote erzeugen
     head_tail->next->prev = eintrag;//die erste Knote auf neue Knote zeigen
     head_tail->next = eintrag;//Head_tail auf neue Knote zeigen
     list_size++;//Size Aktualisieren
 }

 template <typename Tf>void List<Tf>::insertFront(List& _List)
 {
     //ToDo
 /*
     Einfuegen der Liste _List am Anfang an einer vorhandenen Liste
     Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
     Die einzufuegende Liste _List ist anschließend leer.
     Es darf keine Schleife und kein new benutzt werden.
 */

 /*
     gleiches Objekt -> keine Aktion
 */
     if (head_tail == _List.head_tail) return;

     /*
         Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
         Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
         Die Liste _List ist danach leer, aber vorhanden.
     */

     this->head_tail->next->prev = _List.head_tail->prev;//1. Knote this.List auf letzte Knote _List zeigen
     _List.head_tail->prev->next = this->head_tail->next;//letzte Knote _List auf 1. Knote this.List zeigen
     this->head_tail->next = _List.head_tail->next;//this.Head_Tail auf 1. Knote _List zeigen
     _List.head_tail->next->prev = this->head_tail;//1. Knote _List auf this.Head_Tail zeigen
     this->list_size = this->list_size + _List.list_size;//Size addieren

 }

 template <typename Tf> void List<Tf>::insertBack(Tf value)
 {
     //ToDo
 /*
     Einfuegen eines neuen Knotens am Ende der Liste
     Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
 */
     Node<Tf>* eintrag = new Node<Tf>(value, head_tail, head_tail->prev);
     this->head_tail->prev->next = eintrag;
     this->head_tail->prev = eintrag;
     this->list_size++;
 }

 template <typename Tf> void List<Tf>::insertBack(List& _List)
 {
     //ToDo
 /*
     Einfuegen der Liste _List am Ende einer vorhandenen Liste
     Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
     Die einzufuegende Liste _List ist anschließend leer.
     Es darf keine Schleife und kein new benutzt werden.
 */

 /*
     gleiches Objekt -> keine Aktion
 */
     if (head_tail == _List.head_tail) return;

     /*
         Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
         Diese Knoten (koplette Kette) werden an den Ende der Liste (this) übertragen ohne sie zu kopieren!
         Die Liste _List ist danach leer, aber vorhanden.
     */

     this->head_tail->prev->next = _List.head_tail->next;
     _List.head_tail->next->prev = this->head_tail->prev;
     _List.head_tail->prev->next = this->head_tail;
     this->head_tail->prev = _List.head_tail->prev;
     this->list_size = this->list_size + _List.list_size;
 }

 template <typename Tf> bool List<Tf>::getFront(Tf& value)
 {
     //ToDo
 /*
     entnehmen des Knotens am Anfang der Liste
     der Wert wird als Parameter zurueckgegeben
     der Knoten wird entnommen
     im Fehlerfall wird false zurückgegeben
 */

 /*
     gleiches Objekt -> keine Aktion
 */
     if (!list_size) return false;	//Liste Leer
     Node<Tf>* ptr = this->head_tail->next;//Copy-/Hilfspointer
     value = ptr->value;//wert der Value zuweisen
     this->head_tail->next = ptr->next;  //Head_Tail und 2.Knoten verbinden
     ptr->next->prev = this->head_tail;  // ''
     delete ptr; //delete entnommene Pounter;
     this->list_size--;//Size aktualisieren
     return true;
     /*
         Der Wert des vorderen Knotens wird rückgegeben und der Knoten gelöscht.
         Die Methode del(value) darf nicht zum löschen benutzt werden.
     */

 }

 template <typename Tf> bool List<Tf>::getBack(Tf& value)
 {
     //ToDo
 /*
     entnehmen des Knotens am Ende der Liste
     der Wert wird als Parameter zurueckgegeben
     der Knoten wird entnommen
     im Fehlerfall wird false zurückgegeben
 */

 /*
     gleiches Objekt -> keine Aktion
 */
     if (!list_size) return false;
     Node<Tf>* ptr = this->head_tail->prev;
     value = ptr->value;
     this->head_tail->prev = ptr->prev;
     ptr->prev->next = this->head_tail;
     delete ptr;
     this->list_size--;
     return true;
 }
 /*
     Der Wert des letzten Knotens wird rückgegeben und der Knoten gelöscht.
     Die Methode del(value) darf nicht zum löschen benutzt werden.
 */


 template <typename Tf> bool List<Tf>::del(Tf value)
 {
     //ToDo
 /*
     Loeschen eines gegebenen Knotens
     im Fehlerfall wird false zurückgegeben
 */

 /*
     gleiches Objekt -> keine Aktion
 */
     if (!list_size) return false;

     /*
         Löschen des Knotens mit dem Wert value
     */

     Node<Tf>* ptr = this->head_tail->next;
     while (ptr->value != value && ptr != this->head_tail)ptr = ptr->next;//suche nach der value
     if (ptr == this->head_tail)return false;// Value nicht gefunden
     else {
         ptr->prev->next = ptr->next;//2 Knoten ( die next und prev) verbinden
         ptr->next->prev = ptr->prev;// ''
         delete ptr;
         this->list_size--;
         return true;
     }

 }

 template <typename Tf> bool List<Tf>::search(Tf value)
 {
     //ToDo
 /*
     suchen eines Knotens
     nicht gefunden -> Rueckgabe: false
 */

 /*
     leere Liste -> keine Aktion
 */
     if (!list_size) return false;

     /*
         suchen ob ein Knoten mit dem Wert value existiert.
     */
     else {
         Node<Tf>* ptr = this->head_tail;
         while (ptr->value != value && ptr->next != this->head_tail)ptr = ptr->next;
         if (ptr->value == value)return true;
         else return false;
     }

 }

 template <typename Tf> bool List<Tf>::swap(Tf value1, Tf value2)
 {
     //ToDo
 /*
     Vertauschen von zwei Knoten
     Dabei werden die Zeiger der Knoten und deren Nachbarn veraendert.
     im Fehlerfall wird false zurueckgegeben
 */

 /*
     Wenn Liste Leer oder weniger als 2 Knoten besitzt -> Keine Aktion
 */
     if (list_size < 2) return false;

     /*
         Vertauschen von zwei Knoten mit dem Wert value1 und dem Wert value2.
         Es duerfen nicht nur einfach die Werte in den Knoten getauscht werden!
         Die Knoten sind in der Kette umzuhaengen.
     */
     Node<Tf>* ptr1 = this->head_tail->next, * ptr2, * tmp;//hilfspointer
     while (ptr1->value != value1 && ptr1->value != value2 && ptr1 != this->head_tail)ptr1 = ptr1->next;//suche nach eine der Value, als ptr1 deklarieren
     if (ptr1 == head_tail)return false;//wenn die Value nicht existiert
     else {
         ptr2 = ptr1->next;//auf die naechste Knote gehen
         if (ptr1->next->value == value2 || ptr1->next->value == value1) {//wenn die beide Values nebeneinander liegen.
             ptr2 = ptr1->next;
             ptr1->next = ptr2->next;
             ptr2->next->prev = ptr1;
             ptr2->next = ptr1;
             ptr2->prev = ptr1->prev;
             ptr1->prev->next = ptr2;
             ptr1->prev = ptr2;
             return true;
         }
         else {
             while (ptr2->value != value2 && ptr2->value != value1 && ptr2 != this->head_tail)ptr2 = ptr2->next;//suche nach 2. Value, die nicht nebeneinander liegen.
             if (ptr2 == this->head_tail)return false;//wenn die 2. Value nicht gefunden
             else {
                 tmp = ptr1->next;
                 ptr1->next = ptr2->next;
                 ptr2->next->prev = ptr1;
                 ptr2->next = tmp;
                 tmp->prev = ptr2;
                 tmp = ptr1->prev;
                 ptr1->prev = ptr2->prev;
                 ptr2->prev->next = ptr1;
                 ptr2->prev = tmp;
                 tmp->next = ptr2;

                 return true;
             }
         }

     }

 }

 template <typename Tf> int List<Tf>::size(void)
 {
     //ToDo
 /*
     Rueckgabe der Anzahl der Knoten in der Liste mit O(1)
     d.h. die Liste darf NICHT traversiert werden um die Größe zu bestimmen.

     Anzahl der Knoten in der Liste zurückgeben.
     Hier richtiges Ergebnis zurückgeben
 */

     return this->list_size;
 }

 template <typename Tf> bool List<Tf>::test(void)
 {
     // Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und
     // zurück Es werden dabei die Anzahl der Knoten gezahlt. Stimmt die Anzahl
     // der Knoten überein liefert die Methode true
     Node<Tf>* tmp = head_tail->next;
     int   i_next = 0, i_prev = 0;
     while (tmp != head_tail)
     {
         tmp = tmp->next;
         if (i_next > list_size)
             return false;
         i_next++;
     }
     if (i_next != list_size)
         return false;
     tmp = head_tail->prev;
     while (tmp != head_tail)
     {
         tmp = tmp->prev;
         if (i_prev > list_size)
             return false;
         i_prev++;
     }
     return i_prev == i_next;
 }

 //gegeben
 template <typename Tf> List<Tf>& List<Tf>::operator=(const List& _List)
 {   //gegeben
     // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
     // sollen. Kopiert wird in das Objekt "this"
     if (this == &_List)
         return *this; //  !! keine Aktion notwendig
     list_form = _List.list_form;
     Node<Tf>* tmp_node;
     if (list_size)
     {
         Node<Tf>* tmp_del;
         tmp_node = head_tail->next;
         while (tmp_node !=
             head_tail) // Alle eventuell vorhandenen Knoten in this löschen
         {
             tmp_del = tmp_node;
             tmp_node = tmp_node->next;
             delete tmp_del;
         }
         list_size = 0;
         head_tail->next = head_tail;
         head_tail->prev = head_tail;
     }
     tmp_node = _List.head_tail->next; // Die Listen-Knotenwerte werden kopiert
     while (tmp_node != _List.head_tail)
     {
         insertBack(tmp_node->value);
         tmp_node = tmp_node->next;
     }
     if (_List.temp)
         delete& _List; // ist die übergebene Liste eine temporäre Liste? -> aus
                        // Operator +
     return *this;
 }

 //gegeben
 template <typename Tf> List<Tf>& List<Tf>::operator+(const List& List_Append)
 {   //gegeben
     // Die Methode +
     // Es werden zwei Listen aneinander gehangen.
     // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
     // Ergebnisliste.
     Node<Tf>* tmp_node;
     List* tmp;
     if (temp)
     { // this ist eine temporäre Liste und kann verändert werden
         tmp = this;
     }
     else
     {
         tmp =
             new List(*this); // this ist keine temporäre Liste -> Kopie erzeugen
         tmp->temp = true;    // Merker setzten, dass es sich um eine temporäre
                              // Liste handelt
     }
     if (List_Append.list_size)
     { // anhängen der übergebenen Liste an tmp
         tmp_node = List_Append.head_tail->next;
         while (tmp_node != List_Append.head_tail)
         {
             tmp->insertBack(tmp_node->value);
             tmp_node = tmp_node->next;
         }
     }
     if (List_Append.temp)
         delete& List_Append; // wurde eine temporäre Liste übergeben, dann wird
                              // diese gelöscht
     return *tmp;
 }

 //gegeben
 template <typename Tf> void List<Tf>::format(const std::string& start,
     const std::string& zwischen,
     const std::string& ende)
 {
     // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
     // das Format wird für den überladenen Operator << verwendet
     list_form.start = start;
     list_form.zwischen = zwischen;
     list_form.ende = ende;
 }

 template <typename Tf> std::ostream& operator<<(std::ostream& stream, const List <Tf>& Liste)
 {
     // Ausgabe der Liste mit cout
     stream << Liste.list_form.start;
     for (Node<Tf>* tmp = Liste.head_tail->next; tmp != Liste.head_tail;
         tmp = tmp->next)
         stream << tmp->value
         << (tmp->next == Liste.head_tail ? Liste.list_form.ende :
             Liste.list_form.zwischen);
     if (Liste.temp)
         delete& Liste; // wurde eine temporäre Liste übergeben, dann wird diese
                        // gelöscht
     return stream;
 }


template class List<int>;
template class List<std::string>;
