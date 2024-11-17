
(*Esercizi proposti
Definire catAll : string list -> string tale che catAll l restituisce la stringa ottenuta concatenando tutte le stringhe di l secondo l'ordine determinato dalla lista. Utilizzare un parametro di accumulazione per ottenere ricorsione di coda.

Esempio:
*)

let catAll (s:string list) :string  =
    let rec loop (acc:string) (s:string list) =
        match s with 
        | lo::t1 -> loop (acc + lo ) t1 
        | [] -> acc
    loop "" s

assert (catAll ("This" :: " is " :: "awesome!"::[]) = "This is awesome!")

(*Definire catAllFold : string list -> string, equivalente a catAll, ma ottenuta come specializzazione di List.fold.*)
let catAll2 (s:string list) =
    List.fold (fun (acc:string) (k:string) -> acc+k) "" s

assert (catAll2 ("This" :: " is " :: "awesome!"::[]) = "This is awesome!")
(*
Definire zip : 'a list -> 'b list -> ('a * 'b) list tale che

zip (a_0::...::a_n::[]) (b_0::...::b_n::[]) = (a_0,b_0)::...::(a_n,b_n)::[]
La funzione solleva l'eccezione Failure "different length" se le due liste hanno lunghezza diversa. Utilizzare un parametro di accumulazione per ottenere ricorsione di coda.
*)

let failwith msg = 
    raise (Failure "different length")

let rec zip a b  =
    match a,b with
    |[],[] -> []
    |[],_ -> failwith "different length"
    |_,[] -> failwith "different length"
    |p1::t1,p2::t2 -> (p1,p2) :: zip t1 t2 


assert (zip [] [] = [])
 
assert (zip (1 :: 2 :: 3 :: []) ("a" :: "b" :: "c" :: []) = (1, "a") :: (2, "b") :: (3, "c") :: [])
 
assert
     ((try
         zip (1 :: 2 :: []) ("a" :: "b" :: "c" :: [])
       with
       | Failure "different length" -> []) = [])

(*
Definire minEl : 'a list -> 'a option tale che minEl restituisce None se la lista è vuota, altrimenti Some m, con m il minimo della lista; usare la funzione predefinita min : 'a -> 'a -> 'a per semplificare il codice. Utilizzare un parametro di accumulazione per ottenere ricorsione di coda.

Esempi:
*)
let minEl (a:'a list) : 'a option =
    if a=[] then None else Some (List.min a) 

assert (minEl [] = None)

assert (minEl (3 :: 4 :: 6 :: -1 :: []) = Some -1)

assert (minEl ("orange" :: "apple" :: "banana" :: []) = Some "apple")

(*Definire minElFold : 'a list -> 'a option, equivalente a minEl, ma ottenuta usando List.fold.*)

let minElFold (a:'a list) =
    if a=[] then None else
    let b =List.fold (fun acc k -> if k < acc then k else acc) (List.head a) (List.tail a)
    Some b 

assert (minElFold [] = None)

assert (minElFold (3 :: 4 :: 6 :: -1 :: []) = Some -1)

assert (minElFold ("orange" :: "apple" :: "banana" :: []) = Some "apple")

type Direction =
    |North 
    |South
    |East 
    |West 

let versor c  =
    match c with
    | North -> (0,1)
    | East -> (1,0)
    | South -> (0,-1)
    | West -> (-1,0)

assert (versor North = (0,1))
assert (versor East = (1,0))
assert (versor South = (0,-1))
assert (versor West = (-1,0))

type action =
    | Turn of Direction
    | Step of int

(*
Definire move : direction * (int * int) -> action -> direction * (int * int) che, presa una coppia, che definisce la direzione e le coordinate cartesiane iniziali,
 e presa un'azione, restituisce la coppia costituita dalla direzione e coordinate cartesiane finali ottenute compiendo l'azione.
*)

let move ((a:Direction), ((b:int),(c:int))) (d:action) =
    match d with
    |Turn South -> (South,(b,c))
    |Turn North -> (North,(b,c))
    |Turn East -> (East,(b,c))
    |Turn West -> (West,(b,c))
    |Step k-> if a=South then (a,(b,c-k)) elif a=North then (a,(b,c+k)) elif a=East then (a,(b+k,c)) else (a,(b-k,c))


assert (move (North, (0, 0)) (Turn South) = (South, (0, 0)))
assert (move (North, (0, 0)) (Step 2) = (North, (0, 2)))
assert (move (North, (0, 0)) (Step -1) = (North, (0, -1)))
assert (move (North, (0, 0)) (Step 0) = (North, (0, 0)))


(*Usando List.fold, definire la funzione doAll : direction * (int * int) -> action list -> direction * (int * int) che, 
presa una coppia, che definisce la direzione e le coordinate cartesiane iniziali, e presa una lista di azioni, 
restituisce la coppia costituita dalla direzione e coordinate cartesiane finali ottenute compiendo tutte le azioni della lista nell'ordine.

Esempio:*)
let doAll   ((a:Direction), ((b:int),(c:int))) (d:action list) = 
    List.fold (fun ((a:Direction), ((b:int),(c:int))) (e:action) -> move (a,(b,c)) e ) (a,(b,c)) d

assert
(doAll
    (North, (0, 0))
    (Step 2
     :: Turn East
        :: Step 2
           :: Step -1 :: Turn South :: Step 3 :: Step 0 :: []) = (South, (1, -1)))


(*(Difficile) Dichiarare il tipo discriminated union polimorfo 'a tree degli alberi con nodi etichettati con valori di tipo 'a e numero arbitrario di figli.

Definire la funzione postOrder : 'a tree -> 'a list che restituisce la lista delle etichette dell'albero ottenuta tramite visita post-order 
(prima i nodi figlio da sinistra a destra, poi il nodo radice).

Suggerimento: usare un parametro di accumulazione e List.fold. La definizione ricorsiva è di coda?

Esempio:
*)

(*
Da fare
*)

assert
   (Node(
      1,
      (Node(2, [])
         :: Node(3, [])
            :: Node(4, (Node(5, []) :: Node(6, []) :: [])) :: [])
   ))
   |> postOrder = (2 :: 3 :: 5 :: 6 :: 4 :: 1 :: [])    
