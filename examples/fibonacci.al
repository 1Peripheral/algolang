#!/usr/bin/algol

n = 1

a = 0
b = 1
c = 0
i = 2

while n <= 5 repeat
   while i <= n repeat
      c = a + b 
      a = b
      b = c 
      i = i + 1
   end
   write b
   n = n + 1
end

