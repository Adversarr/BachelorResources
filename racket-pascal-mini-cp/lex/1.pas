function max(num1, num2: integer): integer;

var
   (* local variable declaration *)
   result: integer;

begin
   if (num1 > num2) then
      result := num1
   
   else
      result := num2;
   max := result;
end;

var
   a: array [0..3, 0..3] of integer;
   i, j : integer;

begin
   for i:= 0 to 3 do
      for j:= 0 to 3 do
         a[i,j]:= i * j;
    a := 'Good Staff.'
end;