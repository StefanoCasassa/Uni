//Es.1
(*
mulAll : int list -> int

mulAll ls restituisce il prodotto di tutti i numeri interi contenuti nella lista ls.
*)
let rec mulAll ls = 
    match ls with
    | po::lo -> po * mulAll lo
    | [] -> 1

assert (mulAll (2 :: 4 :: 3 :: []) = 24)

//Es.2
(*
isIn : 'a -> 'a list -> bool

isIn el ls restituisce true se e solo se el è un elemento della lista ls.
*)
let rec isIn el ls = 
    match ls with
    | po::lo -> if po=el then true else isIn el lo
    | [] -> false

assert isIn 3 (2 :: 4 :: 3 :: [])
assert not (isIn 5 (2 :: 4 :: 3 :: []))

//Es.3
(*insert : 'a -> 'a list -> 'a list

insert el ls restituisce la lista ottenuta aggiungendo el in fondo alla lista ls se el non appartiene
già a ls; restituisce ls altrimenti.

Esempio:*)

let rec insert  el ls =
    match ls with 
    | po::lo -> if po=el then ls else  po::(insert el lo)
    | [] -> ls@[el]

assert (insert 0 (2 :: 4 :: 3 :: []) = 2 :: 4 :: 3 :: 0 :: [])
assert (insert 3 (2 :: 4 :: 3 :: []) = 2 :: 4 :: 3 :: [])
//Es.4
(*insert2 : 'a -> 'a list -> 'a list

come l'esercizio precedente, ma provare a usare una funzione ricorsiva ausiliaria per evitare di passare
a ogni chiamata ricorsiva l'elemento da inserire.
*)


let insert2 (el: 'a) (ls: 'a list)=
    let rec aux (ls: 'a list) : 'a list= 
        match ls with
        | hd::tl -> if hd = el then ls else hd::aux tl
        | [] -> [el]
    aux ls
    
    


assert (insert2 0 (2 :: 4 :: 3 :: []) = 2 :: 4 :: 3 :: 0 :: [])
assert (insert2 3 (2 :: 4 :: 3 :: []) = 2 :: 4 :: 3 :: [])
//Es.5
(*
`odd : 'a list -> 'a list` 
    
`odd ls` restituisce la lista ottenuta da `ls` tenendo solo gli elementi di indice dispari, considerando
che gli indici iniziano da 0.
*)

let odd ls =
    let rec aux index ls =
        match ls with
        | [] -> []
        | hd :: tl -> if index % 2 <> 0 then hd :: aux (index + 1) tl else aux (index + 1) tl
    aux 0 ls


assert (odd (7 :: 3 :: 4 :: 1 :: 2 :: 5 :: []) = 3 :: 1 :: 5 :: [])

//Es.6
(*
`ordInsert : 'a -> 'a list -> 'a list` 

assumendo che `ls` sia già ordinata in modo crescente e senza ripetizioni, `ordInsert el ls` restituisce
la lista ordinata in modo crescente e senza ripetizioni ottenuta aggiungendo `el` a `ls`.
*)
let rec ordInsert el ls =
    match ls with
    | [] -> ls@[el]
    | hd::tl -> if hd >= el then (if hd = el then ls else el::hd::tl) else hd :: (ordInsert el tl)

assert (ordInsert 0 (1 :: 2 :: 4 :: 5 :: []) = 0 :: 1 :: 2 :: 4 :: 5 :: [])
assert (ordInsert 3 (1 :: 2 :: 4 :: 5 :: []) = 1 :: 2 :: 3 :: 4 :: 5 :: [])
assert (ordInsert 7 (1 :: 2 :: 4 :: 5 :: []) = 1 :: 2 :: 4 :: 5 :: 7 :: [])
assert (ordInsert 2 (1 :: 2 :: 4 :: 5 :: []) = 1 :: 2 :: 4 :: 5 :: [])

//Es.7
(*
`ordInsert2 : 'a -> 'a list -> 'a list` 
come l'esercizio precedente, ma provare a usare una funzione ricorsiva ausiliaria per evitare di passare 
a ogni chiamata ricorsiva l'elemento da inserire.
*)
let  ordInsert2 el ls =
    let rec aux1 ls=
        match ls with
        | [] -> ls@[el]
        | hd::tl -> if hd >= el then (if hd = el then ls else el::hd::tl) else hd :: (aux1 tl)
    aux1 ls

assert (ordInsert2 0 (1 :: 2 :: 4 :: 5 :: []) = 0 :: 1 :: 2 :: 4 :: 5 :: [])
assert (ordInsert2 3 (1 :: 2 :: 4 :: 5 :: []) = 1 :: 2 :: 3 :: 4 :: 5 :: [])
assert (ordInsert2 7 (1 :: 2 :: 4 :: 5 :: []) = 1 :: 2 :: 4 :: 5 :: 7 :: [])
assert (ordInsert2 2 (1 :: 2 :: 4 :: 5 :: []) = 1 :: 2 :: 4 :: 5 :: [])
//Es.8
(*
`merge : 'a list * 'a list -> 'a list` 
    
assumendo che `ls1` e `ls2` siano già ordinate in modo crescente e senza ripetizioni, `merge (ls1,ls2)` 
restituisce la lista ordinata in modo crescente e senza ripetizioni ottenuta fondendo assieme `ls1` e `ls2`. 

    
*Nota*: F# permette di abbreviare le due keyword `else` `if` con la singola `elif`. 
*)

let rec merge (ls1,ls2) =
    match ls1,ls2 with 
    | [],[] -> []
    | [],_ -> ls2
    | _,[] -> ls1
    | ab::lu,bb::ly -> if ab<bb then ab::merge (lu,ls2) else bb::merge (ls1,ly)


assert (merge ((1 :: 3 :: 5 :: []), (2 :: 4 :: 6 :: [])) = 1 :: 2 :: 3 :: 4 :: 5 :: 6 :: [])
assert (merge ((1 :: 2 :: 3 :: []), (4 :: 5 :: [])) = 1 :: 2 :: 3 :: 4 :: 5 :: [])
assert (merge ((3 :: []), (1 :: 2 :: 4 :: 5 :: [])) = 1 :: 2 :: 3 :: 4 :: 5 :: [])
//Es.9
(*
`curriedMerge : 'a list -> 'a list -> 'a list` a
    
definire `curriedMerge`, la versione curried di `merge`, direttamente senza usare `merge`.
*)

let rec curriedMerge ls1 ls2 =
    match ls1,ls2 with 
    | [],[] -> []
    | [],_ -> ls2
    | _,[] -> ls1
    | ab::lu,bb::ly -> if ab<bb then ab::curriedMerge lu ls2 else bb::curriedMerge ls1 ly


assert (curriedMerge (1 :: 3 :: 5 :: []) (2 :: 4 :: 6 :: []) = 1 :: 2 :: 3 :: 4 :: 5 :: 6 :: [])
assert (curriedMerge (1 :: 2 :: 3 :: []) (4 :: 5 :: []) = 1 :: 2 :: 3 :: 4 :: 5 :: [])
assert (curriedMerge (3 :: []) (1 :: 2 :: 4 :: 5 :: []) = 1 :: 2 :: 3 :: 4 :: 5 :: [])