DESIRED UNION STORE ON 
DESIRED.Category = STORE.Category AND 
DESIRED.Product  = STORE.Product  AND  
(
	DESIRED.Units <= STORE.Units AND  
	NOT (DESIRED.Price < STORE.Price) OR 
	DESIRED.Price >= STORE.Price * 2
)
