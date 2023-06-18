/* Arina Lazarenko */

set Areas;
set Shifts;

param min_cars{Areas, Shifts} >= 0;
param max_cars{Areas, Shifts} >= 0;
param needed_cars_for_area{Areas} >= 0;
param needed_cars_for_shift{Shifts} >= 0;

var cars{Areas, Shifts} >= 0; 

/*ograniczenia*/

/*ograniczenie min ilości radiowozow dla dzielnic*/
s.t. cars_min_areas{c in Areas}: sum{a in Shifts} cars[c,a] >= needed_cars_for_area[c]; 

/*ograniczenie min ilości radiowozow dla zmian*/
s.t. cars_min_shifts{c in Shifts}: sum{a in Areas} cars[a,c] >= needed_cars_for_shift[c]; 

/* minimalne ograniczenie */
s.t. final_cars_for_shifts{c in Shifts, a in Areas}: cars[a,c] >= min_cars[a,c];

/* minimalne ograniczenie */
s.t. final_cars_for_areas{c in Shifts, a in Areas}: cars[a,c] >= min_cars[a,c];

/* maksymalne ograniczenie */
s.t. max_final_cars_for_shifts{c in Shifts, a in Areas}: cars[a,c] <= max_cars[a,c];


minimize final_cost : sum{a in Areas, s in Shifts} cars[a,s];


solve;

display '-------Min liczba radiowozow dla zmian oraz dzielnic--------';
display {a in Areas, c in Shifts} final_cars_for_shifts[c, a];
display '-------Experiment--------';
display final_cost;


end;